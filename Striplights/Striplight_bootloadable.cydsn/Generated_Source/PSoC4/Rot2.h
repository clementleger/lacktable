/*******************************************************************************
* File Name: Rot2.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the Rot2
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_Rot2_H)
#define CY_TCPWM_Rot2_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} Rot2_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  Rot2_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define Rot2_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define Rot2_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define Rot2_CONFIG                         (3lu)

/* Quad Mode */
/* Parameters */
#define Rot2_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define Rot2_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define Rot2_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define Rot2_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define Rot2_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define Rot2_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define Rot2_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define Rot2_QUAD_INTERRUPT_MASK            (0lu)

/* Timer/Counter Mode */
/* Parameters */
#define Rot2_TC_RUN_MODE                    (0lu)
#define Rot2_TC_COUNTER_MODE                (0lu)
#define Rot2_TC_COMP_CAP_MODE               (2lu)
#define Rot2_TC_PRESCALER                   (0lu)

/* Signal modes */
#define Rot2_TC_RELOAD_SIGNAL_MODE          (0lu)
#define Rot2_TC_COUNT_SIGNAL_MODE           (3lu)
#define Rot2_TC_START_SIGNAL_MODE           (0lu)
#define Rot2_TC_STOP_SIGNAL_MODE            (0lu)
#define Rot2_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define Rot2_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define Rot2_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define Rot2_TC_START_SIGNAL_PRESENT        (0lu)
#define Rot2_TC_STOP_SIGNAL_PRESENT         (0lu)
#define Rot2_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Rot2_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define Rot2_PWM_KILL_EVENT                 (0lu)
#define Rot2_PWM_STOP_EVENT                 (0lu)
#define Rot2_PWM_MODE                       (4lu)
#define Rot2_PWM_OUT_N_INVERT               (0lu)
#define Rot2_PWM_OUT_INVERT                 (0lu)
#define Rot2_PWM_ALIGN                      (0lu)
#define Rot2_PWM_RUN_MODE                   (0lu)
#define Rot2_PWM_DEAD_TIME_CYCLE            (0lu)
#define Rot2_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define Rot2_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define Rot2_PWM_COUNT_SIGNAL_MODE          (3lu)
#define Rot2_PWM_START_SIGNAL_MODE          (0lu)
#define Rot2_PWM_STOP_SIGNAL_MODE           (0lu)
#define Rot2_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define Rot2_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define Rot2_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define Rot2_PWM_START_SIGNAL_PRESENT       (0lu)
#define Rot2_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define Rot2_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Rot2_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define Rot2_TC_PERIOD_VALUE                (65535lu)
#define Rot2_TC_COMPARE_VALUE               (65535lu)
#define Rot2_TC_COMPARE_BUF_VALUE           (65535lu)
#define Rot2_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define Rot2_PWM_PERIOD_VALUE               (65535lu)
#define Rot2_PWM_PERIOD_BUF_VALUE           (65535lu)
#define Rot2_PWM_PERIOD_SWAP                (0lu)
#define Rot2_PWM_COMPARE_VALUE              (65535lu)
#define Rot2_PWM_COMPARE_BUF_VALUE          (65535lu)
#define Rot2_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Rot2__LEFT 0
#define Rot2__RIGHT 1
#define Rot2__CENTER 2
#define Rot2__ASYMMETRIC 3

#define Rot2__X1 0
#define Rot2__X2 1
#define Rot2__X4 2

#define Rot2__PWM 4
#define Rot2__PWM_DT 5
#define Rot2__PWM_PR 6

#define Rot2__INVERSE 1
#define Rot2__DIRECT 0

#define Rot2__CAPTURE 2
#define Rot2__COMPARE 0

#define Rot2__TRIG_LEVEL 3
#define Rot2__TRIG_RISING 0
#define Rot2__TRIG_FALLING 1
#define Rot2__TRIG_BOTH 2

#define Rot2__INTR_MASK_TC 1
#define Rot2__INTR_MASK_CC_MATCH 2
#define Rot2__INTR_MASK_NONE 0
#define Rot2__INTR_MASK_TC_CC 3

#define Rot2__UNCONFIG 8
#define Rot2__TIMER 1
#define Rot2__QUAD 3
#define Rot2__PWM_SEL 7

#define Rot2__COUNT_UP 0
#define Rot2__COUNT_DOWN 1
#define Rot2__COUNT_UPDOWN0 2
#define Rot2__COUNT_UPDOWN1 3


