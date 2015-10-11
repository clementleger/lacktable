/*******************************************************************************
* File Name: ESP_SPI_UART.h
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_ESP_H)
#define CY_SCB_SPI_UART_ESP_H

#include "ESP.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define ESP_SPI_MODE                   (0u)
#define ESP_SPI_SUB_MODE               (0u)
#define ESP_SPI_CLOCK_MODE             (0u)
#define ESP_SPI_OVS_FACTOR             (16u)
#define ESP_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define ESP_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define ESP_SPI_RX_DATA_BITS_NUM       (8u)
#define ESP_SPI_TX_DATA_BITS_NUM       (8u)
#define ESP_SPI_WAKE_ENABLE            (0u)
#define ESP_SPI_BITS_ORDER             (1u)
#define ESP_SPI_TRANSFER_SEPARATION    (1u)
#define ESP_SPI_NUMBER_OF_SS_LINES     (1u)
#define ESP_SPI_RX_BUFFER_SIZE         (8u)
#define ESP_SPI_TX_BUFFER_SIZE         (8u)

#define ESP_SPI_INTERRUPT_MODE         (0u)

#define ESP_SPI_INTR_RX_MASK           (0u)
#define ESP_SPI_INTR_TX_MASK           (0u)

#define ESP_SPI_RX_TRIGGER_LEVEL       (7u)
#define ESP_SPI_TX_TRIGGER_LEVEL       (0u)

#define ESP_SPI_BYTE_MODE_ENABLE       (0u)
#define ESP_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define ESP_SPI_SS0_POLARITY           (0u)
#define ESP_SPI_SS1_POLARITY           (0u)
#define ESP_SPI_SS2_POLARITY           (0u)
#define ESP_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define ESP_UART_SUB_MODE              (0u)
#define ESP_UART_DIRECTION             (3u)
#define ESP_UART_DATA_BITS_NUM         (8u)
#define ESP_UART_PARITY_TYPE           (2u)
#define ESP_UART_STOP_BITS_NUM         (2u)
#define ESP_UART_OVS_FACTOR            (12u)
#define ESP_UART_IRDA_LOW_POWER        (0u)
#define ESP_UART_MEDIAN_FILTER_ENABLE  (0u)
#define ESP_UART_RETRY_ON_NACK         (0u)
#define ESP_UART_IRDA_POLARITY         (0u)
#define ESP_UART_DROP_ON_FRAME_ERR     (0u)
#define ESP_UART_DROP_ON_PARITY_ERR    (0u)
#define ESP_UART_WAKE_ENABLE           (0u)
#define ESP_UART_RX_BUFFER_SIZE        (16u)
#define ESP_UART_TX_BUFFER_SIZE        (8u)
#define ESP_UART_MP_MODE_ENABLE        (0u)
#define ESP_UART_MP_ACCEPT_ADDRESS     (0u)
#define ESP_UART_MP_RX_ADDRESS         (2u)
#define ESP_UART_MP_RX_ADDRESS_MASK    (255u)

#define ESP_UART_INTERRUPT_MODE        (1u)

#define ESP_UART_INTR_RX_MASK          (12u)
#define ESP_UART_INTR_TX_MASK          (0u)

#define ESP_UART_RX_TRIGGER_LEVEL      (7u)
#define ESP_UART_TX_TRIGGER_LEVEL      (0u)

#define ESP_UART_BYTE_MODE_ENABLE      (0u)
#define ESP_UART_CTS_ENABLE            (0u)
#define ESP_UART_CTS_POLARITY          (0u)
#define ESP_UART_RTS_ENABLE            (0u)
#define ESP_UART_RTS_POLARITY          (0u)
#define ESP_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define ESP_SPI_SLAVE  (0u)
#define ESP_SPI_MASTER (1u)

/* UART direction enum */
#define ESP_UART_RX    (1u)
#define ESP_UART_TX    (2u)
#define ESP_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(ESP_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define ESP_SPI_SLAVE_CONST        (1u)
    #define ESP_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define ESP_RX_DIRECTION           (1u)
    #define ESP_TX_DIRECTION           (1u)
    #define ESP_UART_RX_DIRECTION      (1u)
    #define ESP_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define ESP_INTERNAL_RX_SW_BUFFER   (0u)
    #define ESP_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define ESP_INTERNAL_RX_BUFFER_SIZE    (ESP_rxBufferSize + 1u)
    #define ESP_RX_BUFFER_SIZE             (ESP_rxBufferSize)
    #define ESP_TX_BUFFER_SIZE             (ESP_txBufferSize)

    /* Return true if buffer is provided */
    #define ESP_CHECK_RX_SW_BUFFER (NULL != ESP_rxBuffer)
    #define ESP_CHECK_TX_SW_BUFFER (NULL != ESP_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define ESP_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define ESP_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define ESP_SPI_WAKE_ENABLE_CONST  (1u)
    #define ESP_CHECK_SPI_WAKE_ENABLE  (0u != ESP_scbEnableWake)
    #define ESP_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1)
        #define ESP_SPI_UART_FIFO_SIZE             (ESP_FIFO_SIZE)
        #define ESP_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define ESP_SPI_UART_FIFO_SIZE (ESP_GET_FIFO_SIZE(ESP_CTRL_REG & \
                                                                                    ESP_CTRL_BYTE_MODE))

        #define ESP_CHECK_UART_RTS_CONTROL_FLOW \
                    ((ESP_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != ESP_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(ESP_UART_FLOW_CTRL_REG)))
    #endif /* (ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (ESP_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define ESP_SPI_RX_DIRECTION (1u)
        #define ESP_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1)
            #define ESP_SPI_UART_FIFO_SIZE    (ESP_FIFO_SIZE)
        #else
            #define ESP_SPI_UART_FIFO_SIZE \
                                           ESP_GET_FIFO_SIZE(ESP_SPI_BYTE_MODE_ENABLE)

        #endif /* (ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define ESP_INTERNAL_SPI_RX_SW_BUFFER  (ESP_SPI_RX_BUFFER_SIZE > \
                                                                ESP_SPI_UART_FIFO_SIZE)
        #define ESP_INTERNAL_SPI_TX_SW_BUFFER  (ESP_SPI_TX_BUFFER_SIZE > \
                                                                ESP_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define ESP_INTERNAL_RX_SW_BUFFER  (ESP_INTERNAL_SPI_RX_SW_BUFFER)
        #define ESP_INTERNAL_TX_SW_BUFFER  (ESP_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define ESP_INTERNAL_RX_BUFFER_SIZE    (ESP_SPI_RX_BUFFER_SIZE + 1u)
        #define ESP_RX_BUFFER_SIZE             (ESP_SPI_RX_BUFFER_SIZE)
        #define ESP_TX_BUFFER_SIZE             (ESP_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define ESP_SPI_WAKE_ENABLE_CONST  (0u != ESP_SPI_WAKE_ENABLE)
        #define ESP_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define ESP_UART_RX_DIRECTION (0u != (ESP_UART_DIRECTION & ESP_UART_RX))
        #define ESP_UART_TX_DIRECTION (0u != (ESP_UART_DIRECTION & ESP_UART_TX))

        /* Get FIFO size */
        #if (ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1)
            #define ESP_SPI_UART_FIFO_SIZE    (ESP_FIFO_SIZE)
        #else
            #define ESP_SPI_UART_FIFO_SIZE \
                                           ESP_GET_FIFO_SIZE(ESP_UART_BYTE_MODE_ENABLE)
        #endif /* (ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define ESP_INTERNAL_UART_RX_SW_BUFFER  (ESP_UART_RX_BUFFER_SIZE > \
                                                                ESP_SPI_UART_FIFO_SIZE)
        #define ESP_INTERNAL_UART_TX_SW_BUFFER  (ESP_UART_TX_BUFFER_SIZE > \
                                                                    ESP_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define ESP_INTERNAL_RX_SW_BUFFER  (ESP_INTERNAL_UART_RX_SW_BUFFER)
        #define ESP_INTERNAL_TX_SW_BUFFER  (ESP_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define ESP_INTERNAL_RX_BUFFER_SIZE    (ESP_UART_RX_BUFFER_SIZE + 1u)
        #define ESP_RX_BUFFER_SIZE             (ESP_UART_RX_BUFFER_SIZE)
        #define ESP_TX_BUFFER_SIZE             (ESP_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define ESP_SPI_WAKE_ENABLE_CONST  (0u)
        #define ESP_UART_WAKE_ENABLE_CONST (0u != ESP_UART_WAKE_ENABLE)

    #endif /* (ESP_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define ESP_SPI_SLAVE_CONST    (ESP_SPI_MODE == ESP_SPI_SLAVE)
    #define ESP_SPI_MASTER_CONST   (ESP_SPI_MODE == ESP_SPI_MASTER)

    /* Direction */
    #define ESP_RX_DIRECTION ((ESP_SCB_MODE_SPI_CONST_CFG) ? \
                                            (ESP_SPI_RX_DIRECTION) : (ESP_UART_RX_DIRECTION))

    #define ESP_TX_DIRECTION ((ESP_SCB_MODE_SPI_CONST_CFG) ? \
                                            (ESP_SPI_TX_DIRECTION) : (ESP_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define ESP_CHECK_RX_SW_BUFFER (ESP_INTERNAL_RX_SW_BUFFER)
    #define ESP_CHECK_TX_SW_BUFFER (ESP_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define ESP_INTERNAL_RX_SW_BUFFER_CONST    (ESP_INTERNAL_RX_SW_BUFFER)
    #define ESP_INTERNAL_TX_SW_BUFFER_CONST    (ESP_INTERNAL_TX_SW_BUFFER)

    /* SPI wakeup */
    #define ESP_CHECK_SPI_WAKE_ENABLE  (ESP_SPI_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define ESP_CHECK_UART_RTS_CONTROL_FLOW    (ESP_SCB_MODE_UART_CONST_CFG && \
                                                             ESP_UART_RTS_ENABLE)

