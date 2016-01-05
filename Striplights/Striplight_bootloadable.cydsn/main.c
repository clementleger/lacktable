/******************************************************************************
* Project Name		: Bootloadable Blinking LED
* File Name			: main.c
* Version 			: 1.0
* Device Used		: CY8C4245AXI-483
* Software Used		: PSoC Creator 3.1
* Compiler    		: ARMGCC 4.8.4, ARM RVDS Generic, ARM MDK Generic
* Related Hardware	: CY8CKIT-049-42xx PSoC 4 Prototyping Kit 
*
********************************************************************************
* Copyright (2015), Cypress Semiconductor Corporation. All Rights Reserved.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress)
* and is protected by and subject to worldwide patent protection (United
* States and foreign), United States copyright laws and international treaty
* provisions. Cypress hereby grants to licensee a personal, non-exclusive,
* non-transferable license to copy, use, modify, create derivative works of,
* and compile the Cypress Source Code and derivative works for the sole
* purpose of creating custom software in support of licensee product to be
* used only in conjunction with a Cypress integrated circuit as specified in
* the applicable agreement. Any reproduction, modification, translation,
* compilation, or representation of this software except as specified above 
* is prohibited without the express written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH 
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the 
* materials described herein. Cypress does not assume any liability arising out 
* of the application or use of any product or circuit described herein. Cypress 
* does not authorize its products for use as critical components in life-support 
* systems where a malfunction or failure may reasonably be expected to result in 
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of 
* such use and in doing so indemnifies Cypress against all charges. 
*
* Use of this Software may be limited by and subject to the applicable Cypress
* software license agreement. 
*******************************************************************************/

/******************************************************************************
*                           THEORY OF OPERATION
* This is a blinking LED project. A PWM component drives the pin to blink the 
* LED at regular intervals. This project contains a bootloadable component so 
* that it can be bootloaded into PSoC 4 which has a bootloader already programmed 
* into it.
* Default UART Port Configuration for bootloading the PSoC 4 in CY8CKIT-049-42xx
* Baud Rate : 115200 bps
* Data Bits : 8
* Stop Bits : 1
* Parity    : None
******************************************************************************/
#include <project.h>
#include <stdlib.h>

extern const uint32 StripLights_CLUT[];

/* Prototype the ISR handler */
CY_ISR_PROTO( ResetISR_Handler );
 
/* Implementation of the ISR handler */
CY_ISR( ResetISR_Handler )
{
    PC_Uart_Stop();
    Bootloadable_Load();        /* Force a bootloader restart */
}

/* Prototype the ISR handler */
CY_ISR_PROTO(RotaryEncoderISR_Handler );
 
/* Implementation of the ISR handler */
CY_ISR( RotaryEncoderISR_Handler )
{
    /* Plop */
}

int main()
{
    int i, j;
	StripLights_Start();
    ESP_Start();
    PC_Uart_Start();
    RotaryEncoder_Start();
    
    /* Start the timer - only runs when SW1 is pressed */
    ResetTimer_Start();
 
    /* Install the ISR handler and make sure none are pending */
    ResetISR_ClearPending();
    ResetISR_StartEx( ResetISR_Handler );
    
    RotaryEncoderISR_ClearPending();
    RotaryEncoderISR_StartEx( RotaryEncoderISR_Handler );
    
    // Set dim level 0 = full power, 4 = lowest power
    StripLights_Dim(0); 
	
	// Clear all memory to black
	StripLights_MemClear(StripLights_BLACK);
    // Enable global interrupts, required for StripLights
    CyGlobalIntEnable;

    while(1)
        PC_Uart_UartPutString("Hello world !\r\n");
      
	for(;;) {
        for (j = 0; j < StripLights_ROWS; j++) {
            // Wait for last update to finish
            for (i = 0; i < StripLights_COLUMNS; i++) {

    		// Wait for last update to finish
    	             while( StripLights_Ready() == 0);  
                // Set the color of a single LED
                StripLights_MemClear(StripLights_BLACK);
    	        StripLights_Pixel(i, j, StripLights_YELLOW );
                StripLights_Trigger(1); 
                CyDelay(50);
            }
        }
    }
}
