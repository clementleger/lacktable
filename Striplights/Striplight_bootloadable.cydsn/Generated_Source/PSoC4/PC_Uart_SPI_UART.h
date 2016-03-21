/*******************************************************************************
* File Name: PC_Uart_SPI_UART.h
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

#if !defined(CY_SCB_SPI_UART_PC_Uart_H)
#define CY_SCB_SPI_UART_PC_Uart_H

#include "PC_Uart.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define PC_Uart_SPI_MODE                   (0u)
#define PC_Uart_SPI_SUB_MODE               (0u)
#define PC_Uart_SPI_CLOCK_MODE             (0u)
#define PC_Uart_SPI_OVS_FACTOR             (16u)
#define PC_Uart_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define PC_Uart_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define PC_Uart_SPI_RX_DATA_BITS_NUM       (8u)
#define PC_Uart_SPI_TX_DATA_BITS_NUM       (8u)
#define PC_Uart_SPI_WAKE_ENABLE            (0u)
#define PC_Uart_SPI_BITS_ORDER             (1u)
#define PC_Uart_SPI_TRANSFER_SEPARATION    (1u)
#define PC_Uart_SPI_NUMBER_OF_SS_LINES     (1u)
#define PC_Uart_SPI_RX_BUFFER_SIZE         (8u)
#define PC_Uart_SPI_TX_BUFFER_SIZE         (8u)

#define PC_Uart_SPI_INTERRUPT_MODE         (0u)

#define PC_Uart_SPI_INTR_RX_MASK           (0u)
#define PC_Uart_SPI_INTR_TX_MASK           (0u)

#define PC_Uart_SPI_RX_TRIGGER_LEVEL       (7u)
#define PC_Uart_SPI_TX_TRIGGER_LEVEL       (0u)

#define PC_Uart_SPI_BYTE_MODE_ENABLE       (0u)
#define PC_Uart_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define PC_Uart_SPI_SS0_POLARITY           (0u)
#define PC_Uart_SPI_SS1_POLARITY           (0u)
#define PC_Uart_SPI_SS2_POLARITY           (0u)
#define PC_Uart_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define PC_Uart_UART_SUB_MODE              (0u)
#define PC_Uart_UART_DIRECTION             (3u)
#define PC_Uart_UART_DATA_BITS_NUM         (8u)
#define PC_Uart_UART_PARITY_TYPE           (2u)
#define PC_Uart_UART_STOP_BITS_NUM         (2u)
#define PC_Uart_UART_OVS_FACTOR            (12u)
#define PC_Uart_UART_IRDA_LOW_POWER        (0u)
#define PC_Uart_UART_MEDIAN_FILTER_ENABLE  (0u)
#define PC_Uart_UART_RETRY_ON_NACK         (0u)
#define PC_Uart_UART_IRDA_POLARITY         (0u)
#define PC_Uart_UART_DROP_ON_FRAME_ERR     (0u)
#define PC_Uart_UART_DROP_ON_PARITY_ERR    (0u)
#define PC_Uart_UART_WAKE_ENABLE           (0u)
#define PC_Uart_UART_RX_BUFFER_SIZE        (8u)
#define PC_Uart_UART_TX_BUFFER_SIZE        (8u)
#define PC_Uart_UART_MP_MODE_ENABLE        (0u)
#define PC_Uart_UART_MP_ACCEPT_ADDRESS     (0u)
#define PC_Uart_UART_MP_RX_ADDRESS         (2u)
#define PC_Uart_UART_MP_RX_ADDRESS_MASK    (255u)

#define PC_Uart_UART_INTERRUPT_MODE        (0u)

#define PC_Uart_UART_INTR_RX_MASK          (0u)
#define PC_Uart_UART_INTR_TX_MASK          (0u)

#define PC_Uart_UART_RX_TRIGGER_LEVEL      (7u)
#define PC_Uart_UART_TX_TRIGGER_LEVEL      (0u)

#define PC_Uart_UART_BYTE_MODE_ENABLE      (0u)
#define PC_Uart_UART_CTS_ENABLE            (0u)
#define PC_Uart_UART_CTS_POLARITY          (0u)
#define PC_Uart_UART_RTS_ENABLE            (0u)
#define PC_Uart_UART_RTS_POLARITY          (0u)
#define PC_Uart_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define PC_Uart_SPI_SLAVE  (0u)
#define PC_Uart_SPI_MASTER (1u)

/* UART direction enum */
#define PC_Uart_UART_RX    (1u)
#define PC_Uart_UART_TX    (2u)
#define PC_Uart_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define PC_Uart_SPI_SLAVE_CONST        (1u)
    #define PC_Uart_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define PC_Uart_RX_DIRECTION           (1u)
    #define PC_Uart_TX_DIRECTION           (1u)
    #define PC_Uart_UART_RX_DIRECTION      (1u)
    #define PC_Uart_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define PC_Uart_INTERNAL_RX_SW_BUFFER   (0u)
    #define PC_Uart_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define PC_Uart_INTERNAL_RX_BUFFER_SIZE    (PC_Uart_rxBufferSize + 1u)
    #define PC_Uart_RX_BUFFER_SIZE             (PC_Uart_rxBufferSize)
    #define PC_Uart_TX_BUFFER_SIZE             (PC_Uart_txBufferSize)

    /* Return true if buffer is provided */
    #define PC_Uart_CHECK_RX_SW_BUFFER (NULL != PC_Uart_rxBuffer)
    #define PC_Uart_CHECK_TX_SW_BUFFER (NULL != PC_Uart_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define PC_Uart_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define PC_Uart_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define PC_Uart_SPI_WAKE_ENABLE_CONST  (1u)
    #define PC_Uart_CHECK_SPI_WAKE_ENABLE  (0u != PC_Uart_scbEnableWake)
    #define PC_Uart_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1)
        #define PC_Uart_SPI_UART_FIFO_SIZE             (PC_Uart_FIFO_SIZE)
        #define PC_Uart_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define PC_Uart_SPI_UART_FIFO_SIZE (PC_Uart_GET_FIFO_SIZE(PC_Uart_CTRL_REG & \
                                                                                    PC_Uart_CTRL_BYTE_MODE))

        #define PC_Uart_CHECK_UART_RTS_CONTROL_FLOW \
                    ((PC_Uart_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != PC_Uart_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(PC_Uart_UART_FLOW_CTRL_REG)))
    #endif /* (PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (PC_Uart_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define PC_Uart_SPI_RX_DIRECTION (1u)
        #define PC_Uart_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1)
            #define PC_Uart_SPI_UART_FIFO_SIZE    (PC_Uart_FIFO_SIZE)
        #else
            #define PC_Uart_SPI_UART_FIFO_SIZE \
                                           PC_Uart_GET_FIFO_SIZE(PC_Uart_SPI_BYTE_MODE_ENABLE)

        #endif /* (PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define PC_Uart_INTERNAL_SPI_RX_SW_BUFFER  (PC_Uart_SPI_RX_BUFFER_SIZE > \
                                                                PC_Uart_SPI_UART_FIFO_SIZE)
        #define PC_Uart_INTERNAL_SPI_TX_SW_BUFFER  (PC_Uart_SPI_TX_BUFFER_SIZE > \
                                                                PC_Uart_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define PC_Uart_INTERNAL_RX_SW_BUFFER  (PC_Uart_INTERNAL_SPI_RX_SW_BUFFER)
        #define PC_Uart_INTERNAL_TX_SW_BUFFER  (PC_Uart_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define PC_Uart_INTERNAL_RX_BUFFER_SIZE    (PC_Uart_SPI_RX_BUFFER_SIZE + 1u)
        #define PC_Uart_RX_BUFFER_SIZE             (PC_Uart_SPI_RX_BUFFER_SIZE)
        #define PC_Uart_TX_BUFFER_SIZE             (PC_Uart_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define PC_Uart_SPI_WAKE_ENABLE_CONST  (0u != PC_Uart_SPI_WAKE_ENABLE)
        #define PC_Uart_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define PC_Uart_UART_RX_DIRECTION (0u != (PC_Uart_UART_DIRECTION & PC_Uart_UART_RX))
        #define PC_Uart_UART_TX_DIRECTION (0u != (PC_Uart_UART_DIRECTION & PC_Uart_UART_TX))

        /* Get FIFO size */
        #if (PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1)
            #define PC_Uart_SPI_UART_FIFO_SIZE    (PC_Uart_FIFO_SIZE)
        #else
            #define PC_Uart_SPI_UART_FIFO_SIZE \
                                           PC_Uart_GET_FIFO_SIZE(PC_Uart_UART_BYTE_MODE_ENABLE)
        #endif /* (PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define PC_Uart_INTERNAL_UART_RX_SW_BUFFER  (PC_Uart_UART_RX_BUFFER_SIZE > \
                                                                PC_Uart_SPI_UART_FIFO_SIZE)
        #define PC_Uart_INTERNAL_UART_TX_SW_BUFFER  (PC_Uart_UART_TX_BUFFER_SIZE > \
                                                                    PC_Uart_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define PC_Uart_INTERNAL_RX_SW_BUFFER  (PC_Uart_INTERNAL_UART_RX_SW_BUFFER)
        #define PC_Uart_INTERNAL_TX_SW_BUFFER  (PC_Uart_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define PC_Uart_INTERNAL_RX_BUFFER_SIZE    (PC_Uart_UART_RX_BUFFER_SIZE + 1u)
        #define PC_Uart_RX_BUFFER_SIZE             (PC_Uart_UART_RX_BUFFER_SIZE)
        #define PC_Uart_TX_BUFFER_SIZE             (PC_Uart_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define PC_Uart_SPI_WAKE_ENABLE_CONST  (0u)
        #define PC_Uart_UART_WAKE_ENABLE_CONST (0u != PC_Uart_UART_WAKE_ENABLE)

    #endif /* (PC_Uart_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define PC_Uart_SPI_SLAVE_CONST    (PC_Uart_SPI_MODE == PC_Uart_SPI_SLAVE)
    #define PC_Uart_SPI_MASTER_CONST   (PC_Uart_SPI_MODE == PC_Uart_SPI_MASTER)

    /* Direction */
    #define PC_Uart_RX_DIRECTION ((PC_Uart_SCB_MODE_SPI_CONST_CFG) ? \
                                            (PC_Uart_SPI_RX_DIRECTION) : (PC_Uart_UART_RX_DIRECTION))

    #define PC_Uart_TX_DIRECTION ((PC_Uart_SCB_MODE_SPI_CONST_CFG) ? \
                                            (PC_Uart_SPI_TX_DIRECTION) : (PC_Uart_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define PC_Uart_CHECK_RX_SW_BUFFER (PC_Uart_INTERNAL_RX_SW_BUFFER)
    #define PC_Uart_CHECK_TX_SW_BUFFER (PC_Uart_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define PC_Uart_INTERNAL_RX_SW_BUFFER_CONST    (PC_Uart_INTERNAL_RX_SW_BUFFER)
    #define PC_Uart_INTERNAL_TX_SW_BUFFER_CONST    (PC_Uart_INTERNAL_TX_SW_BUFFER)

    /* SPI wakeup */
    #define PC_Uart_CHECK_SPI_WAKE_ENABLE  (PC_Uart_SPI_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define PC_Uart_CHECK_UART_RTS_CONTROL_FLOW    (PC_Uart_SCB_MODE_UART_CONST_CFG && \
                                                             PC_Uart_UART_RTS_ENABLE)

