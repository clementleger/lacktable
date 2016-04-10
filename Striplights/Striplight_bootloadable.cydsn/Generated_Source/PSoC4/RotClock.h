/*******************************************************************************
* File Name: RotClock.h
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

#if !defined(CY_CLOCK_RotClock_H)
#define CY_CLOCK_RotClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void RotClock_StartEx(uint32 alignClkDiv);
#define RotClock_Start() \
    RotClock_StartEx(RotClock__PA_DIV_ID)

#else

void RotClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void RotClock_Stop(void);

void RotClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 RotClock_GetDividerRegister(void);
uint8  RotClock_GetFractionalDividerRegister(void);

#define RotClock_Enable()                         RotClock_Start()
#define RotClock_Disable()                        RotClock_Stop()
#define RotClock_SetDividerRegister(clkDivider, reset)  \
    RotClock_SetFractionalDividerRegister((clkDivider), 0u)
#define RotClock_SetDivider(clkDivider)           RotClock_SetDividerRegister((clkDivider), 1u)
#define RotClock_SetDividerValue(clkDivider)      RotClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define RotClock_DIV_ID     RotClock__DIV_ID

#define RotClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define RotClock_CTRL_REG   (*(reg32 *)RotClock__CTRL_REGISTER)
#define RotClock_DIV_REG    (*(reg32 *)RotClock__DIV_REGISTER)

#define RotClock_CMD_DIV_SHIFT          (0u)
#define RotClock_CMD_PA_DIV_SHIFT       (8u)
#define RotClock_CMD_DISABLE_SHIFT      (30u)
#define RotClock_CMD_ENABLE_SHIFT       (31u)

#define RotClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << RotClock_CMD_DISABLE_SHIFT))
#define RotClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << RotClock_CMD_ENABLE_SHIFT))

#define RotClock_DIV_FRAC_MASK  (0x000000F8u)
#define RotClock_DIV_FRAC_SHIFT (3u)
#define RotClock_DIV_INT_MASK   (0xFFFFFF00u)
#define RotClock_DIV_INT_SHIFT  (8u)

#else 

#define RotClock_DIV_REG        (*(reg32 *)RotClock__REGISTER)
#define RotClock_ENABLE_REG     RotClock_DIV_REG
#define RotClock_DIV_FRAC_MASK  RotClock__FRAC_MASK
#define RotClock_DIV_FRAC_SHIFT (16u)
#define RotClock_DIV_INT_MASK   RotClock__DIVIDER_MASK
#define RotClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_RotClock_H) */

/* [] END OF FILE */
