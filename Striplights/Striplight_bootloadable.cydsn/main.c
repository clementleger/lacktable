
#include <project.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

extern const uint32 StripLights_CLUT[];

/* Prototype the ISR handler */
CY_ISR_PROTO( ResetISR_Handler );
 
/* Implementation of the ISR handler */
CY_ISR( ResetISR_Handler )
{
    PC_Uart_Stop();
    Bootloadable_Load();        /* Force a bootloader restart */
}
   
static void
set_pixel(unsigned int i, unsigned int j, uint32_t color) {
        
}

static void
clear_pixels()
{
	StripLights_MemClear(StripLights_BLACK);
	StripLights_Trigger(1); 
}

static int rot1_pos, rot2_pos;

static int get_rot1_dir()
{
	int ret;
	int cur = Rot1_ReadCounter();

	if (cur == rot1_pos) {
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

	if (cur == rot2_pos) {
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
	int sw_status = 0;
	int drawing = 0;
	int draw_pixel = 1;
	int reg_status;
	uint32_t draw_color;

	do {
		x += get_rot1_dir;
		filter_coor(&x);
		y += get_rot2_dir;
		filter_coor(&y);

		/* Draw the cursor */
		if (old_x != x || old_y != y) {
			draw_pixel = 1;
		}

		if (draw_pixel) {
			/* Draw or clear old pixel depending on mode*/
			draw_color = drawing ? StripLights_RED : StripLights_BLACK;
			set_pixel(old_x, old_y, draw_color);
			/* Draw new pixel */
			set_pixel(x, y, StripLights_YELLOW);
			draw_pixel = 0;
		}

		reg_status = RotSWReg_Read();
		/* Draw mode on/off */
		if (reg_status & 0x1) {
			drawing = !drawing;
		}

		/* Clear */
		if (reg_status & 0x2) {
			clear_pixels();
			x = 0;
			old_x = 0;
			y = 0;
			old_y = 0;
		}

		/* Wait led update */
		while( StripLights_Ready() == 0);
	} while(reg_status != 0x3);
}

int main()
{
	int i = 0, j;
	char tmp[512];
	uint8_t reg_status;

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

	// Clear all memory to black
	StripLights_MemClear(StripLights_BLACK);
	// Enable global interrupts, required for StripLights
	CyGlobalIntEnable;
	
	//~ 
	//~ for(;;)
	//~ {
		//~ /* Set LED output to logic HIGH */
		//~ sprintf(tmp, "Counter 1: %ld\r\n", Rot1_ReadCounter());
		//~ PC_Uart_UartPutString(tmp);
		//~ sprintf(tmp, "Counter 1: %ld\r\n", Rot2_ReadCounter());
		//~ PC_Uart_UartPutString(tmp);
		//~ reg_status = RotSWReg_Read();
		//~ sprintf(tmp, "Counter 1: %x\r\n", reg_status);
		//~ PC_Uart_UartPutString(tmp);
		//~ /* Delay of 500 ms */
		//~ CyDelay(100u);
	//~ }
    
	rot1_pos = Rot1_ReadCounter();
	rot2_pos = Rot2_ReadCounter();
	while(1) {
		drawing_mode();
	}
}
