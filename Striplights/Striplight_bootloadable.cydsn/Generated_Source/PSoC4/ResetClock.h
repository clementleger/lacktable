/*******************************************************************************
* File Name: ResetClock.h
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

#if !defined(CY_CLOCK_ResetClock_H)
#define CY_CLOCK_ResetClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void ResetClock_StartEx(uint32 alignClkDiv);
#define ResetClock_Start() \
    ResetClock_StartEx(ResetClock__PA_DIV_ID)

#else

void ResetClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void ResetClock_Stop(void);

void ResetClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 ResetClock_GetDividerRegister(void);
uint8  ResetClock_GetFractionalDividerRegister(void);

#define ResetClock_Enable()                         ResetClock_Start()
#define ResetClock_Disable()                        ResetClock_Stop()
#define ResetClock_SetDividerRegister(clkDivider, reset)  \
    ResetClock_SetFractionalDividerRegister((clkDivider), 0u)
#define ResetClock_SetDivider(clkDivider)           ResetClock_SetDividerRegister((clkDivider), 1u)
#define ResetClock_SetDividerValue(clkDivider)      ResetClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define ResetClock_DIV_ID     ResetClock__DIV_ID

#define ResetClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define ResetClock_CTRL_REG   (*(reg32 *)ResetClock__CTRL_REGISTER)
#define ResetClock_DIV_REG    (*(reg32 *)ResetClock__DIV_REGISTER)

#define ResetClock_CMD_DIV_SHIFT          (0u)
#define ResetClock_CMD_PA_DIV_SHIFT       (8u)
#define ResetClock_CMD_DISABLE_SHIFT      (30u)
#define ResetClock_CMD_ENABLE_SHIFT       (31u)

#define ResetClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << ResetClock_CMD_DISABLE_SHIFT))
#define ResetClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << ResetClock_CMD_ENABLE_SHIFT))

#define ResetClock_DIV_FRAC_MASK  (0x000000F8u)
#define ResetClock_DIV_FRAC_SHIFT (3u)
#define ResetClock_DIV_INT_MASK   (0xFFFFFF00u)
#define ResetClock_DIV_INT_SHIFT  (8u)

#else 

#define ResetClock_DIV_REG        (*(reg32 *)ResetClock__REGISTER)
#define ResetClock_ENABLE_REG     ResetClock_DIV_REG
#define ResetClock_DIV_FRAC_MASK  ResetClock__FRAC_MASK
#define ResetClock_DIV_FRAC_SHIFT (16u)
#define ResetClock_DIV_INT_MASK   ResetClock__DIVIDER_MASK
#define ResetClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_ResetClock_H) */

/* [] END OF FILE */