#endif /* End (PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* PC_Uart_SPI_INIT_STRUCT */
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
} PC_Uart_SPI_INIT_STRUCT;

/* PC_Uart_UART_INIT_STRUCT */
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
} PC_Uart_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG)
    void PC_Uart_SpiInit(const PC_Uart_SPI_INIT_STRUCT *config);
#endif /* (PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(PC_Uart_SCB_MODE_SPI_INC)
    #define PC_Uart_SpiIsBusBusy() ((uint32) (0u != (PC_Uart_SPI_STATUS_REG & \
                                                              PC_Uart_SPI_STATUS_BUS_BUSY)))

    #if (PC_Uart_SPI_MASTER_CONST)
        void PC_Uart_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(PC_Uart_SPI_MASTER_CONST) */

    #if !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1)
        void PC_Uart_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1) */
#endif /* (PC_Uart_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG)
    void PC_Uart_UartInit(const PC_Uart_UART_INIT_STRUCT *config);
#endif /* (PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(PC_Uart_SCB_MODE_UART_INC)
    void PC_Uart_UartSetRxAddress(uint32 address);
    void PC_Uart_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(PC_Uart_UART_RX_DIRECTION)
        uint32 PC_Uart_UartGetChar(void);
        uint32 PC_Uart_UartGetByte(void);

        #if !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void PC_Uart_UartSetRtsPolarity(uint32 polarity);
            void PC_Uart_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1) */
    #endif /* (PC_Uart_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(PC_Uart_UART_TX_DIRECTION)
        #define PC_Uart_UartPutChar(ch)    PC_Uart_SpiUartWriteTxData((uint32)(ch))
        void PC_Uart_UartPutString(const char8 string[]);
        void PC_Uart_UartPutCRLF(uint32 txDataByte);

        #if !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void PC_Uart_UartEnableCts(void);
            void PC_Uart_UartDisableCts(void);
            void PC_Uart_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1) */
    #endif /* (PC_Uart_UART_TX_DIRECTION) */
