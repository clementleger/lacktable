/*******************************************************************************
* File Name: ESP.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component.
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

#if (ESP_SCB_MODE_I2C_INC)
    #include "ESP_I2C_PVT.h"
#endif /* (ESP_SCB_MODE_I2C_INC) */

#if (ESP_SCB_MODE_EZI2C_INC)
    #include "ESP_EZI2C_PVT.h"
#endif /* (ESP_SCB_MODE_EZI2C_INC) */

#if (ESP_SCB_MODE_SPI_INC || ESP_SCB_MODE_UART_INC)
    #include "ESP_SPI_UART_PVT.h"
#endif /* (ESP_SCB_MODE_SPI_INC || ESP_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (ESP_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 ESP_scbMode = ESP_SCB_MODE_UNCONFIG;
    uint8 ESP_scbEnableWake;
    uint8 ESP_scbEnableIntr;

    /* I2C configuration variables */
    uint8 ESP_mode;
    uint8 ESP_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * ESP_rxBuffer;
    uint8  ESP_rxDataBits;
    uint32 ESP_rxBufferSize;

    volatile uint8 * ESP_txBuffer;
    uint8  ESP_txDataBits;
    uint32 ESP_txBufferSize;

    /* EZI2C configuration variables */
    uint8 ESP_numberOfAddr;
    uint8 ESP_subAddrSize;
#endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 ESP_initVar = 0u;

#if (ESP_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_ESP_CUSTOM_INTR_HANDLER)
    void (*ESP_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_ESP_CUSTOM_INTR_HANDLER) */
