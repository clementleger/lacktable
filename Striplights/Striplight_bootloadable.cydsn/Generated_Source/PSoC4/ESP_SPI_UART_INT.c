/*******************************************************************************
* File Name: ESP_SPI_UART_INT.c
* Version 3.0
*
* Description:
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ESP_PVT.h"
#include "ESP_SPI_UART_PVT.h"


#if (ESP_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: ESP_SPI_UART_ISR
********************************************************************************
*
* Summary:
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(ESP_SPI_UART_ISR)
{
#if (ESP_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (ESP_INTERNAL_RX_SW_BUFFER_CONST) */

#if (ESP_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (ESP_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef ESP_SPI_UART_ISR_ENTRY_CALLBACK
    ESP_SPI_UART_ISR_EntryCallback();
#endif /* ESP_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != ESP_customIntrHandler)
    {
        ESP_customIntrHandler();
    }

    #if (ESP_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        ESP_ClearSpiExtClkInterruptSource(ESP_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (ESP_CHECK_RX_SW_BUFFER)
    {
        if (ESP_CHECK_INTR_RX_MASKED(ESP_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (ESP_rxBufferHead + 1u);

                /* Adjust local head index */
                if (ESP_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == ESP_rxBufferTail)
                {
                    #if (ESP_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        ESP_INTR_RX_MASK_REG &= ~ESP_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) ESP_RX_FIFO_RD_REG;
                        ESP_rxBufferOverflow = (uint8) ESP_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    ESP_PutWordInRxBuffer(locHead, ESP_RX_FIFO_RD_REG);

                    /* Move head index */
                    ESP_rxBufferHead = locHead;
                }
            }
            while(0u != ESP_GET_RX_FIFO_ENTRIES);

            ESP_ClearRxInterruptSource(ESP_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (ESP_CHECK_TX_SW_BUFFER)
    {
        if (ESP_CHECK_INTR_TX_MASKED(ESP_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (ESP_txBufferHead != ESP_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (ESP_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (ESP_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    ESP_TX_FIFO_WR_REG = ESP_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    ESP_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    ESP_DISABLE_INTR_TX(ESP_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (ESP_SPI_UART_FIFO_SIZE != ESP_GET_TX_FIFO_ENTRIES);

            ESP_ClearTxInterruptSource(ESP_INTR_TX_NOT_FULL);
        }
    }
    #endif
    
#ifdef ESP_SPI_UART_ISR_EXIT_CALLBACK
    ESP_SPI_UART_ISR_ExitCallback();
#endif /* ESP_SPI_UART_ISR_EXIT_CALLBACK */
    
}

#endif /* (ESP_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
