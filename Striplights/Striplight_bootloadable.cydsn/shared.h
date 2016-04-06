#ifndef SHARED_H
#define SHARED_H

#include <stdint.h>
#include <stdlib.h>

#define LED_HEIGHT	12
#define LED_WIDTH	12

extern uint32_t ms_count;

uint32_t
hsv_to_rgb(uint8_t h, uint8_t s, uint8_t v);

void
symbol_mode();

void
blink_mode();

void
myprintf(const char *fmt , ...);
  
int
get_rot1_dir();

int
get_rot2_dir();

void
clear_pixels(uint32_t color);

void
set_pixel(int i, int j, uint32 color);

void
draw_char(char c, int x, int y, uint32_t color);

static inline int
randr(unsigned int min, unsigned int max)
{
       return rand()%(max + 1 - min) + min;
}

#endif
