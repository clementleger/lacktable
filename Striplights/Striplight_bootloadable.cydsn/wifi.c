
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
	sprintf(buffer, "%dx%d", LED_WIDTH, LED_HEIGHT);
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
	int index;
	char tmp;
	uint8_t reg_status;

	do {
		reg_status = RotSWReg_Read();
		if (reg_status != 0)
			return;

		tmp = ESP_UartGetChar();
		if (tmp == 0)
			continue;
		buffer[index] = tmp;
		index++;
	} while (tmp != '\n' || index == MAX_SET_PIXEL_SIZE);
	
	myprintf("Received string %s\n", buffer);
}

void
wifi_mode()
{
	uint8_t reg_status;

	do {
		reg_status = RotSWReg_Read();
		uint8_t byte = ESP_UartGetChar();
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
