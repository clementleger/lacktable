/*******************************************************************************
* File Name: PC_Uart.h
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PC_Uart_H)
#define CY_SCB_PC_Uart_H

#include <cydevice_trm.h>
#include <cyfitter.h>
#include <cytypes.h>
#include <CyLib.h>

/* SCB IP block v0 is available in PSoC 4100/PSoC 4200 */
#define PC_Uart_CY_SCBIP_V0    (CYIPBLOCK_m0s8scb_VERSION == 0u)
/* SCB IP block v1 is available in PSoC 4000 */
#define PC_Uart_CY_SCBIP_V1    (CYIPBLOCK_m0s8scb_VERSION == 1u)
/* SCB IP block v2 is available in all other devices */
#define PC_Uart_CY_SCBIP_V2    (CYIPBLOCK_m0s8scb_VERSION >= 2u)

#define PC_Uart_SCB_MODE                     (4u)

/* SCB modes enum */
#define PC_Uart_SCB_MODE_I2C                 (0x01u)
#define PC_Uart_SCB_MODE_SPI                 (0x02u)
#define PC_Uart_SCB_MODE_UART                (0x04u)
#define PC_Uart_SCB_MODE_EZI2C               (0x08u)
#define PC_Uart_SCB_MODE_UNCONFIG            (0xFFu)

/* Condition compilation depends on operation mode: Unconfigured implies apply to all modes */
#define PC_Uart_SCB_MODE_I2C_CONST_CFG       (PC_Uart_SCB_MODE_I2C       == PC_Uart_SCB_MODE)
#define PC_Uart_SCB_MODE_SPI_CONST_CFG       (PC_Uart_SCB_MODE_SPI       == PC_Uart_SCB_MODE)
#define PC_Uart_SCB_MODE_UART_CONST_CFG      (PC_Uart_SCB_MODE_UART      == PC_Uart_SCB_MODE)
#define PC_Uart_SCB_MODE_EZI2C_CONST_CFG     (PC_Uart_SCB_MODE_EZI2C     == PC_Uart_SCB_MODE)
#define PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG  (PC_Uart_SCB_MODE_UNCONFIG  == PC_Uart_SCB_MODE)

/* Condition compilation for includes */
#define PC_Uart_SCB_MODE_I2C_INC      (0u !=(PC_Uart_SCB_MODE_I2C   & PC_Uart_SCB_MODE))
#define PC_Uart_SCB_MODE_EZI2C_INC    (0u !=(PC_Uart_SCB_MODE_EZI2C & PC_Uart_SCB_MODE))
#if (!PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_SCB_MODE_SPI_INC  (0u !=(PC_Uart_SCB_MODE_SPI   & PC_Uart_SCB_MODE))
    #define PC_Uart_SCB_MODE_UART_INC (0u !=(PC_Uart_SCB_MODE_UART  & PC_Uart_SCB_MODE))
#else
    #define PC_Uart_SCB_MODE_SPI_INC  (0u)
    #define PC_Uart_SCB_MODE_UART_INC (0u)
#endif /* (!PC_Uart_CY_SCBIP_V1) */

/* Interrupts remove options */
#define PC_Uart_REMOVE_SCB_IRQ             (1u)
#define PC_Uart_SCB_IRQ_INTERNAL           (0u == PC_Uart_REMOVE_SCB_IRQ)

#define PC_Uart_REMOVE_UART_RX_WAKEUP_IRQ  (1u)
#define PC_Uart_UART_RX_WAKEUP_IRQ         (0u == PC_Uart_REMOVE_UART_RX_WAKEUP_IRQ)

/* SCB interrupt enum */
#define PC_Uart_SCB_INTR_MODE_NONE     (0u)
#define PC_Uart_SCB_INTR_MODE_INTERNAL (1u)
#define PC_Uart_SCB_INTR_MODE_EXTERNAL (2u)

/* Internal clock remove option */
#define PC_Uart_REMOVE_SCB_CLK     (0u)
#define PC_Uart_SCB_CLK_INTERNAL   (0u == PC_Uart_REMOVE_SCB_CLK)


/***************************************
*       Includes
****************************************/

#include "PC_Uart_PINS.h"

#if (PC_Uart_SCB_CLK_INTERNAL)
    #include "PC_Uart_SCBCLK.h"
#endif /* (PC_Uart_SCB_CLK_INTERNAL) */


/***************************************
*       Type Definitions
***************************************/

typedef struct
{
    uint8 enableState;
} PC_Uart_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* Start and Stop APIs */
void PC_Uart_Init(void);
void PC_Uart_Enable(void);
void PC_Uart_Start(void);
void PC_Uart_Stop(void);

/* Sleep and Wakeup APis */
void PC_Uart_Sleep(void);
void PC_Uart_Wakeup(void);

#if (PC_Uart_SCB_IRQ_INTERNAL)
    /* Custom interrupt handler */
    void PC_Uart_SetCustomInterruptHandler(void (*func)(void));
#endif /* (PC_Uart_SCB_IRQ_INTERNAL) */

/* Interface to internal interrupt component */
#if (PC_Uart_SCB_IRQ_INTERNAL)
    #define PC_Uart_EnableInt()        CyIntEnable      (PC_Uart_ISR_NUMBER)
    #define PC_Uart_DisableInt()       CyIntDisable     (PC_Uart_ISR_NUMBER)
    #define PC_Uart_ClearPendingInt()  CyIntClearPending(PC_Uart_ISR_NUMBER)
#endif /* (PC_Uart_SCB_IRQ_INTERNAL) */

#if (PC_Uart_UART_RX_WAKEUP_IRQ)
    #define PC_Uart_RxWakeEnableInt()        CyIntEnable      (PC_Uart_RX_WAKE_ISR_NUMBER)
    #define PC_Uart_RxWakeDisableInt()       CyIntDisable     (PC_Uart_RX_WAKE_ISR_NUMBER)
    #define PC_Uart_RxWakeClearPendingInt()  CyIntClearPending(PC_Uart_RX_WAKE_ISR_NUMBER)
#endif /* (PC_Uart_UART_RX_WAKEUP_IRQ) */

/* Get interrupt cause */
#define PC_Uart_GetInterruptCause()    (PC_Uart_INTR_CAUSE_REG)

/* APIs to service INTR_RX register */
#define PC_Uart_SetRxInterruptMode(interruptMask)     PC_Uart_WRITE_INTR_RX_MASK(interruptMask)
#define PC_Uart_ClearRxInterruptSource(interruptMask) PC_Uart_CLEAR_INTR_RX(interruptMask)
#define PC_Uart_SetRxInterrupt(interruptMask)         PC_Uart_SET_INTR_RX(interruptMask)
#define PC_Uart_GetRxInterruptSource()                (PC_Uart_INTR_RX_REG)
#define PC_Uart_GetRxInterruptMode()                  (PC_Uart_INTR_RX_MASK_REG)
#define PC_Uart_GetRxInterruptSourceMasked()          (PC_Uart_INTR_RX_MASKED_REG)
void PC_Uart_SetRxFifoLevel(uint32 level);

/* APIs to service INTR_TX register */
#define PC_Uart_SetTxInterruptMode(interruptMask)     PC_Uart_WRITE_INTR_TX_MASK(interruptMask)
#define PC_Uart_ClearTxInterruptSource(interruptMask) PC_Uart_CLEAR_INTR_TX(interruptMask)
#define PC_Uart_SetTxInterrupt(interruptMask)         PC_Uart_SET_INTR_TX(interruptMask)
#define PC_Uart_GetTxInterruptSource()                (PC_Uart_INTR_TX_REG)
#define PC_Uart_GetTxInterruptMode()                  (PC_Uart_INTR_TX_MASK_REG)
#define PC_Uart_GetTxInterruptSourceMasked()          (PC_Uart_INTR_TX_MASKED_REG)
void PC_Uart_SetTxFifoLevel(uint32 level);

/* APIs to service INTR_MASTER register */
#define PC_Uart_SetMasterInterruptMode(interruptMask)    PC_Uart_WRITE_INTR_MASTER_MASK(interruptMask)
#define PC_Uart_ClearMasterInterruptSource(interruptMask) PC_Uart_CLEAR_INTR_MASTER(interruptMask)
#define PC_Uart_SetMasterInterrupt(interruptMask)         PC_Uart_SET_INTR_MASTER(interruptMask)
#define PC_Uart_GetMasterInterruptSource()                (PC_Uart_INTR_MASTER_REG)
#define PC_Uart_GetMasterInterruptMode()                  (PC_Uart_INTR_MASTER_MASK_REG)
#define PC_Uart_GetMasterInterruptSourceMasked()          (PC_Uart_INTR_MASTER_MASKED_REG)

/* APIs to service INTR_SLAVE register */
#define PC_Uart_SetSlaveInterruptMode(interruptMask)     PC_Uart_WRITE_INTR_SLAVE_MASK(interruptMask)
#define PC_Uart_ClearSlaveInterruptSource(interruptMask) PC_Uart_CLEAR_INTR_SLAVE(interruptMask)
#define PC_Uart_SetSlaveInterrupt(interruptMask)         PC_Uart_SET_INTR_SLAVE(interruptMask)
#define PC_Uart_GetSlaveInterruptSource()                (PC_Uart_INTR_SLAVE_REG)
#define PC_Uart_GetSlaveInterruptMode()                  (PC_Uart_INTR_SLAVE_MASK_REG)
#define PC_Uart_GetSlaveInterruptSourceMasked()          (PC_Uart_INTR_SLAVE_MASKED_REG)


/***************************************
*     Vars with External Linkage
***************************************/

extern uint8 PC_Uart_initVar;


/***************************************
*              Registers
***************************************/

#define PC_Uart_CTRL_REG               (*(reg32 *) PC_Uart_SCB__CTRL)
#define PC_Uart_CTRL_PTR               ( (reg32 *) PC_Uart_SCB__CTRL)

#define PC_Uart_STATUS_REG             (*(reg32 *) PC_Uart_SCB__STATUS)
#define PC_Uart_STATUS_PTR             ( (reg32 *) PC_Uart_SCB__STATUS)

#if (!PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_SPI_CTRL_REG           (*(reg32 *) PC_Uart_SCB__SPI_CTRL)
    #define PC_Uart_SPI_CTRL_PTR           ( (reg32 *) PC_Uart_SCB__SPI_CTRL)

    #define PC_Uart_SPI_STATUS_REG         (*(reg32 *) PC_Uart_SCB__SPI_STATUS)
    #define PC_Uart_SPI_STATUS_PTR         ( (reg32 *) PC_Uart_SCB__SPI_STATUS)

    #define PC_Uart_UART_CTRL_REG          (*(reg32 *) PC_Uart_SCB__UART_CTRL)
    #define PC_Uart_UART_CTRL_PTR          ( (reg32 *) PC_Uart_SCB__UART_CTRL)

    #define PC_Uart_UART_TX_CTRL_REG       (*(reg32 *) PC_Uart_SCB__UART_TX_CTRL)
    #define PC_Uart_UART_TX_CTRL_PTR       ( (reg32 *) PC_Uart_SCB__UART_TX_CTRL)

    #define PC_Uart_UART_RX_CTRL_REG       (*(reg32 *) PC_Uart_SCB__UART_RX_CTRL)
    #define PC_Uart_UART_RX_CTRL_PTR       ( (reg32 *) PC_Uart_SCB__UART_RX_CTRL)

    #define PC_Uart_UART_RX_STATUS_REG     (*(reg32 *) PC_Uart_SCB__UART_RX_STATUS)
    #define PC_Uart_UART_RX_STATUS_PTR     ( (reg32 *) PC_Uart_SCB__UART_RX_STATUS)
#endif /* (!PC_Uart_CY_SCBIP_V1) */

#if !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_UART_FLOW_CTRL_REG     (*(reg32 *) PC_Uart_SCB__UART_FLOW_CTRL)
    #define PC_Uart_UART_FLOW_CTRL_PTR     ( (reg32 *) PC_Uart_SCB__UART_FLOW_CTRL)
#endif /* !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1) */

#define PC_Uart_I2C_CTRL_REG           (*(reg32 *) PC_Uart_SCB__I2C_CTRL)
#define PC_Uart_I2C_CTRL_PTR           ( (reg32 *) PC_Uart_SCB__I2C_CTRL)

#define PC_Uart_I2C_STATUS_REG         (*(reg32 *) PC_Uart_SCB__I2C_STATUS)
#define PC_Uart_I2C_STATUS_PTR         ( (reg32 *) PC_Uart_SCB__I2C_STATUS)

#define PC_Uart_I2C_MASTER_CMD_REG     (*(reg32 *) PC_Uart_SCB__I2C_M_CMD)
#define PC_Uart_I2C_MASTER_CMD_PTR     ( (reg32 *) PC_Uart_SCB__I2C_M_CMD)

#define PC_Uart_I2C_SLAVE_CMD_REG      (*(reg32 *) PC_Uart_SCB__I2C_S_CMD)
#define PC_Uart_I2C_SLAVE_CMD_PTR      ( (reg32 *) PC_Uart_SCB__I2C_S_CMD)

#define PC_Uart_I2C_CFG_REG            (*(reg32 *) PC_Uart_SCB__I2C_CFG)
#define PC_Uart_I2C_CFG_PTR            ( (reg32 *) PC_Uart_SCB__I2C_CFG)

#define PC_Uart_TX_CTRL_REG            (*(reg32 *) PC_Uart_SCB__TX_CTRL)
#define PC_Uart_TX_CTRL_PTR            ( (reg32 *) PC_Uart_SCB__TX_CTRL)

#define PC_Uart_TX_FIFO_CTRL_REG       (*(reg32 *) PC_Uart_SCB__TX_FIFO_CTRL)
#define PC_Uart_TX_FIFO_CTRL_PTR       ( (reg32 *) PC_Uart_SCB__TX_FIFO_CTRL)

#define PC_Uart_TX_FIFO_STATUS_REG     (*(reg32 *) PC_Uart_SCB__TX_FIFO_STATUS)
#define PC_Uart_TX_FIFO_STATUS_PTR     ( (reg32 *) PC_Uart_SCB__TX_FIFO_STATUS)

#define PC_Uart_TX_FIFO_WR_REG         (*(reg32 *) PC_Uart_SCB__TX_FIFO_WR)
#define PC_Uart_TX_FIFO_WR_PTR         ( (reg32 *) PC_Uart_SCB__TX_FIFO_WR)

#define PC_Uart_RX_CTRL_REG            (*(reg32 *) PC_Uart_SCB__RX_CTRL)
#define PC_Uart_RX_CTRL_PTR            ( (reg32 *) PC_Uart_SCB__RX_CTRL)

