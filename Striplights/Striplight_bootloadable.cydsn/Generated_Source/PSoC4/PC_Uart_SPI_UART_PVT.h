/*******************************************************************************
* File Name: PC_Uart_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_PC_Uart_H)
#define CY_SCB_SPI_UART_PVT_PC_Uart_H

#include "PC_Uart_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (PC_Uart_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  PC_Uart_rxBufferHead;
    extern volatile uint32  PC_Uart_rxBufferTail;
    extern volatile uint8   PC_Uart_rxBufferOverflow;
#endif /* (PC_Uart_INTERNAL_RX_SW_BUFFER_CONST) */

#if (PC_Uart_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  PC_Uart_txBufferHead;
    extern volatile uint32  PC_Uart_txBufferTail;
#endif /* (PC_Uart_INTERNAL_TX_SW_BUFFER_CONST) */

#if (PC_Uart_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 PC_Uart_rxBufferInternal[PC_Uart_INTERNAL_RX_BUFFER_SIZE];
#endif /* (PC_Uart_INTERNAL_RX_SW_BUFFER) */

#if (PC_Uart_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 PC_Uart_txBufferInternal[PC_Uart_TX_BUFFER_SIZE];
#endif /* (PC_Uart_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void PC_Uart_SpiPostEnable(void);
void PC_Uart_SpiStop(void);

#if (PC_Uart_SCB_MODE_SPI_CONST_CFG)
    void PC_Uart_SpiInit(void);
#endif /* (PC_Uart_SCB_MODE_SPI_CONST_CFG) */

#if (PC_Uart_SPI_WAKE_ENABLE_CONST)
    void PC_Uart_SpiSaveConfig(void);
    void PC_Uart_SpiRestoreConfig(void);
#endif /* (PC_Uart_SPI_WAKE_ENABLE_CONST) */

void PC_Uart_UartPostEnable(void);
void PC_Uart_UartStop(void);

#if (PC_Uart_SCB_MODE_UART_CONST_CFG)
    void PC_Uart_UartInit(void);
#endif /* (PC_Uart_SCB_MODE_UART_CONST_CFG) */

#if (PC_Uart_UART_WAKE_ENABLE_CONST)
    void PC_Uart_UartSaveConfig(void);
    void PC_Uart_UartRestoreConfig(void);
#endif /* (PC_Uart_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in PC_Uart_SetPins() */
#define PC_Uart_UART_RX_PIN_ENABLE    (PC_Uart_UART_RX)
#define PC_Uart_UART_TX_PIN_ENABLE    (PC_Uart_UART_TX)

/* UART RTS and CTS position to be used in  PC_Uart_SetPins() */
#define PC_Uart_UART_RTS_PIN_ENABLE    (0x10u)
#define PC_Uart_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define PC_Uart_SpiUartEnableIntRx(intSourceMask)  PC_Uart_SetRxInterruptMode(intSourceMask)
#define PC_Uart_SpiUartEnableIntTx(intSourceMask)  PC_Uart_SetTxInterruptMode(intSourceMask)
uint32  PC_Uart_SpiUartDisableIntRx(void);
uint32  PC_Uart_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_PC_Uart_H) */


/* [] END OF FILE */