#endif /* End (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* ESP_SPI_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 submode;
    uint32 sclkMode;
    uint32 oversample;
    uint32 enableMedianFilter;
    uint32 enableLateSampling;
    uint32 enableWake;
    uint32 rxDataBits;
    uint32 txDataBits;
    uint32 bitOrder;
    uint32 transferSeperation;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableFreeRunSclk;
    uint8 polaritySs;
} ESP_SPI_INIT_STRUCT;

/* ESP_UART_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 direction;
    uint32 dataBits;
    uint32 parity;
    uint32 stopBits;
    uint32 oversample;
    uint32 enableIrdaLowPower;
    uint32 enableMedianFilter;
    uint32 enableRetryNack;
    uint32 enableInvertedRx;
    uint32 dropOnParityErr;
    uint32 dropOnFrameErr;
    uint32 enableWake;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableMultiproc;
    uint32 multiprocAcceptAddr;
    uint32 multiprocAddr;
    uint32 multiprocAddrMask;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableCts;
    uint8 ctsPolarity;
    uint8 rtsRxFifoLevel;
    uint8 rtsPolarity;
} ESP_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(ESP_SCB_MODE_UNCONFIG_CONST_CFG)
    void ESP_SpiInit(const ESP_SPI_INIT_STRUCT *config);
#endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(ESP_SCB_MODE_SPI_INC)
    #define ESP_SpiIsBusBusy() ((uint32) (0u != (ESP_SPI_STATUS_REG & \
                                                              ESP_SPI_STATUS_BUS_BUSY)))

    #if (ESP_SPI_MASTER_CONST)
        void ESP_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(ESP_SPI_MASTER_CONST) */

    #if !(ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1)
        void ESP_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1) */
