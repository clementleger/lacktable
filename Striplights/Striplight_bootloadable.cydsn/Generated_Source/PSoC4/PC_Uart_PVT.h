/*******************************************************************************
* File Name: .h
* Version 3.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_PC_Uart_H)
#define CY_SCB_PVT_PC_Uart_H

#include "PC_Uart.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define PC_Uart_SetI2CExtClkInterruptMode(interruptMask) PC_Uart_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define PC_Uart_ClearI2CExtClkInterruptSource(interruptMask) PC_Uart_CLEAR_INTR_I2C_EC(interruptMask)
#define PC_Uart_GetI2CExtClkInterruptSource()                (PC_Uart_INTR_I2C_EC_REG)
#define PC_Uart_GetI2CExtClkInterruptMode()                  (PC_Uart_INTR_I2C_EC_MASK_REG)
#define PC_Uart_GetI2CExtClkInterruptSourceMasked()          (PC_Uart_INTR_I2C_EC_MASKED_REG)

#if (!PC_Uart_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define PC_Uart_SetSpiExtClkInterruptMode(interruptMask) \
                                                                PC_Uart_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define PC_Uart_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                PC_Uart_CLEAR_INTR_SPI_EC(interruptMask)
    #define PC_Uart_GetExtSpiClkInterruptSource()                 (PC_Uart_INTR_SPI_EC_REG)
    #define PC_Uart_GetExtSpiClkInterruptMode()                   (PC_Uart_INTR_SPI_EC_MASK_REG)
    #define PC_Uart_GetExtSpiClkInterruptSourceMasked()           (PC_Uart_INTR_SPI_EC_MASKED_REG)
#endif /* (!PC_Uart_CY_SCBIP_V1) */

#if(PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void PC_Uart_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (PC_Uart_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_PC_Uart_CUSTOM_INTR_HANDLER)
    extern cyisraddress PC_Uart_customIntrHandler;
#endif /* !defined (CY_REMOVE_PC_Uart_CUSTOM_INTR_HANDLER) */
#endif /* (PC_Uart_SCB_IRQ_INTERNAL) */

extern PC_Uart_BACKUP_STRUCT PC_Uart_backup;

#if(PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 PC_Uart_scbMode;
    extern uint8 PC_Uart_scbEnableWake;
    extern uint8 PC_Uart_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 PC_Uart_mode;
    extern uint8 PC_Uart_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * PC_Uart_rxBuffer;
    extern uint8   PC_Uart_rxDataBits;
    extern uint32  PC_Uart_rxBufferSize;

    extern volatile uint8 * PC_Uart_txBuffer;
    extern uint8   PC_Uart_txDataBits;
    extern uint32  PC_Uart_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 PC_Uart_numberOfAddr;
    extern uint8 PC_Uart_subAddrSize;
#endif /* (PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define PC_Uart_SCB_MODE_I2C_RUNTM_CFG     (PC_Uart_SCB_MODE_I2C      == PC_Uart_scbMode)
    #define PC_Uart_SCB_MODE_SPI_RUNTM_CFG     (PC_Uart_SCB_MODE_SPI      == PC_Uart_scbMode)
    #define PC_Uart_SCB_MODE_UART_RUNTM_CFG    (PC_Uart_SCB_MODE_UART     == PC_Uart_scbMode)
    #define PC_Uart_SCB_MODE_EZI2C_RUNTM_CFG   (PC_Uart_SCB_MODE_EZI2C    == PC_Uart_scbMode)
    #define PC_Uart_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (PC_Uart_SCB_MODE_UNCONFIG == PC_Uart_scbMode)

    /* Defines wakeup enable */
    #define PC_Uart_SCB_WAKE_ENABLE_CHECK       (0u != PC_Uart_scbEnableWake)
#endif /* (PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_SCB_PINS_NUMBER    (7u)
#else
    #define PC_Uart_SCB_PINS_NUMBER    (2u)
#endif /* (!PC_Uart_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_PC_Uart_H) */


/* [] END OF FILE */