/* Prescaler */
#define Rot2_PRESCALE_DIVBY1                ((uint32)(0u << Rot2_PRESCALER_SHIFT))
#define Rot2_PRESCALE_DIVBY2                ((uint32)(1u << Rot2_PRESCALER_SHIFT))
#define Rot2_PRESCALE_DIVBY4                ((uint32)(2u << Rot2_PRESCALER_SHIFT))
#define Rot2_PRESCALE_DIVBY8                ((uint32)(3u << Rot2_PRESCALER_SHIFT))
#define Rot2_PRESCALE_DIVBY16               ((uint32)(4u << Rot2_PRESCALER_SHIFT))
#define Rot2_PRESCALE_DIVBY32               ((uint32)(5u << Rot2_PRESCALER_SHIFT))
#define Rot2_PRESCALE_DIVBY64               ((uint32)(6u << Rot2_PRESCALER_SHIFT))
#define Rot2_PRESCALE_DIVBY128              ((uint32)(7u << Rot2_PRESCALER_SHIFT))

/* TCPWM set modes */
#define Rot2_MODE_TIMER_COMPARE             ((uint32)(Rot2__COMPARE         <<  \
                                                                  Rot2_MODE_SHIFT))
#define Rot2_MODE_TIMER_CAPTURE             ((uint32)(Rot2__CAPTURE         <<  \
                                                                  Rot2_MODE_SHIFT))
#define Rot2_MODE_QUAD                      ((uint32)(Rot2__QUAD            <<  \
                                                                  Rot2_MODE_SHIFT))
#define Rot2_MODE_PWM                       ((uint32)(Rot2__PWM             <<  \
                                                                  Rot2_MODE_SHIFT))
#define Rot2_MODE_PWM_DT                    ((uint32)(Rot2__PWM_DT          <<  \
                                                                  Rot2_MODE_SHIFT))
#define Rot2_MODE_PWM_PR                    ((uint32)(Rot2__PWM_PR          <<  \
                                                                  Rot2_MODE_SHIFT))

/* Quad Modes */
#define Rot2_MODE_X1                        ((uint32)(Rot2__X1              <<  \
                                                                  Rot2_QUAD_MODE_SHIFT))
#define Rot2_MODE_X2                        ((uint32)(Rot2__X2              <<  \
                                                                  Rot2_QUAD_MODE_SHIFT))
#define Rot2_MODE_X4                        ((uint32)(Rot2__X4              <<  \
                                                                  Rot2_QUAD_MODE_SHIFT))

/* Counter modes */
#define Rot2_COUNT_UP                       ((uint32)(Rot2__COUNT_UP        <<  \
                                                                  Rot2_UPDOWN_SHIFT))
#define Rot2_COUNT_DOWN                     ((uint32)(Rot2__COUNT_DOWN      <<  \
                                                                  Rot2_UPDOWN_SHIFT))
#define Rot2_COUNT_UPDOWN0                  ((uint32)(Rot2__COUNT_UPDOWN0   <<  \
                                                                  Rot2_UPDOWN_SHIFT))
#define Rot2_COUNT_UPDOWN1                  ((uint32)(Rot2__COUNT_UPDOWN1   <<  \
                                                                  Rot2_UPDOWN_SHIFT))

/* PWM output invert */
#define Rot2_INVERT_LINE                    ((uint32)(Rot2__INVERSE         <<  \
                                                                  Rot2_INV_OUT_SHIFT))
#define Rot2_INVERT_LINE_N                  ((uint32)(Rot2__INVERSE         <<  \
                                                                  Rot2_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define Rot2_TRIG_RISING                    ((uint32)Rot2__TRIG_RISING)
#define Rot2_TRIG_FALLING                   ((uint32)Rot2__TRIG_FALLING)
#define Rot2_TRIG_BOTH                      ((uint32)Rot2__TRIG_BOTH)
#define Rot2_TRIG_LEVEL                     ((uint32)Rot2__TRIG_LEVEL)

