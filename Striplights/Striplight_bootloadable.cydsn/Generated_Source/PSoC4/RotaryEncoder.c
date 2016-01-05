/*******************************************************************************
* File Name: RotaryEncoder.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the RotaryEncoder
*  component
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

#include "RotaryEncoder.h"

uint8 RotaryEncoder_initVar = 0u;


/*******************************************************************************
* Function Name: RotaryEncoder_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default RotaryEncoder configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (RotaryEncoder__QUAD == RotaryEncoder_CONFIG)
        RotaryEncoder_CONTROL_REG = RotaryEncoder_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        RotaryEncoder_TRIG_CONTROL1_REG  = RotaryEncoder_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        RotaryEncoder_SetInterruptMode(RotaryEncoder_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        RotaryEncoder_SetCounterMode(RotaryEncoder_COUNT_DOWN);
        RotaryEncoder_WritePeriod(RotaryEncoder_QUAD_PERIOD_INIT_VALUE);
        RotaryEncoder_WriteCounter(RotaryEncoder_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (RotaryEncoder__QUAD == RotaryEncoder_CONFIG) */

    #if (RotaryEncoder__TIMER == RotaryEncoder_CONFIG)
        RotaryEncoder_CONTROL_REG = RotaryEncoder_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        RotaryEncoder_TRIG_CONTROL1_REG  = RotaryEncoder_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        RotaryEncoder_SetInterruptMode(RotaryEncoder_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        RotaryEncoder_WritePeriod(RotaryEncoder_TC_PERIOD_VALUE );

        #if (RotaryEncoder__COMPARE == RotaryEncoder_TC_COMP_CAP_MODE)
            RotaryEncoder_WriteCompare(RotaryEncoder_TC_COMPARE_VALUE);

            #if (1u == RotaryEncoder_TC_COMPARE_SWAP)
                RotaryEncoder_SetCompareSwap(1u);
                RotaryEncoder_WriteCompareBuf(RotaryEncoder_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == RotaryEncoder_TC_COMPARE_SWAP) */
        #endif  /* (RotaryEncoder__COMPARE == RotaryEncoder_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (RotaryEncoder_CY_TCPWM_V2 && RotaryEncoder_TIMER_UPDOWN_CNT_USED && !RotaryEncoder_CY_TCPWM_4000)
            RotaryEncoder_WriteCounter(1u);
        #elif(RotaryEncoder__COUNT_DOWN == RotaryEncoder_TC_COUNTER_MODE)
            RotaryEncoder_WriteCounter(RotaryEncoder_TC_PERIOD_VALUE);
        #else
            RotaryEncoder_WriteCounter(0u);
        #endif /* (RotaryEncoder_CY_TCPWM_V2 && RotaryEncoder_TIMER_UPDOWN_CNT_USED && !RotaryEncoder_CY_TCPWM_4000) */
    #endif  /* (RotaryEncoder__TIMER == RotaryEncoder_CONFIG) */

    #if (RotaryEncoder__PWM_SEL == RotaryEncoder_CONFIG)
        RotaryEncoder_CONTROL_REG = RotaryEncoder_CTRL_PWM_BASE_CONFIG;

        #if (RotaryEncoder__PWM_PR == RotaryEncoder_PWM_MODE)
            RotaryEncoder_CONTROL_REG |= RotaryEncoder_CTRL_PWM_RUN_MODE;
            RotaryEncoder_WriteCounter(RotaryEncoder_PWM_PR_INIT_VALUE);
        #else
            RotaryEncoder_CONTROL_REG |= RotaryEncoder_CTRL_PWM_ALIGN | RotaryEncoder_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (RotaryEncoder_CY_TCPWM_V2 && RotaryEncoder_PWM_UPDOWN_CNT_USED && !RotaryEncoder_CY_TCPWM_4000)
                RotaryEncoder_WriteCounter(1u);
            #elif (RotaryEncoder__RIGHT == RotaryEncoder_PWM_ALIGN)
                RotaryEncoder_WriteCounter(RotaryEncoder_PWM_PERIOD_VALUE);
            #else 
                RotaryEncoder_WriteCounter(0u);
            #endif  /* (RotaryEncoder_CY_TCPWM_V2 && RotaryEncoder_PWM_UPDOWN_CNT_USED && !RotaryEncoder_CY_TCPWM_4000) */
        #endif  /* (RotaryEncoder__PWM_PR == RotaryEncoder_PWM_MODE) */

        #if (RotaryEncoder__PWM_DT == RotaryEncoder_PWM_MODE)
            RotaryEncoder_CONTROL_REG |= RotaryEncoder_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (RotaryEncoder__PWM_DT == RotaryEncoder_PWM_MODE) */

        #if (RotaryEncoder__PWM == RotaryEncoder_PWM_MODE)
            RotaryEncoder_CONTROL_REG |= RotaryEncoder_CTRL_PWM_PRESCALER;
        #endif  /* (RotaryEncoder__PWM == RotaryEncoder_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        RotaryEncoder_TRIG_CONTROL1_REG  = RotaryEncoder_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        RotaryEncoder_SetInterruptMode(RotaryEncoder_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (RotaryEncoder__PWM_PR == RotaryEncoder_PWM_MODE)
            RotaryEncoder_TRIG_CONTROL2_REG =
                    (RotaryEncoder_CC_MATCH_NO_CHANGE    |
                    RotaryEncoder_OVERLOW_NO_CHANGE      |
                    RotaryEncoder_UNDERFLOW_NO_CHANGE);
        #else
            #if (RotaryEncoder__LEFT == RotaryEncoder_PWM_ALIGN)
                RotaryEncoder_TRIG_CONTROL2_REG = RotaryEncoder_PWM_MODE_LEFT;
            #endif  /* ( RotaryEncoder_PWM_LEFT == RotaryEncoder_PWM_ALIGN) */

            #if (RotaryEncoder__RIGHT == RotaryEncoder_PWM_ALIGN)
                RotaryEncoder_TRIG_CONTROL2_REG = RotaryEncoder_PWM_MODE_RIGHT;
            #endif  /* ( RotaryEncoder_PWM_RIGHT == RotaryEncoder_PWM_ALIGN) */

            #if (RotaryEncoder__CENTER == RotaryEncoder_PWM_ALIGN)
                RotaryEncoder_TRIG_CONTROL2_REG = RotaryEncoder_PWM_MODE_CENTER;
            #endif  /* ( RotaryEncoder_PWM_CENTER == RotaryEncoder_PWM_ALIGN) */

            #if (RotaryEncoder__ASYMMETRIC == RotaryEncoder_PWM_ALIGN)
                RotaryEncoder_TRIG_CONTROL2_REG = RotaryEncoder_PWM_MODE_ASYM;
            #endif  /* (RotaryEncoder__ASYMMETRIC == RotaryEncoder_PWM_ALIGN) */
        #endif  /* (RotaryEncoder__PWM_PR == RotaryEncoder_PWM_MODE) */

        /* Set other values from customizer */
        RotaryEncoder_WritePeriod(RotaryEncoder_PWM_PERIOD_VALUE );
        RotaryEncoder_WriteCompare(RotaryEncoder_PWM_COMPARE_VALUE);

        #if (1u == RotaryEncoder_PWM_COMPARE_SWAP)
            RotaryEncoder_SetCompareSwap(1u);
            RotaryEncoder_WriteCompareBuf(RotaryEncoder_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == RotaryEncoder_PWM_COMPARE_SWAP) */

        #if (1u == RotaryEncoder_PWM_PERIOD_SWAP)
            RotaryEncoder_SetPeriodSwap(1u);
            RotaryEncoder_WritePeriodBuf(RotaryEncoder_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == RotaryEncoder_PWM_PERIOD_SWAP) */
    #endif  /* (RotaryEncoder__PWM_SEL == RotaryEncoder_CONFIG) */
    
}