#define PC_Uart_RX_FIFO_CTRL_REG       (*(reg32 *) PC_Uart_SCB__RX_FIFO_CTRL)
#define PC_Uart_RX_FIFO_CTRL_PTR       ( (reg32 *) PC_Uart_SCB__RX_FIFO_CTRL)

#define PC_Uart_RX_FIFO_STATUS_REG     (*(reg32 *) PC_Uart_SCB__RX_FIFO_STATUS)
#define PC_Uart_RX_FIFO_STATUS_PTR     ( (reg32 *) PC_Uart_SCB__RX_FIFO_STATUS)

#define PC_Uart_RX_MATCH_REG           (*(reg32 *) PC_Uart_SCB__RX_MATCH)
#define PC_Uart_RX_MATCH_PTR           ( (reg32 *) PC_Uart_SCB__RX_MATCH)

#define PC_Uart_RX_FIFO_RD_REG         (*(reg32 *) PC_Uart_SCB__RX_FIFO_RD)
#define PC_Uart_RX_FIFO_RD_PTR         ( (reg32 *) PC_Uart_SCB__RX_FIFO_RD)

#define PC_Uart_RX_FIFO_RD_SILENT_REG  (*(reg32 *) PC_Uart_SCB__RX_FIFO_RD_SILENT)
#define PC_Uart_RX_FIFO_RD_SILENT_PTR  ( (reg32 *) PC_Uart_SCB__RX_FIFO_RD_SILENT)

#define PC_Uart_EZBUF_DATA00_REG       (*(reg32 *) PC_Uart_SCB__EZ_DATA00)
#define PC_Uart_EZBUF_DATA00_PTR       ( (reg32 *) PC_Uart_SCB__EZ_DATA00)

#define PC_Uart_INTR_CAUSE_REG         (*(reg32 *) PC_Uart_SCB__INTR_CAUSE)
#define PC_Uart_INTR_CAUSE_PTR         ( (reg32 *) PC_Uart_SCB__INTR_CAUSE)

#define PC_Uart_INTR_I2C_EC_REG        (*(reg32 *) PC_Uart_SCB__INTR_I2C_EC)
#define PC_Uart_INTR_I2C_EC_PTR        ( (reg32 *) PC_Uart_SCB__INTR_I2C_EC)

#define PC_Uart_INTR_I2C_EC_MASK_REG   (*(reg32 *) PC_Uart_SCB__INTR_I2C_EC_MASK)
#define PC_Uart_INTR_I2C_EC_MASK_PTR   ( (reg32 *) PC_Uart_SCB__INTR_I2C_EC_MASK)

#define PC_Uart_INTR_I2C_EC_MASKED_REG (*(reg32 *) PC_Uart_SCB__INTR_I2C_EC_MASKED)
#define PC_Uart_INTR_I2C_EC_MASKED_PTR ( (reg32 *) PC_Uart_SCB__INTR_I2C_EC_MASKED)

#if (!PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_INTR_SPI_EC_REG        (*(reg32 *) PC_Uart_SCB__INTR_SPI_EC)
    #define PC_Uart_INTR_SPI_EC_PTR        ( (reg32 *) PC_Uart_SCB__INTR_SPI_EC)

    #define PC_Uart_INTR_SPI_EC_MASK_REG   (*(reg32 *) PC_Uart_SCB__INTR_SPI_EC_MASK)
    #define PC_Uart_INTR_SPI_EC_MASK_PTR   ( (reg32 *) PC_Uart_SCB__INTR_SPI_EC_MASK)

    #define PC_Uart_INTR_SPI_EC_MASKED_REG (*(reg32 *) PC_Uart_SCB__INTR_SPI_EC_MASKED)
    #define PC_Uart_INTR_SPI_EC_MASKED_PTR ( (reg32 *) PC_Uart_SCB__INTR_SPI_EC_MASKED)
#endif /* (!PC_Uart_CY_SCBIP_V1) */

#define PC_Uart_INTR_MASTER_REG        (*(reg32 *) PC_Uart_SCB__INTR_M)
#define PC_Uart_INTR_MASTER_PTR        ( (reg32 *) PC_Uart_SCB__INTR_M)

#define PC_Uart_INTR_MASTER_SET_REG    (*(reg32 *) PC_Uart_SCB__INTR_M_SET)
#define PC_Uart_INTR_MASTER_SET_PTR    ( (reg32 *) PC_Uart_SCB__INTR_M_SET)

#define PC_Uart_INTR_MASTER_MASK_REG   (*(reg32 *) PC_Uart_SCB__INTR_M_MASK)
#define PC_Uart_INTR_MASTER_MASK_PTR   ( (reg32 *) PC_Uart_SCB__INTR_M_MASK)

#define PC_Uart_INTR_MASTER_MASKED_REG (*(reg32 *) PC_Uart_SCB__INTR_M_MASKED)
#define PC_Uart_INTR_MASTER_MASKED_PTR ( (reg32 *) PC_Uart_SCB__INTR_M_MASKED)

#define PC_Uart_INTR_SLAVE_REG         (*(reg32 *) PC_Uart_SCB__INTR_S)
#define PC_Uart_INTR_SLAVE_PTR         ( (reg32 *) PC_Uart_SCB__INTR_S)

#define PC_Uart_INTR_SLAVE_SET_REG     (*(reg32 *) PC_Uart_SCB__INTR_S_SET)
#define PC_Uart_INTR_SLAVE_SET_PTR     ( (reg32 *) PC_Uart_SCB__INTR_S_SET)

#define PC_Uart_INTR_SLAVE_MASK_REG    (*(reg32 *) PC_Uart_SCB__INTR_S_MASK)
#define PC_Uart_INTR_SLAVE_MASK_PTR    ( (reg32 *) PC_Uart_SCB__INTR_S_MASK)

#define PC_Uart_INTR_SLAVE_MASKED_REG  (*(reg32 *) PC_Uart_SCB__INTR_S_MASKED)
#define PC_Uart_INTR_SLAVE_MASKED_PTR  ( (reg32 *) PC_Uart_SCB__INTR_S_MASKED)

#define PC_Uart_INTR_TX_REG            (*(reg32 *) PC_Uart_SCB__INTR_TX)
#define PC_Uart_INTR_TX_PTR            ( (reg32 *) PC_Uart_SCB__INTR_TX)

#define PC_Uart_INTR_TX_SET_REG        (*(reg32 *) PC_Uart_SCB__INTR_TX_SET)
#define PC_Uart_INTR_TX_SET_PTR        ( (reg32 *) PC_Uart_SCB__INTR_TX_SET)

#define PC_Uart_INTR_TX_MASK_REG       (*(reg32 *) PC_Uart_SCB__INTR_TX_MASK)
#define PC_Uart_INTR_TX_MASK_PTR       ( (reg32 *) PC_Uart_SCB__INTR_TX_MASK)

#define PC_Uart_INTR_TX_MASKED_REG     (*(reg32 *) PC_Uart_SCB__INTR_TX_MASKED)
#define PC_Uart_INTR_TX_MASKED_PTR     ( (reg32 *) PC_Uart_SCB__INTR_TX_MASKED)

#define PC_Uart_INTR_RX_REG            (*(reg32 *) PC_Uart_SCB__INTR_RX)
#define PC_Uart_INTR_RX_PTR            ( (reg32 *) PC_Uart_SCB__INTR_RX)

#define PC_Uart_INTR_RX_SET_REG        (*(reg32 *) PC_Uart_SCB__INTR_RX_SET)
#define PC_Uart_INTR_RX_SET_PTR        ( (reg32 *) PC_Uart_SCB__INTR_RX_SET)

#define PC_Uart_INTR_RX_MASK_REG       (*(reg32 *) PC_Uart_SCB__INTR_RX_MASK)
#define PC_Uart_INTR_RX_MASK_PTR       ( (reg32 *) PC_Uart_SCB__INTR_RX_MASK)

#define PC_Uart_INTR_RX_MASKED_REG     (*(reg32 *) PC_Uart_SCB__INTR_RX_MASKED)
#define PC_Uart_INTR_RX_MASKED_PTR     ( (reg32 *) PC_Uart_SCB__INTR_RX_MASKED)

#if (PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_FF_DATA_NR_LOG2_PLUS1_MASK (0x0Fu) /* FF_DATA_NR_LOG2_PLUS1 = 4, MASK = 2^4 - 1 = 15 */
    #define PC_Uart_FF_DATA_NR_LOG2_MASK       (0x07u) /* FF_DATA_NR_LOG2 = 3, MASK = 2^3 - 1 = 7 */
#else
    #define PC_Uart_FF_DATA_NR_LOG2_PLUS1_MASK (0x1Fu) /* FF_DATA_NR_LOG2_PLUS1 = 5, MASK = 2^5 - 1 = 31 */
    #define PC_Uart_FF_DATA_NR_LOG2_MASK       (0x0Fu) /* FF_DATA_NR_LOG2 = 4, MASK = 2^4 - 1 = 15 */
#endif /* (PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1) */


/***************************************
*        Registers Constants
***************************************/

#if (PC_Uart_SCB_IRQ_INTERNAL)
    #define PC_Uart_ISR_NUMBER     ((uint8) PC_Uart_SCB_IRQ__INTC_NUMBER)
    #define PC_Uart_ISR_PRIORITY   ((uint8) PC_Uart_SCB_IRQ__INTC_PRIOR_NUM)
#endif /* (PC_Uart_SCB_IRQ_INTERNAL) */

#if (PC_Uart_UART_RX_WAKEUP_IRQ)
    #define PC_Uart_RX_WAKE_ISR_NUMBER     ((uint8) PC_Uart_RX_WAKEUP_IRQ__INTC_NUMBER)
    #define PC_Uart_RX_WAKE_ISR_PRIORITY   ((uint8) PC_Uart_RX_WAKEUP_IRQ__INTC_PRIOR_NUM)
#endif /* (PC_Uart_UART_RX_WAKEUP_IRQ) */

/* PC_Uart_CTRL_REG */
#define PC_Uart_CTRL_OVS_POS           (0u)  /* [3:0]   Oversampling factor                 */
#define PC_Uart_CTRL_EC_AM_MODE_POS    (8u)  /* [8]     Externally clocked address match    */
#define PC_Uart_CTRL_EC_OP_MODE_POS    (9u)  /* [9]     Externally clocked operation mode   */
#define PC_Uart_CTRL_EZBUF_MODE_POS    (10u) /* [10]    EZ buffer is enabled                */
#if !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_CTRL_BYTE_MODE_POS (11u) /* [11]    Determines the number of bits per FIFO data element */
#endif /* !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1) */
#define PC_Uart_CTRL_ADDR_ACCEPT_POS   (16u) /* [16]    Put matched address in RX FIFO       */
#define PC_Uart_CTRL_BLOCK_POS         (17u) /* [17]    Ext and Int logic to resolve collide */
#define PC_Uart_CTRL_MODE_POS          (24u) /* [25:24] Operation mode                       */
#define PC_Uart_CTRL_ENABLED_POS       (31u) /* [31]    Enable SCB block                     */
#define PC_Uart_CTRL_OVS_MASK          ((uint32) 0x0Fu)
#define PC_Uart_CTRL_EC_AM_MODE        ((uint32) 0x01u << PC_Uart_CTRL_EC_AM_MODE_POS)
#define PC_Uart_CTRL_EC_OP_MODE        ((uint32) 0x01u << PC_Uart_CTRL_EC_OP_MODE_POS)
#define PC_Uart_CTRL_EZBUF_MODE        ((uint32) 0x01u << PC_Uart_CTRL_EZBUF_MODE_POS)
#if !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_CTRL_BYTE_MODE ((uint32) 0x01u << PC_Uart_CTRL_BYTE_MODE_POS)
#endif /* !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1) */
#define PC_Uart_CTRL_ADDR_ACCEPT       ((uint32) 0x01u << PC_Uart_CTRL_ADDR_ACCEPT_POS)
#define PC_Uart_CTRL_BLOCK             ((uint32) 0x01u << PC_Uart_CTRL_BLOCK_POS)
#define PC_Uart_CTRL_MODE_MASK         ((uint32) 0x03u << PC_Uart_CTRL_MODE_POS)
#define PC_Uart_CTRL_MODE_I2C          ((uint32) 0x00u)
#define PC_Uart_CTRL_MODE_SPI          ((uint32) 0x01u << PC_Uart_CTRL_MODE_POS)
#define PC_Uart_CTRL_MODE_UART         ((uint32) 0x02u << PC_Uart_CTRL_MODE_POS)
#define PC_Uart_CTRL_ENABLED           ((uint32) 0x01u << PC_Uart_CTRL_ENABLED_POS)

/* PC_Uart_STATUS_REG */
#define PC_Uart_STATUS_EC_BUSY_POS     (0u)  /* [0] Bus busy. Externally clocked logic access to EZ memory */
#define PC_Uart_STATUS_EC_BUSY         ((uint32) 0x0Fu)

/* PC_Uart_SPI_CTRL_REG  */
#define PC_Uart_SPI_CTRL_CONTINUOUS_POS        (0u)  /* [0]     Continuous or Separated SPI data transfers */
#define PC_Uart_SPI_CTRL_SELECT_PRECEDE_POS    (1u)  /* [1]     Precedes or coincides start of data frame  */
#define PC_Uart_SPI_CTRL_CPHA_POS              (2u)  /* [2]     SCLK phase                                 */
#define PC_Uart_SPI_CTRL_CPOL_POS              (3u)  /* [3]     SCLK polarity                              */
#define PC_Uart_SPI_CTRL_LATE_MISO_SAMPLE_POS  (4u)  /* [4]     Late MISO sample enabled                   */
#if !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_SPI_CTRL_SCLK_CONTINUOUS_POS   (5u)  /* [5]     Enable continuous SCLK generation */
    #define PC_Uart_SPI_CTRL_SSEL0_POLARITY_POS    (8u)  /* [8]     SS0 polarity                      */
    #define PC_Uart_SPI_CTRL_SSEL1_POLARITY_POS    (9u)  /* [9]     SS1 polarity                      */
    #define PC_Uart_SPI_CTRL_SSEL2_POLARITY_POS    (10u) /* [10]    SS2 polarity                      */
    #define PC_Uart_SPI_CTRL_SSEL3_POLARITY_POS    (11u) /* [11]    SS3 polarity                      */