#endif /* (ESP_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(ESP_SCB_MODE_UNCONFIG_CONST_CFG)
    void ESP_UartInit(const ESP_UART_INIT_STRUCT *config);
#endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(ESP_SCB_MODE_UART_INC)
    void ESP_UartSetRxAddress(uint32 address);
    void ESP_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(ESP_UART_RX_DIRECTION)
        uint32 ESP_UartGetChar(void);
        uint32 ESP_UartGetByte(void);

        #if !(ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void ESP_UartSetRtsPolarity(uint32 polarity);
            void ESP_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1) */
    #endif /* (ESP_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(ESP_UART_TX_DIRECTION)
        #define ESP_UartPutChar(ch)    ESP_SpiUartWriteTxData((uint32)(ch))
        void ESP_UartPutString(const char8 string[]);
        void ESP_UartPutCRLF(uint32 txDataByte);

        #if !(ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void ESP_UartEnableCts(void);
            void ESP_UartDisableCts(void);
            void ESP_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(ESP_CY_SCBIP_V0 || ESP_CY_SCBIP_V1) */
    #endif /* (ESP_UART_TX_DIRECTION) */
#endif /* (ESP_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(ESP_RX_DIRECTION)
    uint32 ESP_SpiUartReadRxData(void);
    uint32 ESP_SpiUartGetRxBufferSize(void);
    void   ESP_SpiUartClearRxBuffer(void);
