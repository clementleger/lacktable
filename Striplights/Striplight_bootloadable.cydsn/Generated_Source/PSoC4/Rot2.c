/*******************************************************************************
* File Name: Rot2.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the Rot2
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

#include "Rot2.h"

uint8 Rot2_initVar = 0u;


/*******************************************************************************
* Function Name: Rot2_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default Rot2 configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Rot2_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (Rot2__QUAD == Rot2_CONFIG)
        Rot2_CONTROL_REG = Rot2_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Rot2_TRIG_CONTROL1_REG  = Rot2_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        Rot2_SetInterruptMode(Rot2_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        Rot2_SetCounterMode(Rot2_COUNT_DOWN);
        Rot2_WritePeriod(Rot2_QUAD_PERIOD_INIT_VALUE);
        Rot2_WriteCounter(Rot2_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (Rot2__QUAD == Rot2_CONFIG) */

    #if (Rot2__TIMER == Rot2_CONFIG)
        Rot2_CONTROL_REG = Rot2_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Rot2_TRIG_CONTROL1_REG  = Rot2_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Rot2_SetInterruptMode(Rot2_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        Rot2_WritePeriod(Rot2_TC_PERIOD_VALUE );

        #if (Rot2__COMPARE == Rot2_TC_COMP_CAP_MODE)
            Rot2_WriteCompare(Rot2_TC_COMPARE_VALUE);

            #if (1u == Rot2_TC_COMPARE_SWAP)
                Rot2_SetCompareSwap(1u);
                Rot2_WriteCompareBuf(Rot2_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == Rot2_TC_COMPARE_SWAP) */
        #endif  /* (Rot2__COMPARE == Rot2_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (Rot2_CY_TCPWM_V2 && Rot2_TIMER_UPDOWN_CNT_USED && !Rot2_CY_TCPWM_4000)
            Rot2_WriteCounter(1u);
        #elif(Rot2__COUNT_DOWN == Rot2_TC_COUNTER_MODE)
            Rot2_WriteCounter(Rot2_TC_PERIOD_VALUE);
        #else
            Rot2_WriteCounter(0u);
        #endif /* (Rot2_CY_TCPWM_V2 && Rot2_TIMER_UPDOWN_CNT_USED && !Rot2_CY_TCPWM_4000) */
    #endif  /* (Rot2__TIMER == Rot2_CONFIG) */

    #if (Rot2__PWM_SEL == Rot2_CONFIG)
        Rot2_CONTROL_REG = Rot2_CTRL_PWM_BASE_CONFIG;

        #if (Rot2__PWM_PR == Rot2_PWM_MODE)
            Rot2_CONTROL_REG |= Rot2_CTRL_PWM_RUN_MODE;
            Rot2_WriteCounter(Rot2_PWM_PR_INIT_VALUE);
        #else
            Rot2_CONTROL_REG |= Rot2_CTRL_PWM_ALIGN | Rot2_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (Rot2_CY_TCPWM_V2 && Rot2_PWM_UPDOWN_CNT_USED && !Rot2_CY_TCPWM_4000)
                Rot2_WriteCounter(1u);
            #elif (Rot2__RIGHT == Rot2_PWM_ALIGN)
                Rot2_WriteCounter(Rot2_PWM_PERIOD_VALUE);
            #else 
                Rot2_WriteCounter(0u);
            #endif  /* (Rot2_CY_TCPWM_V2 && Rot2_PWM_UPDOWN_CNT_USED && !Rot2_CY_TCPWM_4000) */
        #endif  /* (Rot2__PWM_PR == Rot2_PWM_MODE) */

        #if (Rot2__PWM_DT == Rot2_PWM_MODE)
            Rot2_CONTROL_REG |= Rot2_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (Rot2__PWM_DT == Rot2_PWM_MODE) */

        #if (Rot2__PWM == Rot2_PWM_MODE)
            Rot2_CONTROL_REG |= Rot2_CTRL_PWM_PRESCALER;
        #endif  /* (Rot2__PWM == Rot2_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        Rot2_TRIG_CONTROL1_REG  = Rot2_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Rot2_SetInterruptMode(Rot2_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (Rot2__PWM_PR == Rot2_PWM_MODE)
            Rot2_TRIG_CONTROL2_REG =
                    (Rot2_CC_MATCH_NO_CHANGE    |
                    Rot2_OVERLOW_NO_CHANGE      |
                    Rot2_UNDERFLOW_NO_CHANGE);
        #else
            #if (Rot2__LEFT == Rot2_PWM_ALIGN)
                Rot2_TRIG_CONTROL2_REG = Rot2_PWM_MODE_LEFT;
            #endif  /* ( Rot2_PWM_LEFT == Rot2_PWM_ALIGN) */

            #if (Rot2__RIGHT == Rot2_PWM_ALIGN)
                Rot2_TRIG_CONTROL2_REG = Rot2_PWM_MODE_RIGHT;
            #endif  /* ( Rot2_PWM_RIGHT == Rot2_PWM_ALIGN) */

            #if (Rot2__CENTER == Rot2_PWM_ALIGN)
                Rot2_TRIG_CONTROL2_REG = Rot2_PWM_MODE_CENTER;
            #endif  /* ( Rot2_PWM_CENTER == Rot2_PWM_ALIGN) */

            #if (Rot2__ASYMMETRIC == Rot2_PWM_ALIGN)
                Rot2_TRIG_CONTROL2_REG = Rot2_PWM_MODE_ASYM;
            #endif  /* (Rot2__ASYMMETRIC == Rot2_PWM_ALIGN) */
        #endif  /* (Rot2__PWM_PR == Rot2_PWM_MODE) */

        /* Set other values from customizer */
        Rot2_WritePeriod(Rot2_PWM_PERIOD_VALUE );
        Rot2_WriteCompare(Rot2_PWM_COMPARE_VALUE);

        #if (1u == Rot2_PWM_COMPARE_SWAP)
            Rot2_SetCompareSwap(1u);
            Rot2_WriteCompareBuf(Rot2_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == Rot2_PWM_COMPARE_SWAP) */

        #if (1u == Rot2_PWM_PERIOD_SWAP)
            Rot2_SetPeriodSwap(1u);
            Rot2_WritePeriodBuf(Rot2_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == Rot2_PWM_PERIOD_SWAP) */
    #endif  /* (Rot2__PWM_SEL == Rot2_CONFIG) */
    
}