#endif /* !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1) */
#define PC_Uart_SPI_CTRL_LOOPBACK_POS          (16u) /* [16]    Local loop-back control enabled            */
#define PC_Uart_SPI_CTRL_MODE_POS              (24u) /* [25:24] Submode of SPI operation                   */
#define PC_Uart_SPI_CTRL_SLAVE_SELECT_POS      (26u) /* [27:26] Selects SPI SS signal                      */
#define PC_Uart_SPI_CTRL_MASTER_MODE_POS       (31u) /* [31]    Master mode enabled                        */
#define PC_Uart_SPI_CTRL_CONTINUOUS            ((uint32) 0x01u)
#define PC_Uart_SPI_CTRL_SELECT_PRECEDE        ((uint32) 0x01u << PC_Uart_SPI_CTRL_SELECT_PRECEDE_POS)
#define PC_Uart_SPI_CTRL_SCLK_MODE_MASK        ((uint32) 0x03u << PC_Uart_SPI_CTRL_CPHA_POS)
#define PC_Uart_SPI_CTRL_CPHA                  ((uint32) 0x01u << PC_Uart_SPI_CTRL_CPHA_POS)
#define PC_Uart_SPI_CTRL_CPOL                  ((uint32) 0x01u << PC_Uart_SPI_CTRL_CPOL_POS)
#define PC_Uart_SPI_CTRL_LATE_MISO_SAMPLE      ((uint32) 0x01u << \
                                                                    PC_Uart_SPI_CTRL_LATE_MISO_SAMPLE_POS)
#if !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_SPI_CTRL_SCLK_CONTINUOUS  ((uint32) 0x01u << PC_Uart_SPI_CTRL_SCLK_CONTINUOUS_POS)
    #define PC_Uart_SPI_CTRL_SSEL0_POLARITY   ((uint32) 0x01u << PC_Uart_SPI_CTRL_SSEL0_POLARITY_POS)
    #define PC_Uart_SPI_CTRL_SSEL1_POLARITY   ((uint32) 0x01u << PC_Uart_SPI_CTRL_SSEL1_POLARITY_POS)
    #define PC_Uart_SPI_CTRL_SSEL2_POLARITY   ((uint32) 0x01u << PC_Uart_SPI_CTRL_SSEL2_POLARITY_POS)
    #define PC_Uart_SPI_CTRL_SSEL3_POLARITY   ((uint32) 0x01u << PC_Uart_SPI_CTRL_SSEL3_POLARITY_POS)
    #define PC_Uart_SPI_CTRL_SSEL_POLARITY_MASK ((uint32)0x0Fu << PC_Uart_SPI_CTRL_SSEL0_POLARITY_POS)
#endif /* !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1) */

#define PC_Uart_SPI_CTRL_LOOPBACK              ((uint32) 0x01u << PC_Uart_SPI_CTRL_LOOPBACK_POS)
#define PC_Uart_SPI_CTRL_MODE_MASK             ((uint32) 0x03u << PC_Uart_SPI_CTRL_MODE_POS)
#define PC_Uart_SPI_CTRL_MODE_MOTOROLA         ((uint32) 0x00u)
#define PC_Uart_SPI_CTRL_MODE_TI               ((uint32) 0x01u << PC_Uart_CTRL_MODE_POS)
#define PC_Uart_SPI_CTRL_MODE_NS               ((uint32) 0x02u << PC_Uart_CTRL_MODE_POS)
#define PC_Uart_SPI_CTRL_SLAVE_SELECT_MASK     ((uint32) 0x03u << PC_Uart_SPI_CTRL_SLAVE_SELECT_POS)
#define PC_Uart_SPI_CTRL_SLAVE_SELECT0         ((uint32) 0x00u)
#define PC_Uart_SPI_CTRL_SLAVE_SELECT1         ((uint32) 0x01u << PC_Uart_SPI_CTRL_SLAVE_SELECT_POS)
#define PC_Uart_SPI_CTRL_SLAVE_SELECT2         ((uint32) 0x02u << PC_Uart_SPI_CTRL_SLAVE_SELECT_POS)
#define PC_Uart_SPI_CTRL_SLAVE_SELECT3         ((uint32) 0x03u << PC_Uart_SPI_CTRL_SLAVE_SELECT_POS)
#define PC_Uart_SPI_CTRL_MASTER                ((uint32) 0x01u << PC_Uart_SPI_CTRL_MASTER_MODE_POS)
#define PC_Uart_SPI_CTRL_SLAVE                 ((uint32) 0x00u)

/* PC_Uart_SPI_STATUS_REG  */
#define PC_Uart_SPI_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy - slave selected */
#define PC_Uart_SPI_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EzAddress                 */
#define PC_Uart_SPI_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define PC_Uart_SPI_STATUS_EZBUF_ADDR_MASK ((uint32) 0xFFu << PC_Uart_I2C_STATUS_EZBUF_ADDR_POS)

/* PC_Uart_UART_CTRL */
#define PC_Uart_UART_CTRL_LOOPBACK_POS         (16u) /* [16] Loop-back    */
#define PC_Uart_UART_CTRL_MODE_POS             (24u) /* [24] UART subMode */
#define PC_Uart_UART_CTRL_LOOPBACK             ((uint32) 0x01u << PC_Uart_UART_CTRL_LOOPBACK_POS)
#define PC_Uart_UART_CTRL_MODE_UART_STD        ((uint32) 0x00u)
#define PC_Uart_UART_CTRL_MODE_UART_SMARTCARD  ((uint32) 0x01u << PC_Uart_UART_CTRL_MODE_POS)
#define PC_Uart_UART_CTRL_MODE_UART_IRDA       ((uint32) 0x02u << PC_Uart_UART_CTRL_MODE_POS)
#define PC_Uart_UART_CTRL_MODE_MASK            ((uint32) 0x03u << PC_Uart_UART_CTRL_MODE_POS)

/* PC_Uart_UART_TX_CTRL */
#define PC_Uart_UART_TX_CTRL_STOP_BITS_POS         (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period */
#define PC_Uart_UART_TX_CTRL_PARITY_POS            (4u)  /* [4]   Parity bit                              */
#define PC_Uart_UART_TX_CTRL_PARITY_ENABLED_POS    (5u)  /* [5]   Parity enable                           */
#define PC_Uart_UART_TX_CTRL_RETRY_ON_NACK_POS     (8u)  /* [8]   Smart Card: re-send frame on NACK       */
#define PC_Uart_UART_TX_CTRL_ONE_STOP_BIT          ((uint32) 0x01u)
#define PC_Uart_UART_TX_CTRL_ONE_HALF_STOP_BITS    ((uint32) 0x02u)
#define PC_Uart_UART_TX_CTRL_TWO_STOP_BITS         ((uint32) 0x03u)
#define PC_Uart_UART_TX_CTRL_STOP_BITS_MASK        ((uint32) 0x07u)
#define PC_Uart_UART_TX_CTRL_PARITY                ((uint32) 0x01u << \
                                                                    PC_Uart_UART_TX_CTRL_PARITY_POS)
#define PC_Uart_UART_TX_CTRL_PARITY_ENABLED        ((uint32) 0x01u << \
                                                                    PC_Uart_UART_TX_CTRL_PARITY_ENABLED_POS)
#define PC_Uart_UART_TX_CTRL_RETRY_ON_NACK         ((uint32) 0x01u << \
                                                                    PC_Uart_UART_TX_CTRL_RETRY_ON_NACK_POS)

/* PC_Uart_UART_RX_CTRL */
#define PC_Uart_UART_RX_CTRL_STOP_BITS_POS             (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period*/
#define PC_Uart_UART_RX_CTRL_PARITY_POS                (4u)  /* [4]   Parity bit                             */
#define PC_Uart_UART_RX_CTRL_PARITY_ENABLED_POS        (5u)  /* [5]   Parity enable                          */
#define PC_Uart_UART_RX_CTRL_POLARITY_POS              (6u)  /* [6]   IrDA: inverts polarity of RX signal    */
#define PC_Uart_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS    (8u)  /* [8]   Drop and lost RX FIFO on parity error  */
#define PC_Uart_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS     (9u)  /* [9]   Drop and lost RX FIFO on frame error   */
#define PC_Uart_UART_RX_CTRL_MP_MODE_POS               (10u) /* [10]  Multi-processor mode                   */
#define PC_Uart_UART_RX_CTRL_LIN_MODE_POS              (12u) /* [12]  Lin mode: applicable for UART Standard */
#define PC_Uart_UART_RX_CTRL_SKIP_START_POS            (13u) /* [13]  Skip start not: only for UART Standard */
#define PC_Uart_UART_RX_CTRL_BREAK_WIDTH_POS           (16u) /* [19:16]  Break width: (Break width + 1)      */
#define PC_Uart_UART_TX_CTRL_ONE_STOP_BIT              ((uint32) 0x01u)
#define PC_Uart_UART_TX_CTRL_ONE_HALF_STOP_BITS        ((uint32) 0x02u)
#define PC_Uart_UART_TX_CTRL_TWO_STOP_BITS             ((uint32) 0x03u)
#define PC_Uart_UART_RX_CTRL_STOP_BITS_MASK            ((uint32) 0x07u)
#define PC_Uart_UART_RX_CTRL_PARITY                    ((uint32) 0x01u << \
                                                                    PC_Uart_UART_RX_CTRL_PARITY_POS)
#define PC_Uart_UART_RX_CTRL_PARITY_ENABLED            ((uint32) 0x01u << \
                                                                    PC_Uart_UART_RX_CTRL_PARITY_ENABLED_POS)
#define PC_Uart_UART_RX_CTRL_POLARITY                  ((uint32) 0x01u << \
                                                                    PC_Uart_UART_RX_CTRL_POLARITY_POS)
#define PC_Uart_UART_RX_CTRL_DROP_ON_PARITY_ERR        ((uint32) 0x01u << \
                                                                   PC_Uart_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS)
#define PC_Uart_UART_RX_CTRL_DROP_ON_FRAME_ERR         ((uint32) 0x01u << \
                                                                    PC_Uart_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS)
#define PC_Uart_UART_RX_CTRL_MP_MODE                   ((uint32) 0x01u << \
                                                                    PC_Uart_UART_RX_CTRL_MP_MODE_POS)
#define PC_Uart_UART_RX_CTRL_LIN_MODE                  ((uint32) 0x01u << \
                                                                    PC_Uart_UART_RX_CTRL_LIN_MODE_POS)
#define PC_Uart_UART_RX_CTRL_SKIP_START                ((uint32) 0x01u << \
                                                                    PC_Uart_UART_RX_CTRL_SKIP_START_POS)
#define PC_Uart_UART_RX_CTRL_BREAK_WIDTH_MASK          ((uint32) 0x0Fu << \
                                                                    PC_Uart_UART_RX_CTRL_BREAK_WIDTH_POS)
/* PC_Uart_UART_RX_STATUS_REG */
#define PC_Uart_UART_RX_STATUS_BR_COUNTER_POS     (0u)  /* [11:0] Baud Rate counter */
#define PC_Uart_UART_RX_STATUS_BR_COUNTER_MASK    ((uint32) 0xFFFu)

#if !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1)
    /* PC_Uart_UART_FLOW_CTRL_REG */
    #define PC_Uart_UART_FLOW_CTRL_TRIGGER_LEVEL_POS    (0u)  /* [7:0] RTS RX FIFO trigger level         */
    #define PC_Uart_UART_FLOW_CTRL_RTS_POLARITY_POS     (16u) /* [16]  Polarity of the RTS output signal */
    #define PC_Uart_UART_FLOW_CTRL_CTS_POLARITY_POS     (24u) /* [24]  Polarity of the CTS input signal  */
    #define PC_Uart_UART_FLOW_CTRL_CTS_ENABLED_POS      (25u) /* [25]  Enable CTS signal                 */
    #define PC_Uart_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK   ((uint32) PC_Uart_FF_DATA_NR_LOG2_MASK)
    #define PC_Uart_UART_FLOW_CTRL_RTS_POLARITY         ((uint32) 0x01u << \
                                                                       PC_Uart_UART_FLOW_CTRL_RTS_POLARITY_POS)
    #define PC_Uart_UART_FLOW_CTRL_CTS_POLARITY         ((uint32) 0x01u << \
                                                                       PC_Uart_UART_FLOW_CTRL_CTS_POLARITY_POS)
    #define PC_Uart_UART_FLOW_CTRL_CTS_ENABLE           ((uint32) 0x01u << \
                                                                       PC_Uart_UART_FLOW_CTRL_CTS_ENABLED_POS)
#endif /* !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1) */

/* PC_Uart_I2C_CTRL */
#define PC_Uart_I2C_CTRL_HIGH_PHASE_OVS_POS           (0u)   /* [3:0] Oversampling factor high: master only */
#define PC_Uart_I2C_CTRL_LOW_PHASE_OVS_POS            (4u)   /* [7:4] Oversampling factor low:  master only */
#define PC_Uart_I2C_CTRL_M_READY_DATA_ACK_POS         (8u)   /* [8]   Master ACKs data while RX FIFO != FULL*/
#define PC_Uart_I2C_CTRL_M_NOT_READY_DATA_NACK_POS    (9u)   /* [9]   Master NACKs data if RX FIFO ==  FULL */
#define PC_Uart_I2C_CTRL_S_GENERAL_IGNORE_POS         (11u)  /* [11]  Slave ignores General call            */
#define PC_Uart_I2C_CTRL_S_READY_ADDR_ACK_POS         (12u)  /* [12]  Slave ACKs Address if RX FIFO != FULL */
#define PC_Uart_I2C_CTRL_S_READY_DATA_ACK_POS         (13u)  /* [13]  Slave ACKs data while RX FIFO == FULL */
#define PC_Uart_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS    (14u)  /* [14]  Slave NACKs address if RX FIFO == FULL*/
#define PC_Uart_I2C_CTRL_S_NOT_READY_DATA_NACK_POS    (15u)  /* [15]  Slave NACKs data if RX FIFO is  FULL  */
#define PC_Uart_I2C_CTRL_LOOPBACK_POS                 (16u)  /* [16]  Loop-back                             */
#define PC_Uart_I2C_CTRL_SLAVE_MODE_POS               (30u)  /* [30]  Slave mode enabled                    */
#define PC_Uart_I2C_CTRL_MASTER_MODE_POS              (31u)  /* [31]  Master mode enabled                   */
#define PC_Uart_I2C_CTRL_HIGH_PHASE_OVS_MASK  ((uint32) 0x0Fu)
#define PC_Uart_I2C_CTRL_LOW_PHASE_OVS_MASK   ((uint32) 0x0Fu << \
                                                                PC_Uart_I2C_CTRL_LOW_PHASE_OVS_POS)
#define PC_Uart_I2C_CTRL_M_READY_DATA_ACK      ((uint32) 0x01u << \
                                                                PC_Uart_I2C_CTRL_M_READY_DATA_ACK_POS)
#define PC_Uart_I2C_CTRL_M_NOT_READY_DATA_NACK ((uint32) 0x01u << \
                                                                PC_Uart_I2C_CTRL_M_NOT_READY_DATA_NACK_POS)
