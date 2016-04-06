
#include <project.h>
#include "shared.h"

/* Blink stuff */
#define MIN_SPAWN_TIME			0
#define MAX_SPAWN_TIME			1000
#define STAR_MIN_DURATION		7000
#define STAR_MAX_DURATION		15000
#define LIGHTING_CURVE			1000
#define BLINK_UPDATE_TIME		50
#define BLINK_SATURATION		200
#define MAX_BLINK_COUNT			20


struct blink_led_state {
	uint16_t duration;	/* Led lit duration */
	uint16_t value;		/* Current duration */
};

static int
blink_update_leds (struct blink_led_state state[LED_WIDTH][LED_HEIGHT], uint8_t h)
{
	int x, y;
	uint32_t color;
	uint8_t sat;
	uint16_t value, duration;
	int star_count = 0;
	
	while(StripLights_Ready() == 0);
	for (x = 0; x < LED_WIDTH; x++) {
		for (y = 0; y < LED_HEIGHT; y++) {
			duration = state[x][y].duration;
			/* Star is off */
			if (duration == 0)
				continue;
			
			value = state[x][y].value;
			/* Slow lighting curve */
			if (value < LIGHTING_CURVE) {
				sat = value * BLINK_SATURATION / LIGHTING_CURVE;
				color = hsv_to_rgb(h, 200, sat);
			} else if (value > (duration - LIGHTING_CURVE)) {
				sat = (duration - value) * BLINK_SATURATION / LIGHTING_CURVE;
				color = hsv_to_rgb(h, 200, sat);
			} else {
				color = hsv_to_rgb(h, 200, BLINK_SATURATION);
			}

			set_pixel(x, y, color);
			state[x][y].value += BLINK_UPDATE_TIME;
			if (state[x][y].value == state[x][y].duration) {
				state[x][y].duration = 0;
				set_pixel(x, y, 0x000000);
			} else {
				star_count++;	
			}
		}
	}
	StripLights_Trigger(1);
	
	return star_count;
}

static void
blink_spawn_star (struct blink_led_state state[LED_WIDTH][LED_HEIGHT])
{
	int x, y;
	int duration;

again:
	x = randr(0, LED_WIDTH - 1);
	y = randr(0, LED_HEIGHT - 1);

	if (state[x][y].duration != 0)
		goto again;

	if (x > 0) {
		if (state[x - 1][y].duration != 0) {
			goto again;
		}
	}

	if (x < (LED_WIDTH - 1)) {
		if (state[x + 1][y].duration != 0) {
			goto again;
		}
	}
	
	if (y > 0) {
		if (state[x][y - 1].duration != 0) {
			goto again;
		}
	}

	if (y < (LED_HEIGHT - 1)) {
		if (state[x][y + 1].duration != 0) {
			goto again;
		}
	}

	
	duration = randr(STAR_MIN_DURATION, STAR_MAX_DURATION);
	/* Round it for better sync with update func */
	duration -= (duration % BLINK_UPDATE_TIME);

	state[x][y].duration = duration;
	state[x][y].value = 0;
}

void
blink_mode()
{
	struct blink_led_state state[LED_WIDTH][LED_HEIGHT] = {{{0, 0}}};
	uint8_t reg_status;
	int h = 255;
	int x, y;
	uint32_t next_spawn_time = 0, last_spawn_ms = 0, last_update_ms= 0;
	int blink_count = 0, max_blink_count = 6;

	srand(ms_count);

	do {
		
		h += (get_rot2_dir() * 5);
		FILTER_VALUE(h, 255);
		max_blink_count += get_rot1_dir();
		FILTER_VALUE(max_blink_count, MAX_BLINK_COUNT);

		/* Spawn a random "star" */
		if (blink_count < max_blink_count) {
			if ((ms_count - last_spawn_ms) > next_spawn_time) {
				blink_spawn_star(state);
				next_spawn_time = randr(MIN_SPAWN_TIME, MAX_SPAWN_TIME);
				last_spawn_ms = ms_count;
			}
		}

		/* Update every 50 msec */
		if ((ms_count - last_update_ms) > BLINK_UPDATE_TIME) {
			blink_count = blink_update_leds(state, h);
			last_update_ms = ms_count;
		}

		reg_status = RotSWReg_Read();

		/* Reset */
		if (!(reg_status & 0x1)) {
			for (x = 0; x < LED_WIDTH; x++) {
				for (y = 0; y < LED_HEIGHT; y++) {
					state[x][y].duration = 0;
					state[x][y].value = 0;
					blink_count = 0;
				}
			}
		}

	} while(reg_status != 0);
	
	
	
}