/* Interrupt mask */
#define Rot2_INTR_MASK_TC                   ((uint32)Rot2__INTR_MASK_TC)
#define Rot2_INTR_MASK_CC_MATCH             ((uint32)Rot2__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define Rot2_CC_MATCH_SET                   (0x00u)
#define Rot2_CC_MATCH_CLEAR                 (0x01u)
#define Rot2_CC_MATCH_INVERT                (0x02u)
#define Rot2_CC_MATCH_NO_CHANGE             (0x03u)
#define Rot2_OVERLOW_SET                    (0x00u)
#define Rot2_OVERLOW_CLEAR                  (0x04u)
#define Rot2_OVERLOW_INVERT                 (0x08u)
#define Rot2_OVERLOW_NO_CHANGE              (0x0Cu)
#define Rot2_UNDERFLOW_SET                  (0x00u)
#define Rot2_UNDERFLOW_CLEAR                (0x10u)
#define Rot2_UNDERFLOW_INVERT               (0x20u)
#define Rot2_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define Rot2_PWM_MODE_LEFT                  (Rot2_CC_MATCH_CLEAR        |   \
                                                         Rot2_OVERLOW_SET           |   \
                                                         Rot2_UNDERFLOW_NO_CHANGE)
#define Rot2_PWM_MODE_RIGHT                 (Rot2_CC_MATCH_SET          |   \
                                                         Rot2_OVERLOW_NO_CHANGE     |   \
                                                         Rot2_UNDERFLOW_CLEAR)
#define Rot2_PWM_MODE_ASYM                  (Rot2_CC_MATCH_INVERT       |   \
                                                         Rot2_OVERLOW_SET           |   \
                                                         Rot2_UNDERFLOW_CLEAR)

#if (Rot2_CY_TCPWM_V2)
    #if(Rot2_CY_TCPWM_4000)
        #define Rot2_PWM_MODE_CENTER                (Rot2_CC_MATCH_INVERT       |   \
                                                                 Rot2_OVERLOW_NO_CHANGE     |   \
                                                                 Rot2_UNDERFLOW_CLEAR)
    #else
        #define Rot2_PWM_MODE_CENTER                (Rot2_CC_MATCH_INVERT       |   \
                                                                 Rot2_OVERLOW_SET           |   \
                                                                 Rot2_UNDERFLOW_CLEAR)
    #endif /* (Rot2_CY_TCPWM_4000) */
#else
    #define Rot2_PWM_MODE_CENTER                (Rot2_CC_MATCH_INVERT       |   \
                                                             Rot2_OVERLOW_NO_CHANGE     |   \
                                                             Rot2_UNDERFLOW_CLEAR)
#endif /* (Rot2_CY_TCPWM_NEW) */

/* Command operations without condition */
#define Rot2_CMD_CAPTURE                    (0u)
#define Rot2_CMD_RELOAD                     (8u)
#define Rot2_CMD_STOP                       (16u)
#define Rot2_CMD_START                      (24u)

/* Status */
#define Rot2_STATUS_DOWN                    (1u)
#define Rot2_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   Rot2_Init(void);
void   Rot2_Enable(void);
void   Rot2_Start(void);
void   Rot2_Stop(void);

void   Rot2_SetMode(uint32 mode);
void   Rot2_SetCounterMode(uint32 counterMode);
void   Rot2_SetPWMMode(uint32 modeMask);
void   Rot2_SetQDMode(uint32 qdMode);

void   Rot2_SetPrescaler(uint32 prescaler);
void   Rot2_TriggerCommand(uint32 mask, uint32 command);
void   Rot2_SetOneShot(uint32 oneShotEnable);
uint32 Rot2_ReadStatus(void);

void   Rot2_SetPWMSyncKill(uint32 syncKillEnable);
void   Rot2_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   Rot2_SetPWMDeadTime(uint32 deadTime);
void   Rot2_SetPWMInvert(uint32 mask);

void   Rot2_SetInterruptMode(uint32 interruptMask);
uint32 Rot2_GetInterruptSourceMasked(void);
uint32 Rot2_GetInterruptSource(void);
void   Rot2_ClearInterrupt(uint32 interruptMask);
void   Rot2_SetInterrupt(uint32 interruptMask);

void   Rot2_WriteCounter(uint32 count);
uint32 Rot2_ReadCounter(void);

uint32 Rot2_ReadCapture(void);
uint32 Rot2_ReadCaptureBuf(void);

void   Rot2_WritePeriod(uint32 period);
uint32 Rot2_ReadPeriod(void);
void   Rot2_WritePeriodBuf(uint32 periodBuf);
uint32 Rot2_ReadPeriodBuf(void);