#define PC_Uart_I2C_CTRL_S_GENERAL_IGNORE      ((uint32) 0x01u << \
                                                                PC_Uart_I2C_CTRL_S_GENERAL_IGNORE_POS)
#define PC_Uart_I2C_CTRL_S_READY_ADDR_ACK      ((uint32) 0x01u << \
                                                                PC_Uart_I2C_CTRL_S_READY_ADDR_ACK_POS)
#define PC_Uart_I2C_CTRL_S_READY_DATA_ACK      ((uint32) 0x01u << \
                                                                PC_Uart_I2C_CTRL_S_READY_DATA_ACK_POS)
#define PC_Uart_I2C_CTRL_S_NOT_READY_ADDR_NACK ((uint32) 0x01u << \
                                                                PC_Uart_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS)
#define PC_Uart_I2C_CTRL_S_NOT_READY_DATA_NACK ((uint32) 0x01u << \
                                                                PC_Uart_I2C_CTRL_S_NOT_READY_DATA_NACK_POS)
#define PC_Uart_I2C_CTRL_LOOPBACK              ((uint32) 0x01u << \
                                                                PC_Uart_I2C_CTRL_LOOPBACK_POS)
#define PC_Uart_I2C_CTRL_SLAVE_MODE            ((uint32) 0x01u << \
                                                                PC_Uart_I2C_CTRL_SLAVE_MODE_POS)
#define PC_Uart_I2C_CTRL_MASTER_MODE           ((uint32) 0x01u << \
                                                                PC_Uart_I2C_CTRL_MASTER_MODE_POS)
#define PC_Uart_I2C_CTRL_SLAVE_MASTER_MODE_MASK    ((uint32) 0x03u << \
                                                                PC_Uart_I2C_CTRL_SLAVE_MODE_POS)

/* PC_Uart_I2C_STATUS_REG  */
#define PC_Uart_I2C_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy: internally clocked */
#define PC_Uart_I2C_STATUS_S_READ_POS      (4u)  /* [4]    Slave is read by master      */
#define PC_Uart_I2C_STATUS_M_READ_POS      (5u)  /* [5]    Master reads Slave           */
#define PC_Uart_I2C_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EZAddress                    */
#define PC_Uart_I2C_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define PC_Uart_I2C_STATUS_S_READ          ((uint32) 0x01u << PC_Uart_I2C_STATUS_S_READ_POS)
#define PC_Uart_I2C_STATUS_M_READ          ((uint32) 0x01u << PC_Uart_I2C_STATUS_M_READ_POS)
#define PC_Uart_I2C_STATUS_EZBUF_ADDR_MASK ((uint32) 0xFFu << PC_Uart_I2C_STATUS_EZBUF_ADDR_POS)

/* PC_Uart_I2C_MASTER_CMD_REG */
#define PC_Uart_I2C_MASTER_CMD_M_START_POS             (0u)  /* [0] Master generate Start                */
#define PC_Uart_I2C_MASTER_CMD_M_START_ON_IDLE_POS     (1u)  /* [1] Master generate Start if bus is free */
#define PC_Uart_I2C_MASTER_CMD_M_ACK_POS               (2u)  /* [2] Master generate ACK                  */
#define PC_Uart_I2C_MASTER_CMD_M_NACK_POS              (3u)  /* [3] Master generate NACK                 */
#define PC_Uart_I2C_MASTER_CMD_M_STOP_POS              (4u)  /* [4] Master generate Stop                 */
#define PC_Uart_I2C_MASTER_CMD_M_START         ((uint32) 0x01u)
#define PC_Uart_I2C_MASTER_CMD_M_START_ON_IDLE ((uint32) 0x01u << \
                                                                   PC_Uart_I2C_MASTER_CMD_M_START_ON_IDLE_POS)
#define PC_Uart_I2C_MASTER_CMD_M_ACK           ((uint32) 0x01u << \
                                                                   PC_Uart_I2C_MASTER_CMD_M_ACK_POS)
#define PC_Uart_I2C_MASTER_CMD_M_NACK          ((uint32) 0x01u << \
                                                                    PC_Uart_I2C_MASTER_CMD_M_NACK_POS)
#define PC_Uart_I2C_MASTER_CMD_M_STOP          ((uint32) 0x01u << \
                                                                    PC_Uart_I2C_MASTER_CMD_M_STOP_POS)

/* PC_Uart_I2C_SLAVE_CMD_REG  */
#define PC_Uart_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define PC_Uart_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define PC_Uart_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define PC_Uart_I2C_SLAVE_CMD_S_NACK       ((uint32) 0x01u << PC_Uart_I2C_SLAVE_CMD_S_NACK_POS)

#define PC_Uart_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define PC_Uart_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define PC_Uart_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define PC_Uart_I2C_SLAVE_CMD_S_NACK       ((uint32) 0x01u << PC_Uart_I2C_SLAVE_CMD_S_NACK_POS)

/* PC_Uart_I2C_CFG_REG */
#if (PC_Uart_CY_SCBIP_V0)
#define PC_Uart_I2C_CFG_SDA_FILT_HYS_POS           (0u)  /* [1:0]   Trim bits for the I2C SDA filter         */
#define PC_Uart_I2C_CFG_SDA_FILT_TRIM_POS          (2u)  /* [3:2]   Trim bits for the I2C SDA filter         */
#define PC_Uart_I2C_CFG_SCL_FILT_HYS_POS           (4u)  /* [5:4]   Trim bits for the I2C SCL filter         */
#define PC_Uart_I2C_CFG_SCL_FILT_TRIM_POS          (6u)  /* [7:6]   Trim bits for the I2C SCL filter         */
#define PC_Uart_I2C_CFG_SDA_FILT_OUT_HYS_POS       (8u)  /* [9:8]   Trim bits for I2C SDA filter output path */
#define PC_Uart_I2C_CFG_SDA_FILT_OUT_TRIM_POS      (10u) /* [11:10] Trim bits for I2C SDA filter output path */
#define PC_Uart_I2C_CFG_SDA_FILT_HS_POS            (16u) /* [16]    '0': 50 ns filter, '1': 10 ns filter     */
#define PC_Uart_I2C_CFG_SDA_FILT_ENABLED_POS       (17u) /* [17]    I2C SDA filter enabled                   */
#define PC_Uart_I2C_CFG_SCL_FILT_HS_POS            (24u) /* [24]    '0': 50 ns filter, '1': 10 ns filter     */
#define PC_Uart_I2C_CFG_SCL_FILT_ENABLED_POS       (25u) /* [25]    I2C SCL filter enabled                   */
#define PC_Uart_I2C_CFG_SDA_FILT_OUT_HS_POS        (26u) /* [26]    '0': 50 ns filter, '1': 10 ns filter     */
#define PC_Uart_I2C_CFG_SDA_FILT_OUT_ENABLED_POS   (27u) /* [27]    I2C SDA output delay filter enabled      */
#define PC_Uart_I2C_CFG_SDA_FILT_HYS_MASK          ((uint32) 0x03u)
#define PC_Uart_I2C_CFG_SDA_FILT_TRIM_MASK         ((uint32) 0x03u << \
                                                                PC_Uart_I2C_CFG_SDA_FILT_TRIM_POS)
#define PC_Uart_I2C_CFG_SCL_FILT_HYS_MASK          ((uint32) 0x03u << \
                                                                PC_Uart_I2C_CFG_SCL_FILT_HYS_POS)
#define PC_Uart_I2C_CFG_SCL_FILT_TRIM_MASK         ((uint32) 0x03u << \
                                                                PC_Uart_I2C_CFG_SCL_FILT_TRIM_POS)
#define PC_Uart_I2C_CFG_SDA_FILT_OUT_HYS_MASK      ((uint32) 0x03u << \
                                                                PC_Uart_I2C_CFG_SDA_FILT_OUT_HYS_POS)
#define PC_Uart_I2C_CFG_SDA_FILT_OUT_TRIM_MASK     ((uint32) 0x03u << \
                                                                PC_Uart_I2C_CFG_SDA_FILT_OUT_TRIM_POS)
#define PC_Uart_I2C_CFG_SDA_FILT_HS                ((uint32) 0x01u << \
                                                                PC_Uart_I2C_CFG_SDA_FILT_HS_POS)
#define PC_Uart_I2C_CFG_SDA_FILT_ENABLED           ((uint32) 0x01u << \
                                                                PC_Uart_I2C_CFG_SDA_FILT_ENABLED_POS)
#define PC_Uart_I2C_CFG_SCL_FILT_HS                ((uint32) 0x01u << \
                                                                PC_Uart_I2C_CFG_SCL_FILT_HS_POS)
#define PC_Uart_I2C_CFG_SCL_FILT_ENABLED           ((uint32) 0x01u << \
                                                                PC_Uart_I2C_CFG_SCL_FILT_ENABLED_POS)
#define PC_Uart_I2C_CFG_SDA_FILT_OUT_HS            ((uint32) 0x01u << \
                                                                PC_Uart_I2C_CFG_SDA_FILT_OUT_HS_POS)
#define PC_Uart_I2C_CFG_SDA_FILT_OUT_ENABLED       ((uint32) 0x01u << \
                                                                PC_Uart_I2C_CFG_SDA_FILT_OUT_ENABLED_POS)
#else
#define PC_Uart_I2C_CFG_SDA_IN_FILT_TRIM_POS   (0u)  /* [1:0] Trim bits for "i2c_sda_in" 50 ns filter */
#define PC_Uart_I2C_CFG_SDA_IN_FILT_SEL_POS    (4u)  /* [4]   "i2c_sda_in" filter delay: 0 ns and 50 ns */
#define PC_Uart_I2C_CFG_SCL_IN_FILT_TRIM_POS   (8u)  /* [9:8] Trim bits for "i2c_scl_in" 50 ns filter */
#define PC_Uart_I2C_CFG_SCL_IN_FILT_SEL_POS    (12u) /* [12]  "i2c_scl_in" filter delay: 0 ns and 50 ns */
#define PC_Uart_I2C_CFG_SDA_OUT_FILT0_TRIM_POS (16u) /* [17:16] Trim bits for "i2c_sda_out" 50 ns filter 0 */
#define PC_Uart_I2C_CFG_SDA_OUT_FILT1_TRIM_POS (18u) /* [19:18] Trim bits for "i2c_sda_out" 50 ns filter 1 */
#define PC_Uart_I2C_CFG_SDA_OUT_FILT2_TRIM_POS (20u) /* [21:20] Trim bits for "i2c_sda_out" 50 ns filter 2 */
#define PC_Uart_I2C_CFG_SDA_OUT_FILT_SEL_POS   (28u) /* [29:28] Cumulative "i2c_sda_out" filter delay: */

#define PC_Uart_I2C_CFG_SDA_IN_FILT_TRIM_MASK  ((uint32) 0x03u)
#define PC_Uart_I2C_CFG_SDA_IN_FILT_SEL        ((uint32) 0x01u << PC_Uart_I2C_CFG_SDA_IN_FILT_SEL_POS)
#define PC_Uart_I2C_CFG_SCL_IN_FILT_TRIM_MASK  ((uint32) 0x03u << \
                                                            PC_Uart_I2C_CFG_SCL_IN_FILT_TRIM_POS)
#define PC_Uart_I2C_CFG_SCL_IN_FILT_SEL        ((uint32) 0x01u << PC_Uart_I2C_CFG_SCL_IN_FILT_SEL_POS)
#define PC_Uart_I2C_CFG_SDA_OUT_FILT0_TRIM_MASK ((uint32) 0x03u << \
                                                            PC_Uart_I2C_CFG_SDA_OUT_FILT0_TRIM_POS)
#define PC_Uart_I2C_CFG_SDA_OUT_FILT1_TRIM_MASK ((uint32) 0x03u << \
                                                            PC_Uart_I2C_CFG_SDA_OUT_FILT1_TRIM_POS)
#define PC_Uart_I2C_CFG_SDA_OUT_FILT2_TRIM_MASK ((uint32) 0x03u << \
                                                            PC_Uart_I2C_CFG_SDA_OUT_FILT2_TRIM_POS)
#define PC_Uart_I2C_CFG_SDA_OUT_FILT_SEL_MASK   ((uint32) 0x03u << \
                                                            PC_Uart_I2C_CFG_SDA_OUT_FILT_SEL_POS)
#endif /* (PC_Uart_CY_SCBIP_V0) */


/* PC_Uart_TX_CTRL_REG */
#define PC_Uart_TX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Data frame width: (Data width - 1) */
#define PC_Uart_TX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define PC_Uart_TX_CTRL_ENABLED_POS        (31u) /* [31]  Transmitter enabled               */
#define PC_Uart_TX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define PC_Uart_TX_CTRL_MSB_FIRST          ((uint32) 0x01u << PC_Uart_TX_CTRL_MSB_FIRST_POS)
#define PC_Uart_TX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define PC_Uart_TX_CTRL_ENABLED            ((uint32) 0x01u << PC_Uart_TX_CTRL_ENABLED_POS)

/* PC_Uart_TX_CTRL_FIFO_REG */
#define PC_Uart_TX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)  /* [2:0] Trigger level                              */
#define PC_Uart_TX_FIFO_CTRL_CLEAR_POS             (16u) /* [16]  Clear TX FIFO: cleared after set           */
#define PC_Uart_TX_FIFO_CTRL_FREEZE_POS            (17u) /* [17]  Freeze TX FIFO: HW do not inc read pointer */
#define PC_Uart_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) PC_Uart_FF_DATA_NR_LOG2_MASK)
#define PC_Uart_TX_FIFO_CTRL_CLEAR                 ((uint32) 0x01u << PC_Uart_TX_FIFO_CTRL_CLEAR_POS)
#define PC_Uart_TX_FIFO_CTRL_FREEZE                ((uint32) 0x01u << PC_Uart_TX_FIFO_CTRL_FREEZE_POS)

/* PC_Uart_TX_FIFO_STATUS_REG */
#define PC_Uart_TX_FIFO_STATUS_USED_POS    (0u)  /* [3:0]   Amount of entries in TX FIFO */
#define PC_Uart_TX_FIFO_SR_VALID_POS       (15u) /* [15]    Shifter status of TX FIFO    */
#define PC_Uart_TX_FIFO_STATUS_RD_PTR_POS  (16u) /* [18:16] TX FIFO read pointer         */
#define PC_Uart_TX_FIFO_STATUS_WR_PTR_POS  (24u) /* [26:24] TX FIFO write pointer        */
#define PC_Uart_TX_FIFO_STATUS_USED_MASK   ((uint32) PC_Uart_FF_DATA_NR_LOG2_PLUS1_MASK)
#define PC_Uart_TX_FIFO_SR_VALID           ((uint32) 0x01u << PC_Uart_TX_FIFO_SR_VALID_POS)
#define PC_Uart_TX_FIFO_STATUS_RD_PTR_MASK ((uint32) PC_Uart_FF_DATA_NR_LOG2_MASK << \
                                                                    PC_Uart_TX_FIFO_STATUS_RD_PTR_POS)