#endif /* (PC_Uart_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(PC_Uart_RX_DIRECTION)
    uint32 PC_Uart_SpiUartReadRxData(void);
    uint32 PC_Uart_SpiUartGetRxBufferSize(void);
    void   PC_Uart_SpiUartClearRxBuffer(void);
#endif /* (PC_Uart_RX_DIRECTION) */

/* Common APIs TX direction */
#if(PC_Uart_TX_DIRECTION)
    void   PC_Uart_SpiUartWriteTxData(uint32 txData);
    void   PC_Uart_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    uint32 PC_Uart_SpiUartGetTxBufferSize(void);
    void   PC_Uart_SpiUartClearTxBuffer(void);
#endif /* (PC_Uart_TX_DIRECTION) */

CY_ISR_PROTO(PC_Uart_SPI_UART_ISR);

#if(PC_Uart_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(PC_Uart_UART_WAKEUP_ISR);
#endif /* (PC_Uart_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   PC_Uart_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 PC_Uart_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   PC_Uart_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 PC_Uart_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(PC_Uart_INTERNAL_RX_SW_BUFFER_CONST)
        #define PC_Uart_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    PC_Uart_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define PC_Uart_GetWordFromRxBuffer(idx) PC_Uart_rxBufferInternal[(idx)]

    #endif /* (PC_Uart_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(PC_Uart_INTERNAL_TX_SW_BUFFER_CONST)
        #define PC_Uart_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        PC_Uart_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define PC_Uart_GetWordFromTxBuffer(idx) PC_Uart_txBufferInternal[(idx)]

    #endif /* (PC_Uart_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (PC_Uart_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define PC_Uart_SPI_MODE_MOTOROLA      (0x00u)
