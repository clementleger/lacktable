/*******************************************************************************
* File Name: ESP_UART.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
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


#if(ESP_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const ESP_UART_INIT_STRUCT ESP_configUart =
    {
        ESP_UART_SUB_MODE,
        ESP_UART_DIRECTION,
        ESP_UART_DATA_BITS_NUM,
        ESP_UART_PARITY_TYPE,
        ESP_UART_STOP_BITS_NUM,
        ESP_UART_OVS_FACTOR,
        ESP_UART_IRDA_LOW_POWER,
        ESP_UART_MEDIAN_FILTER_ENABLE,
        ESP_UART_RETRY_ON_NACK,
        ESP_UART_IRDA_POLARITY,
        ESP_UART_DROP_ON_PARITY_ERR,
        ESP_UART_DROP_ON_FRAME_ERR,
        ESP_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        ESP_UART_MP_MODE_ENABLE,
        ESP_UART_MP_ACCEPT_ADDRESS,
        ESP_UART_MP_RX_ADDRESS,
        ESP_UART_MP_RX_ADDRESS_MASK,
        (uint32) ESP_SCB_IRQ_INTERNAL,
        ESP_UART_INTR_RX_MASK,
        ESP_UART_RX_TRIGGER_LEVEL,
        ESP_UART_INTR_TX_MASK,
        ESP_UART_TX_TRIGGER_LEVEL,
        (uint8) ESP_UART_BYTE_MODE_ENABLE,
        (uint8) ESP_UART_CTS_ENABLE,
        (uint8) ESP_UART_CTS_POLARITY,
        (uint8) ESP_UART_RTS_POLARITY,
        (uint8) ESP_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: ESP_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ESP_UartInit(const ESP_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if (NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (ESP_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (ESP_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1) */

            /* Configure pins */
            ESP_SetPins(ESP_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            ESP_scbMode       = (uint8) ESP_SCB_MODE_UART;
            ESP_scbEnableWake = (uint8) config->enableWake;
            ESP_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            ESP_rxBuffer      =         config->rxBuffer;
            ESP_rxDataBits    = (uint8) config->dataBits;
            ESP_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            ESP_txBuffer      =         config->txBuffer;
            ESP_txDataBits    = (uint8) config->dataBits;
            ESP_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(ESP_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                ESP_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (ESP_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (ESP_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                ESP_CTRL_REG  = ESP_GET_CTRL_OVS(config->oversample);
            }

            ESP_CTRL_REG     |= ESP_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             ESP_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             ESP_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            ESP_UART_CTRL_REG = ESP_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            ESP_UART_RX_CTRL_REG = ESP_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        ESP_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        ESP_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        ESP_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        ESP_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(ESP_UART_PARITY_NONE != config->parity)
            {
               ESP_UART_RX_CTRL_REG |= ESP_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    ESP_UART_RX_CTRL_PARITY_ENABLED;
            }

            ESP_RX_CTRL_REG      = ESP_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                ESP_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                ESP_GET_UART_RX_CTRL_ENABLED(config->direction);

            ESP_RX_FIFO_CTRL_REG = ESP_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            ESP_RX_MATCH_REG     = ESP_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                ESP_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            ESP_UART_TX_CTRL_REG = ESP_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                ESP_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(ESP_UART_PARITY_NONE != config->parity)
            {
               ESP_UART_TX_CTRL_REG |= ESP_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    ESP_UART_TX_CTRL_PARITY_ENABLED;
            }

            ESP_TX_CTRL_REG      = ESP_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                ESP_GET_UART_TX_CTRL_ENABLED(config->direction);

            ESP_TX_FIFO_CTRL_REG = ESP_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1)
            ESP_UART_FLOW_CTRL_REG = ESP_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            ESP_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            ESP_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            ESP_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (ESP_ISR_NUMBER);
            CyIntSetPriority(ESP_ISR_NUMBER, ESP_ISR_PRIORITY);
            (void) CyIntSetVector(ESP_ISR_NUMBER, &ESP_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(ESP_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (ESP_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(ESP_RX_WAKE_ISR_NUMBER, ESP_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(ESP_RX_WAKE_ISR_NUMBER, &ESP_UART_WAKEUP_ISR);
        #endif /* (ESP_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            ESP_INTR_I2C_EC_MASK_REG = ESP_NO_INTR_SOURCES;
            ESP_INTR_SPI_EC_MASK_REG = ESP_NO_INTR_SOURCES;
            ESP_INTR_SLAVE_MASK_REG  = ESP_NO_INTR_SOURCES;
            ESP_INTR_MASTER_MASK_REG = ESP_NO_INTR_SOURCES;
            ESP_INTR_RX_MASK_REG     = config->rxInterruptMask;
            ESP_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            ESP_rxBufferHead     = 0u;
            ESP_rxBufferTail     = 0u;
            ESP_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            ESP_txBufferHead = 0u;
            ESP_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: ESP_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ESP_UartInit(void)
    {
        /* Configure UART interface */
        ESP_CTRL_REG = ESP_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        ESP_UART_CTRL_REG = ESP_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        ESP_UART_RX_CTRL_REG = ESP_UART_DEFAULT_UART_RX_CTRL;
        ESP_RX_CTRL_REG      = ESP_UART_DEFAULT_RX_CTRL;
        ESP_RX_FIFO_CTRL_REG = ESP_UART_DEFAULT_RX_FIFO_CTRL;
        ESP_RX_MATCH_REG     = ESP_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        ESP_UART_TX_CTRL_REG = ESP_UART_DEFAULT_UART_TX_CTRL;
        ESP_TX_CTRL_REG      = ESP_UART_DEFAULT_TX_CTRL;
        ESP_TX_FIFO_CTRL_REG = ESP_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1)
        ESP_UART_FLOW_CTRL_REG = ESP_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(ESP_SCB_IRQ_INTERNAL)
        CyIntDisable    (ESP_ISR_NUMBER);
        CyIntSetPriority(ESP_ISR_NUMBER, ESP_ISR_PRIORITY);
        (void) CyIntSetVector(ESP_ISR_NUMBER, &ESP_SPI_UART_ISR);
    #endif /* (ESP_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(ESP_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (ESP_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(ESP_RX_WAKE_ISR_NUMBER, ESP_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(ESP_RX_WAKE_ISR_NUMBER, &ESP_UART_WAKEUP_ISR);
    #endif /* (ESP_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        ESP_INTR_I2C_EC_MASK_REG = ESP_UART_DEFAULT_INTR_I2C_EC_MASK;
        ESP_INTR_SPI_EC_MASK_REG = ESP_UART_DEFAULT_INTR_SPI_EC_MASK;
        ESP_INTR_SLAVE_MASK_REG  = ESP_UART_DEFAULT_INTR_SLAVE_MASK;
        ESP_INTR_MASTER_MASK_REG = ESP_UART_DEFAULT_INTR_MASTER_MASK;
        ESP_INTR_RX_MASK_REG     = ESP_UART_DEFAULT_INTR_RX_MASK;
        ESP_INTR_TX_MASK_REG     = ESP_UART_DEFAULT_INTR_TX_MASK;

    #if(ESP_INTERNAL_RX_SW_BUFFER_CONST)
        ESP_rxBufferHead     = 0u;
        ESP_rxBufferTail     = 0u;
        ESP_rxBufferOverflow = 0u;
    #endif /* (ESP_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(ESP_INTERNAL_TX_SW_BUFFER_CONST)
        ESP_txBufferHead = 0u;
        ESP_txBufferTail = 0u;
    #endif /* (ESP_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: ESP_UartPostEnable
********************************************************************************
*
* Summary:
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be 
*  controlled by the SCB UART.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ESP_UartPostEnable(void)
{
#if (ESP_SCB_MODE_UNCONFIG_CONST_CFG)

#if (ESP_TX_SDA_MISO_PIN)
    if (ESP_CHECK_TX_SDA_MISO_PIN_USED)
    {
        /* Set SCB UART to drive the output pin */
        ESP_SET_HSIOM_SEL(ESP_TX_SDA_MISO_HSIOM_REG, ESP_TX_SDA_MISO_HSIOM_MASK,
                                       ESP_TX_SDA_MISO_HSIOM_POS, ESP_HSIOM_UART_SEL);
    }
#endif /* (ESP_TX_SDA_MISO_PIN_PIN) */

#if (ESP_SS0_PIN)
    if (ESP_CHECK_SS0_PIN_USED)
    {
        /* Set SCB UART to drive the output pin */
        ESP_SET_HSIOM_SEL(ESP_SS0_HSIOM_REG, ESP_SS0_HSIOM_MASK,
                                       ESP_SS0_HSIOM_POS, ESP_HSIOM_UART_SEL);
    }
#endif /* (ESP_SS0_PIN) */

#else
#if (ESP_UART_TX_PIN)
     /* Set SCB UART to drive the output pin */
    ESP_SET_HSIOM_SEL(ESP_TX_HSIOM_REG, ESP_TX_HSIOM_MASK,
                                   ESP_TX_HSIOM_POS, ESP_HSIOM_UART_SEL);
#endif /* (ESP_UART_TX_PIN) */

#if (ESP_UART_RTS_PIN)
    /* Set SCB UART to drive the output pin */
    ESP_SET_HSIOM_SEL(ESP_RTS_HSIOM_REG, ESP_RTS_HSIOM_MASK,
                                   ESP_RTS_HSIOM_POS, ESP_HSIOM_UART_SEL);
#endif /* (ESP_UART_RTS_PIN) */

#endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ESP_UartStop
********************************************************************************
*
* Summary:
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature to
*  not cause it to trigger after the component is enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ESP_UartStop(void)
{
#if(ESP_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (ESP_TX_SDA_MISO_PIN)
        if (ESP_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            ESP_SET_HSIOM_SEL(ESP_TX_SDA_MISO_HSIOM_REG, ESP_TX_SDA_MISO_HSIOM_MASK,
                                           ESP_TX_SDA_MISO_HSIOM_POS, ESP_HSIOM_GPIO_SEL);
        }
    #endif /* (ESP_TX_SDA_MISO_PIN_PIN) */

    #if (ESP_SS0_PIN)
        if (ESP_CHECK_SS0_PIN_USED)
        {
            /* Set output pin state after block is disabled */
            ESP_spi_ss0_Write(ESP_GET_UART_RTS_INACTIVE);

            /* Set GPIO to drive output pin */
            ESP_SET_HSIOM_SEL(ESP_SS0_HSIOM_REG, ESP_SS0_HSIOM_MASK,
                                           ESP_SS0_HSIOM_POS, ESP_HSIOM_GPIO_SEL);
        }
    #endif /* (ESP_SS0_PIN) */

#else
    #if (ESP_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        ESP_SET_HSIOM_SEL(ESP_TX_HSIOM_REG, ESP_TX_HSIOM_MASK,
                                       ESP_TX_HSIOM_POS, ESP_HSIOM_GPIO_SEL);
    #endif /* (ESP_UART_TX_PIN) */

    #if (ESP_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        ESP_rts_Write(ESP_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        ESP_SET_HSIOM_SEL(ESP_RTS_HSIOM_REG, ESP_RTS_HSIOM_MASK,
                                       ESP_RTS_HSIOM_POS, ESP_HSIOM_GPIO_SEL);
    #endif /* (ESP_UART_RTS_PIN) */

#endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (ESP_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    ESP_UART_RX_CTRL_REG &= (uint32) ~ESP_UART_RX_CTRL_SKIP_START;
#endif /* (ESP_UART_WAKE_ENABLE_CONST) */
}


/*******************************************************************************
* Function Name: ESP_UartSetRxAddress
********************************************************************************
*
* Summary:
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
* Parameters:
*  address: Address for hardware address detection.
*
* Return:
*  None
*
*******************************************************************************/
void ESP_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = ESP_RX_MATCH_REG;

    matchReg &= ((uint32) ~ESP_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & ESP_RX_MATCH_ADDR_MASK)); /* Set address  */

    ESP_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: ESP_UartSetRxAddressMask
********************************************************************************
*
* Summary:
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
* Parameters:
*  addressMask: Address mask.
*   0 - address bit does not care while comparison.
*   1 - address bit is significant while comparison.
*
* Return:
*  None
*
*******************************************************************************/
void ESP_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = ESP_RX_MATCH_REG;

    matchReg &= ((uint32) ~ESP_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << ESP_RX_MATCH_MASK_POS));

    ESP_RX_MATCH_REG = matchReg;
}


#if(ESP_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: ESP_UartGetChar
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *  This function is designed for ASCII characters and returns a char
    *  where 1 to 255 are valid characters and 0 indicates an error occurred or
    *  no data present.
    *  - The RX software buffer is disabled: returns the data element
    *    retrieved from the RX FIFO.
    *    Undefined data will be returned if the RX FIFO is empty.
    *  - The RX software buffer is enabled: returns the data element from
    *    the software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The next data element from the receive buffer.
    *  ASCII character values from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is enabled: The internal software buffer overflow
    *  does not treat as an error condition.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 ESP_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != ESP_SpiUartGetRxBufferSize())
        {
            rxData = ESP_SpiUartReadRxData();
        }

        if (ESP_CHECK_INTR_RX(ESP_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            ESP_ClearRxInterruptSource(ESP_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: ESP_UartGetByte
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Bits 7-0 contain the next data element from the receive buffer and
    *  other bits contain the error condition.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is disabled: The internal software buffer overflow
    *  is not returned as status by this function.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 ESP_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (ESP_CHECK_RX_SW_BUFFER)
        {
            ESP_DisableInt();
        }
        #endif

        if (0u != ESP_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (ESP_CHECK_RX_SW_BUFFER)
            {            
                ESP_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = ESP_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the case
            * of empty. Otherwise the first received byte will be read.
            */
            rxData = ESP_RX_FIFO_RD_REG;

            /* Enables interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by the interrupt routine
            * in case the byte was received and read by code above.
            */
            #if (ESP_CHECK_RX_SW_BUFFER)
            {
                ESP_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (ESP_GetRxInterruptSource() & ESP_INTR_RX_ERR);
        ESP_ClearRxInterruptSource(ESP_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: ESP_UartSetRtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of RTS output signal.
        *
        * Parameters:
        *  polarity: Active polarity of RTS output signal.
        *   ESP_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   ESP_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void ESP_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                ESP_UART_FLOW_CTRL_REG |= (uint32)  ESP_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                ESP_UART_FLOW_CTRL_REG &= (uint32) ~ESP_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: ESP_UartSetRtsFifoLevel
        ********************************************************************************
        *
        * Summary:
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *
        * Parameters:
        *  level: Level in the RX FIFO for RTS signal activation.
        *         The range of valid level values is between 0 and RX FIFO depth - 1.
        *         Setting level value to 0 disables RTS signal activation.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void ESP_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = ESP_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~ESP_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (ESP_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            ESP_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1) */

#endif /* (ESP_UART_RX_DIRECTION) */


#if(ESP_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: ESP_UartPutString
    ********************************************************************************
    *
    * Summary:
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  string: pointer to the null terminated string array to be placed in the
    *          transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ESP_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            ESP_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: ESP_UartPutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data followed by a carriage return (0x0D) and
    *  line feed (0x0A) into the transmit buffer.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  txDataByte : the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ESP_UartPutCRLF(uint32 txDataByte)
    {
        ESP_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        ESP_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        ESP_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: ESPSCB_UartEnableCts
        ********************************************************************************
        *
        * Summary:
        *  Enables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void ESP_UartEnableCts(void)
        {
            ESP_UART_FLOW_CTRL_REG |= (uint32)  ESP_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: ESP_UartDisableCts
        ********************************************************************************
        *
        * Summary:
        *  Disables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void ESP_UartDisableCts(void)
        {
            ESP_UART_FLOW_CTRL_REG &= (uint32) ~ESP_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: ESP_UartSetCtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of CTS input signal.
        *
        * Parameters:
        *  polarity: Active polarity of CTS output signal.
        *   ESP_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   ESP_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void ESP_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                ESP_UART_FLOW_CTRL_REG |= (uint32)  ESP_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                ESP_UART_FLOW_CTRL_REG &= (uint32) ~ESP_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1) */

#endif /* (ESP_UART_TX_DIRECTION) */


#if(ESP_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: ESP_UartSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Clears and enables interrupt on a falling edge of the Rx input. The GPIO
    *  event wakes up the device and SKIP_START feature allows the UART continue
    *  receiving data bytes properly. The GPIO interrupt does not track in the
    *  active mode therefore requires to be cleared by this API.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ESP_UartSaveConfig(void)
    {
        /* Clear interrupt activity:
        *  - set skip start and disable RX. At GPIO wakeup RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers during normal operation.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        ESP_UART_RX_CTRL_REG |= ESP_UART_RX_CTRL_SKIP_START;

    #if(ESP_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(ESP_MOSI_SCL_RX_WAKE_PIN)
            (void) ESP_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt();
        #endif /* (ESP_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(ESP_UART_RX_WAKE_PIN)
            (void) ESP_rx_wake_ClearInterrupt();
        #endif /* (ESP_UART_RX_WAKE_PIN) */
    #endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */

    #if(ESP_UART_RX_WAKEUP_IRQ)
        ESP_RxWakeClearPendingInt();
        ESP_RxWakeEnableInt();
    #endif /* (ESP_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: ESP_UartRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ESP_UartRestoreConfig(void)
    {
    /* Disable RX GPIO interrupt: no more triggers in active mode */
    #if(ESP_UART_RX_WAKEUP_IRQ)
        ESP_RxWakeDisableInt();
    #endif /* (ESP_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (ESP_UART_WAKE_ENABLE_CONST) */


#if(ESP_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: ESP_UART_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
    *  event. This event is configured to trigger on a falling edge of the RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    CY_ISR(ESP_UART_WAKEUP_ISR)
    {
    #ifdef ESP_UART_WAKEUP_ISR_ENTRY_CALLBACK
        ESP_UART_WAKEUP_ISR_EntryCallback();
    #endif /* ESP_UART_WAKEUP_ISR_ENTRY_CALLBACK */

        /* Clear interrupt source: the event becomes multi triggered and is
        * only disabled by ESP_UartRestoreConfig() call.
        */
    #if(ESP_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(ESP_MOSI_SCL_RX_WAKE_PIN)
            (void) ESP_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt();
        #endif /* (ESP_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(ESP_UART_RX_WAKE_PIN)
            (void) ESP_rx_wake_ClearInterrupt();
        #endif /* (ESP_UART_RX_WAKE_PIN) */
    #endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */

    #ifdef ESP_UART_WAKEUP_ISR_EXIT_CALLBACK
        ESP_UART_WAKEUP_ISR_ExitCallback();
    #endif /* ESP_UART_WAKEUP_ISR_EXIT_CALLBACK */
    }
#endif /* (ESP_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
