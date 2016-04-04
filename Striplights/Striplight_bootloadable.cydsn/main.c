
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

#define MIN_SPAWN_TIME		1000
#define MAX_SPAWN_TIME		4000
#define STAR_MIN_DURATION	6000
#define STAR_MAX_DURATION	10000
#define LIGHTING_CURVE		1000

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

int
randr(unsigned int min, unsigned int max)
{
       return rand()%(max + 1 - min) + min;
}
static inline void
myprintf(const char *fmt , ...)
{
#ifndef NDEBUG
	va_list args;
        char buffer[512];

        va_start(args, fmt);
        vsnprintf(buffer, 512, fmt, args);
        va_end(args);

        PC_Uart_UartPutString(buffer);
#endif
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

#define BLINK_UPDATE_TIME		50
#define BLINK_LIGHTING_INCREMENT	(LIGHTING_CURVE / 50)
#define BLINK_STEPS			((float) LIGHTING_CURVE / BLINK_LIGHTING_INCREMENT)

struct blink_led_state {
	uint16_t duration;	/* Led lit duration */
	uint16_t value;		/* Current duration */
};

static void
blink_update_leds (struct blink_led_state state[LED_WIDTH][LED_HEIGHT])
{
	int x, y;
	uint32_t color;
	
	while(StripLights_Ready() == 0);
	for (x = 0; x < LED_WIDTH; x++) {
		for (y = 0; y < LED_HEIGHT; y++) {

			/* Star is off */
			if (state[x][y].duration == 0)
				continue;

			/* Slow lighting curve */
			if (state[x][y].value < LIGHTING_CURVE) {
				color = hsv_to_rgb(255, 200, 200)
			} else {
				color = hsv_to_rgb(255, 200, 200)
			}

			set_pixel(x, y, color);
			state[x][y].value += BLINK_UPDATE_TIME;
			if (state[x][y].value == state[x][y].duration) {
				state[x][y].duration = 0;
				set_pixel(x, y, 0x000000);
			}
		}
	}
	StripLights_Trigger(1);
}

static void
blink_spawn_star (struct blink_led_state state[LED_WIDTH][LED_HEIGHT])
{
	int x, y;
	int duration;

	do {
		x = randr(0, LED_WIDTH - 1);
		y = randr(0, LED_HEIGHT - 1);
	} while (state[x][y].duration != 0);
	
	duration = randr(STAR_MIN_DURATION, STAR_MAX_DURATION);
	/* Round it for better sync with update func */
	duration -= (duration % BLINK_UPDATE_TIME);

	state[x][y].duration = duration;
	state[x][y].value = 0;
}

static void
blink_mode()
{
	struct blink_led_state state[LED_WIDTH][LED_HEIGHT] = {{0}};
	uint8_t reg_status;
	int x, y;
	uint32_t next_spawn_time = 0, last_spawn_ms = 0, last_update_ms= 0;

	srand(ms_count);

	do {
		/* Spawn a random "star" */
		if ((ms_count - last_spawn_ms) > next_spawn_time) {
			blink_spawn_star(state);
			next_spawn_time = randr(MIN_SPAWN_TIME, MAX_SPAWN_TIME);
			last_spawn_ms = ms_count;
		}

		/* Update every 50 msec */
		if ((ms_count - last_update_ms) > BLINK_UPDATE_TIME) {
			blink_update_leds(state);
			last_update_ms = ms_count;
		}

		reg_status = RotSWReg_Read();
		/* Draw mode on/off */
		if (!(reg_status & 0x1)) {
			for (x = 0; x < LED_WIDTH; x++) {
				for (y = 0; y < LED_HEIGHT; y++) {
					state[x][y].duration = 0;
				}
			}
		}

	} while(reg_status != 0);
	
	
	
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
	uint32_t color;
};

struct mode_description mode_desc[] = 
{
	[MODE_DRAW] = { 'D', drawing_mode, 0xFF9D1D},
	[MODE_BLINK] = { 'B', blink_mode, 0xE84C27},
	[MODE_SNAKE] = { 'S', star_mode, 0xFF2AB0},
	[MODE_MATRIX] = { 'M', star_mode, 0x8827E8},
	[MODE_RAINBOW] = { 'R', rainbow_mode, 0x2A53FF},
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
			
			draw_char(mode_desc[mode].sign, 3, 2, mode_desc[mode].color);
			myprintf("Mode change: %s\n", mode_desc[mode].sign);
		}

		old_mode = mode;
	} while (reg_status == 0x3 );

	myprintf("Mode selected: %s\n", mode_desc[mode].sign);
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