#endif /* (ESP_RX_DIRECTION) */

/* Common APIs TX direction */
#if(ESP_TX_DIRECTION)
    void   ESP_SpiUartWriteTxData(uint32 txData);
    void   ESP_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    uint32 ESP_SpiUartGetTxBufferSize(void);
    void   ESP_SpiUartClearTxBuffer(void);
#endif /* (ESP_TX_DIRECTION) */

CY_ISR_PROTO(ESP_SPI_UART_ISR);

#if(ESP_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(ESP_UART_WAKEUP_ISR);
#endif /* (ESP_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(ESP_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   ESP_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 ESP_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   ESP_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 ESP_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(ESP_INTERNAL_RX_SW_BUFFER_CONST)
        #define ESP_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    ESP_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define ESP_GetWordFromRxBuffer(idx) ESP_rxBufferInternal[(idx)]

    #endif /* (ESP_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(ESP_INTERNAL_TX_SW_BUFFER_CONST)
        #define ESP_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        ESP_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define ESP_GetWordFromTxBuffer(idx) ESP_txBufferInternal[(idx)]

    #endif /* (ESP_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (ESP_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define ESP_SPI_MODE_MOTOROLA      (0x00u)
#define ESP_SPI_MODE_TI_COINCIDES  (0x01u)
#define ESP_SPI_MODE_TI_PRECEDES   (0x11u)
#define ESP_SPI_MODE_NATIONAL      (0x02u)
#define ESP_SPI_MODE_MASK          (0x03u)
#define ESP_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define ESP_SPI_MODE_NS_MICROWIRE  (ESP_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define ESP_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define ESP_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define ESP_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define ESP_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define ESP_BITS_ORDER_LSB_FIRST   (0u)
#define ESP_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define ESP_SPI_TRANSFER_SEPARATED     (0u)
#define ESP_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define ESP_SPI_SLAVE_SELECT0    (ESP_SCB__SS0_POSISTION)
#define ESP_SPI_SLAVE_SELECT1    (ESP_SCB__SS1_POSISTION)
#define ESP_SPI_SLAVE_SELECT2    (ESP_SCB__SS2_POSISTION)
#define ESP_SPI_SLAVE_SELECT3    (ESP_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define ESP_SPI_SS_ACTIVE_LOW  (0u)
#define ESP_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define ESP_UART_MODE_STD          (0u)
#define ESP_UART_MODE_SMARTCARD    (1u)
#define ESP_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define ESP_UART_RX    (1u)
#define ESP_UART_TX    (2u)
#define ESP_UART_TX_RX (3u)

/* UART parity enum */
#define ESP_UART_PARITY_EVEN   (0u)
#define ESP_UART_PARITY_ODD    (1u)
#define ESP_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define ESP_UART_STOP_BITS_1   (2u)
#define ESP_UART_STOP_BITS_1_5 (3u)
#define ESP_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define ESP_UART_IRDA_LP_OVS16     (16u)
#define ESP_UART_IRDA_LP_OVS32     (32u)
#define ESP_UART_IRDA_LP_OVS48     (48u)
#define ESP_UART_IRDA_LP_OVS96     (96u)
#define ESP_UART_IRDA_LP_OVS192    (192u)
#define ESP_UART_IRDA_LP_OVS768    (768u)
#define ESP_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define ESP_UART_MP_MARK       (0x100u)
#define ESP_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define ESP_UART_CTS_ACTIVE_LOW    (0u)
#define ESP_UART_CTS_ACTIVE_HIGH   (1u)
#define ESP_UART_RTS_ACTIVE_LOW    (0u)
#define ESP_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define ESP_INTR_RX_ERR        (ESP_INTR_RX_OVERFLOW    | \
                                             ESP_INTR_RX_UNDERFLOW   | \
                                             ESP_INTR_RX_FRAME_ERROR | \
                                             ESP_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for ESP_UartGetByte() */