#define PC_Uart_TX_FIFO_STATUS_WR_PTR_MASK ((uint32) PC_Uart_FF_DATA_NR_LOG2_MASK << \
                                                                    PC_Uart_TX_FIFO_STATUS_WR_PTR_POS)

/* PC_Uart_TX_FIFO_WR_REG */
#define PC_Uart_TX_FIFO_WR_POS    (0u)  /* [15:0] Data written into TX FIFO */
#define PC_Uart_TX_FIFO_WR_MASK   ((uint32) 0xFFu)

/* PC_Uart_RX_CTRL_REG */
#define PC_Uart_RX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Data frame width: (Data width - 1) */
#define PC_Uart_RX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define PC_Uart_RX_CTRL_MEDIAN_POS         (9u)  /* [9]   Median filter                     */
#define PC_Uart_RX_CTRL_ENABLED_POS        (31u) /* [31]  Receiver enabled                  */
#define PC_Uart_RX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define PC_Uart_RX_CTRL_MSB_FIRST          ((uint32) 0x01u << PC_Uart_RX_CTRL_MSB_FIRST_POS)
#define PC_Uart_RX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define PC_Uart_RX_CTRL_MEDIAN             ((uint32) 0x01u << PC_Uart_RX_CTRL_MEDIAN_POS)
#define PC_Uart_RX_CTRL_ENABLED            ((uint32) 0x01u << PC_Uart_RX_CTRL_ENABLED_POS)


/* PC_Uart_RX_FIFO_CTRL_REG */
#define PC_Uart_RX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)   /* [2:0] Trigger level                            */
#define PC_Uart_RX_FIFO_CTRL_CLEAR_POS             (16u)  /* [16]  Clear RX FIFO: clear after set           */
#define PC_Uart_RX_FIFO_CTRL_FREEZE_POS            (17u)  /* [17]  Freeze RX FIFO: HW writes has not effect */
#define PC_Uart_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) PC_Uart_FF_DATA_NR_LOG2_MASK)
#define PC_Uart_RX_FIFO_CTRL_CLEAR                 ((uint32) 0x01u << PC_Uart_RX_FIFO_CTRL_CLEAR_POS)
#define PC_Uart_RX_FIFO_CTRL_FREEZE                ((uint32) 0x01u << PC_Uart_RX_FIFO_CTRL_FREEZE_POS)

/* PC_Uart_RX_FIFO_STATUS_REG */
#define PC_Uart_RX_FIFO_STATUS_USED_POS    (0u)   /* [3:0]   Amount of entries in RX FIFO */
#define PC_Uart_RX_FIFO_SR_VALID_POS       (15u)  /* [15]    Shifter status of RX FIFO    */
#define PC_Uart_RX_FIFO_STATUS_RD_PTR_POS  (16u)  /* [18:16] RX FIFO read pointer         */
#define PC_Uart_RX_FIFO_STATUS_WR_PTR_POS  (24u)  /* [26:24] RX FIFO write pointer        */
#define PC_Uart_RX_FIFO_STATUS_USED_MASK   ((uint32) PC_Uart_FF_DATA_NR_LOG2_PLUS1_MASK)
#define PC_Uart_RX_FIFO_SR_VALID           ((uint32) 0x01u << PC_Uart_RX_FIFO_SR_VALID_POS)
#define PC_Uart_RX_FIFO_STATUS_RD_PTR_MASK ((uint32) PC_Uart_FF_DATA_NR_LOG2_MASK << \
                                                                    PC_Uart_RX_FIFO_STATUS_RD_PTR_POS)
#define PC_Uart_RX_FIFO_STATUS_WR_PTR_MASK ((uint32) PC_Uart_FF_DATA_NR_LOG2_MASK << \
                                                                    PC_Uart_RX_FIFO_STATUS_WR_PTR_POS)

/* PC_Uart_RX_MATCH_REG */
#define PC_Uart_RX_MATCH_ADDR_POS     (0u)  /* [7:0]   Slave address                        */
#define PC_Uart_RX_MATCH_MASK_POS     (16u) /* [23:16] Slave address mask: 0 - doesn't care */
#define PC_Uart_RX_MATCH_ADDR_MASK    ((uint32) 0xFFu)
#define PC_Uart_RX_MATCH_MASK_MASK    ((uint32) 0xFFu << PC_Uart_RX_MATCH_MASK_POS)

/* PC_Uart_RX_FIFO_WR_REG */
#define PC_Uart_RX_FIFO_RD_POS    (0u)  /* [15:0] Data read from RX FIFO */
#define PC_Uart_RX_FIFO_RD_MASK   ((uint32) 0xFFu)

/* PC_Uart_RX_FIFO_RD_SILENT_REG */
#define PC_Uart_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define PC_Uart_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* PC_Uart_RX_FIFO_RD_SILENT_REG */
#define PC_Uart_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define PC_Uart_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* PC_Uart_EZBUF_DATA_REG */
#define PC_Uart_EZBUF_DATA_POS   (0u)  /* [7:0] Data from EZ Memory */
#define PC_Uart_EZBUF_DATA_MASK  ((uint32) 0xFFu)

/*  PC_Uart_INTR_CAUSE_REG */
#define PC_Uart_INTR_CAUSE_MASTER_POS  (0u)  /* [0] Master interrupt active                 */
#define PC_Uart_INTR_CAUSE_SLAVE_POS   (1u)  /* [1] Slave interrupt active                  */
#define PC_Uart_INTR_CAUSE_TX_POS      (2u)  /* [2] Transmitter interrupt active            */
#define PC_Uart_INTR_CAUSE_RX_POS      (3u)  /* [3] Receiver interrupt active               */
#define PC_Uart_INTR_CAUSE_I2C_EC_POS  (4u)  /* [4] Externally clock I2C interrupt active   */
#define PC_Uart_INTR_CAUSE_SPI_EC_POS  (5u)  /* [5] Externally clocked SPI interrupt active */
#define PC_Uart_INTR_CAUSE_MASTER      ((uint32) 0x01u)
#define PC_Uart_INTR_CAUSE_SLAVE       ((uint32) 0x01u << PC_Uart_INTR_CAUSE_SLAVE_POS)
#define PC_Uart_INTR_CAUSE_TX          ((uint32) 0x01u << PC_Uart_INTR_CAUSE_TX_POS)
#define PC_Uart_INTR_CAUSE_RX          ((uint32) 0x01u << PC_Uart_INTR_CAUSE_RX_POS)
#define PC_Uart_INTR_CAUSE_I2C_EC      ((uint32) 0x01u << PC_Uart_INTR_CAUSE_I2C_EC_POS)
#define PC_Uart_INTR_CAUSE_SPI_EC      ((uint32) 0x01u << PC_Uart_INTR_CAUSE_SPI_EC_POS)

/* PC_Uart_INTR_SPI_EC_REG, PC_Uart_INTR_SPI_EC_MASK_REG, PC_Uart_INTR_SPI_EC_MASKED_REG */
#define PC_Uart_INTR_SPI_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define PC_Uart_INTR_SPI_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define PC_Uart_INTR_SPI_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define PC_Uart_INTR_SPI_EC_WAKE_UP              ((uint32) 0x01u)
#define PC_Uart_INTR_SPI_EC_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    PC_Uart_INTR_SPI_EC_EZBUF_STOP_POS)
#define PC_Uart_INTR_SPI_EC_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                    PC_Uart_INTR_SPI_EC_EZBUF_WRITE_STOP_POS)

/* PC_Uart_INTR_I2C_EC, PC_Uart_INTR_I2C_EC_MASK, PC_Uart_INTR_I2C_EC_MASKED */
#define PC_Uart_INTR_I2C_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define PC_Uart_INTR_I2C_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define PC_Uart_INTR_I2C_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define PC_Uart_INTR_I2C_EC_WAKE_UP              ((uint32) 0x01u)
#define PC_Uart_INTR_I2C_EC_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    PC_Uart_INTR_I2C_EC_EZBUF_STOP_POS)
#define PC_Uart_INTR_I2C_EC_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                    PC_Uart_INTR_I2C_EC_EZBUF_WRITE_STOP_POS)

/* PC_Uart_INTR_MASTER, PC_Uart_INTR_MASTER_SET,
   PC_Uart_INTR_MASTER_MASK, PC_Uart_INTR_MASTER_MASKED */
#define PC_Uart_INTR_MASTER_I2C_ARB_LOST_POS   (0u)  /* [0] Master lost arbitration                          */
#define PC_Uart_INTR_MASTER_I2C_NACK_POS       (1u)  /* [1] Master receives NACK: address or write to slave  */
#define PC_Uart_INTR_MASTER_I2C_ACK_POS        (2u)  /* [2] Master receives NACK: address or write to slave  */
#define PC_Uart_INTR_MASTER_I2C_STOP_POS       (4u)  /* [4] Master detects the Stop: only self generated Stop*/
#define PC_Uart_INTR_MASTER_I2C_BUS_ERROR_POS  (8u)  /* [8] Master detects bus error: misplaced Start or Stop*/
#define PC_Uart_INTR_MASTER_SPI_DONE_POS       (9u)  /* [9] Master complete transfer: Only for SPI           */
#define PC_Uart_INTR_MASTER_I2C_ARB_LOST       ((uint32) 0x01u)
#define PC_Uart_INTR_MASTER_I2C_NACK           ((uint32) 0x01u << PC_Uart_INTR_MASTER_I2C_NACK_POS)
#define PC_Uart_INTR_MASTER_I2C_ACK            ((uint32) 0x01u << PC_Uart_INTR_MASTER_I2C_ACK_POS)
#define PC_Uart_INTR_MASTER_I2C_STOP           ((uint32) 0x01u << PC_Uart_INTR_MASTER_I2C_STOP_POS)
#define PC_Uart_INTR_MASTER_I2C_BUS_ERROR      ((uint32) 0x01u << \
                                                                    PC_Uart_INTR_MASTER_I2C_BUS_ERROR_POS)
#define PC_Uart_INTR_MASTER_SPI_DONE           ((uint32) 0x01u << PC_Uart_INTR_MASTER_SPI_DONE_POS)

/*
* PC_Uart_INTR_SLAVE, PC_Uart_INTR_SLAVE_SET,
* PC_Uart_INTR_SLAVE_MASK, PC_Uart_INTR_SLAVE_MASKED
*/
#define PC_Uart_INTR_SLAVE_I2C_ARB_LOST_POS         (0u)  /* [0]  Slave lost arbitration                   */
#define PC_Uart_INTR_SLAVE_I2C_NACK_POS             (1u)  /* [1]  Slave receives NACK: master reads data   */
#define PC_Uart_INTR_SLAVE_I2C_ACK_POS              (2u)  /* [2]  Slave receives ACK: master reads data    */
#define PC_Uart_INTR_SLAVE_I2C_WRITE_STOP_POS       (3u)  /* [3]  Slave detects end of write transaction   */
#define PC_Uart_INTR_SLAVE_I2C_STOP_POS             (4u)  /* [4]  Slave detects end of transaction intended */
#define PC_Uart_INTR_SLAVE_I2C_START_POS            (5u)  /* [5]  Slave detects Start                      */
#define PC_Uart_INTR_SLAVE_I2C_ADDR_MATCH_POS       (6u)  /* [6]  Slave address matches                    */
#define PC_Uart_INTR_SLAVE_I2C_GENERAL_POS          (7u)  /* [7]  General call received                    */
#define PC_Uart_INTR_SLAVE_I2C_BUS_ERROR_POS        (8u)  /* [8]  Slave detects bus error                  */
#define PC_Uart_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS (9u)  /* [9]  Slave write complete: Only for SPI       */
#define PC_Uart_INTR_SLAVE_SPI_EZBUF_STOP_POS       (10u) /* [10] Slave end of transaction: Only for SPI   */
#define PC_Uart_INTR_SLAVE_SPI_BUS_ERROR_POS        (11u) /* [11] Slave detects bus error: Only for SPI    */
#define PC_Uart_INTR_SLAVE_I2C_ARB_LOST             ((uint32) 0x01u)
#define PC_Uart_INTR_SLAVE_I2C_NACK                 ((uint32) 0x01u << \
                                                                    PC_Uart_INTR_SLAVE_I2C_NACK_POS)
#define PC_Uart_INTR_SLAVE_I2C_ACK                  ((uint32) 0x01u << \
                                                                    PC_Uart_INTR_SLAVE_I2C_ACK_POS)
#define PC_Uart_INTR_SLAVE_I2C_WRITE_STOP           ((uint32) 0x01u << \
                                                                    PC_Uart_INTR_SLAVE_I2C_WRITE_STOP_POS)
#define PC_Uart_INTR_SLAVE_I2C_STOP                 ((uint32) 0x01u << \
                                                                    PC_Uart_INTR_SLAVE_I2C_STOP_POS)
#define PC_Uart_INTR_SLAVE_I2C_START                ((uint32) 0x01u << \
                                                                    PC_Uart_INTR_SLAVE_I2C_START_POS)
#define PC_Uart_INTR_SLAVE_I2C_ADDR_MATCH           ((uint32) 0x01u << \
                                                                    PC_Uart_INTR_SLAVE_I2C_ADDR_MATCH_POS)
#define PC_Uart_INTR_SLAVE_I2C_GENERAL              ((uint32) 0x01u << \
                                                                    PC_Uart_INTR_SLAVE_I2C_GENERAL_POS)
#define PC_Uart_INTR_SLAVE_I2C_BUS_ERROR            ((uint32) 0x01u << \
                                                                    PC_Uart_INTR_SLAVE_I2C_BUS_ERROR_POS)
#define PC_Uart_INTR_SLAVE_SPI_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                   PC_Uart_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS)
#define PC_Uart_INTR_SLAVE_SPI_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    PC_Uart_INTR_SLAVE_SPI_EZBUF_STOP_POS)
#define PC_Uart_INTR_SLAVE_SPI_BUS_ERROR           ((uint32) 0x01u << \
                                                                    PC_Uart_INTR_SLAVE_SPI_BUS_ERROR_POS)

