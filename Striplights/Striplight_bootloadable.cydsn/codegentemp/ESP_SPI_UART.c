/*******************************************************************************
* File Name: ESP_SPI_UART.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ESP_PVT.h"
#include "ESP_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(ESP_INTERNAL_RX_SW_BUFFER_CONST)
    volatile uint32 ESP_rxBufferHead;
    volatile uint32 ESP_rxBufferTail;
    volatile uint8  ESP_rxBufferOverflow;
#endif /* (ESP_INTERNAL_RX_SW_BUFFER_CONST) */

#if(ESP_INTERNAL_TX_SW_BUFFER_CONST)
    volatile uint32 ESP_txBufferHead;
    volatile uint32 ESP_txBufferTail;
#endif /* (ESP_INTERNAL_TX_SW_BUFFER_CONST) */

#if(ESP_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 ESP_rxBufferInternal[ESP_INTERNAL_RX_BUFFER_SIZE];
#endif /* (ESP_INTERNAL_RX_SW_BUFFER) */

#if(ESP_INTERNAL_TX_SW_BUFFER)
    volatile uint8 ESP_txBufferInternal[ESP_TX_BUFFER_SIZE];
#endif /* (ESP_INTERNAL_TX_SW_BUFFER) */


#if(ESP_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: ESP_SpiUartReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Next data element from the receive buffer.
    *
    * Global Variables:
    *  Look into ESP_SpiInit for description.
    *
    *******************************************************************************/
    uint32 ESP_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (ESP_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (ESP_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (ESP_CHECK_RX_SW_BUFFER)
        {
            if (ESP_rxBufferHead != ESP_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (ESP_rxBufferTail + 1u);

                if (ESP_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = ESP_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                ESP_rxBufferTail = locTail;

                #if (ESP_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (ESP_INTR_RX_MASK_REG & ESP_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        ESP_INTR_RX_MASK_REG |= ESP_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = ESP_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: ESP_SpiUartGetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of received data elements
    *
    *******************************************************************************/
    uint32 ESP_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (ESP_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (ESP_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (ESP_CHECK_RX_SW_BUFFER)
        {
            locHead = ESP_rxBufferHead;

            if(locHead >= ESP_rxBufferTail)
            {
                size = (locHead - ESP_rxBufferTail);
            }
            else
            {
                size = (locHead + (ESP_INTERNAL_RX_BUFFER_SIZE - ESP_rxBufferTail));
            }
        }
        #else
        {
            size = ESP_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: ESP_SpiUartClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receive buffer and RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ESP_SpiUartClearRxBuffer(void)
    {
        #if (ESP_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            ESP_DisableInt();

            /* Flush RX software buffer */
            ESP_rxBufferHead = ESP_rxBufferTail;
            ESP_rxBufferOverflow = 0u;

            ESP_CLEAR_RX_FIFO;
            ESP_ClearRxInterruptSource(ESP_INTR_RX_ALL);

            #if (ESP_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                ESP_INTR_RX_MASK_REG |= ESP_INTR_RX_NOT_EMPTY;
            }
            #endif

            /* Release lock */
            ESP_EnableInt();
        }
        #else
        {
            ESP_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (ESP_RX_DIRECTION) */


#if(ESP_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: ESP_SpiUartWriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    * Parameters:
    *  txDataByte: the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ESP_SpiUartWriteTxData(uint32 txData)
    {
    #if (ESP_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (ESP_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (ESP_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((ESP_txBufferHead == ESP_txBufferTail) &&
                (ESP_SPI_UART_FIFO_SIZE != ESP_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                ESP_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (ESP_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (ESP_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == ESP_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                ESP_ClearTxInterruptSource(ESP_INTR_TX_NOT_FULL);

                ESP_PutWordInTxBuffer(locHead, txData);

                ESP_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (ESP_INTR_TX_MASK_REG & ESP_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    ESP_INTR_TX_MASK_REG |= (uint32) ESP_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (ESP_SPI_UART_FIFO_SIZE == ESP_GET_TX_FIFO_ENTRIES)
            {
            }

            ESP_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: ESP_SpiUartPutArray
    ********************************************************************************
    *
    * Summary:
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * Parameters:
    *  wrBuf:  pointer to an array with data to be placed in transmit buffer.
    *  count:  number of data elements to be placed in the transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ESP_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            ESP_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: ESP_SpiUartGetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    * Returns the number of elements currently in the transmit buffer.
    *  - TX software buffer is disabled: returns the number of used entries in
    *    TX FIFO.
    *  - TX software buffer is enabled: returns the number of elements currently
    *    used in the transmit buffer. This number does not include used entries in
    *    the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *    not full.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of data elements ready to transmit.
    *
    *******************************************************************************/
    uint32 ESP_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (ESP_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (ESP_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (ESP_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = ESP_txBufferTail;

            if (ESP_txBufferHead >= locTail)
            {
                size = (ESP_txBufferHead - locTail);
            }
            else
            {
                size = (ESP_txBufferHead + (ESP_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = ESP_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: ESP_SpiUartClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the transmit buffer and TX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ESP_SpiUartClearTxBuffer(void)
    {
        #if (ESP_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            ESP_DisableInt();

            /* Flush TX software buffer */
            ESP_txBufferHead = ESP_txBufferTail;

            ESP_INTR_TX_MASK_REG &= (uint32) ~ESP_INTR_TX_NOT_FULL;
            ESP_CLEAR_TX_FIFO;
            ESP_ClearTxInterruptSource(ESP_INTR_TX_ALL);

            /* Release lock */
            ESP_EnableInt();
        }
        #else
        {
            ESP_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (ESP_TX_DIRECTION) */


/*******************************************************************************
* Function Name: ESP_SpiUartDisableIntRx
********************************************************************************
*
* Summary:
*  Disables the RX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 ESP_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = ESP_GetRxInterruptMode();

    ESP_SetRxInterruptMode(ESP_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: ESP_SpiUartDisableIntTx
********************************************************************************
*
* Summary:
*  Disables TX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 ESP_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = ESP_GetTxInterruptMode();

    ESP_SetTxInterruptMode(ESP_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(ESP_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: ESP_PutWordInRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  index:      index to store data byte/word in the RX buffer.
    *  rxDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ESP_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (ESP_ONE_BYTE_WIDTH == ESP_rxDataBits)
        {
            ESP_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            ESP_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            ESP_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: ESP_GetWordFromRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 ESP_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (ESP_ONE_BYTE_WIDTH == ESP_rxDataBits)
        {
            value = ESP_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) ESP_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)ESP_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: ESP_PutWordInTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx:        index to store data byte/word in the TX buffer.
    *  txDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ESP_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (ESP_ONE_BYTE_WIDTH == ESP_txDataBits)
        {
            ESP_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            ESP_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            ESP_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: ESP_GetWordFromTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx: index to get data byte/word from the TX buffer.
    *
    * Return:
    *  Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 ESP_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (ESP_ONE_BYTE_WIDTH == ESP_txDataBits)
        {
            value = (uint32) ESP_txBuffer[idx];
        }
        else
        {
            value  = (uint32) ESP_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) ESP_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