#define ESP_UART_RX_OVERFLOW       (ESP_INTR_RX_OVERFLOW << 8u)
#define ESP_UART_RX_UNDERFLOW      (ESP_INTR_RX_UNDERFLOW << 8u)
#define ESP_UART_RX_FRAME_ERROR    (ESP_INTR_RX_FRAME_ERROR << 8u)
#define ESP_UART_RX_PARITY_ERROR   (ESP_INTR_RX_PARITY_ERROR << 8u)
#define ESP_UART_RX_ERROR_MASK     (ESP_UART_RX_OVERFLOW    | \
                                                 ESP_UART_RX_UNDERFLOW   | \
                                                 ESP_UART_RX_FRAME_ERROR | \
                                                 ESP_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(ESP_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const ESP_SPI_INIT_STRUCT  ESP_configSpi;
    extern const ESP_UART_INIT_STRUCT ESP_configUart;
#endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define ESP_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & ESP_INTR_SLAVE_SPI_BUS_ERROR)
#define ESP_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & ESP_INTR_MASTER_SPI_DONE)
#define ESP_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~ESP_INTR_SLAVE_SPI_BUS_ERROR)

#define ESP_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~ESP_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define ESP_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((ESP_UART_IRDA_LP_OVS16   == (oversample)) ? ESP_CTRL_OVS_IRDA_LP_OVS16 : \
         ((ESP_UART_IRDA_LP_OVS32   == (oversample)) ? ESP_CTRL_OVS_IRDA_LP_OVS32 : \
          ((ESP_UART_IRDA_LP_OVS48   == (oversample)) ? ESP_CTRL_OVS_IRDA_LP_OVS48 : \
           ((ESP_UART_IRDA_LP_OVS96   == (oversample)) ? ESP_CTRL_OVS_IRDA_LP_OVS96 : \
            ((ESP_UART_IRDA_LP_OVS192  == (oversample)) ? ESP_CTRL_OVS_IRDA_LP_OVS192 : \
             ((ESP_UART_IRDA_LP_OVS768  == (oversample)) ? ESP_CTRL_OVS_IRDA_LP_OVS768 : \
              ((ESP_UART_IRDA_LP_OVS1536 == (oversample)) ? ESP_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          ESP_CTRL_OVS_IRDA_LP_OVS16)))))))

#define ESP_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (ESP_UART_RX & (direction))) ? \
                                                                     (ESP_RX_CTRL_ENABLED) : (0u))