/*
* PC_Uart_INTR_TX, PC_Uart_INTR_TX_SET,
* PC_Uart_INTR_TX_MASK, PC_Uart_INTR_TX_MASKED
*/
#define PC_Uart_INTR_TX_TRIGGER_POS        (0u)  /* [0]  Trigger on TX FIFO entires                       */
#define PC_Uart_INTR_TX_NOT_FULL_POS       (1u)  /* [1]  TX FIFO is not full                              */
#define PC_Uart_INTR_TX_EMPTY_POS          (4u)  /* [4]  TX FIFO is empty                                 */
#define PC_Uart_INTR_TX_OVERFLOW_POS       (5u)  /* [5]  Attempt to write to a full TX FIFO               */
#define PC_Uart_INTR_TX_UNDERFLOW_POS      (6u)  /* [6]  Attempt to read from an empty TX FIFO            */
#define PC_Uart_INTR_TX_BLOCKED_POS        (7u)  /* [7]  No access to the EZ memory                       */
#define PC_Uart_INTR_TX_UART_NACK_POS      (8u)  /* [8]  UART transmitter received a NACK: SmartCard mode */
#define PC_Uart_INTR_TX_UART_DONE_POS      (9u)  /* [9]  UART transmitter done even                       */
#define PC_Uart_INTR_TX_UART_ARB_LOST_POS  (10u) /* [10] UART lost arbitration: LIN or SmartCard          */
#define PC_Uart_INTR_TX_TRIGGER            ((uint32) 0x01u)
#define PC_Uart_INTR_TX_FIFO_LEVEL         (PC_Uart_INTR_TX_TRIGGER)
#define PC_Uart_INTR_TX_NOT_FULL           ((uint32) 0x01u << PC_Uart_INTR_TX_NOT_FULL_POS)
#define PC_Uart_INTR_TX_EMPTY              ((uint32) 0x01u << PC_Uart_INTR_TX_EMPTY_POS)
#define PC_Uart_INTR_TX_OVERFLOW           ((uint32) 0x01u << PC_Uart_INTR_TX_OVERFLOW_POS)
#define PC_Uart_INTR_TX_UNDERFLOW          ((uint32) 0x01u << PC_Uart_INTR_TX_UNDERFLOW_POS)
#define PC_Uart_INTR_TX_BLOCKED            ((uint32) 0x01u << PC_Uart_INTR_TX_BLOCKED_POS)
#define PC_Uart_INTR_TX_UART_NACK          ((uint32) 0x01u << PC_Uart_INTR_TX_UART_NACK_POS)
#define PC_Uart_INTR_TX_UART_DONE          ((uint32) 0x01u << PC_Uart_INTR_TX_UART_DONE_POS)
#define PC_Uart_INTR_TX_UART_ARB_LOST      ((uint32) 0x01u << PC_Uart_INTR_TX_UART_ARB_LOST_POS)

/*
* PC_Uart_INTR_RX, PC_Uart_INTR_RX_SET,
* PC_Uart_INTR_RX_MASK, PC_Uart_INTR_RX_MASKED
*/
#define PC_Uart_INTR_RX_TRIGGER_POS        (0u)   /* [0]  Trigger on RX FIFO entires            */
#define PC_Uart_INTR_RX_NOT_EMPTY_POS      (2u)   /* [2]  RX FIFO is not empty                  */
#define PC_Uart_INTR_RX_FULL_POS           (3u)   /* [3]  RX FIFO is full                       */
#define PC_Uart_INTR_RX_OVERFLOW_POS       (5u)   /* [5]  Attempt to write to a full RX FIFO    */
#define PC_Uart_INTR_RX_UNDERFLOW_POS      (6u)   /* [6]  Attempt to read from an empty RX FIFO */
#define PC_Uart_INTR_RX_BLOCKED_POS        (7u)   /* [7]  No access to the EZ memory            */
#define PC_Uart_INTR_RX_FRAME_ERROR_POS    (8u)   /* [8]  Frame error in received data frame    */
#define PC_Uart_INTR_RX_PARITY_ERROR_POS   (9u)   /* [9]  Parity error in received data frame   */
#define PC_Uart_INTR_RX_BAUD_DETECT_POS    (10u)  /* [10] LIN baud rate detection is completed   */
#define PC_Uart_INTR_RX_BREAK_DETECT_POS   (11u)  /* [11] Break detection is successful         */
#define PC_Uart_INTR_RX_TRIGGER            ((uint32) 0x01u)
#define PC_Uart_INTR_RX_FIFO_LEVEL         (PC_Uart_INTR_RX_TRIGGER)
#define PC_Uart_INTR_RX_NOT_EMPTY          ((uint32) 0x01u << PC_Uart_INTR_RX_NOT_EMPTY_POS)
#define PC_Uart_INTR_RX_FULL               ((uint32) 0x01u << PC_Uart_INTR_RX_FULL_POS)
#define PC_Uart_INTR_RX_OVERFLOW           ((uint32) 0x01u << PC_Uart_INTR_RX_OVERFLOW_POS)
#define PC_Uart_INTR_RX_UNDERFLOW          ((uint32) 0x01u << PC_Uart_INTR_RX_UNDERFLOW_POS)
#define PC_Uart_INTR_RX_BLOCKED            ((uint32) 0x01u << PC_Uart_INTR_RX_BLOCKED_POS)
#define PC_Uart_INTR_RX_FRAME_ERROR        ((uint32) 0x01u << PC_Uart_INTR_RX_FRAME_ERROR_POS)
#define PC_Uart_INTR_RX_PARITY_ERROR       ((uint32) 0x01u << PC_Uart_INTR_RX_PARITY_ERROR_POS)
#define PC_Uart_INTR_RX_BAUD_DETECT        ((uint32) 0x01u << PC_Uart_INTR_RX_BAUD_DETECT_POS)
#define PC_Uart_INTR_RX_BREAK_DETECT       ((uint32) 0x01u << PC_Uart_INTR_RX_BREAK_DETECT_POS)

/* Define all interrupt sources */
#define PC_Uart_INTR_I2C_EC_ALL    (PC_Uart_INTR_I2C_EC_WAKE_UP    | \
                                             PC_Uart_INTR_I2C_EC_EZBUF_STOP | \
                                             PC_Uart_INTR_I2C_EC_EZBUF_WRITE_STOP)

#define PC_Uart_INTR_SPI_EC_ALL    (PC_Uart_INTR_SPI_EC_WAKE_UP    | \
                                             PC_Uart_INTR_SPI_EC_EZBUF_STOP | \
                                             PC_Uart_INTR_SPI_EC_EZBUF_WRITE_STOP)

#define PC_Uart_INTR_MASTER_ALL    (PC_Uart_INTR_MASTER_I2C_ARB_LOST  | \
                                             PC_Uart_INTR_MASTER_I2C_NACK      | \
                                             PC_Uart_INTR_MASTER_I2C_ACK       | \
                                             PC_Uart_INTR_MASTER_I2C_STOP      | \
                                             PC_Uart_INTR_MASTER_I2C_BUS_ERROR | \
                                             PC_Uart_INTR_MASTER_SPI_DONE)

#define PC_Uart_INTR_SLAVE_ALL     (PC_Uart_INTR_SLAVE_I2C_ARB_LOST      | \
                                             PC_Uart_INTR_SLAVE_I2C_NACK          | \
                                             PC_Uart_INTR_SLAVE_I2C_ACK           | \
                                             PC_Uart_INTR_SLAVE_I2C_WRITE_STOP    | \
                                             PC_Uart_INTR_SLAVE_I2C_STOP          | \
                                             PC_Uart_INTR_SLAVE_I2C_START         | \
                                             PC_Uart_INTR_SLAVE_I2C_ADDR_MATCH    | \
                                             PC_Uart_INTR_SLAVE_I2C_GENERAL       | \
                                             PC_Uart_INTR_SLAVE_I2C_BUS_ERROR     | \
                                             PC_Uart_INTR_SLAVE_SPI_EZBUF_WRITE_STOP | \
                                             PC_Uart_INTR_SLAVE_SPI_EZBUF_STOP       | \
                                             PC_Uart_INTR_SLAVE_SPI_BUS_ERROR)

#define PC_Uart_INTR_TX_ALL        (PC_Uart_INTR_TX_TRIGGER   | \
                                             PC_Uart_INTR_TX_NOT_FULL  | \
                                             PC_Uart_INTR_TX_EMPTY     | \
                                             PC_Uart_INTR_TX_OVERFLOW  | \
                                             PC_Uart_INTR_TX_UNDERFLOW | \
                                             PC_Uart_INTR_TX_BLOCKED   | \
                                             PC_Uart_INTR_TX_UART_NACK | \
                                             PC_Uart_INTR_TX_UART_DONE | \
                                             PC_Uart_INTR_TX_UART_ARB_LOST)

#define PC_Uart_INTR_RX_ALL        (PC_Uart_INTR_RX_TRIGGER      | \
                                             PC_Uart_INTR_RX_NOT_EMPTY    | \
                                             PC_Uart_INTR_RX_FULL         | \
                                             PC_Uart_INTR_RX_OVERFLOW     | \
                                             PC_Uart_INTR_RX_UNDERFLOW    | \
                                             PC_Uart_INTR_RX_BLOCKED      | \
                                             PC_Uart_INTR_RX_FRAME_ERROR  | \
                                             PC_Uart_INTR_RX_PARITY_ERROR | \
                                             PC_Uart_INTR_RX_BAUD_DETECT  | \
                                             PC_Uart_INTR_RX_BREAK_DETECT)

/* General usage HW definitions */
#define PC_Uart_ONE_BYTE_WIDTH (8u)   /* Number of bits in one byte           */
#define PC_Uart_FIFO_SIZE      (8u)   /* Size of TX or RX FIFO: defined by HW */
#define PC_Uart_EZBUFFER_SIZE  (32u)  /* EZ Buffer size: defined by HW        */

/* I2C and EZI2C slave address defines */
#define PC_Uart_I2C_SLAVE_ADDR_POS    (0x01u)    /* 7-bit address shift */
#define PC_Uart_I2C_SLAVE_ADDR_MASK   (0xFEu)    /* 8-bit address mask */

/* OVS constants for IrDA Low Power operation */
#define PC_Uart_CTRL_OVS_IRDA_LP_OVS16     (0x00u)
#define PC_Uart_CTRL_OVS_IRDA_LP_OVS32     (0x01u)
#define PC_Uart_CTRL_OVS_IRDA_LP_OVS48     (0x02u)
#define PC_Uart_CTRL_OVS_IRDA_LP_OVS96     (0x03u)
#define PC_Uart_CTRL_OVS_IRDA_LP_OVS192    (0x04u)
#define PC_Uart_CTRL_OVS_IRDA_LP_OVS768    (0x05u)
#define PC_Uart_CTRL_OVS_IRDA_LP_OVS1536   (0x06u)

/* OVS constant for IrDA */
#define PC_Uart_CTRL_OVS_IRDA_OVS16        (PC_Uart_UART_IRDA_LP_OVS16)


/***************************************
*    Common Macro Definitions
***************************************/

/* Re-enables the SCB IP. A clear enable bit has a different effect
* on the scb IP depending on the version:
*  CY_SCBIP_V0: resets state, status, TX and RX FIFOs.
*  CY_SCBIP_V1 or later: resets state, status, TX and RX FIFOs and interrupt sources.
*/
#define PC_Uart_SCB_SW_RESET \
                        do{           \
                            PC_Uart_CTRL_REG &= ((uint32) ~PC_Uart_CTRL_ENABLED); \
                            PC_Uart_CTRL_REG |= ((uint32)  PC_Uart_CTRL_ENABLED); \
                        }while(0)

/* TX FIFO macro */
#define PC_Uart_CLEAR_TX_FIFO \
                            do{        \
                                PC_Uart_TX_FIFO_CTRL_REG |= ((uint32)  PC_Uart_TX_FIFO_CTRL_CLEAR); \
                                PC_Uart_TX_FIFO_CTRL_REG &= ((uint32) ~PC_Uart_TX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define PC_Uart_GET_TX_FIFO_ENTRIES    (PC_Uart_TX_FIFO_STATUS_REG & \
                                                 PC_Uart_TX_FIFO_STATUS_USED_MASK)

#define PC_Uart_GET_TX_FIFO_SR_VALID   ((0u != (PC_Uart_TX_FIFO_STATUS_REG & \
                                                         PC_Uart_TX_FIFO_SR_VALID)) ? (1u) : (0u))

/* RX FIFO macro */
#define PC_Uart_CLEAR_RX_FIFO \
                            do{        \
                                PC_Uart_RX_FIFO_CTRL_REG |= ((uint32)  PC_Uart_RX_FIFO_CTRL_CLEAR); \
                                PC_Uart_RX_FIFO_CTRL_REG &= ((uint32) ~PC_Uart_RX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define PC_Uart_GET_RX_FIFO_ENTRIES    (PC_Uart_RX_FIFO_STATUS_REG & \
                                                    PC_Uart_RX_FIFO_STATUS_USED_MASK)

#define PC_Uart_GET_RX_FIFO_SR_VALID   ((0u != (PC_Uart_RX_FIFO_STATUS_REG & \
                                                         PC_Uart_RX_FIFO_SR_VALID)) ? (1u) : (0u))

