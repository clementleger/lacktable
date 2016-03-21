
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
set_pixel(unsigned int i, unsigned int j) {
        
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
    
        for(;;)
    {
        /* Set LED output to logic HIGH */
        sprintf(tmp, "Counter 1: %ld\r\n", Rot1_ReadCounter());
        PC_Uart_UartPutString(tmp);
        sprintf(tmp, "Counter 1: %ld\r\n", Rot2_ReadCounter());
        PC_Uart_UartPutString(tmp);
        reg_status = RotSWReg_Read();
        sprintf(tmp, "Counter 1: %x\r\n", reg_status);
        PC_Uart_UartPutString(tmp);
        /* Delay of 500 ms */
        CyDelay(100u);
    }
    
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