void   Rot2_WriteCompare(uint32 compare);
uint32 Rot2_ReadCompare(void);
void   Rot2_WriteCompareBuf(uint32 compareBuf);
uint32 Rot2_ReadCompareBuf(void);

void   Rot2_SetPeriodSwap(uint32 swapEnable);
void   Rot2_SetCompareSwap(uint32 swapEnable);

void   Rot2_SetCaptureMode(uint32 triggerMode);
void   Rot2_SetReloadMode(uint32 triggerMode);
void   Rot2_SetStartMode(uint32 triggerMode);
void   Rot2_SetStopMode(uint32 triggerMode);
void   Rot2_SetCountMode(uint32 triggerMode);

void   Rot2_SaveConfig(void);
void   Rot2_RestoreConfig(void);
void   Rot2_Sleep(void);
void   Rot2_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define Rot2_BLOCK_CONTROL_REG              (*(reg32 *) Rot2_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Rot2_BLOCK_CONTROL_PTR              ( (reg32 *) Rot2_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Rot2_COMMAND_REG                    (*(reg32 *) Rot2_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Rot2_COMMAND_PTR                    ( (reg32 *) Rot2_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Rot2_INTRRUPT_CAUSE_REG             (*(reg32 *) Rot2_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Rot2_INTRRUPT_CAUSE_PTR             ( (reg32 *) Rot2_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Rot2_CONTROL_REG                    (*(reg32 *) Rot2_cy_m0s8_tcpwm_1__CTRL )
#define Rot2_CONTROL_PTR                    ( (reg32 *) Rot2_cy_m0s8_tcpwm_1__CTRL )
#define Rot2_STATUS_REG                     (*(reg32 *) Rot2_cy_m0s8_tcpwm_1__STATUS )
#define Rot2_STATUS_PTR                     ( (reg32 *) Rot2_cy_m0s8_tcpwm_1__STATUS )
#define Rot2_COUNTER_REG                    (*(reg32 *) Rot2_cy_m0s8_tcpwm_1__COUNTER )
#define Rot2_COUNTER_PTR                    ( (reg32 *) Rot2_cy_m0s8_tcpwm_1__COUNTER )
#define Rot2_COMP_CAP_REG                   (*(reg32 *) Rot2_cy_m0s8_tcpwm_1__CC )
#define Rot2_COMP_CAP_PTR                   ( (reg32 *) Rot2_cy_m0s8_tcpwm_1__CC )
#define Rot2_COMP_CAP_BUF_REG               (*(reg32 *) Rot2_cy_m0s8_tcpwm_1__CC_BUFF )
#define Rot2_COMP_CAP_BUF_PTR               ( (reg32 *) Rot2_cy_m0s8_tcpwm_1__CC_BUFF )
#define Rot2_PERIOD_REG                     (*(reg32 *) Rot2_cy_m0s8_tcpwm_1__PERIOD )
#define Rot2_PERIOD_PTR                     ( (reg32 *) Rot2_cy_m0s8_tcpwm_1__PERIOD )
#define Rot2_PERIOD_BUF_REG                 (*(reg32 *) Rot2_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Rot2_PERIOD_BUF_PTR                 ( (reg32 *) Rot2_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Rot2_TRIG_CONTROL0_REG              (*(reg32 *) Rot2_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Rot2_TRIG_CONTROL0_PTR              ( (reg32 *) Rot2_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Rot2_TRIG_CONTROL1_REG              (*(reg32 *) Rot2_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Rot2_TRIG_CONTROL1_PTR              ( (reg32 *) Rot2_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Rot2_TRIG_CONTROL2_REG              (*(reg32 *) Rot2_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Rot2_TRIG_CONTROL2_PTR              ( (reg32 *) Rot2_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Rot2_INTERRUPT_REQ_REG              (*(reg32 *) Rot2_cy_m0s8_tcpwm_1__INTR )
#define Rot2_INTERRUPT_REQ_PTR              ( (reg32 *) Rot2_cy_m0s8_tcpwm_1__INTR )
#define Rot2_INTERRUPT_SET_REG              (*(reg32 *) Rot2_cy_m0s8_tcpwm_1__INTR_SET )
#define Rot2_INTERRUPT_SET_PTR              ( (reg32 *) Rot2_cy_m0s8_tcpwm_1__INTR_SET )
#define Rot2_INTERRUPT_MASK_REG             (*(reg32 *) Rot2_cy_m0s8_tcpwm_1__INTR_MASK )
#define Rot2_INTERRUPT_MASK_PTR             ( (reg32 *) Rot2_cy_m0s8_tcpwm_1__INTR_MASK )
#define Rot2_INTERRUPT_MASKED_REG           (*(reg32 *) Rot2_cy_m0s8_tcpwm_1__INTR_MASKED )
#define Rot2_INTERRUPT_MASKED_PTR           ( (reg32 *) Rot2_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define Rot2_MASK                           ((uint32)Rot2_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define Rot2_RELOAD_CC_SHIFT                (0u)
#define Rot2_RELOAD_PERIOD_SHIFT            (1u)
#define Rot2_PWM_SYNC_KILL_SHIFT            (2u)
#define Rot2_PWM_STOP_KILL_SHIFT            (3u)
#define Rot2_PRESCALER_SHIFT                (8u)
#define Rot2_UPDOWN_SHIFT                   (16u)
#define Rot2_ONESHOT_SHIFT                  (18u)
#define Rot2_QUAD_MODE_SHIFT                (20u)
#define Rot2_INV_OUT_SHIFT                  (20u)
#define Rot2_INV_COMPL_OUT_SHIFT            (21u)
#define Rot2_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define Rot2_RELOAD_CC_MASK                 ((uint32)(Rot2_1BIT_MASK        <<  \
                                                                            Rot2_RELOAD_CC_SHIFT))
#define Rot2_RELOAD_PERIOD_MASK             ((uint32)(Rot2_1BIT_MASK        <<  \
                                                                            Rot2_RELOAD_PERIOD_SHIFT))
#define Rot2_PWM_SYNC_KILL_MASK             ((uint32)(Rot2_1BIT_MASK        <<  \
                                                                            Rot2_PWM_SYNC_KILL_SHIFT))