#define PC_Uart_SPI_MODE_TI_COINCIDES  (0x01u)
#define PC_Uart_SPI_MODE_TI_PRECEDES   (0x11u)
#define PC_Uart_SPI_MODE_NATIONAL      (0x02u)
#define PC_Uart_SPI_MODE_MASK          (0x03u)
#define PC_Uart_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define PC_Uart_SPI_MODE_NS_MICROWIRE  (PC_Uart_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define PC_Uart_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define PC_Uart_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define PC_Uart_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define PC_Uart_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define PC_Uart_BITS_ORDER_LSB_FIRST   (0u)
#define PC_Uart_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define PC_Uart_SPI_TRANSFER_SEPARATED     (0u)
#define PC_Uart_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define PC_Uart_SPI_SLAVE_SELECT0    (PC_Uart_SCB__SS0_POSISTION)
#define PC_Uart_SPI_SLAVE_SELECT1    (PC_Uart_SCB__SS1_POSISTION)
#define PC_Uart_SPI_SLAVE_SELECT2    (PC_Uart_SCB__SS2_POSISTION)
#define PC_Uart_SPI_SLAVE_SELECT3    (PC_Uart_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define PC_Uart_SPI_SS_ACTIVE_LOW  (0u)
#define PC_Uart_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define PC_Uart_UART_MODE_STD          (0u)
#define PC_Uart_UART_MODE_SMARTCARD    (1u)
#define PC_Uart_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define PC_Uart_UART_RX    (1u)
#define PC_Uart_UART_TX    (2u)
#define PC_Uart_UART_TX_RX (3u)