/* Write interrupt source: set sourceMask bits in PC_Uart_INTR_X_MASK_REG */
#define PC_Uart_WRITE_INTR_I2C_EC_MASK(sourceMask) \
                                                do{         \
                                                    PC_Uart_INTR_I2C_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#if (!PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_WRITE_INTR_SPI_EC_MASK(sourceMask) \
                                                do{         \
                                                    PC_Uart_INTR_SPI_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!PC_Uart_CY_SCBIP_V1) */

#define PC_Uart_WRITE_INTR_MASTER_MASK(sourceMask) \
                                                do{         \
                                                    PC_Uart_INTR_MASTER_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define PC_Uart_WRITE_INTR_SLAVE_MASK(sourceMask)  \
                                                do{         \
                                                    PC_Uart_INTR_SLAVE_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define PC_Uart_WRITE_INTR_TX_MASK(sourceMask)     \
                                                do{         \
                                                    PC_Uart_INTR_TX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define PC_Uart_WRITE_INTR_RX_MASK(sourceMask)     \
                                                do{         \
                                                    PC_Uart_INTR_RX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Enable interrupt source: set sourceMask bits in PC_Uart_INTR_X_MASK_REG */
#define PC_Uart_ENABLE_INTR_I2C_EC(sourceMask) \
                                                do{     \
                                                    PC_Uart_INTR_I2C_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)
#if (!PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_ENABLE_INTR_SPI_EC(sourceMask) \
                                                do{     \
                                                    PC_Uart_INTR_SPI_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!PC_Uart_CY_SCBIP_V1) */

#define PC_Uart_ENABLE_INTR_MASTER(sourceMask) \
                                                do{     \
                                                    PC_Uart_INTR_MASTER_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define PC_Uart_ENABLE_INTR_SLAVE(sourceMask)  \
                                                do{     \
                                                    PC_Uart_INTR_SLAVE_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define PC_Uart_ENABLE_INTR_TX(sourceMask)     \
                                                do{     \
                                                    PC_Uart_INTR_TX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define PC_Uart_ENABLE_INTR_RX(sourceMask)     \
                                                do{     \
                                                    PC_Uart_INTR_RX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

/* Disable interrupt source: clear sourceMask bits in PC_Uart_INTR_X_MASK_REG */
#define PC_Uart_DISABLE_INTR_I2C_EC(sourceMask) \
                                do{                      \
                                    PC_Uart_INTR_I2C_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#if (!PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_DISABLE_INTR_SPI_EC(sourceMask) \
                                do{                      \
                                    PC_Uart_INTR_SPI_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)
#endif /* (!PC_Uart_CY_SCBIP_V1) */

#define PC_Uart_DISABLE_INTR_MASTER(sourceMask) \
                                do{                      \
                                PC_Uart_INTR_MASTER_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define PC_Uart_DISABLE_INTR_SLAVE(sourceMask) \
                                do{                     \
                                    PC_Uart_INTR_SLAVE_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define PC_Uart_DISABLE_INTR_TX(sourceMask)    \
                                do{                     \
                                    PC_Uart_INTR_TX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)

#define PC_Uart_DISABLE_INTR_RX(sourceMask)    \
                                do{                     \
                                    PC_Uart_INTR_RX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

/* Set interrupt sources: write sourceMask bits in PC_Uart_INTR_X_SET_REG */
#define PC_Uart_SET_INTR_MASTER(sourceMask)    \
                                                do{     \
                                                    PC_Uart_INTR_MASTER_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define PC_Uart_SET_INTR_SLAVE(sourceMask) \
                                                do{ \
                                                    PC_Uart_INTR_SLAVE_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define PC_Uart_SET_INTR_TX(sourceMask)    \
                                                do{ \
                                                    PC_Uart_INTR_TX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define PC_Uart_SET_INTR_RX(sourceMask)    \
                                                do{ \
                                                    PC_Uart_INTR_RX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Clear interrupt sources: write sourceMask bits in PC_Uart_INTR_X_REG */
#define PC_Uart_CLEAR_INTR_I2C_EC(sourceMask)  \
                                                do{     \
                                                    PC_Uart_INTR_I2C_EC_REG = (uint32) (sourceMask); \
                                                }while(0)

#if (!PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_CLEAR_INTR_SPI_EC(sourceMask)  \
                                                do{     \
                                                    PC_Uart_INTR_SPI_EC_REG = (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!PC_Uart_CY_SCBIP_V1) */

#define PC_Uart_CLEAR_INTR_MASTER(sourceMask)  \
                                                do{     \
                                                    PC_Uart_INTR_MASTER_REG = (uint32) (sourceMask); \
                                                }while(0)

#define PC_Uart_CLEAR_INTR_SLAVE(sourceMask)   \
                                                do{     \
                                                    PC_Uart_INTR_SLAVE_REG  = (uint32) (sourceMask); \
                                                }while(0)

#define PC_Uart_CLEAR_INTR_TX(sourceMask)      \
                                                do{     \
                                                    PC_Uart_INTR_TX_REG     = (uint32) (sourceMask); \
                                                }while(0)

#define PC_Uart_CLEAR_INTR_RX(sourceMask)      \
                                                do{     \
                                                    PC_Uart_INTR_RX_REG     = (uint32) (sourceMask); \
                                                }while(0)

/* Return true if sourceMask is set in PC_Uart_INTR_CAUSE_REG */
#define PC_Uart_CHECK_CAUSE_INTR(sourceMask)    (0u != (PC_Uart_INTR_CAUSE_REG & (sourceMask)))

/* Return true if sourceMask is set in INTR_X_MASKED_REG */
#define PC_Uart_CHECK_INTR_I2C_EC(sourceMask)  (0u != (PC_Uart_INTR_I2C_EC_REG & (sourceMask)))
#if (!PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_CHECK_INTR_SPI_EC(sourceMask)  (0u != (PC_Uart_INTR_SPI_EC_REG & (sourceMask)))
#endif /* (!PC_Uart_CY_SCBIP_V1) */
#define PC_Uart_CHECK_INTR_MASTER(sourceMask)  (0u != (PC_Uart_INTR_MASTER_REG & (sourceMask)))
#define PC_Uart_CHECK_INTR_SLAVE(sourceMask)   (0u != (PC_Uart_INTR_SLAVE_REG  & (sourceMask)))
#define PC_Uart_CHECK_INTR_TX(sourceMask)      (0u != (PC_Uart_INTR_TX_REG     & (sourceMask)))
#define PC_Uart_CHECK_INTR_RX(sourceMask)      (0u != (PC_Uart_INTR_RX_REG     & (sourceMask)))

/* Return true if sourceMask is set in PC_Uart_INTR_X_MASKED_REG */
#define PC_Uart_CHECK_INTR_I2C_EC_MASKED(sourceMask)   (0u != (PC_Uart_INTR_I2C_EC_MASKED_REG & \
                                                                       (sourceMask)))
#if (!PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_CHECK_INTR_SPI_EC_MASKED(sourceMask)   (0u != (PC_Uart_INTR_SPI_EC_MASKED_REG & \
                                                                       (sourceMask)))
#endif /* (!PC_Uart_CY_SCBIP_V1) */
#define PC_Uart_CHECK_INTR_MASTER_MASKED(sourceMask)   (0u != (PC_Uart_INTR_MASTER_MASKED_REG & \
                                                                       (sourceMask)))
#define PC_Uart_CHECK_INTR_SLAVE_MASKED(sourceMask)    (0u != (PC_Uart_INTR_SLAVE_MASKED_REG  & \
                                                                       (sourceMask)))
#define PC_Uart_CHECK_INTR_TX_MASKED(sourceMask)       (0u != (PC_Uart_INTR_TX_MASKED_REG     & \
                                                                       (sourceMask)))
#define PC_Uart_CHECK_INTR_RX_MASKED(sourceMask)       (0u != (PC_Uart_INTR_RX_MASKED_REG     & \
                                                                       (sourceMask)))

/* Return true if sourceMask is set in PC_Uart_CTRL_REG: generally is used to check enable bit */
#define PC_Uart_GET_CTRL_ENABLED    (0u != (PC_Uart_CTRL_REG & PC_Uart_CTRL_ENABLED))

#define PC_Uart_CHECK_SLAVE_AUTO_ADDR_NACK     (0u != (PC_Uart_I2C_CTRL_REG & \
                                                                PC_Uart_I2C_CTRL_S_NOT_READY_DATA_NACK))


/***************************************
*      I2C Macro Definitions
***************************************/

/* Enable auto ACK/NACK */
#define PC_Uart_ENABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                      \
                                PC_Uart_I2C_CTRL_REG |= PC_Uart_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define PC_Uart_ENABLE_SLAVE_AUTO_DATA_ACK \
                            do{                     \
                                PC_Uart_I2C_CTRL_REG |= PC_Uart_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define PC_Uart_ENABLE_SLAVE_AUTO_DATA_NACK \
                            do{                      \
                                PC_Uart_I2C_CTRL_REG |= PC_Uart_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define PC_Uart_ENABLE_MASTER_AUTO_DATA_ACK \
                            do{                      \
                                PC_Uart_I2C_CTRL_REG |= PC_Uart_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define PC_Uart_ENABLE_MASTER_AUTO_DATA_NACK \
                            do{                       \
                                PC_Uart_I2C_CTRL_REG |= PC_Uart_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Disable auto ACK/NACK */
#define PC_Uart_DISABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                       \
                                PC_Uart_I2C_CTRL_REG &= ~PC_Uart_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define PC_Uart_DISABLE_SLAVE_AUTO_DATA_ACK \
                            do{                      \
                                PC_Uart_I2C_CTRL_REG &= ~PC_Uart_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define PC_Uart_DISABLE_SLAVE_AUTO_DATA_NACK \
                            do{                       \
                                PC_Uart_I2C_CTRL_REG &= ~PC_Uart_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define PC_Uart_DISABLE_MASTER_AUTO_DATA_ACK \
                            do{                       \
                                PC_Uart_I2C_CTRL_REG &= ~PC_Uart_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define PC_Uart_DISABLE_MASTER_AUTO_DATA_NACK \
                            do{                        \
                                PC_Uart_I2C_CTRL_REG &= ~PC_Uart_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Enable Slave autoACK/NACK Data */
#define PC_Uart_ENABLE_SLAVE_AUTO_DATA \
                            do{                 \
                                PC_Uart_I2C_CTRL_REG |= (PC_Uart_I2C_CTRL_S_READY_DATA_ACK |      \
                                                                  PC_Uart_I2C_CTRL_S_NOT_READY_DATA_NACK); \
                            }while(0)

/* Disable Slave autoACK/NACK Data */
#define PC_Uart_DISABLE_SLAVE_AUTO_DATA \
                            do{                  \
                                PC_Uart_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(PC_Uart_I2C_CTRL_S_READY_DATA_ACK |       \
                                                                    PC_Uart_I2C_CTRL_S_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Disable Master autoACK/NACK Data */
#define PC_Uart_DISABLE_MASTER_AUTO_DATA \
                            do{                   \
                                PC_Uart_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(PC_Uart_I2C_CTRL_M_READY_DATA_ACK |       \
                                                                    PC_Uart_I2C_CTRL_M_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Master commands */
#define PC_Uart_I2C_MASTER_GENERATE_START \
                            do{                    \
                                PC_Uart_I2C_MASTER_CMD_REG = PC_Uart_I2C_MASTER_CMD_M_START_ON_IDLE; \
                            }while(0)

#define PC_Uart_I2C_MASTER_CLEAR_START \
                            do{                 \
                                PC_Uart_I2C_MASTER_CMD_REG =  ((uint32) 0u); \
                            }while(0)

#define PC_Uart_I2C_MASTER_GENERATE_RESTART PC_Uart_I2CReStartGeneration()

#define PC_Uart_I2C_MASTER_GENERATE_STOP \
                            do{                   \
                                PC_Uart_I2C_MASTER_CMD_REG =                                            \
                                    (PC_Uart_I2C_MASTER_CMD_M_STOP |                                    \
                                        (PC_Uart_CHECK_I2C_STATUS(PC_Uart_I2C_STATUS_M_READ) ? \
                                            (PC_Uart_I2C_MASTER_CMD_M_NACK) : (0u)));                   \
                            }while(0)

#define PC_Uart_I2C_MASTER_GENERATE_ACK \
                            do{                  \
                                PC_Uart_I2C_MASTER_CMD_REG = PC_Uart_I2C_MASTER_CMD_M_ACK; \
                            }while(0)

#define PC_Uart_I2C_MASTER_GENERATE_NACK \
                            do{                   \
                                PC_Uart_I2C_MASTER_CMD_REG = PC_Uart_I2C_MASTER_CMD_M_NACK; \
                            }while(0)

/* Slave commands */
#define PC_Uart_I2C_SLAVE_GENERATE_ACK \
                            do{                 \
                                PC_Uart_I2C_SLAVE_CMD_REG = PC_Uart_I2C_SLAVE_CMD_S_ACK; \
                            }while(0)

#if (PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1)
    /* Slave NACK generation for EC_AM logic on address phase. Ticket ID #183902 */
    void PC_Uart_I2CSlaveNackGeneration(void);
    #define PC_Uart_I2C_SLAVE_GENERATE_NACK PC_Uart_I2CSlaveNackGeneration()

#else
    #define PC_Uart_I2C_SLAVE_GENERATE_NACK \
                            do{                      \
                                PC_Uart_I2C_SLAVE_CMD_REG = PC_Uart_I2C_SLAVE_CMD_S_NACK; \
                            }while(0)
#endif /* (PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1) */

#define PC_Uart_I2C_SLAVE_CLEAR_NACK \
                            do{               \
                                PC_Uart_I2C_SLAVE_CMD_REG = 0u; \
                            }while(0)

/* Return 8-bit address. The input address should be 7-bits */
#define PC_Uart_GET_I2C_8BIT_ADDRESS(addr) (((uint32) ((uint32) (addr) << \
                                                                    PC_Uart_I2C_SLAVE_ADDR_POS)) & \
                                                                        PC_Uart_I2C_SLAVE_ADDR_MASK)

#define PC_Uart_GET_I2C_7BIT_ADDRESS(addr) ((uint32) (addr) >> PC_Uart_I2C_SLAVE_ADDR_POS)

/* Adjust SDA filter Trim settings */
#define PC_Uart_DEFAULT_I2C_CFG_SDA_FILT_TRIM  (0x02u)
#define PC_Uart_EC_AM_I2C_CFG_SDA_FILT_TRIM    (0x03u)

#if (PC_Uart_CY_SCBIP_V0)
    #define PC_Uart_SET_I2C_CFG_SDA_FILT_TRIM(sdaTrim) \
        do{                                                 \
            PC_Uart_I2C_CFG_REG =                  \
                            ((PC_Uart_I2C_CFG_REG & (uint32) ~PC_Uart_I2C_CFG_SDA_FILT_TRIM_MASK) | \
                             ((uint32) ((uint32) (sdaTrim) <<PC_Uart_I2C_CFG_SDA_FILT_TRIM_POS)));           \
        }while(0)
#endif /* (PC_Uart_CY_SCBIP_V0) */

/* Enable/Disable analog and digital filter */
#define PC_Uart_DIGITAL_FILTER_DISABLE    (0u)
#define PC_Uart_DIGITAL_FILTER_ENABLE     (1u)
#define PC_Uart_I2C_DATA_RATE_FS_MODE_MAX (400u)
#if (PC_Uart_CY_SCBIP_V0)
    /* PC_Uart_I2C_CFG_SDA_FILT_OUT_ENABLED is disabled by default */
    #define PC_Uart_I2C_CFG_FILT_MASK  (PC_Uart_I2C_CFG_SDA_FILT_ENABLED | \
                                                 PC_Uart_I2C_CFG_SCL_FILT_ENABLED)
#else
    /* PC_Uart_I2C_CFG_SDA_OUT_FILT_SEL_MASK is disabled by default */
    #define PC_Uart_I2C_CFG_FILT_MASK  (PC_Uart_I2C_CFG_SDA_IN_FILT_SEL | \
                                                 PC_Uart_I2C_CFG_SCL_IN_FILT_SEL)
#endif /* (PC_Uart_CY_SCBIP_V0) */

#define PC_Uart_I2C_CFG_ANALOG_FITER_DISABLE \
        do{                                           \
            PC_Uart_I2C_CFG_REG &= (uint32) ~PC_Uart_I2C_CFG_FILT_MASK; \
        }while(0)

#define PC_Uart_I2C_CFG_ANALOG_FITER_ENABLE \
        do{                                          \
            PC_Uart_I2C_CFG_REG |= (uint32)  PC_Uart_I2C_CFG_FILT_MASK; \
        }while(0)

/* Return slave select number from SPI_CTRL register */
#define PC_Uart_GET_SPI_CTRL_SS(activeSelect) (((uint32) ((uint32) (activeSelect) << \
                                                                    PC_Uart_SPI_CTRL_SLAVE_SELECT_POS)) & \
                                                                        PC_Uart_SPI_CTRL_SLAVE_SELECT_MASK)

/* Return true if bit is set in PC_Uart_I2C_STATUS_REG */
#define PC_Uart_CHECK_I2C_STATUS(sourceMask)   (0u != (PC_Uart_I2C_STATUS_REG & (sourceMask)))

/* Return true if bit is set in PC_Uart_SPI_STATUS_REG */
#define PC_Uart_CHECK_SPI_STATUS(sourceMask)   (0u != (PC_Uart_SPI_STATUS_REG & (sourceMask)))

/* Return FIFO size depends on PC_Uart_CTRL_BYTE_MODE bit */
#define PC_Uart_GET_FIFO_SIZE(condition) ((0u != (condition)) ? \
                                                    (2u * PC_Uart_FIFO_SIZE) : (PC_Uart_FIFO_SIZE))


/***************************************
*       Get Macros Definitions
***************************************/

/* PC_Uart_CTRL */
#define PC_Uart_GET_CTRL_OVS(oversample)       (((uint32) (oversample) - 1u) & PC_Uart_CTRL_OVS_MASK)

#define PC_Uart_GET_CTRL_EC_OP_MODE(opMode)        ((0u != (opMode)) ? \
                                                                (PC_Uart_CTRL_EC_OP_MODE)  : (0u))

#define PC_Uart_GET_CTRL_EC_AM_MODE(amMode)        ((0u != (amMode)) ? \
                                                                (PC_Uart_CTRL_EC_AM_MODE)  : (0u))

#define PC_Uart_GET_CTRL_BLOCK(block)              ((0u != (block))  ? \
                                                                (PC_Uart_CTRL_BLOCK)       : (0u))

#define PC_Uart_GET_CTRL_ADDR_ACCEPT(acceptAddr)   ((0u != (acceptAddr)) ? \
                                                                (PC_Uart_CTRL_ADDR_ACCEPT) : (0u))

#if (PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_GET_CTRL_BYTE_MODE(mode)   (0u)
#else
    #define PC_Uart_GET_CTRL_BYTE_MODE(mode)   ((0u != (mode)) ? \
                                                            (PC_Uart_CTRL_BYTE_MODE) : (0u))
#endif /* (PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1) */

/* PC_Uart_I2C_CTRL */
#define PC_Uart_GET_I2C_CTRL_HIGH_PHASE_OVS(oversampleHigh) (((uint32) (oversampleHigh) - 1u) & \
                                                                        PC_Uart_I2C_CTRL_HIGH_PHASE_OVS_MASK)

#define PC_Uart_GET_I2C_CTRL_LOW_PHASE_OVS(oversampleLow)  ((((uint32) (oversampleLow) - 1u) << \
                                                                    PC_Uart_I2C_CTRL_LOW_PHASE_OVS_POS) &  \
                                                                    PC_Uart_I2C_CTRL_LOW_PHASE_OVS_MASK)