#define Rot2_PWM_STOP_KILL_MASK             ((uint32)(Rot2_1BIT_MASK        <<  \
                                                                            Rot2_PWM_STOP_KILL_SHIFT))
#define Rot2_PRESCALER_MASK                 ((uint32)(Rot2_8BIT_MASK        <<  \
                                                                            Rot2_PRESCALER_SHIFT))
#define Rot2_UPDOWN_MASK                    ((uint32)(Rot2_2BIT_MASK        <<  \
                                                                            Rot2_UPDOWN_SHIFT))
#define Rot2_ONESHOT_MASK                   ((uint32)(Rot2_1BIT_MASK        <<  \
                                                                            Rot2_ONESHOT_SHIFT))
#define Rot2_QUAD_MODE_MASK                 ((uint32)(Rot2_3BIT_MASK        <<  \
                                                                            Rot2_QUAD_MODE_SHIFT))
#define Rot2_INV_OUT_MASK                   ((uint32)(Rot2_2BIT_MASK        <<  \
                                                                            Rot2_INV_OUT_SHIFT))
#define Rot2_MODE_MASK                      ((uint32)(Rot2_3BIT_MASK        <<  \
                                                                            Rot2_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define Rot2_CAPTURE_SHIFT                  (0u)
#define Rot2_COUNT_SHIFT                    (2u)
#define Rot2_RELOAD_SHIFT                   (4u)
#define Rot2_STOP_SHIFT                     (6u)
#define Rot2_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define Rot2_CAPTURE_MASK                   ((uint32)(Rot2_2BIT_MASK        <<  \
                                                                  Rot2_CAPTURE_SHIFT))
#define Rot2_COUNT_MASK                     ((uint32)(Rot2_2BIT_MASK        <<  \
                                                                  Rot2_COUNT_SHIFT))
#define Rot2_RELOAD_MASK                    ((uint32)(Rot2_2BIT_MASK        <<  \
                                                                  Rot2_RELOAD_SHIFT))
#define Rot2_STOP_MASK                      ((uint32)(Rot2_2BIT_MASK        <<  \
                                                                  Rot2_STOP_SHIFT))
#define Rot2_START_MASK                     ((uint32)(Rot2_2BIT_MASK        <<  \
                                                                  Rot2_START_SHIFT))

/* MASK */
#define Rot2_1BIT_MASK                      ((uint32)0x01u)
#define Rot2_2BIT_MASK                      ((uint32)0x03u)
#define Rot2_3BIT_MASK                      ((uint32)0x07u)
#define Rot2_6BIT_MASK                      ((uint32)0x3Fu)
#define Rot2_8BIT_MASK                      ((uint32)0xFFu)
#define Rot2_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define Rot2_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define Rot2_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(Rot2_QUAD_ENCODING_MODES     << Rot2_QUAD_MODE_SHIFT))       |\
         ((uint32)(Rot2_CONFIG                  << Rot2_MODE_SHIFT)))