/* UART parity enum */
#define PC_Uart_UART_PARITY_EVEN   (0u)
#define PC_Uart_UART_PARITY_ODD    (1u)
#define PC_Uart_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define PC_Uart_UART_STOP_BITS_1   (2u)
#define PC_Uart_UART_STOP_BITS_1_5 (3u)
#define PC_Uart_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define PC_Uart_UART_IRDA_LP_OVS16     (16u)
#define PC_Uart_UART_IRDA_LP_OVS32     (32u)
#define PC_Uart_UART_IRDA_LP_OVS48     (48u)
#define PC_Uart_UART_IRDA_LP_OVS96     (96u)
#define PC_Uart_UART_IRDA_LP_OVS192    (192u)
#define PC_Uart_UART_IRDA_LP_OVS768    (768u)
#define PC_Uart_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define PC_Uart_UART_MP_MARK       (0x100u)
#define PC_Uart_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define PC_Uart_UART_CTS_ACTIVE_LOW    (0u)
#define PC_Uart_UART_CTS_ACTIVE_HIGH   (1u)
#define PC_Uart_UART_RTS_ACTIVE_LOW    (0u)
#define PC_Uart_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define PC_Uart_INTR_RX_ERR        (PC_Uart_INTR_RX_OVERFLOW    | \
                                             PC_Uart_INTR_RX_UNDERFLOW   | \
                                             PC_Uart_INTR_RX_FRAME_ERROR | \
                                             PC_Uart_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for PC_Uart_UartGetByte() */
#define PC_Uart_UART_RX_OVERFLOW       (PC_Uart_INTR_RX_OVERFLOW << 8u)
#define PC_Uart_UART_RX_UNDERFLOW      (PC_Uart_INTR_RX_UNDERFLOW << 8u)
#define PC_Uart_UART_RX_FRAME_ERROR    (PC_Uart_INTR_RX_FRAME_ERROR << 8u)
#define PC_Uart_UART_RX_PARITY_ERROR   (PC_Uart_INTR_RX_PARITY_ERROR << 8u)
#define PC_Uart_UART_RX_ERROR_MASK     (PC_Uart_UART_RX_OVERFLOW    | \
                                                 PC_Uart_UART_RX_UNDERFLOW   | \
                                                 PC_Uart_UART_RX_FRAME_ERROR | \
                                                 PC_Uart_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const PC_Uart_SPI_INIT_STRUCT  PC_Uart_configSpi;
    extern const PC_Uart_UART_INIT_STRUCT PC_Uart_configUart;
#endif /* (PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define PC_Uart_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & PC_Uart_INTR_SLAVE_SPI_BUS_ERROR)
#define PC_Uart_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & PC_Uart_INTR_MASTER_SPI_DONE)
#define PC_Uart_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~PC_Uart_INTR_SLAVE_SPI_BUS_ERROR)

#define PC_Uart_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~PC_Uart_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define PC_Uart_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((PC_Uart_UART_IRDA_LP_OVS16   == (oversample)) ? PC_Uart_CTRL_OVS_IRDA_LP_OVS16 : \
         ((PC_Uart_UART_IRDA_LP_OVS32   == (oversample)) ? PC_Uart_CTRL_OVS_IRDA_LP_OVS32 : \
          ((PC_Uart_UART_IRDA_LP_OVS48   == (oversample)) ? PC_Uart_CTRL_OVS_IRDA_LP_OVS48 : \
           ((PC_Uart_UART_IRDA_LP_OVS96   == (oversample)) ? PC_Uart_CTRL_OVS_IRDA_LP_OVS96 : \
            ((PC_Uart_UART_IRDA_LP_OVS192  == (oversample)) ? PC_Uart_CTRL_OVS_IRDA_LP_OVS192 : \
             ((PC_Uart_UART_IRDA_LP_OVS768  == (oversample)) ? PC_Uart_CTRL_OVS_IRDA_LP_OVS768 : \
              ((PC_Uart_UART_IRDA_LP_OVS1536 == (oversample)) ? PC_Uart_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          PC_Uart_CTRL_OVS_IRDA_LP_OVS16)))))))