/*******************************************************************************
* Function Name: RotaryEncoder_Enable
********************************************************************************
*
* Summary:
*  Enables the RotaryEncoder.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    RotaryEncoder_BLOCK_CONTROL_REG |= RotaryEncoder_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (RotaryEncoder__PWM_SEL == RotaryEncoder_CONFIG)
        #if (0u == RotaryEncoder_PWM_START_SIGNAL_PRESENT)
            RotaryEncoder_TriggerCommand(RotaryEncoder_MASK, RotaryEncoder_CMD_START);
        #endif /* (0u == RotaryEncoder_PWM_START_SIGNAL_PRESENT) */
    #endif /* (RotaryEncoder__PWM_SEL == RotaryEncoder_CONFIG) */

    #if (RotaryEncoder__TIMER == RotaryEncoder_CONFIG)
        #if (0u == RotaryEncoder_TC_START_SIGNAL_PRESENT)
            RotaryEncoder_TriggerCommand(RotaryEncoder_MASK, RotaryEncoder_CMD_START);
        #endif /* (0u == RotaryEncoder_TC_START_SIGNAL_PRESENT) */
    #endif /* (RotaryEncoder__TIMER == RotaryEncoder_CONFIG) */
}


/*******************************************************************************
* Function Name: RotaryEncoder_Start
********************************************************************************
*
* Summary:
*  Initializes the RotaryEncoder with default customizer
*  values when called the first time and enables the RotaryEncoder.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  RotaryEncoder_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time RotaryEncoder_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the RotaryEncoder_Start() routine.
*
*******************************************************************************/
void RotaryEncoder_Start(void)
{
    if (0u == RotaryEncoder_initVar)
    {
        RotaryEncoder_Init();
        RotaryEncoder_initVar = 1u;
    }

    RotaryEncoder_Enable();
}