#define Rot2_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(Rot2_PWM_STOP_EVENT          << Rot2_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(Rot2_PWM_OUT_INVERT          << Rot2_INV_OUT_SHIFT))         |\
         ((uint32)(Rot2_PWM_OUT_N_INVERT        << Rot2_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(Rot2_PWM_MODE                << Rot2_MODE_SHIFT)))

#define Rot2_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(Rot2_PWM_RUN_MODE         << Rot2_ONESHOT_SHIFT))
            
#define Rot2_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(Rot2_PWM_ALIGN            << Rot2_UPDOWN_SHIFT))

#define Rot2_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(Rot2_PWM_KILL_EVENT      << Rot2_PWM_SYNC_KILL_SHIFT))

#define Rot2_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(Rot2_PWM_DEAD_TIME_CYCLE  << Rot2_PRESCALER_SHIFT))

#define Rot2_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(Rot2_PWM_PRESCALER        << Rot2_PRESCALER_SHIFT))

#define Rot2_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(Rot2_TC_PRESCALER            << Rot2_PRESCALER_SHIFT))       |\
         ((uint32)(Rot2_TC_COUNTER_MODE         << Rot2_UPDOWN_SHIFT))          |\
         ((uint32)(Rot2_TC_RUN_MODE             << Rot2_ONESHOT_SHIFT))         |\
         ((uint32)(Rot2_TC_COMP_CAP_MODE        << Rot2_MODE_SHIFT)))
        
#define Rot2_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(Rot2_QUAD_PHIA_SIGNAL_MODE   << Rot2_COUNT_SHIFT))           |\
         ((uint32)(Rot2_QUAD_INDEX_SIGNAL_MODE  << Rot2_RELOAD_SHIFT))          |\
         ((uint32)(Rot2_QUAD_STOP_SIGNAL_MODE   << Rot2_STOP_SHIFT))            |\
         ((uint32)(Rot2_QUAD_PHIB_SIGNAL_MODE   << Rot2_START_SHIFT)))

#define Rot2_PWM_SIGNALS_MODES                                                              \
        (((uint32)(Rot2_PWM_SWITCH_SIGNAL_MODE  << Rot2_CAPTURE_SHIFT))         |\
         ((uint32)(Rot2_PWM_COUNT_SIGNAL_MODE   << Rot2_COUNT_SHIFT))           |\
         ((uint32)(Rot2_PWM_RELOAD_SIGNAL_MODE  << Rot2_RELOAD_SHIFT))          |\
         ((uint32)(Rot2_PWM_STOP_SIGNAL_MODE    << Rot2_STOP_SHIFT))            |\
         ((uint32)(Rot2_PWM_START_SIGNAL_MODE   << Rot2_START_SHIFT)))

#define Rot2_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(Rot2_TC_CAPTURE_SIGNAL_MODE  << Rot2_CAPTURE_SHIFT))         |\
         ((uint32)(Rot2_TC_COUNT_SIGNAL_MODE    << Rot2_COUNT_SHIFT))           |\
         ((uint32)(Rot2_TC_RELOAD_SIGNAL_MODE   << Rot2_RELOAD_SHIFT))          |\
         ((uint32)(Rot2_TC_STOP_SIGNAL_MODE     << Rot2_STOP_SHIFT))            |\
         ((uint32)(Rot2_TC_START_SIGNAL_MODE    << Rot2_START_SHIFT)))
        
#define Rot2_TIMER_UPDOWN_CNT_USED                                                          \
                ((Rot2__COUNT_UPDOWN0 == Rot2_TC_COUNTER_MODE)                  ||\
                 (Rot2__COUNT_UPDOWN1 == Rot2_TC_COUNTER_MODE))

#define Rot2_PWM_UPDOWN_CNT_USED                                                            \
                ((Rot2__CENTER == Rot2_PWM_ALIGN)                               ||\
                 (Rot2__ASYMMETRIC == Rot2_PWM_ALIGN))               
        
#define Rot2_PWM_PR_INIT_VALUE              (1u)
#define Rot2_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_Rot2_H */

/* [] END OF FILE */
