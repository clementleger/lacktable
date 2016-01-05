/*******************************************************************************
* File Name: PC_Uart_BOOT.h
* Version 3.0
*
* Description:
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_PC_Uart_H)
#define CY_SCB_BOOT_PC_Uart_H

#include "PC_Uart_PVT.h"

#if (PC_Uart_SCB_MODE_I2C_INC)
    #include "PC_Uart_I2C.h"
#endif /* (PC_Uart_SCB_MODE_I2C_INC) */

#if (PC_Uart_SCB_MODE_EZI2C_INC)
    #include "PC_Uart_EZI2C.h"
#endif /* (PC_Uart_SCB_MODE_EZI2C_INC) */

#if (PC_Uart_SCB_MODE_SPI_INC || PC_Uart_SCB_MODE_UART_INC)
    #include "PC_Uart_SPI_UART.h"
#endif /* (PC_Uart_SCB_MODE_SPI_INC || PC_Uart_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define PC_Uart_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_PC_Uart) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (PC_Uart_SCB_MODE_I2C_INC)
    #define PC_Uart_I2C_BTLDR_COMM_ENABLED     (PC_Uart_BTLDR_COMM_ENABLED && \
                                                            (PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             PC_Uart_I2C_SLAVE_CONST))
#else
     #define PC_Uart_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (PC_Uart_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (PC_Uart_SCB_MODE_EZI2C_INC)
    #define PC_Uart_EZI2C_BTLDR_COMM_ENABLED   (PC_Uart_BTLDR_COMM_ENABLED && \
                                                         PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define PC_Uart_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (PC_Uart_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (PC_Uart_SCB_MODE_SPI_INC)
    #define PC_Uart_SPI_BTLDR_COMM_ENABLED     (PC_Uart_BTLDR_COMM_ENABLED && \
                                                            (PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             PC_Uart_SPI_SLAVE_CONST))
#else
        #define PC_Uart_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (PC_Uart_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (PC_Uart_SCB_MODE_UART_INC)
       #define PC_Uart_UART_BTLDR_COMM_ENABLED    (PC_Uart_BTLDR_COMM_ENABLED && \
                                                            (PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (PC_Uart_UART_RX_DIRECTION && \
                                                              PC_Uart_UART_TX_DIRECTION)))
#else
     #define PC_Uart_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (PC_Uart_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define PC_Uart_BTLDR_COMM_MODE_ENABLED    (PC_Uart_I2C_BTLDR_COMM_ENABLED   || \
                                                     PC_Uart_SPI_BTLDR_COMM_ENABLED   || \
                                                     PC_Uart_EZI2C_BTLDR_COMM_ENABLED || \
                                                     PC_Uart_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (PC_Uart_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void PC_Uart_I2CCyBtldrCommStart(void);
    void PC_Uart_I2CCyBtldrCommStop (void);
    void PC_Uart_I2CCyBtldrCommReset(void);
    cystatus PC_Uart_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus PC_Uart_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (PC_Uart_SCB_MODE_I2C_CONST_CFG)
        #define PC_Uart_CyBtldrCommStart   PC_Uart_I2CCyBtldrCommStart
        #define PC_Uart_CyBtldrCommStop    PC_Uart_I2CCyBtldrCommStop
        #define PC_Uart_CyBtldrCommReset   PC_Uart_I2CCyBtldrCommReset
        #define PC_Uart_CyBtldrCommRead    PC_Uart_I2CCyBtldrCommRead
        #define PC_Uart_CyBtldrCommWrite   PC_Uart_I2CCyBtldrCommWrite
    #endif /* (PC_Uart_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (PC_Uart_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (PC_Uart_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void PC_Uart_EzI2CCyBtldrCommStart(void);
    void PC_Uart_EzI2CCyBtldrCommStop (void);
    void PC_Uart_EzI2CCyBtldrCommReset(void);
    cystatus PC_Uart_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus PC_Uart_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (PC_Uart_SCB_MODE_EZI2C_CONST_CFG)
        #define PC_Uart_CyBtldrCommStart   PC_Uart_EzI2CCyBtldrCommStart
        #define PC_Uart_CyBtldrCommStop    PC_Uart_EzI2CCyBtldrCommStop
        #define PC_Uart_CyBtldrCommReset   PC_Uart_EzI2CCyBtldrCommReset
        #define PC_Uart_CyBtldrCommRead    PC_Uart_EzI2CCyBtldrCommRead
        #define PC_Uart_CyBtldrCommWrite   PC_Uart_EzI2CCyBtldrCommWrite
    #endif /* (PC_Uart_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (PC_Uart_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (PC_Uart_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void PC_Uart_SpiCyBtldrCommStart(void);
    void PC_Uart_SpiCyBtldrCommStop (void);
    void PC_Uart_SpiCyBtldrCommReset(void);
    cystatus PC_Uart_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus PC_Uart_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (PC_Uart_SCB_MODE_SPI_CONST_CFG)
        #define PC_Uart_CyBtldrCommStart   PC_Uart_SpiCyBtldrCommStart
        #define PC_Uart_CyBtldrCommStop    PC_Uart_SpiCyBtldrCommStop
        #define PC_Uart_CyBtldrCommReset   PC_Uart_SpiCyBtldrCommReset
        #define PC_Uart_CyBtldrCommRead    PC_Uart_SpiCyBtldrCommRead
        #define PC_Uart_CyBtldrCommWrite   PC_Uart_SpiCyBtldrCommWrite
    #endif /* (PC_Uart_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (PC_Uart_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (PC_Uart_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void PC_Uart_UartCyBtldrCommStart(void);
    void PC_Uart_UartCyBtldrCommStop (void);
    void PC_Uart_UartCyBtldrCommReset(void);
    cystatus PC_Uart_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus PC_Uart_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (PC_Uart_SCB_MODE_UART_CONST_CFG)
        #define PC_Uart_CyBtldrCommStart   PC_Uart_UartCyBtldrCommStart
        #define PC_Uart_CyBtldrCommStop    PC_Uart_UartCyBtldrCommStop
        #define PC_Uart_CyBtldrCommReset   PC_Uart_UartCyBtldrCommReset
        #define PC_Uart_CyBtldrCommRead    PC_Uart_UartCyBtldrCommRead
        #define PC_Uart_CyBtldrCommWrite   PC_Uart_UartCyBtldrCommWrite
    #endif /* (PC_Uart_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (PC_Uart_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (PC_Uart_BTLDR_COMM_ENABLED)
    #if (PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void PC_Uart_CyBtldrCommStart(void);
        void PC_Uart_CyBtldrCommStop (void);
        void PC_Uart_CyBtldrCommReset(void);
        cystatus PC_Uart_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus PC_Uart_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_PC_Uart)
        #define CyBtldrCommStart    PC_Uart_CyBtldrCommStart
        #define CyBtldrCommStop     PC_Uart_CyBtldrCommStop
        #define CyBtldrCommReset    PC_Uart_CyBtldrCommReset
        #define CyBtldrCommWrite    PC_Uart_CyBtldrCommWrite
        #define CyBtldrCommRead     PC_Uart_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_PC_Uart) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (PC_Uart_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define PC_Uart_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define PC_Uart_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define PC_Uart_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define PC_Uart_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef PC_Uart_SPI_BYTE_TO_BYTE
    #define PC_Uart_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef PC_Uart_UART_BYTE_TO_BYTE
    #define PC_Uart_UART_BYTE_TO_BYTE  (171u)
#endif /* PC_Uart_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_PC_Uart_H) */


/* [] END OF FILE */