#define PC_Uart_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (PC_Uart_UART_RX & (direction))) ? \
                                                                     (PC_Uart_RX_CTRL_ENABLED) : (0u))

#define PC_Uart_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (PC_Uart_UART_TX & (direction))) ? \
                                                                     (PC_Uart_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define PC_Uart_CTRL_SPI      (PC_Uart_CTRL_MODE_SPI)
#define PC_Uart_SPI_RX_CTRL   (PC_Uart_RX_CTRL_ENABLED)
#define PC_Uart_SPI_TX_CTRL   (PC_Uart_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define PC_Uart_SPI_SS_POLARITY \
             (((uint32) PC_Uart_SPI_SS0_POLARITY << PC_Uart_SPI_SLAVE_SELECT0) | \
              ((uint32) PC_Uart_SPI_SS1_POLARITY << PC_Uart_SPI_SLAVE_SELECT1) | \
              ((uint32) PC_Uart_SPI_SS2_POLARITY << PC_Uart_SPI_SLAVE_SELECT2) | \
              ((uint32) PC_Uart_SPI_SS3_POLARITY << PC_Uart_SPI_SLAVE_SELECT3))

#if(PC_Uart_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define PC_Uart_SPI_DEFAULT_CTRL \
                    (PC_Uart_GET_CTRL_OVS(PC_Uart_SPI_OVS_FACTOR) | \
                     PC_Uart_GET_CTRL_BYTE_MODE (PC_Uart_SPI_BYTE_MODE_ENABLE) | \
                     PC_Uart_GET_CTRL_EC_AM_MODE(PC_Uart_SPI_WAKE_ENABLE)      | \
                     PC_Uart_CTRL_SPI)

    #define PC_Uart_SPI_DEFAULT_SPI_CTRL \
                    (PC_Uart_GET_SPI_CTRL_CONTINUOUS    (PC_Uart_SPI_TRANSFER_SEPARATION)       | \
                     PC_Uart_GET_SPI_CTRL_SELECT_PRECEDE(PC_Uart_SPI_SUB_MODE &                   \
                                                                  PC_Uart_SPI_MODE_TI_PRECEDES_MASK)     | \
                     PC_Uart_GET_SPI_CTRL_SCLK_MODE     (PC_Uart_SPI_CLOCK_MODE)                | \
                     PC_Uart_GET_SPI_CTRL_LATE_MISO_SAMPLE(PC_Uart_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     PC_Uart_GET_SPI_CTRL_SCLK_CONTINUOUS(PC_Uart_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     PC_Uart_GET_SPI_CTRL_SSEL_POLARITY (PC_Uart_SPI_SS_POLARITY)               | \
                     PC_Uart_GET_SPI_CTRL_SUB_MODE      (PC_Uart_SPI_SUB_MODE)                  | \
                     PC_Uart_GET_SPI_CTRL_MASTER_MODE   (PC_Uart_SPI_MODE))

    /* RX direction */
    #define PC_Uart_SPI_DEFAULT_RX_CTRL \
                    (PC_Uart_GET_RX_CTRL_DATA_WIDTH(PC_Uart_SPI_RX_DATA_BITS_NUM)     | \
                     PC_Uart_GET_RX_CTRL_BIT_ORDER (PC_Uart_SPI_BITS_ORDER)           | \
                     PC_Uart_GET_RX_CTRL_MEDIAN    (PC_Uart_SPI_MEDIAN_FILTER_ENABLE) | \
                     PC_Uart_SPI_RX_CTRL)

    #define PC_Uart_SPI_DEFAULT_RX_FIFO_CTRL \
                    PC_Uart_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(PC_Uart_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define PC_Uart_SPI_DEFAULT_TX_CTRL \
                    (PC_Uart_GET_TX_CTRL_DATA_WIDTH(PC_Uart_SPI_TX_DATA_BITS_NUM) | \
                     PC_Uart_GET_TX_CTRL_BIT_ORDER (PC_Uart_SPI_BITS_ORDER)       | \
                     PC_Uart_SPI_TX_CTRL)

    #define PC_Uart_SPI_DEFAULT_TX_FIFO_CTRL \
                    PC_Uart_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(PC_Uart_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define PC_Uart_SPI_DEFAULT_INTR_SPI_EC_MASK   (PC_Uart_NO_INTR_SOURCES)

    #define PC_Uart_SPI_DEFAULT_INTR_I2C_EC_MASK   (PC_Uart_NO_INTR_SOURCES)
    #define PC_Uart_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (PC_Uart_SPI_INTR_RX_MASK & PC_Uart_INTR_SLAVE_SPI_BUS_ERROR)

    #define PC_Uart_SPI_DEFAULT_INTR_MASTER_MASK \
                    (PC_Uart_SPI_INTR_TX_MASK & PC_Uart_INTR_MASTER_SPI_DONE)

    #define PC_Uart_SPI_DEFAULT_INTR_RX_MASK \
                    (PC_Uart_SPI_INTR_RX_MASK & (uint32) ~PC_Uart_INTR_SLAVE_SPI_BUS_ERROR)

    #define PC_Uart_SPI_DEFAULT_INTR_TX_MASK \
                    (PC_Uart_SPI_INTR_TX_MASK & (uint32) ~PC_Uart_INTR_MASTER_SPI_DONE)

#endif /* (PC_Uart_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define PC_Uart_CTRL_UART      (PC_Uart_CTRL_MODE_UART)
#define PC_Uart_UART_RX_CTRL   (PC_Uart_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define PC_Uart_UART_TX_CTRL   (PC_Uart_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(PC_Uart_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(PC_Uart_UART_MODE_IRDA == PC_Uart_UART_SUB_MODE)

        #define PC_Uart_DEFAULT_CTRL_OVS   ((0u != PC_Uart_UART_IRDA_LOW_POWER) ?              \
                                (PC_Uart_UART_GET_CTRL_OVS_IRDA_LP(PC_Uart_UART_OVS_FACTOR)) : \
                                (PC_Uart_CTRL_OVS_IRDA_OVS16))

    #else

        #define PC_Uart_DEFAULT_CTRL_OVS   PC_Uart_GET_CTRL_OVS(PC_Uart_UART_OVS_FACTOR)

    #endif /* (PC_Uart_UART_MODE_IRDA == PC_Uart_UART_SUB_MODE) */

    #define PC_Uart_UART_DEFAULT_CTRL \
                                (PC_Uart_GET_CTRL_BYTE_MODE  (PC_Uart_UART_BYTE_MODE_ENABLE)  | \
                                 PC_Uart_GET_CTRL_ADDR_ACCEPT(PC_Uart_UART_MP_ACCEPT_ADDRESS) | \
                                 PC_Uart_DEFAULT_CTRL_OVS                                              | \
                                 PC_Uart_CTRL_UART)

    #define PC_Uart_UART_DEFAULT_UART_CTRL \
                                    (PC_Uart_GET_UART_CTRL_MODE(PC_Uart_UART_SUB_MODE))

    /* RX direction */
    #define PC_Uart_UART_DEFAULT_RX_CTRL_PARITY \
                                ((PC_Uart_UART_PARITY_NONE != PC_Uart_UART_PARITY_TYPE) ?      \
                                  (PC_Uart_GET_UART_RX_CTRL_PARITY(PC_Uart_UART_PARITY_TYPE) | \
                                   PC_Uart_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define PC_Uart_UART_DEFAULT_UART_RX_CTRL \
                    (PC_Uart_GET_UART_RX_CTRL_MODE(PC_Uart_UART_STOP_BITS_NUM)                    | \
                     PC_Uart_GET_UART_RX_CTRL_POLARITY(PC_Uart_UART_IRDA_POLARITY)                | \
                     PC_Uart_GET_UART_RX_CTRL_MP_MODE(PC_Uart_UART_MP_MODE_ENABLE)                | \
                     PC_Uart_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(PC_Uart_UART_DROP_ON_PARITY_ERR) | \
                     PC_Uart_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(PC_Uart_UART_DROP_ON_FRAME_ERR)   | \
                     PC_Uart_UART_DEFAULT_RX_CTRL_PARITY)

    #define PC_Uart_UART_DEFAULT_RX_CTRL \
                                (PC_Uart_GET_RX_CTRL_DATA_WIDTH(PC_Uart_UART_DATA_BITS_NUM)        | \
                                 PC_Uart_GET_RX_CTRL_MEDIAN    (PC_Uart_UART_MEDIAN_FILTER_ENABLE) | \
                                 PC_Uart_GET_UART_RX_CTRL_ENABLED(PC_Uart_UART_DIRECTION))

    #define PC_Uart_UART_DEFAULT_RX_FIFO_CTRL \
                                PC_Uart_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(PC_Uart_UART_RX_TRIGGER_LEVEL)

    #define PC_Uart_UART_DEFAULT_RX_MATCH_REG  ((0u != PC_Uart_UART_MP_MODE_ENABLE) ?          \
                                (PC_Uart_GET_RX_MATCH_ADDR(PC_Uart_UART_MP_RX_ADDRESS) | \
                                 PC_Uart_GET_RX_MATCH_MASK(PC_Uart_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define PC_Uart_UART_DEFAULT_TX_CTRL_PARITY (PC_Uart_UART_DEFAULT_RX_CTRL_PARITY)

    #define PC_Uart_UART_DEFAULT_UART_TX_CTRL \
                                (PC_Uart_GET_UART_TX_CTRL_MODE(PC_Uart_UART_STOP_BITS_NUM)       | \
                                 PC_Uart_GET_UART_TX_CTRL_RETRY_NACK(PC_Uart_UART_RETRY_ON_NACK) | \
                                 PC_Uart_UART_DEFAULT_TX_CTRL_PARITY)

    #define PC_Uart_UART_DEFAULT_TX_CTRL \
                                (PC_Uart_GET_TX_CTRL_DATA_WIDTH(PC_Uart_UART_DATA_BITS_NUM) | \
                                 PC_Uart_GET_UART_TX_CTRL_ENABLED(PC_Uart_UART_DIRECTION))

    #define PC_Uart_UART_DEFAULT_TX_FIFO_CTRL \
                                PC_Uart_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(PC_Uart_UART_TX_TRIGGER_LEVEL)

    #define PC_Uart_UART_DEFAULT_FLOW_CTRL \
                        (PC_Uart_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(PC_Uart_UART_RTS_FIFO_LEVEL) | \
                         PC_Uart_GET_UART_FLOW_CTRL_RTS_POLARITY (PC_Uart_UART_RTS_POLARITY)   | \
                         PC_Uart_GET_UART_FLOW_CTRL_CTS_POLARITY (PC_Uart_UART_CTS_POLARITY)   | \
                         PC_Uart_GET_UART_FLOW_CTRL_CTS_ENABLE   (PC_Uart_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define PC_Uart_UART_DEFAULT_INTR_I2C_EC_MASK  (PC_Uart_NO_INTR_SOURCES)
    #define PC_Uart_UART_DEFAULT_INTR_SPI_EC_MASK  (PC_Uart_NO_INTR_SOURCES)
    #define PC_Uart_UART_DEFAULT_INTR_SLAVE_MASK   (PC_Uart_NO_INTR_SOURCES)
    #define PC_Uart_UART_DEFAULT_INTR_MASTER_MASK  (PC_Uart_NO_INTR_SOURCES)
    #define PC_Uart_UART_DEFAULT_INTR_RX_MASK      (PC_Uart_UART_INTR_RX_MASK)
    #define PC_Uart_UART_DEFAULT_INTR_TX_MASK      (PC_Uart_UART_INTR_TX_MASK)

#endif /* (PC_Uart_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define PC_Uart_SPIM_ACTIVE_SS0    (PC_Uart_SPI_SLAVE_SELECT0)
#define PC_Uart_SPIM_ACTIVE_SS1    (PC_Uart_SPI_SLAVE_SELECT1)
#define PC_Uart_SPIM_ACTIVE_SS2    (PC_Uart_SPI_SLAVE_SELECT2)
#define PC_Uart_SPIM_ACTIVE_SS3    (PC_Uart_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_PC_Uart_H */


/* [] END OF FILE */