/*******************************************************************************
* Function Name: Rot2_Enable
********************************************************************************
*
* Summary:
*  Enables the Rot2.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Rot2_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    Rot2_BLOCK_CONTROL_REG |= Rot2_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (Rot2__PWM_SEL == Rot2_CONFIG)
        #if (0u == Rot2_PWM_START_SIGNAL_PRESENT)
            Rot2_TriggerCommand(Rot2_MASK, Rot2_CMD_START);
        #endif /* (0u == Rot2_PWM_START_SIGNAL_PRESENT) */
    #endif /* (Rot2__PWM_SEL == Rot2_CONFIG) */

    #if (Rot2__TIMER == Rot2_CONFIG)
        #if (0u == Rot2_TC_START_SIGNAL_PRESENT)
            Rot2_TriggerCommand(Rot2_MASK, Rot2_CMD_START);
        #endif /* (0u == Rot2_TC_START_SIGNAL_PRESENT) */
    #endif /* (Rot2__TIMER == Rot2_CONFIG) */
}


/*******************************************************************************
* Function Name: Rot2_Start
********************************************************************************
*
* Summary:
*  Initializes the Rot2 with default customizer
*  values when called the first time and enables the Rot2.
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
*  Rot2_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time Rot2_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the Rot2_Start() routine.
*
*******************************************************************************/
void Rot2_Start(void)
{
    if (0u == Rot2_initVar)
    {
        Rot2_Init();
        Rot2_initVar = 1u;
    }

    Rot2_Enable();
}


