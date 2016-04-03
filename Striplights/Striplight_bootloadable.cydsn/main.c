
#include <project.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

#include "fonts.h"
#include "color.h"

#define NUMBER_OF_TICKS		 24000

#define LED_HEIGHT	12
#define LED_WIDTH	12

enum disp_mode {
	MODE_DRAW = 0,
	MODE_BLINK,
	MODE_SNAKE,
	MODE_MATRIX,
	MODE_RAINBOW,
	MODE_COUNT,
};

static uint32_t ms_count = 0;

/* Prototype the ISR handler */
CY_ISR_PROTO( ResetISR_Handler );
 
/* Implementation of the ISR handler */
CY_ISR( ResetISR_Handler )
{
    PC_Uart_Stop();
    Bootloadable_Load();        /* Force a bootloader restart */
}

CY_ISR_PROTO(SystickISR_Handler);

CY_ISR(SystickISR_Handler)
{
	ms_count++;
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
}

static void
draw_char(char c, int x, int y, uint32_t color)
{
	int ir = 0, jr = 0, i, j;
	uint8_t *letter = &Font5x7[(c - 32) * 5];

	while(StripLights_Ready() == 0);
	for (i = x; i < LED_WIDTH; i++) {
		for (j = y; j < LED_HEIGHT; j++) {
			if (letter[ir] & (1 << jr)) {
				set_pixel(i, j, color);
			} else {
				set_pixel(i, j, 0x000000);
			}	
			jr++;
			if (jr == FONT_HEIGHT)
				break;
		}
		jr = 0;
		ir++;
		if (ir == FONT_WIDTH)
			break;

	}

	StripLights_Trigger(1); 
}


static void
clear_pixels(uint32_t color)
{
	while(StripLights_Ready() == 0);
	StripLights_MemClear(color);
	StripLights_Trigger(1); 
}

static int rot1_pos, rot2_pos;

static int
get_rot1_dir()
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

static int
get_rot2_dir()
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


#define FILTER_VALUE(_value, _max) \
	if ((_value) > (_max)) \
		(_value) = (_max); \
	else if ((_value) < 0) \
		(_value) = 0;

static void
drawing_mode()
{
	int x = 0, y = 0, old_x = 0, old_y = 0;
	int drawing = 0;
	int draw_pixel = 1;
	uint8_t reg_status;
	uint32 draw_color;

	myprintf("Drawing mode started\n");
	do {
		x += get_rot1_dir();
		FILTER_VALUE(x, LED_WIDTH - 1);
		y += get_rot2_dir();
		FILTER_VALUE(y, LED_HEIGHT - 1);

		/* Draw the cursor */
		if (old_x != x || old_y != y) {
			draw_pixel = 1;
		}

		if (draw_pixel) {
                        /* Wait led update */
                        while(StripLights_Ready() == 0);
			/* Draw or clear old pixel depending on mode*/
			draw_color = drawing ? 0xFF0000 : 0x000000;
			set_pixel(old_x, old_y, draw_color);
			/* Draw new pixel */
			set_pixel(x, y, 0x00FF00);
			StripLights_Trigger(1); 
			draw_pixel = 0;
		}

		reg_status = RotSWReg_Read();
		/* Draw mode on/off */
		if (!(reg_status & 0x1)) {
			drawing = !drawing;
		}

		/* Clear */
		if (!(reg_status & 0x2)) {
			clear_pixels(0x000000 );
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

static void
star_mode()
{
	
}

static void
blink_mode()
{
	
}
 
static void
rainbow_mode()
{
	int sleep_time = 500;
	int increment = 255 / LED_HEIGHT;
	int x, y;
	uint8_t reg_status, starth = 0;
	uint32_t color;
	uint32_t last_ms = 0;

	myprintf("Rainbow mode started\n");
	do {
		sleep_time += (get_rot1_dir() * 10);
		FILTER_VALUE(sleep_time, INT_MAX - 20);

		if ((ms_count - last_ms) > sleep_time) {
			while(StripLights_Ready() == 0);
			color = hsv_to_rgb(starth, 200, 200);
			for (x = 0; x < LED_WIDTH; x++) {
				for (y = 0; y < LED_HEIGHT; y++) {
					set_pixel(x, y, color);
				}
				color = hsv_to_rgb(starth + x * increment, 200, 200);
			}
			StripLights_Trigger(1);

			starth += increment;
			last_ms = ms_count;
		}

		reg_status = RotSWReg_Read();
	} while(reg_status != 0);
}

struct mode_description {
	char sign;
	void (* handler)(void);
};

struct mode_description mode_desc[] = 
{
	[MODE_DRAW] = { 'D', drawing_mode},
	[MODE_BLINK] = { 'B', blink_mode},
	[MODE_SNAKE] = { 'S', star_mode},
	[MODE_MATRIX] = { 'M', star_mode},
	[MODE_RAINBOW] = { 'R', rainbow_mode},
};

static int
select_mode()
{
	uint8_t reg_status;
	int mode = 0, old_mode = -1;

	myprintf("Entering mode selection\n");
	CyDelay(200);
	do {
		reg_status = RotSWReg_Read();
		mode += get_rot1_dir();
		FILTER_VALUE(mode, MODE_COUNT - 1);

		if (mode != old_mode) {
			
			draw_char(mode_desc[mode].sign, 3, 2, 0x0000FF);
			myprintf("Mode change: %d\n", mode);
		}

		old_mode = mode;
	} while (reg_status == 0x3 );

	myprintf("Mode selected: %d\n", mode);
	CyDelay(200);

	return mode;
}

int
main()
{
	int mode;

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
	
	/* Map systick ISR to the user defined ISR. SysTick_IRQn is already defined in core_cm0.h file */
	CyIntSetSysVector((SysTick_IRQn + 16), SystickISR_Handler);
	
	/* Enable Systick timer with desired period/number of ticks */
	SysTick_Config(NUMBER_OF_TICKS);

	// Set dim level 0 = full power, 4 = lowest power
	StripLights_Dim(0); 

	// Enable global interrupts, required for StripLights
	CyGlobalIntEnable;
        clear_pixels(0x000000);

	rot1_pos = Rot1_ReadCounter();
	rot2_pos = Rot2_ReadCounter();

        
        while(1) {
		mode = select_mode();

		clear_pixels(0x000000);
		mode_desc[mode].handler();
		clear_pixels(0x000000);
	}
}
