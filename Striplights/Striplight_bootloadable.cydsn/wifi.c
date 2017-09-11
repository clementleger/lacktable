
#include <project.h>
#include "shared.h"
#include <stdio.h>

enum request_type {
	GET_INFO		= 'i',
	SET_PIXEL		= 'p',
	SET_FRAME		= 'f',
};

/**
 * Protocol:
 * First byte is the type of request
 * 
 */
 
static uint32_t frame_buffer[LED_HEIGHT][LED_WIDTH];

static void handle_get_info()
{
	char buffer[20];
	sprintf(buffer, "%dx%d\n", LED_WIDTH, LED_HEIGHT);
	ESP_UartPutString(buffer);
}

#define MAX_SET_PIXEL_SIZE 18
/* Handle set_pixel command
 * x,y:r,g,b\n
 * 
 *   */
static void handle_set_pixel()
{
	char buffer[MAX_SET_PIXEL_SIZE] = {0};
	char *ptr;
	char tmp;
	int index = 0, x, y;
	uint8_t r,g,b;
	uint8_t reg_status;
	myprintf("Entering set_pixel\n");

	do {
		reg_status = RotSWReg_Read();
		if (reg_status != 0x3)
			return;

		tmp = ESP_UartGetChar();
		if (tmp == 0)
			continue;
		buffer[index] = tmp;
		index++;
		if (tmp == '\n')
			buffer[index] = 0;
	} while (tmp != '\n' || index == MAX_SET_PIXEL_SIZE);
	x = atoi(buffer);
	ptr = strchr(buffer, ',');
	if (ptr == buffer)
		return;
	y = atoi(++ptr);
	ptr = strchr(ptr, ':');
	if (ptr == ptr)
		return;
	r = atoi(++ptr);
	ptr = strchr(ptr, ',');
	if (ptr == ptr)
		return;
	g = atoi(++ptr);
	ptr = strchr(ptr, ',');
	if (ptr == ptr)
		return;
	b = atoi(++ptr);

	if (x > (LED_WIDTH - 1)|| y > (LED_HEIGHT - 1))
		return;

	set_pixel(x, y, RGB_TO_STRIP(r, g, b));
	StripLights_Trigger(1);
}

void
wifi_mode()
{
	uint8_t reg_status;

	do {
		reg_status = RotSWReg_Read();
		uint8_t byte = ESP_UartGetChar();
		if (byte) {
			myprintf("Recefived '%c'\n", byte);
		}
		switch(byte) {
		case GET_INFO:
			handle_get_info(0);
		break;
		case SET_PIXEL:
			handle_set_pixel(0);
		break;
		}
	} while(reg_status != 0);
}