/*******************************************************************************
* Function Name: Rot2_Stop
********************************************************************************
*
* Summary:
*  Disables the Rot2.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Rot2_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Rot2_BLOCK_CONTROL_REG &= (uint32)~Rot2_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rot2_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the Rot2. This function is used when
*  configured as a generic Rot2 and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the Rot2 to operate in
*   Values:
*   - Rot2_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - Rot2_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - Rot2_MODE_QUAD - Quadrature decoder
*         - Rot2_MODE_PWM - PWM
*         - Rot2_MODE_PWM_DT - PWM with dead time
*         - Rot2_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void Rot2_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Rot2_CONTROL_REG &= (uint32)~Rot2_MODE_MASK;
    Rot2_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rot2_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - Rot2_MODE_X1 - Counts on phi 1 rising
*         - Rot2_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - Rot2_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void Rot2_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Rot2_CONTROL_REG &= (uint32)~Rot2_QUAD_MODE_MASK;
    Rot2_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rot2_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - Rot2_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - Rot2_PRESCALE_DIVBY2    - Divide by 2
*         - Rot2_PRESCALE_DIVBY4    - Divide by 4
*         - Rot2_PRESCALE_DIVBY8    - Divide by 8
*         - Rot2_PRESCALE_DIVBY16   - Divide by 16
*         - Rot2_PRESCALE_DIVBY32   - Divide by 32
*         - Rot2_PRESCALE_DIVBY64   - Divide by 64
*         - Rot2_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void Rot2_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Rot2_CONTROL_REG &= (uint32)~Rot2_PRESCALER_MASK;
    Rot2_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rot2_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the Rot2 runs
*  continuously or stops when terminal count is reached.  By default the
*  Rot2 operates in the continuous mode.
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
void Rot2_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Rot2_CONTROL_REG &= (uint32)~Rot2_ONESHOT_MASK;
    Rot2_CONTROL_REG |= ((uint32)((oneShotEnable & Rot2_1BIT_MASK) <<
                                                               Rot2_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rot2_SetPWMMode
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
void Rot2_SetPWMMode(uint32 modeMask)
{
    Rot2_TRIG_CONTROL2_REG = (modeMask & Rot2_6BIT_MASK);
}



/*******************************************************************************
* Function Name: Rot2_SetPWMSyncKill
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
void Rot2_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Rot2_CONTROL_REG &= (uint32)~Rot2_PWM_SYNC_KILL_MASK;
    Rot2_CONTROL_REG |= ((uint32)((syncKillEnable & Rot2_1BIT_MASK)  <<
                                               Rot2_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rot2_SetPWMStopOnKill
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
void Rot2_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Rot2_CONTROL_REG &= (uint32)~Rot2_PWM_STOP_KILL_MASK;
    Rot2_CONTROL_REG |= ((uint32)((stopOnKillEnable & Rot2_1BIT_MASK)  <<
                                                         Rot2_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rot2_SetPWMDeadTime
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
void Rot2_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Rot2_CONTROL_REG &= (uint32)~Rot2_PRESCALER_MASK;
    Rot2_CONTROL_REG |= ((uint32)((deadTime & Rot2_8BIT_MASK) <<
                                                          Rot2_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rot2_SetPWMInvert
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
*         - Rot2_INVERT_LINE   - Inverts the line output
*         - Rot2_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void Rot2_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Rot2_CONTROL_REG &= (uint32)~Rot2_INV_OUT_MASK;
    Rot2_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: Rot2_WriteCounter
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
void Rot2_WriteCounter(uint32 count)
{
    Rot2_COUNTER_REG = (count & Rot2_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Rot2_ReadCounter
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
uint32 Rot2_ReadCounter(void)
{
    return (Rot2_COUNTER_REG & Rot2_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Rot2_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - Rot2_COUNT_UP       - Counts up
*     - Rot2_COUNT_DOWN     - Counts down
*     - Rot2_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - Rot2_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void Rot2_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Rot2_CONTROL_REG &= (uint32)~Rot2_UPDOWN_MASK;
    Rot2_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rot2_WritePeriod
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
void Rot2_WritePeriod(uint32 period)
{
    Rot2_PERIOD_REG = (period & Rot2_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Rot2_ReadPeriod
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
uint32 Rot2_ReadPeriod(void)
{
    return (Rot2_PERIOD_REG & Rot2_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Rot2_SetCompareSwap
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
void Rot2_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Rot2_CONTROL_REG &= (uint32)~Rot2_RELOAD_CC_MASK;
    Rot2_CONTROL_REG |= (swapEnable & Rot2_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rot2_WritePeriodBuf
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
void Rot2_WritePeriodBuf(uint32 periodBuf)
{
    Rot2_PERIOD_BUF_REG = (periodBuf & Rot2_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Rot2_ReadPeriodBuf
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
uint32 Rot2_ReadPeriodBuf(void)
{
    return (Rot2_PERIOD_BUF_REG & Rot2_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Rot2_SetPeriodSwap
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
void Rot2_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Rot2_CONTROL_REG &= (uint32)~Rot2_RELOAD_PERIOD_MASK;
    Rot2_CONTROL_REG |= ((uint32)((swapEnable & Rot2_1BIT_MASK) <<
                                                            Rot2_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rot2_WriteCompare
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
void Rot2_WriteCompare(uint32 compare)
{
    #if (Rot2_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Rot2_CY_TCPWM_4000) */

    #if (Rot2_CY_TCPWM_4000)
        currentMode = ((Rot2_CONTROL_REG & Rot2_UPDOWN_MASK) >> Rot2_UPDOWN_SHIFT);

        if (((uint32)Rot2__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)Rot2__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (Rot2_CY_TCPWM_4000) */
    
    Rot2_COMP_CAP_REG = (compare & Rot2_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Rot2_ReadCompare
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
uint32 Rot2_ReadCompare(void)
{
    #if (Rot2_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Rot2_CY_TCPWM_4000) */

    #if (Rot2_CY_TCPWM_4000)
        currentMode = ((Rot2_CONTROL_REG & Rot2_UPDOWN_MASK) >> Rot2_UPDOWN_SHIFT);
        
        regVal = Rot2_COMP_CAP_REG;
        
        if (((uint32)Rot2__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Rot2__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Rot2_16BIT_MASK);
    #else
        return (Rot2_COMP_CAP_REG & Rot2_16BIT_MASK);
    #endif /* (Rot2_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Rot2_WriteCompareBuf
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
void Rot2_WriteCompareBuf(uint32 compareBuf)
{
    #if (Rot2_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Rot2_CY_TCPWM_4000) */

    #if (Rot2_CY_TCPWM_4000)
        currentMode = ((Rot2_CONTROL_REG & Rot2_UPDOWN_MASK) >> Rot2_UPDOWN_SHIFT);

        if (((uint32)Rot2__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)Rot2__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (Rot2_CY_TCPWM_4000) */
    
    Rot2_COMP_CAP_BUF_REG = (compareBuf & Rot2_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Rot2_ReadCompareBuf
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
uint32 Rot2_ReadCompareBuf(void)
{
    #if (Rot2_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Rot2_CY_TCPWM_4000) */

    #if (Rot2_CY_TCPWM_4000)
        currentMode = ((Rot2_CONTROL_REG & Rot2_UPDOWN_MASK) >> Rot2_UPDOWN_SHIFT);

        regVal = Rot2_COMP_CAP_BUF_REG;
        
        if (((uint32)Rot2__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Rot2__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Rot2_16BIT_MASK);
    #else
        return (Rot2_COMP_CAP_BUF_REG & Rot2_16BIT_MASK);
    #endif /* (Rot2_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Rot2_ReadCapture
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
uint32 Rot2_ReadCapture(void)
{
    return (Rot2_COMP_CAP_REG & Rot2_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Rot2_ReadCaptureBuf
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
uint32 Rot2_ReadCaptureBuf(void)
{
    return (Rot2_COMP_CAP_BUF_REG & Rot2_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Rot2_SetCaptureMode
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
*     - Rot2_TRIG_LEVEL     - Level
*     - Rot2_TRIG_RISING    - Rising edge
*     - Rot2_TRIG_FALLING   - Falling edge
*     - Rot2_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Rot2_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Rot2_TRIG_CONTROL1_REG &= (uint32)~Rot2_CAPTURE_MASK;
    Rot2_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rot2_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Rot2_TRIG_LEVEL     - Level
*     - Rot2_TRIG_RISING    - Rising edge
*     - Rot2_TRIG_FALLING   - Falling edge
*     - Rot2_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Rot2_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Rot2_TRIG_CONTROL1_REG &= (uint32)~Rot2_RELOAD_MASK;
    Rot2_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Rot2_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rot2_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Rot2_TRIG_LEVEL     - Level
*     - Rot2_TRIG_RISING    - Rising edge
*     - Rot2_TRIG_FALLING   - Falling edge
*     - Rot2_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Rot2_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Rot2_TRIG_CONTROL1_REG &= (uint32)~Rot2_START_MASK;
    Rot2_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Rot2_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rot2_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Rot2_TRIG_LEVEL     - Level
*     - Rot2_TRIG_RISING    - Rising edge
*     - Rot2_TRIG_FALLING   - Falling edge
*     - Rot2_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Rot2_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Rot2_TRIG_CONTROL1_REG &= (uint32)~Rot2_STOP_MASK;
    Rot2_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Rot2_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rot2_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Rot2_TRIG_LEVEL     - Level
*     - Rot2_TRIG_RISING    - Rising edge
*     - Rot2_TRIG_FALLING   - Falling edge
*     - Rot2_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Rot2_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Rot2_TRIG_CONTROL1_REG &= (uint32)~Rot2_COUNT_MASK;
    Rot2_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Rot2_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rot2_TriggerCommand
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
*     - Rot2_CMD_CAPTURE    - Trigger Capture command
*     - Rot2_CMD_RELOAD     - Trigger Reload command
*     - Rot2_CMD_STOP       - Trigger Stop command
*     - Rot2_CMD_START      - Trigger Start command
*
* Return:
*  None
*
*******************************************************************************/
void Rot2_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Rot2_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rot2_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the Rot2.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - Rot2_STATUS_DOWN    - Set if counting down
*     - Rot2_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 Rot2_ReadStatus(void)
{
    return ((Rot2_STATUS_REG >> Rot2_RUNNING_STATUS_SHIFT) |
            (Rot2_STATUS_REG & Rot2_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: Rot2_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - Rot2_INTR_MASK_TC       - Terminal count mask
*     - Rot2_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Rot2_SetInterruptMode(uint32 interruptMask)
{
    Rot2_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: Rot2_GetInterruptSourceMasked
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
*     - Rot2_INTR_MASK_TC       - Terminal count mask
*     - Rot2_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Rot2_GetInterruptSourceMasked(void)
{
    return (Rot2_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: Rot2_GetInterruptSource
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
*     - Rot2_INTR_MASK_TC       - Terminal count mask
*     - Rot2_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Rot2_GetInterruptSource(void)
{
    return (Rot2_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: Rot2_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - Rot2_INTR_MASK_TC       - Terminal count mask
*     - Rot2_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Rot2_ClearInterrupt(uint32 interruptMask)
{
    Rot2_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: Rot2_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - Rot2_INTR_MASK_TC       - Terminal count mask
*     - Rot2_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Rot2_SetInterrupt(uint32 interruptMask)
{
    Rot2_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
