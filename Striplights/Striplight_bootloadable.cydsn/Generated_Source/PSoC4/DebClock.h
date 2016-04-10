/*******************************************************************************
* File Name: DebClock.h
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

#if !defined(CY_CLOCK_DebClock_H)
#define CY_CLOCK_DebClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void DebClock_StartEx(uint32 alignClkDiv);
#define DebClock_Start() \
    DebClock_StartEx(DebClock__PA_DIV_ID)

#else

void DebClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void DebClock_Stop(void);

void DebClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 DebClock_GetDividerRegister(void);
uint8  DebClock_GetFractionalDividerRegister(void);

#define DebClock_Enable()                         DebClock_Start()
#define DebClock_Disable()                        DebClock_Stop()
#define DebClock_SetDividerRegister(clkDivider, reset)  \
    DebClock_SetFractionalDividerRegister((clkDivider), 0u)
#define DebClock_SetDivider(clkDivider)           DebClock_SetDividerRegister((clkDivider), 1u)
#define DebClock_SetDividerValue(clkDivider)      DebClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define DebClock_DIV_ID     DebClock__DIV_ID

#define DebClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define DebClock_CTRL_REG   (*(reg32 *)DebClock__CTRL_REGISTER)
#define DebClock_DIV_REG    (*(reg32 *)DebClock__DIV_REGISTER)

#define DebClock_CMD_DIV_SHIFT          (0u)
#define DebClock_CMD_PA_DIV_SHIFT       (8u)
#define DebClock_CMD_DISABLE_SHIFT      (30u)
#define DebClock_CMD_ENABLE_SHIFT       (31u)

#define DebClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << DebClock_CMD_DISABLE_SHIFT))
#define DebClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << DebClock_CMD_ENABLE_SHIFT))

#define DebClock_DIV_FRAC_MASK  (0x000000F8u)
#define DebClock_DIV_FRAC_SHIFT (3u)
#define DebClock_DIV_INT_MASK   (0xFFFFFF00u)
#define DebClock_DIV_INT_SHIFT  (8u)

#else 

#define DebClock_DIV_REG        (*(reg32 *)DebClock__REGISTER)
#define DebClock_ENABLE_REG     DebClock_DIV_REG
#define DebClock_DIV_FRAC_MASK  DebClock__FRAC_MASK
#define DebClock_DIV_FRAC_SHIFT (16u)
#define DebClock_DIV_INT_MASK   DebClock__DIVIDER_MASK
#define DebClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_DebClock_H) */

/* [] END OF FILE */
