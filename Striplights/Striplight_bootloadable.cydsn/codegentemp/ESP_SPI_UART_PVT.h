/*******************************************************************************
* File Name: ESP_SPI_UART_PVT.h
* Version 3.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
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

#if !defined(CY_SCB_SPI_UART_PVT_ESP_H)
#define CY_SCB_SPI_UART_PVT_ESP_H

#include "ESP_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (ESP_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  ESP_rxBufferHead;
    extern volatile uint32  ESP_rxBufferTail;
    extern volatile uint8   ESP_rxBufferOverflow;
#endif /* (ESP_INTERNAL_RX_SW_BUFFER_CONST) */

#if (ESP_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  ESP_txBufferHead;
    extern volatile uint32  ESP_txBufferTail;
#endif /* (ESP_INTERNAL_TX_SW_BUFFER_CONST) */

#if (ESP_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 ESP_rxBufferInternal[ESP_INTERNAL_RX_BUFFER_SIZE];
#endif /* (ESP_INTERNAL_RX_SW_BUFFER) */

#if (ESP_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 ESP_txBufferInternal[ESP_TX_BUFFER_SIZE];
#endif /* (ESP_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void ESP_SpiPostEnable(void);
void ESP_SpiStop(void);

#if (ESP_SCB_MODE_SPI_CONST_CFG)
    void ESP_SpiInit(void);
#endif /* (ESP_SCB_MODE_SPI_CONST_CFG) */

#if (ESP_SPI_WAKE_ENABLE_CONST)
    void ESP_SpiSaveConfig(void);
    void ESP_SpiRestoreConfig(void);
#endif /* (ESP_SPI_WAKE_ENABLE_CONST) */

void ESP_UartPostEnable(void);
void ESP_UartStop(void);

#if (ESP_SCB_MODE_UART_CONST_CFG)
    void ESP_UartInit(void);
#endif /* (ESP_SCB_MODE_UART_CONST_CFG) */

#if (ESP_UART_WAKE_ENABLE_CONST)
    void ESP_UartSaveConfig(void);
    void ESP_UartRestoreConfig(void);
#endif /* (ESP_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in ESP_SetPins() */
#define ESP_UART_RX_PIN_ENABLE    (ESP_UART_RX)
#define ESP_UART_TX_PIN_ENABLE    (ESP_UART_TX)

/* UART RTS and CTS position to be used in  ESP_SetPins() */
#define ESP_UART_RTS_PIN_ENABLE    (0x10u)
#define ESP_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define ESP_SpiUartEnableIntRx(intSourceMask)  ESP_SetRxInterruptMode(intSourceMask)
#define ESP_SpiUartEnableIntTx(intSourceMask)  ESP_SetTxInterruptMode(intSourceMask)
uint32  ESP_SpiUartDisableIntRx(void);
uint32  ESP_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_ESP_H) */


/* [] END OF FILE */
