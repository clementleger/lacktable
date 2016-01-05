/*******************************************************************************
* File Name: RotaryEncoderClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_RotaryEncoderClock_H)
#define CY_CLOCK_RotaryEncoderClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void RotaryEncoderClock_StartEx(uint32 alignClkDiv);
#define RotaryEncoderClock_Start() \
    RotaryEncoderClock_StartEx(RotaryEncoderClock__PA_DIV_ID)

#else

void RotaryEncoderClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void RotaryEncoderClock_Stop(void);

void RotaryEncoderClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 RotaryEncoderClock_GetDividerRegister(void);
uint8  RotaryEncoderClock_GetFractionalDividerRegister(void);

#define RotaryEncoderClock_Enable()                         RotaryEncoderClock_Start()
#define RotaryEncoderClock_Disable()                        RotaryEncoderClock_Stop()
#define RotaryEncoderClock_SetDividerRegister(clkDivider, reset)  \
    RotaryEncoderClock_SetFractionalDividerRegister((clkDivider), 0u)
#define RotaryEncoderClock_SetDivider(clkDivider)           RotaryEncoderClock_SetDividerRegister((clkDivider), 1u)
#define RotaryEncoderClock_SetDividerValue(clkDivider)      RotaryEncoderClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define RotaryEncoderClock_DIV_ID     RotaryEncoderClock__DIV_ID

#define RotaryEncoderClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define RotaryEncoderClock_CTRL_REG   (*(reg32 *)RotaryEncoderClock__CTRL_REGISTER)
#define RotaryEncoderClock_DIV_REG    (*(reg32 *)RotaryEncoderClock__DIV_REGISTER)

#define RotaryEncoderClock_CMD_DIV_SHIFT          (0u)
#define RotaryEncoderClock_CMD_PA_DIV_SHIFT       (8u)
#define RotaryEncoderClock_CMD_DISABLE_SHIFT      (30u)
#define RotaryEncoderClock_CMD_ENABLE_SHIFT       (31u)

#define RotaryEncoderClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << RotaryEncoderClock_CMD_DISABLE_SHIFT))
#define RotaryEncoderClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << RotaryEncoderClock_CMD_ENABLE_SHIFT))

#define RotaryEncoderClock_DIV_FRAC_MASK  (0x000000F8u)
#define RotaryEncoderClock_DIV_FRAC_SHIFT (3u)
#define RotaryEncoderClock_DIV_INT_MASK   (0xFFFFFF00u)
#define RotaryEncoderClock_DIV_INT_SHIFT  (8u)

#else 

#define RotaryEncoderClock_DIV_REG        (*(reg32 *)RotaryEncoderClock__REGISTER)
#define RotaryEncoderClock_ENABLE_REG     RotaryEncoderClock_DIV_REG
#define RotaryEncoderClock_DIV_FRAC_MASK  RotaryEncoderClock__FRAC_MASK
#define RotaryEncoderClock_DIV_FRAC_SHIFT (16u)
#define RotaryEncoderClock_DIV_INT_MASK   RotaryEncoderClock__DIVIDER_MASK
#define RotaryEncoderClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_RotaryEncoderClock_H) */

/* [] END OF FILE */