#endif /* (ESP_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void ESP_ScbEnableIntr(void);
static void ESP_ScbModeStop(void);
static void ESP_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: ESP_Init
********************************************************************************
*
* Summary:
*  Initializes the SCB component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  SCB_I2CInit, SCB_SpiInit, SCB_UartInit or SCB_EzI2CInit.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ESP_Init(void)
{
#if (ESP_SCB_MODE_UNCONFIG_CONST_CFG)
    if (ESP_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        ESP_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (ESP_SCB_MODE_I2C_CONST_CFG)
    ESP_I2CInit();

#elif (ESP_SCB_MODE_SPI_CONST_CFG)
    ESP_SpiInit();

#elif (ESP_SCB_MODE_UART_CONST_CFG)
    ESP_UartInit();

#elif (ESP_SCB_MODE_EZI2C_CONST_CFG)
    ESP_EzI2CInit();

#endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ESP_Enable
********************************************************************************
*
* Summary:
*  Enables the SCB component operation.
*  The SCB configuration should be not changed when the component is enabled.
*  Any configuration changes should be made after disabling the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ESP_Enable(void)
{
#if (ESP_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!ESP_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        ESP_CTRL_REG |= ESP_CTRL_ENABLED;

        ESP_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        ESP_ScbModePostEnable();
    }
#else
    ESP_CTRL_REG |= ESP_CTRL_ENABLED;

    ESP_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    ESP_ScbModePostEnable();
#endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ESP_Start
********************************************************************************
*
* Summary:
*  Invokes SCB_Init() and SCB_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZ I2C. Otherwise this function does not enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ESP_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void ESP_Start(void)
{
    if (0u == ESP_initVar)
    {
        ESP_Init();
        ESP_initVar = 1u; /* Component was initialized */
    }

    ESP_Enable();
}


/*******************************************************************************
* Function Name: ESP_Stop
********************************************************************************
*
* Summary:
*  Disables the SCB component and its interrupt.
*  It also disables all TX interrupt sources so as not to cause an unexpected
*  interrupt trigger because after the component is enabled, the TX FIFO 
*  is empty.
*
* Parameters:
*  None
*
* Return:
*  None
* 
*******************************************************************************/
void ESP_Stop(void)
{
#if (ESP_SCB_IRQ_INTERNAL)
    ESP_DisableInt();
#endif /* (ESP_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    ESP_ScbModeStop();

    /* Disable SCB IP */
    ESP_CTRL_REG &= (uint32) ~ESP_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger because after the component is enabled, the TX FIFO
    * is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when they are disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    ESP_SetTxInterruptMode(ESP_NO_INTR_SOURCES);

#if (ESP_SCB_IRQ_INTERNAL)
    ESP_ClearPendingInt();
#endif /* (ESP_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: ESP_SetRxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the RX FIFO to generate RX level interrupt.
*         The range of valid level values is between 0 and RX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void ESP_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = ESP_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~ESP_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (ESP_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    ESP_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: ESP_SetTxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has more entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the TX FIFO to generate TX level interrupt.
*         The range of valid level values is between 0 and TX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void ESP_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = ESP_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~ESP_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (ESP_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    ESP_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (ESP_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: ESP_SetCustomInterruptHandler
    ********************************************************************************
    *
    * Summary:
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    * Parameters:
    *  func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ESP_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_ESP_CUSTOM_INTR_HANDLER)
        ESP_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_ESP_CUSTOM_INTR_HANDLER) */
    }
#endif /* (ESP_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: ESP_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Enables an interrupt for a specific mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void ESP_ScbEnableIntr(void)
{
#if (ESP_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (ESP_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != ESP_scbEnableIntr)
        {
            ESP_EnableInt();
        }

    #else
        ESP_EnableInt();

    #endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (ESP_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: ESP_ScbModePostEnable
********************************************************************************
*
* Summary:
*  Calls the PostEnable function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void ESP_ScbModePostEnable(void)
{
#if (ESP_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!ESP_CY_SCBIP_V1)
    if (ESP_SCB_MODE_SPI_RUNTM_CFG)
    {
        ESP_SpiPostEnable();
    }
    else if (ESP_SCB_MODE_UART_RUNTM_CFG)
    {
        ESP_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!ESP_CY_SCBIP_V1) */

#elif (ESP_SCB_MODE_SPI_CONST_CFG)
    ESP_SpiPostEnable();

#elif (ESP_SCB_MODE_UART_CONST_CFG)
    ESP_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ESP_ScbModeStop
********************************************************************************
*
* Summary:
*  Calls the Stop function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void ESP_ScbModeStop(void)
{
#if (ESP_SCB_MODE_UNCONFIG_CONST_CFG)
    if (ESP_SCB_MODE_I2C_RUNTM_CFG)
    {
        ESP_I2CStop();
    }
    else if (ESP_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        ESP_EzI2CStop();
    }
#if (!ESP_CY_SCBIP_V1)
    else if (ESP_SCB_MODE_SPI_RUNTM_CFG)
    {
        ESP_SpiStop();
    }
    else if (ESP_SCB_MODE_UART_RUNTM_CFG)
    {
        ESP_UartStop();
    }
#endif /* (!ESP_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (ESP_SCB_MODE_I2C_CONST_CFG)
    ESP_I2CStop();

#elif (ESP_SCB_MODE_EZI2C_CONST_CFG)
    ESP_EzI2CStop();

#elif (ESP_SCB_MODE_SPI_CONST_CFG)
    ESP_SpiStop();

#elif (ESP_SCB_MODE_UART_CONST_CFG)
    ESP_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (ESP_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: ESP_SetPins
    ********************************************************************************
    *
    * Summary:
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    * Parameters:
    *  mode:      Mode of SCB operation.
    *  subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ESP_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 hsiomSel [ESP_SCB_PINS_NUMBER];
        uint32 pinsDm   [ESP_SCB_PINS_NUMBER];

    #if (!ESP_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!ESP_CY_SCBIP_V1) */

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < ESP_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = ESP_HSIOM_DEF_SEL;
            pinsDm[i]    = ESP_PIN_DM_ALG_HIZ;
        }

        if ((ESP_SCB_MODE_I2C   == mode) ||
           (ESP_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[ESP_RX_SCL_MOSI_PIN_INDEX] = ESP_HSIOM_I2C_SEL;
            hsiomSel[ESP_TX_SDA_MISO_PIN_INDEX] = ESP_HSIOM_I2C_SEL;

            pinsDm[ESP_RX_SCL_MOSI_PIN_INDEX] = ESP_PIN_DM_OD_LO;
            pinsDm[ESP_TX_SDA_MISO_PIN_INDEX] = ESP_PIN_DM_OD_LO;
        }
    #if (!ESP_CY_SCBIP_V1)
        else if (ESP_SCB_MODE_SPI == mode)
        {
            hsiomSel[ESP_RX_SCL_MOSI_PIN_INDEX] = ESP_HSIOM_SPI_SEL;
            hsiomSel[ESP_TX_SDA_MISO_PIN_INDEX] = ESP_HSIOM_SPI_SEL;
            hsiomSel[ESP_SCLK_PIN_INDEX] = ESP_HSIOM_SPI_SEL;

            if (ESP_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[ESP_RX_SCL_MOSI_PIN_INDEX] = ESP_PIN_DM_DIG_HIZ;
                pinsDm[ESP_TX_SDA_MISO_PIN_INDEX] = ESP_PIN_DM_STRONG;
                pinsDm[ESP_SCLK_PIN_INDEX] = ESP_PIN_DM_DIG_HIZ;

            #if (ESP_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[ESP_SS0_PIN_INDEX] = ESP_HSIOM_SPI_SEL;
                pinsDm  [ESP_SS0_PIN_INDEX] = ESP_PIN_DM_DIG_HIZ;
            #endif /* (ESP_SS0_PIN) */

            #if (ESP_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= ESP_TX_SDA_MISO_PIN_MASK;
            #endif /* (ESP_TX_SDA_MISO_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[ESP_RX_SCL_MOSI_PIN_INDEX] = ESP_PIN_DM_STRONG;
                pinsDm[ESP_TX_SDA_MISO_PIN_INDEX] = ESP_PIN_DM_DIG_HIZ;
                pinsDm[ESP_SCLK_PIN_INDEX] = ESP_PIN_DM_STRONG;

            #if (ESP_SS0_PIN)
                hsiomSel [ESP_SS0_PIN_INDEX] = ESP_HSIOM_SPI_SEL;
                pinsDm   [ESP_SS0_PIN_INDEX] = ESP_PIN_DM_STRONG;
                pinsInBuf |= ESP_SS0_PIN_MASK;
            #endif /* (ESP_SS0_PIN) */

            #if (ESP_SS1_PIN)
                hsiomSel [ESP_SS1_PIN_INDEX] = ESP_HSIOM_SPI_SEL;
                pinsDm   [ESP_SS1_PIN_INDEX] = ESP_PIN_DM_STRONG;
                pinsInBuf |= ESP_SS1_PIN_MASK;
            #endif /* (ESP_SS1_PIN) */

            #if (ESP_SS2_PIN)
                hsiomSel [ESP_SS2_PIN_INDEX] = ESP_HSIOM_SPI_SEL;
                pinsDm   [ESP_SS2_PIN_INDEX] = ESP_PIN_DM_STRONG;
                pinsInBuf |= ESP_SS2_PIN_MASK;
            #endif /* (ESP_SS2_PIN) */

            #if (ESP_SS3_PIN)
                hsiomSel [ESP_SS3_PIN_INDEX] = ESP_HSIOM_SPI_SEL;
                pinsDm   [ESP_SS3_PIN_INDEX] = ESP_PIN_DM_STRONG;
                pinsInBuf |= ESP_SS3_PIN_MASK;
            #endif /* (ESP_SS3_PIN) */

                /* Disable input buffers */
            #if (ESP_RX_SCL_MOSI_PIN)
                pinsInBuf |= ESP_RX_SCL_MOSI_PIN_MASK;
            #endif /* (ESP_RX_SCL_MOSI_PIN) */

             #if (ESP_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= ESP_RX_WAKE_SCL_MOSI_PIN_MASK;
            #endif /* (ESP_RX_WAKE_SCL_MOSI_PIN) */

            #if (ESP_SCLK_PIN)
                pinsInBuf |= ESP_SCLK_PIN_MASK;
            #endif /* (ESP_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (ESP_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[ESP_TX_SDA_MISO_PIN_INDEX] = ESP_HSIOM_UART_SEL;
                pinsDm  [ESP_TX_SDA_MISO_PIN_INDEX] = ESP_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if (0u != (ESP_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[ESP_RX_SCL_MOSI_PIN_INDEX] = ESP_HSIOM_UART_SEL;
                    pinsDm  [ESP_RX_SCL_MOSI_PIN_INDEX] = ESP_PIN_DM_DIG_HIZ;
                }

                if (0u != (ESP_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[ESP_TX_SDA_MISO_PIN_INDEX] = ESP_HSIOM_UART_SEL;
                    pinsDm  [ESP_TX_SDA_MISO_PIN_INDEX] = ESP_PIN_DM_STRONG;

                #if (ESP_TX_SDA_MISO_PIN)
                     pinsInBuf |= ESP_TX_SDA_MISO_PIN_MASK;
                #endif /* (ESP_TX_SDA_MISO_PIN) */
                }

            #if !(ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1)
                if (ESP_UART_MODE_STD == subMode)
                {
                    if (0u != (ESP_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                        hsiomSel[ESP_SCLK_PIN_INDEX] = ESP_HSIOM_UART_SEL;
                        pinsDm  [ESP_SCLK_PIN_INDEX] = ESP_PIN_DM_DIG_HIZ;
                    }

                    if (0u != (ESP_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                        hsiomSel[ESP_SS0_PIN_INDEX] = ESP_HSIOM_UART_SEL;
                        pinsDm  [ESP_SS0_PIN_INDEX] = ESP_PIN_DM_STRONG;

                    #if (ESP_SS0_PIN)
                        /* Disable input buffer */
                        pinsInBuf |= ESP_SS0_PIN_MASK;
                    #endif /* (ESP_SS0_PIN) */
                    }
                }
            #endif /* !(ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1) */
            }
        }
    #endif /* (!ESP_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (ESP_RX_WAKE_SCL_MOSI_PIN)
        ESP_SET_HSIOM_SEL(ESP_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       ESP_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       ESP_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[ESP_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        ESP_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[ESP_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        ESP_SET_INP_DIS(ESP_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     ESP_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & ESP_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        ESP_SET_INCFG_TYPE(ESP_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        ESP_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        ESP_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        ESP_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (ESP_RX_WAKE_SCL_MOSI_PIN) */

    #if (ESP_RX_SCL_MOSI_PIN)
        ESP_SET_HSIOM_SEL(ESP_RX_SCL_MOSI_HSIOM_REG,
                                       ESP_RX_SCL_MOSI_HSIOM_MASK,
                                       ESP_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[ESP_RX_SCL_MOSI_PIN_INDEX]);

        ESP_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[ESP_RX_SCL_MOSI_PIN_INDEX]);

    #if (!ESP_CY_SCBIP_V1)
        ESP_SET_INP_DIS(ESP_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                     ESP_uart_rx_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & ESP_RX_SCL_MOSI_PIN_MASK)));
    #endif /* (!ESP_CY_SCBIP_V1) */
    #endif /* (ESP_RX_SCL_MOSI_PIN) */

    #if (ESP_TX_SDA_MISO_PIN)
        ESP_SET_HSIOM_SEL(ESP_TX_SDA_MISO_HSIOM_REG,
                                       ESP_TX_SDA_MISO_HSIOM_MASK,
                                       ESP_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[ESP_TX_SDA_MISO_PIN_INDEX]);

        ESP_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[ESP_TX_SDA_MISO_PIN_INDEX]);

    #if (!ESP_CY_SCBIP_V1)
        ESP_SET_INP_DIS(ESP_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     ESP_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & ESP_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!ESP_CY_SCBIP_V1) */
    #endif /* (ESP_RX_SCL_MOSI_PIN) */

    #if (ESP_SCLK_PIN)
        ESP_SET_HSIOM_SEL(ESP_SCLK_HSIOM_REG,
                                       ESP_SCLK_HSIOM_MASK,
                                       ESP_SCLK_HSIOM_POS,
                                       hsiomSel[ESP_SCLK_PIN_INDEX]);

        ESP_spi_sclk_SetDriveMode((uint8) pinsDm[ESP_SCLK_PIN_INDEX]);

        ESP_SET_INP_DIS(ESP_spi_sclk_INP_DIS,
                                     ESP_spi_sclk_MASK,
                                     (0u != (pinsInBuf & ESP_SCLK_PIN_MASK)));
    #endif /* (ESP_SCLK_PIN) */

    #if (ESP_SS0_PIN)
        ESP_SET_HSIOM_SEL(ESP_SS0_HSIOM_REG,
                                       ESP_SS0_HSIOM_MASK,
                                       ESP_SS0_HSIOM_POS,
                                       hsiomSel[ESP_SS0_PIN_INDEX]);

        ESP_spi_ss0_SetDriveMode((uint8) pinsDm[ESP_SS0_PIN_INDEX]);

        ESP_SET_INP_DIS(ESP_spi_ss0_INP_DIS,
                                     ESP_spi_ss0_MASK,
                                     (0u != (pinsInBuf & ESP_SS0_PIN_MASK)));
    #endif /* (ESP_SS0_PIN) */

    #if (ESP_SS1_PIN)
        ESP_SET_HSIOM_SEL(ESP_SS1_HSIOM_REG,
                                       ESP_SS1_HSIOM_MASK,
                                       ESP_SS1_HSIOM_POS,
                                       hsiomSel[ESP_SS1_PIN_INDEX]);

        ESP_spi_ss1_SetDriveMode((uint8) pinsDm[ESP_SS1_PIN_INDEX]);

        ESP_SET_INP_DIS(ESP_spi_ss1_INP_DIS,
                                     ESP_spi_ss1_MASK,
                                     (0u != (pinsInBuf & ESP_SS1_PIN_MASK)));
    #endif /* (ESP_SS1_PIN) */

    #if (ESP_SS2_PIN)
        ESP_SET_HSIOM_SEL(ESP_SS2_HSIOM_REG,
                                       ESP_SS2_HSIOM_MASK,
                                       ESP_SS2_HSIOM_POS,
                                       hsiomSel[ESP_SS2_PIN_INDEX]);

        ESP_spi_ss2_SetDriveMode((uint8) pinsDm[ESP_SS2_PIN_INDEX]);

        ESP_SET_INP_DIS(ESP_spi_ss2_INP_DIS,
                                     ESP_spi_ss2_MASK,
                                     (0u != (pinsInBuf & ESP_SS2_PIN_MASK)));
    #endif /* (ESP_SS2_PIN) */

    #if (ESP_SS3_PIN)
        ESP_SET_HSIOM_SEL(ESP_SS3_HSIOM_REG,
                                       ESP_SS3_HSIOM_MASK,
                                       ESP_SS3_HSIOM_POS,
                                       hsiomSel[ESP_SS3_PIN_INDEX]);

        ESP_spi_ss3_SetDriveMode((uint8) pinsDm[ESP_SS3_PIN_INDEX]);

        ESP_SET_INP_DIS(ESP_spi_ss3_INP_DIS,
                                     ESP_spi_ss3_MASK,
                                     (0u != (pinsInBuf & ESP_SS3_PIN_MASK)));
    #endif /* (ESP_SS3_PIN) */
    }

#endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: ESP_I2CSlaveNackGeneration
    ********************************************************************************
    *
    * Summary:
    *  Sets command to generate NACK to the address or data.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ESP_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (ESP_CTRL_REG & ESP_CTRL_EC_AM_MODE)) &&
            (0u == (ESP_I2C_CTRL_REG & ESP_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            ESP_CTRL_REG &= ~ESP_CTRL_EC_AM_MODE;
            ESP_CTRL_REG |=  ESP_CTRL_EC_AM_MODE;
        }

        ESP_I2C_SLAVE_CMD_REG = ESP_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1) */


/* [] END OF FILE */