#define ESP_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (ESP_UART_TX & (direction))) ? \
                                                                     (ESP_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define ESP_CTRL_SPI      (ESP_CTRL_MODE_SPI)
#define ESP_SPI_RX_CTRL   (ESP_RX_CTRL_ENABLED)
#define ESP_SPI_TX_CTRL   (ESP_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define ESP_SPI_SS_POLARITY \
             (((uint32) ESP_SPI_SS0_POLARITY << ESP_SPI_SLAVE_SELECT0) | \
              ((uint32) ESP_SPI_SS1_POLARITY << ESP_SPI_SLAVE_SELECT1) | \
              ((uint32) ESP_SPI_SS2_POLARITY << ESP_SPI_SLAVE_SELECT2) | \
              ((uint32) ESP_SPI_SS3_POLARITY << ESP_SPI_SLAVE_SELECT3))

#if(ESP_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define ESP_SPI_DEFAULT_CTRL \
                    (ESP_GET_CTRL_OVS(ESP_SPI_OVS_FACTOR) | \
                     ESP_GET_CTRL_BYTE_MODE (ESP_SPI_BYTE_MODE_ENABLE) | \
                     ESP_GET_CTRL_EC_AM_MODE(ESP_SPI_WAKE_ENABLE)      | \
                     ESP_CTRL_SPI)

    #define ESP_SPI_DEFAULT_SPI_CTRL \
                    (ESP_GET_SPI_CTRL_CONTINUOUS    (ESP_SPI_TRANSFER_SEPARATION)       | \
                     ESP_GET_SPI_CTRL_SELECT_PRECEDE(ESP_SPI_SUB_MODE &                   \
                                                                  ESP_SPI_MODE_TI_PRECEDES_MASK)     | \
                     ESP_GET_SPI_CTRL_SCLK_MODE     (ESP_SPI_CLOCK_MODE)                | \
                     ESP_GET_SPI_CTRL_LATE_MISO_SAMPLE(ESP_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     ESP_GET_SPI_CTRL_SCLK_CONTINUOUS(ESP_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     ESP_GET_SPI_CTRL_SSEL_POLARITY (ESP_SPI_SS_POLARITY)               | \
                     ESP_GET_SPI_CTRL_SUB_MODE      (ESP_SPI_SUB_MODE)                  | \
                     ESP_GET_SPI_CTRL_MASTER_MODE   (ESP_SPI_MODE))

    /* RX direction */
    #define ESP_SPI_DEFAULT_RX_CTRL \
                    (ESP_GET_RX_CTRL_DATA_WIDTH(ESP_SPI_RX_DATA_BITS_NUM)     | \
                     ESP_GET_RX_CTRL_BIT_ORDER (ESP_SPI_BITS_ORDER)           | \
                     ESP_GET_RX_CTRL_MEDIAN    (ESP_SPI_MEDIAN_FILTER_ENABLE) | \
                     ESP_SPI_RX_CTRL)

    #define ESP_SPI_DEFAULT_RX_FIFO_CTRL \
                    ESP_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(ESP_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define ESP_SPI_DEFAULT_TX_CTRL \
                    (ESP_GET_TX_CTRL_DATA_WIDTH(ESP_SPI_TX_DATA_BITS_NUM) | \
                     ESP_GET_TX_CTRL_BIT_ORDER (ESP_SPI_BITS_ORDER)       | \
                     ESP_SPI_TX_CTRL)

    #define ESP_SPI_DEFAULT_TX_FIFO_CTRL \
                    ESP_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(ESP_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define ESP_SPI_DEFAULT_INTR_SPI_EC_MASK   (ESP_NO_INTR_SOURCES)

    #define ESP_SPI_DEFAULT_INTR_I2C_EC_MASK   (ESP_NO_INTR_SOURCES)
    #define ESP_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (ESP_SPI_INTR_RX_MASK & ESP_INTR_SLAVE_SPI_BUS_ERROR)

    #define ESP_SPI_DEFAULT_INTR_MASTER_MASK \
                    (ESP_SPI_INTR_TX_MASK & ESP_INTR_MASTER_SPI_DONE)

    #define ESP_SPI_DEFAULT_INTR_RX_MASK \
                    (ESP_SPI_INTR_RX_MASK & (uint32) ~ESP_INTR_SLAVE_SPI_BUS_ERROR)

    #define ESP_SPI_DEFAULT_INTR_TX_MASK \
                    (ESP_SPI_INTR_TX_MASK & (uint32) ~ESP_INTR_MASTER_SPI_DONE)

#endif /* (ESP_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define ESP_CTRL_UART      (ESP_CTRL_MODE_UART)
#define ESP_UART_RX_CTRL   (ESP_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define ESP_UART_TX_CTRL   (ESP_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(ESP_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(ESP_UART_MODE_IRDA == ESP_UART_SUB_MODE)

        #define ESP_DEFAULT_CTRL_OVS   ((0u != ESP_UART_IRDA_LOW_POWER) ?              \
                                (ESP_UART_GET_CTRL_OVS_IRDA_LP(ESP_UART_OVS_FACTOR)) : \
                                (ESP_CTRL_OVS_IRDA_OVS16))

    #else

        #define ESP_DEFAULT_CTRL_OVS   ESP_GET_CTRL_OVS(ESP_UART_OVS_FACTOR)

    #endif /* (ESP_UART_MODE_IRDA == ESP_UART_SUB_MODE) */

    #define ESP_UART_DEFAULT_CTRL \
                                (ESP_GET_CTRL_BYTE_MODE  (ESP_UART_BYTE_MODE_ENABLE)  | \
                                 ESP_GET_CTRL_ADDR_ACCEPT(ESP_UART_MP_ACCEPT_ADDRESS) | \
                                 ESP_DEFAULT_CTRL_OVS                                              | \
                                 ESP_CTRL_UART)

    #define ESP_UART_DEFAULT_UART_CTRL \
                                    (ESP_GET_UART_CTRL_MODE(ESP_UART_SUB_MODE))

    /* RX direction */
    #define ESP_UART_DEFAULT_RX_CTRL_PARITY \
                                ((ESP_UART_PARITY_NONE != ESP_UART_PARITY_TYPE) ?      \
                                  (ESP_GET_UART_RX_CTRL_PARITY(ESP_UART_PARITY_TYPE) | \
                                   ESP_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define ESP_UART_DEFAULT_UART_RX_CTRL \
                    (ESP_GET_UART_RX_CTRL_MODE(ESP_UART_STOP_BITS_NUM)                    | \
                     ESP_GET_UART_RX_CTRL_POLARITY(ESP_UART_IRDA_POLARITY)                | \
                     ESP_GET_UART_RX_CTRL_MP_MODE(ESP_UART_MP_MODE_ENABLE)                | \
                     ESP_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(ESP_UART_DROP_ON_PARITY_ERR) | \
                     ESP_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(ESP_UART_DROP_ON_FRAME_ERR)   | \
                     ESP_UART_DEFAULT_RX_CTRL_PARITY)

    #define ESP_UART_DEFAULT_RX_CTRL \
                                (ESP_GET_RX_CTRL_DATA_WIDTH(ESP_UART_DATA_BITS_NUM)        | \
                                 ESP_GET_RX_CTRL_MEDIAN    (ESP_UART_MEDIAN_FILTER_ENABLE) | \
                                 ESP_GET_UART_RX_CTRL_ENABLED(ESP_UART_DIRECTION))

    #define ESP_UART_DEFAULT_RX_FIFO_CTRL \
                                ESP_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(ESP_UART_RX_TRIGGER_LEVEL)

    #define ESP_UART_DEFAULT_RX_MATCH_REG  ((0u != ESP_UART_MP_MODE_ENABLE) ?          \
                                (ESP_GET_RX_MATCH_ADDR(ESP_UART_MP_RX_ADDRESS) | \
                                 ESP_GET_RX_MATCH_MASK(ESP_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define ESP_UART_DEFAULT_TX_CTRL_PARITY (ESP_UART_DEFAULT_RX_CTRL_PARITY)

    #define ESP_UART_DEFAULT_UART_TX_CTRL \
                                (ESP_GET_UART_TX_CTRL_MODE(ESP_UART_STOP_BITS_NUM)       | \
                                 ESP_GET_UART_TX_CTRL_RETRY_NACK(ESP_UART_RETRY_ON_NACK) | \
                                 ESP_UART_DEFAULT_TX_CTRL_PARITY)

    #define ESP_UART_DEFAULT_TX_CTRL \
                                (ESP_GET_TX_CTRL_DATA_WIDTH(ESP_UART_DATA_BITS_NUM) | \
                                 ESP_GET_UART_TX_CTRL_ENABLED(ESP_UART_DIRECTION))

    #define ESP_UART_DEFAULT_TX_FIFO_CTRL \
                                ESP_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(ESP_UART_TX_TRIGGER_LEVEL)

    #define ESP_UART_DEFAULT_FLOW_CTRL \
                        (ESP_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(ESP_UART_RTS_FIFO_LEVEL) | \
                         ESP_GET_UART_FLOW_CTRL_RTS_POLARITY (ESP_UART_RTS_POLARITY)   | \
                         ESP_GET_UART_FLOW_CTRL_CTS_POLARITY (ESP_UART_CTS_POLARITY)   | \
                         ESP_GET_UART_FLOW_CTRL_CTS_ENABLE   (ESP_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define ESP_UART_DEFAULT_INTR_I2C_EC_MASK  (ESP_NO_INTR_SOURCES)
    #define ESP_UART_DEFAULT_INTR_SPI_EC_MASK  (ESP_NO_INTR_SOURCES)
    #define ESP_UART_DEFAULT_INTR_SLAVE_MASK   (ESP_NO_INTR_SOURCES)
    #define ESP_UART_DEFAULT_INTR_MASTER_MASK  (ESP_NO_INTR_SOURCES)
    #define ESP_UART_DEFAULT_INTR_RX_MASK      (ESP_UART_INTR_RX_MASK)
    #define ESP_UART_DEFAULT_INTR_TX_MASK      (ESP_UART_INTR_TX_MASK)

#endif /* (ESP_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define ESP_SPIM_ACTIVE_SS0    (ESP_SPI_SLAVE_SELECT0)
#define ESP_SPIM_ACTIVE_SS1    (ESP_SPI_SLAVE_SELECT1)
#define ESP_SPIM_ACTIVE_SS2    (ESP_SPI_SLAVE_SELECT2)
#define ESP_SPIM_ACTIVE_SS3    (ESP_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_ESP_H */


/* [] END OF FILE */