#define PC_Uart_GET_I2C_CTRL_S_NOT_READY_ADDR_NACK(wakeNack) ((0u != (wakeNack)) ? \
                                                            (PC_Uart_I2C_CTRL_S_NOT_READY_ADDR_NACK) : (0u))

#define PC_Uart_GET_I2C_CTRL_S_GENERAL_IGNORE(genCall) ((0u != (genCall)) ? \
                                                                    (PC_Uart_I2C_CTRL_S_GENERAL_IGNORE) : (0u))

#define PC_Uart_GET_I2C_CTRL_SL_MSTR_MODE(mode)    ((uint32)(mode) << PC_Uart_I2C_CTRL_SLAVE_MODE_POS)

/* PC_Uart_SPI_CTRL */
#define PC_Uart_GET_SPI_CTRL_CONTINUOUS(separate)  ((0u != (separate)) ? \
                                                                (PC_Uart_SPI_CTRL_CONTINUOUS) : (0u))

#define PC_Uart_GET_SPI_CTRL_SELECT_PRECEDE(mode)  ((0u != (mode)) ? \
                                                                      (PC_Uart_SPI_CTRL_SELECT_PRECEDE) : (0u))

#define PC_Uart_GET_SPI_CTRL_SCLK_MODE(mode)       (((uint32) (mode) << \
                                                                        PC_Uart_SPI_CTRL_CPHA_POS) & \
                                                                        PC_Uart_SPI_CTRL_SCLK_MODE_MASK)

#define PC_Uart_GET_SPI_CTRL_LATE_MISO_SAMPLE(lateMiso) ((0u != (lateMiso)) ? \
                                                                    (PC_Uart_SPI_CTRL_LATE_MISO_SAMPLE) : (0u))

#if (PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_GET_SPI_CTRL_SCLK_CONTINUOUS(sclkType) (0u)
    #define PC_Uart_GET_SPI_CTRL_SSEL_POLARITY(polarity)   (0u)
#else
    #define PC_Uart_GET_SPI_CTRL_SCLK_CONTINUOUS(sclkType) ((0u != (sclkType)) ? \
                                                                    (PC_Uart_SPI_CTRL_SCLK_CONTINUOUS) : (0u))

    #define PC_Uart_GET_SPI_CTRL_SSEL_POLARITY(polarity)   (((uint32) (polarity) << \
                                                                     PC_Uart_SPI_CTRL_SSEL0_POLARITY_POS) & \
                                                                     PC_Uart_SPI_CTRL_SSEL_POLARITY_MASK)
#endif /* ((PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1) */

#define PC_Uart_GET_SPI_CTRL_SUB_MODE(mode)        (((uint32) (mode) << PC_Uart_SPI_CTRL_MODE_POS) & \
                                                                                 PC_Uart_SPI_CTRL_MODE_MASK)

#define PC_Uart_GET_SPI_CTRL_SLAVE_SELECT(select)  (((uint32) (select) << \
                                                                      PC_Uart_SPI_CTRL_SLAVE_SELECT_POS) & \
                                                                      PC_Uart_SPI_CTRL_SLAVE_SELECT_MASK)

#define PC_Uart_GET_SPI_CTRL_MASTER_MODE(mode)     ((0u != (mode)) ? \
                                                                (PC_Uart_SPI_CTRL_MASTER) : (0u))

/* PC_Uart_UART_CTRL */
#define PC_Uart_GET_UART_CTRL_MODE(mode)           (((uint32) (mode) << \
                                                                            PC_Uart_UART_CTRL_MODE_POS) & \
                                                                            PC_Uart_UART_CTRL_MODE_MASK)

/* PC_Uart_UART_RX_CTRL */
#define PC_Uart_GET_UART_RX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                        PC_Uart_UART_RX_CTRL_STOP_BITS_MASK)

#define PC_Uart_GET_UART_RX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                                    (PC_Uart_UART_RX_CTRL_PARITY) : (0u))

#define PC_Uart_GET_UART_RX_CTRL_POLARITY(polarity)    ((0u != (polarity)) ? \
                                                                    (PC_Uart_UART_RX_CTRL_POLARITY) : (0u))

#define PC_Uart_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (PC_Uart_UART_RX_CTRL_DROP_ON_PARITY_ERR) : (0u))

#define PC_Uart_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (PC_Uart_UART_RX_CTRL_DROP_ON_FRAME_ERR) : (0u))

#define PC_Uart_GET_UART_RX_CTRL_MP_MODE(mpMode)   ((0u != (mpMode)) ? \
                                                        (PC_Uart_UART_RX_CTRL_MP_MODE) : (0u))

/* PC_Uart_UART_TX_CTRL */
#define PC_Uart_GET_UART_TX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                PC_Uart_UART_RX_CTRL_STOP_BITS_MASK)

#define PC_Uart_GET_UART_TX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                               (PC_Uart_UART_TX_CTRL_PARITY) : (0u))

#define PC_Uart_GET_UART_TX_CTRL_RETRY_NACK(nack)  ((0u != (nack)) ? \
                                                               (PC_Uart_UART_TX_CTRL_RETRY_ON_NACK) : (0u))

/* PC_Uart_UART_FLOW_CTRL */
#if !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(level)   ( (uint32) (level) & \
                                                                 PC_Uart_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK)

    #define PC_Uart_GET_UART_FLOW_CTRL_RTS_POLARITY(polarity) ((0u != (polarity)) ? \
                                                                (PC_Uart_UART_FLOW_CTRL_RTS_POLARITY) : (0u))

    #define PC_Uart_GET_UART_FLOW_CTRL_CTS_POLARITY(polarity) ((0u != (polarity)) ? \
                                                                (PC_Uart_UART_FLOW_CTRL_CTS_POLARITY) : (0u))

    #define PC_Uart_GET_UART_FLOW_CTRL_CTS_ENABLE(ctsEn)      ((0u != (ctsEn)) ? \
                                                                (PC_Uart_UART_FLOW_CTRL_CTS_ENABLE) : (0u))
#endif /* !(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1) */

/* PC_Uart_RX_CTRL */
#define PC_Uart_GET_RX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                PC_Uart_RX_CTRL_DATA_WIDTH_MASK)

#define PC_Uart_GET_RX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (PC_Uart_RX_CTRL_MSB_FIRST) : (0u))

#define PC_Uart_GET_RX_CTRL_MEDIAN(filterEn)       ((0u != (filterEn)) ? \
                                                                (PC_Uart_RX_CTRL_MEDIAN) : (0u))

/* PC_Uart_RX_MATCH */
#define PC_Uart_GET_RX_MATCH_ADDR(addr)    ((uint32) (addr) & PC_Uart_RX_MATCH_ADDR_MASK)
#define PC_Uart_GET_RX_MATCH_MASK(mask)    (((uint32) (mask) << \
                                                            PC_Uart_RX_MATCH_MASK_POS) & \
                                                            PC_Uart_RX_MATCH_MASK_MASK)

/* PC_Uart_RX_FIFO_CTRL */
#define PC_Uart_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    PC_Uart_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* PC_Uart_TX_CTRL */
#define PC_Uart_GET_TX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                PC_Uart_RX_CTRL_DATA_WIDTH_MASK)

#define PC_Uart_GET_TX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (PC_Uart_TX_CTRL_MSB_FIRST) : (0u))

/* PC_Uart_TX_FIFO_CTRL */
#define PC_Uart_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    PC_Uart_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* PC_Uart_INTR_SLAVE_I2C_GENERAL */
#define PC_Uart_GET_INTR_SLAVE_I2C_GENERAL(genCall)  ((0u != (genCall)) ? \
                                                                (PC_Uart_INTR_SLAVE_I2C_GENERAL) : (0u))

/* Return true if master mode is enabled PC_Uart_SPI_CTRL_REG */
#define PC_Uart_CHECK_SPI_MASTER   (0u != (PC_Uart_SPI_CTRL_REG & PC_Uart_SPI_CTRL_MASTER))

/* Return inactive state of SPI SCLK line depends on CPOL */
#define PC_Uart_GET_SPI_SCLK_INACTIVE \
            ((0u == (PC_Uart_SPI_CTRL_REG & PC_Uart_SPI_CTRL_CPOL)) ? (0u) : (1u))

/* Get output pin inactive state */
#if (PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1)
#define PC_Uart_GET_SPI_SS0_INACTIVE       (1u)
#define PC_Uart_GET_SPI_SS1_INACTIVE       (1u)
#define PC_Uart_GET_SPI_SS2_INACTIVE       (1u)
#define PC_Uart_GET_SPI_SS3_INACTIVE       (1u)
#define PC_Uart_GET_UART_RTS_INACTIVE      (1u)

#else
#define PC_Uart_GET_SPI_SS0_INACTIVE  \
        ((0u != (PC_Uart_SPI_CTRL_REG & PC_Uart_SPI_CTRL_SSEL0_POLARITY)) ? (0u) : (1u))

#define PC_Uart_GET_SPI_SS1_INACTIVE  \
        ((0u != (PC_Uart_SPI_CTRL_REG & PC_Uart_SPI_CTRL_SSEL1_POLARITY)) ? (0u) : (1u))

#define PC_Uart_GET_SPI_SS2_INACTIVE  \
        ((0u != (PC_Uart_SPI_CTRL_REG & PC_Uart_SPI_CTRL_SSEL2_POLARITY)) ? (0u) : (1u))

#define PC_Uart_GET_SPI_SS3_INACTIVE  \
        ((0u != (PC_Uart_SPI_CTRL_REG & PC_Uart_SPI_CTRL_SSEL3_POLARITY)) ? (0u) : (1u))

#define PC_Uart_GET_UART_RTS_INACTIVE \
        ((0u == (PC_Uart_UART_FLOW_CTRL_REG & PC_Uart_UART_FLOW_CTRL_RTS_POLARITY)) ? (0u) : (1u))

#endif /*(PC_Uart_CY_SCBIP_V0 || PC_Uart_CY_SCBIP_V1) */

/* Clear register constants for configuration and interrupt mask */
#define PC_Uart_CLEAR_REG          ((uint32) (0u))
#define PC_Uart_NO_INTR_SOURCES    ((uint32) (0u))
#define PC_Uart_DUMMY_PARAM        ((uint32) (0u))
#define PC_Uart_SUBMODE_SPI_SLAVE  ((uint32) (0u))

/* Return in case of I2C read error */
#define PC_Uart_I2C_INVALID_BYTE   ((uint32) 0xFFFFFFFFu)
#define PC_Uart_CHECK_VALID_BYTE   ((uint32) 0x80000000u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define PC_Uart_CHECK_INTR_EC_I2C(sourceMask)  PC_Uart_CHECK_INTR_I2C_EC(sourceMask)
#if (!PC_Uart_CY_SCBIP_V1)
    #define PC_Uart_CHECK_INTR_EC_SPI(sourceMask)  PC_Uart_CHECK_INTR_SPI_EC(sourceMask)
#endif /* (!PC_Uart_CY_SCBIP_V1) */

#define PC_Uart_CY_SCBIP_V1_I2C_ONLY   (PC_Uart_CY_SCBIP_V1)

#endif /* (CY_SCB_PC_Uart_H) */


/* [] END OF FILE */
