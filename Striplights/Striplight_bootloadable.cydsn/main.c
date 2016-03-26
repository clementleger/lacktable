
#include <project.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

#define LED_HEIGHT      12
#define LED_WIDTH      12

extern const uint32 StripLights_CLUT[];

/* Prototype the ISR handler */
CY_ISR_PROTO( ResetISR_Handler );
 
/* Implementation of the ISR handler */
CY_ISR( ResetISR_Handler )
{
    PC_Uart_Stop();
    Bootloadable_Load();        /* Force a bootloader restart */
}
   
static inline void
myprintf(const char *fmt , ...)
{
	va_list args;
        char buffer[512];

        va_start(args, fmt);
        vsnprintf(buffer, 512, fmt, args);
        va_end(args);

        PC_Uart_UartPutString(buffer);
}


static void
set_pixel(int i, int j, uint32 color)
{
        int row = i / 2;
        int column =  ((i % 2) * LED_HEIGHT) + j;
         
        StripLights_Pixel(column, row, color);
        myprintf("Drawing col %d, row %d, color %x\r\n", column, row, color);
}

static void
clear_pixels()
{
	while(StripLights_Ready() == 0);
	StripLights_MemClear(StripLights_BLACK);
	StripLights_Trigger(1); 
}

static int rot1_pos, rot2_pos;

static int get_rot1_dir()
{
	int ret;
	int cur = Rot1_ReadCounter();

	if (cur == rot1_pos)
		ret = 0;
	else if (cur < rot1_pos)
		ret = -1;
	else
		ret = 1;
	
	rot1_pos = cur;
	return ret;
}

static int get_rot2_dir()
{
	int ret;
	int cur = Rot2_ReadCounter();

	if (cur == rot2_pos)
		ret = 0;
	else if (cur < rot2_pos)
		ret = -1;
	else
		ret = 1;
	
	rot2_pos = cur;
	return ret;
}


static void
filter_coor(int *coor)
{
	if (*coor > 11)
		*coor = 11;
	else if (*coor < 0)
		*coor = 0;
}

static void drawing_mode()
{
	int x = 0, y = 0, old_x = 0, old_y = 0;
	int drawing = 0;
	int draw_pixel = 1;
	uint8_t reg_status;
	uint32 draw_color;

	do {
		x += get_rot1_dir();
		filter_coor(&x);
		y += get_rot2_dir();
		filter_coor(&y);
                
                myprintf("x: %d, y = %d\r\n", x, y);

		/* Draw the cursor */
		if (old_x != x || old_y != y) {
			draw_pixel = 1;
		}

		if (draw_pixel) {
                        /* Wait led update */
                        while(StripLights_Ready() == 0);
                        myprintf("Drawing, mode: %d\r\n", drawing);
			/* Draw or clear old pixel depending on mode*/
			draw_color = drawing ? StripLights_RED : StripLights_BLACK;
			set_pixel(old_x, old_y, draw_color);
			/* Draw new pixel */
			set_pixel(x, y, StripLights_YELLOW);
			StripLights_Trigger(1); 
			draw_pixel = 0;
		}

		reg_status = RotSWReg_Read();
		/* Draw mode on/off */
		if (!(reg_status & 0x1)) {
			drawing = !drawing;
                        myprintf("Change mode\r\n");
		}

		/* Clear */
		if (!(reg_status & 0x2)) {
                        myprintf("Reset\r\n");
			clear_pixels();
			x = 0;
			old_x = 0;
			y = 0;
			old_y = 0;
                        draw_pixel = 1;
                        drawing = 0;
		}

                old_x = x;
                old_y = y;
                CyDelay(100);

	} while(reg_status != 0);
}

int main()
{
	StripLights_Start();
	ESP_Start();
	PC_Uart_Start();

	/* Start the timer - only runs when SW1 is pressed */
	ResetTimer_Start();

	/* Install the ISR handler and make sure none are pending */
	ResetISR_ClearPending();
	ResetISR_StartEx( ResetISR_Handler );

	Rot1_Start();
	Rot1_TriggerCommand(Rot1_MASK, Rot1_CMD_RELOAD);
	Rot2_Start();
	Rot2_TriggerCommand(Rot2_MASK, Rot2_CMD_RELOAD);

	// Set dim level 0 = full power, 4 = lowest power
	StripLights_Dim(0); 

	// Enable global interrupts, required for StripLights
	CyGlobalIntEnable;
        clear_pixels();
    
	rot1_pos = Rot1_ReadCounter();
	rot2_pos = Rot2_ReadCounter();

        
        while(1) {
		drawing_mode();
	}
}
