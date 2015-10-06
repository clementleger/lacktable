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

#if !defined(CY_SCB_PVT_ESP_H)
#define CY_SCB_PVT_ESP_H

#include "ESP.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define ESP_SetI2CExtClkInterruptMode(interruptMask) ESP_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define ESP_ClearI2CExtClkInterruptSource(interruptMask) ESP_CLEAR_INTR_I2C_EC(interruptMask)
#define ESP_GetI2CExtClkInterruptSource()                (ESP_INTR_I2C_EC_REG)
#define ESP_GetI2CExtClkInterruptMode()                  (ESP_INTR_I2C_EC_MASK_REG)
#define ESP_GetI2CExtClkInterruptSourceMasked()          (ESP_INTR_I2C_EC_MASKED_REG)

#if (!ESP_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define ESP_SetSpiExtClkInterruptMode(interruptMask) \
                                                                ESP_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define ESP_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                ESP_CLEAR_INTR_SPI_EC(interruptMask)
    #define ESP_GetExtSpiClkInterruptSource()                 (ESP_INTR_SPI_EC_REG)
    #define ESP_GetExtSpiClkInterruptMode()                   (ESP_INTR_SPI_EC_MASK_REG)
    #define ESP_GetExtSpiClkInterruptSourceMasked()           (ESP_INTR_SPI_EC_MASKED_REG)
#endif /* (!ESP_CY_SCBIP_V1) */

#if(ESP_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void ESP_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (ESP_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_ESP_CUSTOM_INTR_HANDLER)
    extern cyisraddress ESP_customIntrHandler;
#endif /* !defined (CY_REMOVE_ESP_CUSTOM_INTR_HANDLER) */
#endif /* (ESP_SCB_IRQ_INTERNAL) */

extern ESP_BACKUP_STRUCT ESP_backup;

#if(ESP_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 ESP_scbMode;
    extern uint8 ESP_scbEnableWake;
    extern uint8 ESP_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 ESP_mode;
    extern uint8 ESP_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * ESP_rxBuffer;
    extern uint8   ESP_rxDataBits;
    extern uint32  ESP_rxBufferSize;

    extern volatile uint8 * ESP_txBuffer;
    extern uint8   ESP_txDataBits;
    extern uint32  ESP_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 ESP_numberOfAddr;
    extern uint8 ESP_subAddrSize;
#endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(ESP_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define ESP_SCB_MODE_I2C_RUNTM_CFG     (ESP_SCB_MODE_I2C      == ESP_scbMode)
    #define ESP_SCB_MODE_SPI_RUNTM_CFG     (ESP_SCB_MODE_SPI      == ESP_scbMode)
    #define ESP_SCB_MODE_UART_RUNTM_CFG    (ESP_SCB_MODE_UART     == ESP_scbMode)
    #define ESP_SCB_MODE_EZI2C_RUNTM_CFG   (ESP_SCB_MODE_EZI2C    == ESP_scbMode)
    #define ESP_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (ESP_SCB_MODE_UNCONFIG == ESP_scbMode)

    /* Defines wakeup enable */
    #define ESP_SCB_WAKE_ENABLE_CHECK       (0u != ESP_scbEnableWake)
#endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!ESP_CY_SCBIP_V1)
    #define ESP_SCB_PINS_NUMBER    (7u)
#else
    #define ESP_SCB_PINS_NUMBER    (2u)
#endif /* (!ESP_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_ESP_H) */


/* [] END OF FILE */
