/*******************************************************************************
* File Name: ESP_BOOT.h
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

#if !defined(CY_SCB_BOOT_ESP_H)
#define CY_SCB_BOOT_ESP_H

#include "ESP_PVT.h"

#if (ESP_SCB_MODE_I2C_INC)
    #include "ESP_I2C.h"
#endif /* (ESP_SCB_MODE_I2C_INC) */

#if (ESP_SCB_MODE_EZI2C_INC)
    #include "ESP_EZI2C.h"
#endif /* (ESP_SCB_MODE_EZI2C_INC) */

#if (ESP_SCB_MODE_SPI_INC || ESP_SCB_MODE_UART_INC)
    #include "ESP_SPI_UART.h"
#endif /* (ESP_SCB_MODE_SPI_INC || ESP_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define ESP_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ESP) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (ESP_SCB_MODE_I2C_INC)
    #define ESP_I2C_BTLDR_COMM_ENABLED     (ESP_BTLDR_COMM_ENABLED && \
                                                            (ESP_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             ESP_I2C_SLAVE_CONST))
#else
     #define ESP_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (ESP_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (ESP_SCB_MODE_EZI2C_INC)
    #define ESP_EZI2C_BTLDR_COMM_ENABLED   (ESP_BTLDR_COMM_ENABLED && \
                                                         ESP_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define ESP_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (ESP_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (ESP_SCB_MODE_SPI_INC)
    #define ESP_SPI_BTLDR_COMM_ENABLED     (ESP_BTLDR_COMM_ENABLED && \
                                                            (ESP_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             ESP_SPI_SLAVE_CONST))
#else
        #define ESP_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (ESP_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (ESP_SCB_MODE_UART_INC)
       #define ESP_UART_BTLDR_COMM_ENABLED    (ESP_BTLDR_COMM_ENABLED && \
                                                            (ESP_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (ESP_UART_RX_DIRECTION && \
                                                              ESP_UART_TX_DIRECTION)))
#else
     #define ESP_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (ESP_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define ESP_BTLDR_COMM_MODE_ENABLED    (ESP_I2C_BTLDR_COMM_ENABLED   || \
                                                     ESP_SPI_BTLDR_COMM_ENABLED   || \
                                                     ESP_EZI2C_BTLDR_COMM_ENABLED || \
                                                     ESP_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ESP_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void ESP_I2CCyBtldrCommStart(void);
    void ESP_I2CCyBtldrCommStop (void);
    void ESP_I2CCyBtldrCommReset(void);
    cystatus ESP_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus ESP_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (ESP_SCB_MODE_I2C_CONST_CFG)
        #define ESP_CyBtldrCommStart   ESP_I2CCyBtldrCommStart
        #define ESP_CyBtldrCommStop    ESP_I2CCyBtldrCommStop
        #define ESP_CyBtldrCommReset   ESP_I2CCyBtldrCommReset
        #define ESP_CyBtldrCommRead    ESP_I2CCyBtldrCommRead
        #define ESP_CyBtldrCommWrite   ESP_I2CCyBtldrCommWrite
    #endif /* (ESP_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ESP_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ESP_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void ESP_EzI2CCyBtldrCommStart(void);
    void ESP_EzI2CCyBtldrCommStop (void);
    void ESP_EzI2CCyBtldrCommReset(void);
    cystatus ESP_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus ESP_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (ESP_SCB_MODE_EZI2C_CONST_CFG)
        #define ESP_CyBtldrCommStart   ESP_EzI2CCyBtldrCommStart
        #define ESP_CyBtldrCommStop    ESP_EzI2CCyBtldrCommStop
        #define ESP_CyBtldrCommReset   ESP_EzI2CCyBtldrCommReset
        #define ESP_CyBtldrCommRead    ESP_EzI2CCyBtldrCommRead
        #define ESP_CyBtldrCommWrite   ESP_EzI2CCyBtldrCommWrite
    #endif /* (ESP_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ESP_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ESP_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void ESP_SpiCyBtldrCommStart(void);
    void ESP_SpiCyBtldrCommStop (void);
    void ESP_SpiCyBtldrCommReset(void);
    cystatus ESP_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus ESP_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (ESP_SCB_MODE_SPI_CONST_CFG)
        #define ESP_CyBtldrCommStart   ESP_SpiCyBtldrCommStart
        #define ESP_CyBtldrCommStop    ESP_SpiCyBtldrCommStop
        #define ESP_CyBtldrCommReset   ESP_SpiCyBtldrCommReset
        #define ESP_CyBtldrCommRead    ESP_SpiCyBtldrCommRead
        #define ESP_CyBtldrCommWrite   ESP_SpiCyBtldrCommWrite
    #endif /* (ESP_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ESP_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ESP_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void ESP_UartCyBtldrCommStart(void);
    void ESP_UartCyBtldrCommStop (void);
    void ESP_UartCyBtldrCommReset(void);
    cystatus ESP_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus ESP_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (ESP_SCB_MODE_UART_CONST_CFG)
        #define ESP_CyBtldrCommStart   ESP_UartCyBtldrCommStart
        #define ESP_CyBtldrCommStop    ESP_UartCyBtldrCommStop
        #define ESP_CyBtldrCommReset   ESP_UartCyBtldrCommReset
        #define ESP_CyBtldrCommRead    ESP_UartCyBtldrCommRead
        #define ESP_CyBtldrCommWrite   ESP_UartCyBtldrCommWrite
    #endif /* (ESP_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ESP_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ESP_BTLDR_COMM_ENABLED)
    #if (ESP_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void ESP_CyBtldrCommStart(void);
        void ESP_CyBtldrCommStop (void);
        void ESP_CyBtldrCommReset(void);
        cystatus ESP_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus ESP_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ESP)
        #define CyBtldrCommStart    ESP_CyBtldrCommStart
        #define CyBtldrCommStop     ESP_CyBtldrCommStop
        #define CyBtldrCommReset    ESP_CyBtldrCommReset
        #define CyBtldrCommWrite    ESP_CyBtldrCommWrite
        #define CyBtldrCommRead     ESP_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ESP) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ESP_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define ESP_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define ESP_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define ESP_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define ESP_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef ESP_SPI_BYTE_TO_BYTE
    #define ESP_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef ESP_UART_BYTE_TO_BYTE
    #define ESP_UART_BYTE_TO_BYTE  (171u)
#endif /* ESP_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_ESP_H) */


/* [] END OF FILE */
