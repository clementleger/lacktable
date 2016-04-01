#ifndef COLOR_H
#define COLOR_H

typedef struct rgb_color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} rgb_color_t;

typedef struct hsv_color
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
} hsv_color_t;

rgb_color_t hsv_to_rgb(hsv_color_t hsv);

hsv_color_t rgb_to_hsv(rgb_color_t rgb);

#endif