/*******************************************************************************
* Function Name: RotaryEncoder_Stop
********************************************************************************
*
* Summary:
*  Disables the RotaryEncoder.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RotaryEncoder_BLOCK_CONTROL_REG &= (uint32)~RotaryEncoder_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RotaryEncoder_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the RotaryEncoder. This function is used when
*  configured as a generic RotaryEncoder and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the RotaryEncoder to operate in
*   Values:
*   - RotaryEncoder_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - RotaryEncoder_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - RotaryEncoder_MODE_QUAD - Quadrature decoder
*         - RotaryEncoder_MODE_PWM - PWM
*         - RotaryEncoder_MODE_PWM_DT - PWM with dead time
*         - RotaryEncoder_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RotaryEncoder_CONTROL_REG &= (uint32)~RotaryEncoder_MODE_MASK;
    RotaryEncoder_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RotaryEncoder_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - RotaryEncoder_MODE_X1 - Counts on phi 1 rising
*         - RotaryEncoder_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - RotaryEncoder_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RotaryEncoder_CONTROL_REG &= (uint32)~RotaryEncoder_QUAD_MODE_MASK;
    RotaryEncoder_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RotaryEncoder_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - RotaryEncoder_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - RotaryEncoder_PRESCALE_DIVBY2    - Divide by 2
*         - RotaryEncoder_PRESCALE_DIVBY4    - Divide by 4
*         - RotaryEncoder_PRESCALE_DIVBY8    - Divide by 8
*         - RotaryEncoder_PRESCALE_DIVBY16   - Divide by 16
*         - RotaryEncoder_PRESCALE_DIVBY32   - Divide by 32
*         - RotaryEncoder_PRESCALE_DIVBY64   - Divide by 64
*         - RotaryEncoder_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RotaryEncoder_CONTROL_REG &= (uint32)~RotaryEncoder_PRESCALER_MASK;
    RotaryEncoder_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RotaryEncoder_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the RotaryEncoder runs
*  continuously or stops when terminal count is reached.  By default the
*  RotaryEncoder operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RotaryEncoder_CONTROL_REG &= (uint32)~RotaryEncoder_ONESHOT_MASK;
    RotaryEncoder_CONTROL_REG |= ((uint32)((oneShotEnable & RotaryEncoder_1BIT_MASK) <<
                                                               RotaryEncoder_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RotaryEncoder_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetPWMMode(uint32 modeMask)
{
    RotaryEncoder_TRIG_CONTROL2_REG = (modeMask & RotaryEncoder_6BIT_MASK);
}



/*******************************************************************************
* Function Name: RotaryEncoder_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RotaryEncoder_CONTROL_REG &= (uint32)~RotaryEncoder_PWM_SYNC_KILL_MASK;
    RotaryEncoder_CONTROL_REG |= ((uint32)((syncKillEnable & RotaryEncoder_1BIT_MASK)  <<
                                               RotaryEncoder_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RotaryEncoder_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RotaryEncoder_CONTROL_REG &= (uint32)~RotaryEncoder_PWM_STOP_KILL_MASK;
    RotaryEncoder_CONTROL_REG |= ((uint32)((stopOnKillEnable & RotaryEncoder_1BIT_MASK)  <<
                                                         RotaryEncoder_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RotaryEncoder_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RotaryEncoder_CONTROL_REG &= (uint32)~RotaryEncoder_PRESCALER_MASK;
    RotaryEncoder_CONTROL_REG |= ((uint32)((deadTime & RotaryEncoder_8BIT_MASK) <<
                                                          RotaryEncoder_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RotaryEncoder_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - RotaryEncoder_INVERT_LINE   - Inverts the line output
*         - RotaryEncoder_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RotaryEncoder_CONTROL_REG &= (uint32)~RotaryEncoder_INV_OUT_MASK;
    RotaryEncoder_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: RotaryEncoder_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_WriteCounter(uint32 count)
{
    RotaryEncoder_COUNTER_REG = (count & RotaryEncoder_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RotaryEncoder_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 RotaryEncoder_ReadCounter(void)
{
    return (RotaryEncoder_COUNTER_REG & RotaryEncoder_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RotaryEncoder_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - RotaryEncoder_COUNT_UP       - Counts up
*     - RotaryEncoder_COUNT_DOWN     - Counts down
*     - RotaryEncoder_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - RotaryEncoder_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RotaryEncoder_CONTROL_REG &= (uint32)~RotaryEncoder_UPDOWN_MASK;
    RotaryEncoder_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RotaryEncoder_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_WritePeriod(uint32 period)
{
    RotaryEncoder_PERIOD_REG = (period & RotaryEncoder_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RotaryEncoder_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 RotaryEncoder_ReadPeriod(void)
{
    return (RotaryEncoder_PERIOD_REG & RotaryEncoder_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RotaryEncoder_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RotaryEncoder_CONTROL_REG &= (uint32)~RotaryEncoder_RELOAD_CC_MASK;
    RotaryEncoder_CONTROL_REG |= (swapEnable & RotaryEncoder_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RotaryEncoder_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_WritePeriodBuf(uint32 periodBuf)
{
    RotaryEncoder_PERIOD_BUF_REG = (periodBuf & RotaryEncoder_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RotaryEncoder_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 RotaryEncoder_ReadPeriodBuf(void)
{
    return (RotaryEncoder_PERIOD_BUF_REG & RotaryEncoder_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RotaryEncoder_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RotaryEncoder_CONTROL_REG &= (uint32)~RotaryEncoder_RELOAD_PERIOD_MASK;
    RotaryEncoder_CONTROL_REG |= ((uint32)((swapEnable & RotaryEncoder_1BIT_MASK) <<
                                                            RotaryEncoder_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RotaryEncoder_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_WriteCompare(uint32 compare)
{
    #if (RotaryEncoder_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (RotaryEncoder_CY_TCPWM_4000) */

    #if (RotaryEncoder_CY_TCPWM_4000)
        currentMode = ((RotaryEncoder_CONTROL_REG & RotaryEncoder_UPDOWN_MASK) >> RotaryEncoder_UPDOWN_SHIFT);

        if (((uint32)RotaryEncoder__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)RotaryEncoder__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (RotaryEncoder_CY_TCPWM_4000) */
    
    RotaryEncoder_COMP_CAP_REG = (compare & RotaryEncoder_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RotaryEncoder_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
*******************************************************************************/
uint32 RotaryEncoder_ReadCompare(void)
{
    #if (RotaryEncoder_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (RotaryEncoder_CY_TCPWM_4000) */

    #if (RotaryEncoder_CY_TCPWM_4000)
        currentMode = ((RotaryEncoder_CONTROL_REG & RotaryEncoder_UPDOWN_MASK) >> RotaryEncoder_UPDOWN_SHIFT);
        
        regVal = RotaryEncoder_COMP_CAP_REG;
        
        if (((uint32)RotaryEncoder__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)RotaryEncoder__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & RotaryEncoder_16BIT_MASK);
    #else
        return (RotaryEncoder_COMP_CAP_REG & RotaryEncoder_16BIT_MASK);
    #endif /* (RotaryEncoder_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: RotaryEncoder_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_WriteCompareBuf(uint32 compareBuf)
{
    #if (RotaryEncoder_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (RotaryEncoder_CY_TCPWM_4000) */

    #if (RotaryEncoder_CY_TCPWM_4000)
        currentMode = ((RotaryEncoder_CONTROL_REG & RotaryEncoder_UPDOWN_MASK) >> RotaryEncoder_UPDOWN_SHIFT);

        if (((uint32)RotaryEncoder__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)RotaryEncoder__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (RotaryEncoder_CY_TCPWM_4000) */
    
    RotaryEncoder_COMP_CAP_BUF_REG = (compareBuf & RotaryEncoder_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RotaryEncoder_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
*******************************************************************************/
uint32 RotaryEncoder_ReadCompareBuf(void)
{
    #if (RotaryEncoder_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (RotaryEncoder_CY_TCPWM_4000) */

    #if (RotaryEncoder_CY_TCPWM_4000)
        currentMode = ((RotaryEncoder_CONTROL_REG & RotaryEncoder_UPDOWN_MASK) >> RotaryEncoder_UPDOWN_SHIFT);

        regVal = RotaryEncoder_COMP_CAP_BUF_REG;
        
        if (((uint32)RotaryEncoder__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)RotaryEncoder__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & RotaryEncoder_16BIT_MASK);
    #else
        return (RotaryEncoder_COMP_CAP_BUF_REG & RotaryEncoder_16BIT_MASK);
    #endif /* (RotaryEncoder_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: RotaryEncoder_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 RotaryEncoder_ReadCapture(void)
{
    return (RotaryEncoder_COMP_CAP_REG & RotaryEncoder_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RotaryEncoder_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 RotaryEncoder_ReadCaptureBuf(void)
{
    return (RotaryEncoder_COMP_CAP_BUF_REG & RotaryEncoder_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RotaryEncoder_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - RotaryEncoder_TRIG_LEVEL     - Level
*     - RotaryEncoder_TRIG_RISING    - Rising edge
*     - RotaryEncoder_TRIG_FALLING   - Falling edge
*     - RotaryEncoder_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RotaryEncoder_TRIG_CONTROL1_REG &= (uint32)~RotaryEncoder_CAPTURE_MASK;
    RotaryEncoder_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RotaryEncoder_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - RotaryEncoder_TRIG_LEVEL     - Level
*     - RotaryEncoder_TRIG_RISING    - Rising edge
*     - RotaryEncoder_TRIG_FALLING   - Falling edge
*     - RotaryEncoder_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RotaryEncoder_TRIG_CONTROL1_REG &= (uint32)~RotaryEncoder_RELOAD_MASK;
    RotaryEncoder_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << RotaryEncoder_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RotaryEncoder_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - RotaryEncoder_TRIG_LEVEL     - Level
*     - RotaryEncoder_TRIG_RISING    - Rising edge
*     - RotaryEncoder_TRIG_FALLING   - Falling edge
*     - RotaryEncoder_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RotaryEncoder_TRIG_CONTROL1_REG &= (uint32)~RotaryEncoder_START_MASK;
    RotaryEncoder_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << RotaryEncoder_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RotaryEncoder_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - RotaryEncoder_TRIG_LEVEL     - Level
*     - RotaryEncoder_TRIG_RISING    - Rising edge
*     - RotaryEncoder_TRIG_FALLING   - Falling edge
*     - RotaryEncoder_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RotaryEncoder_TRIG_CONTROL1_REG &= (uint32)~RotaryEncoder_STOP_MASK;
    RotaryEncoder_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << RotaryEncoder_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RotaryEncoder_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - RotaryEncoder_TRIG_LEVEL     - Level
*     - RotaryEncoder_TRIG_RISING    - Rising edge
*     - RotaryEncoder_TRIG_FALLING   - Falling edge
*     - RotaryEncoder_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RotaryEncoder_TRIG_CONTROL1_REG &= (uint32)~RotaryEncoder_COUNT_MASK;
    RotaryEncoder_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << RotaryEncoder_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RotaryEncoder_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - RotaryEncoder_CMD_CAPTURE    - Trigger Capture command
*     - RotaryEncoder_CMD_RELOAD     - Trigger Reload command
*     - RotaryEncoder_CMD_STOP       - Trigger Stop command
*     - RotaryEncoder_CMD_START      - Trigger Start command
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RotaryEncoder_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RotaryEncoder_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the RotaryEncoder.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - RotaryEncoder_STATUS_DOWN    - Set if counting down
*     - RotaryEncoder_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 RotaryEncoder_ReadStatus(void)
{
    return ((RotaryEncoder_STATUS_REG >> RotaryEncoder_RUNNING_STATUS_SHIFT) |
            (RotaryEncoder_STATUS_REG & RotaryEncoder_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: RotaryEncoder_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - RotaryEncoder_INTR_MASK_TC       - Terminal count mask
*     - RotaryEncoder_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetInterruptMode(uint32 interruptMask)
{
    RotaryEncoder_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: RotaryEncoder_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - RotaryEncoder_INTR_MASK_TC       - Terminal count mask
*     - RotaryEncoder_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 RotaryEncoder_GetInterruptSourceMasked(void)
{
    return (RotaryEncoder_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: RotaryEncoder_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - RotaryEncoder_INTR_MASK_TC       - Terminal count mask
*     - RotaryEncoder_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 RotaryEncoder_GetInterruptSource(void)
{
    return (RotaryEncoder_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: RotaryEncoder_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - RotaryEncoder_INTR_MASK_TC       - Terminal count mask
*     - RotaryEncoder_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_ClearInterrupt(uint32 interruptMask)
{
    RotaryEncoder_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: RotaryEncoder_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - RotaryEncoder_INTR_MASK_TC       - Terminal count mask
*     - RotaryEncoder_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SetInterrupt(uint32 interruptMask)
{
    RotaryEncoder_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
