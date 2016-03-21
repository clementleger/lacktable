/*******************************************************************************
* File Name: ClockRot_1.h
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

#if !defined(CY_CLOCK_ClockRot_1_H)
#define CY_CLOCK_ClockRot_1_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void ClockRot_1_StartEx(uint32 alignClkDiv);
#define ClockRot_1_Start() \
    ClockRot_1_StartEx(ClockRot_1__PA_DIV_ID)

#else

void ClockRot_1_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void ClockRot_1_Stop(void);

void ClockRot_1_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 ClockRot_1_GetDividerRegister(void);
uint8  ClockRot_1_GetFractionalDividerRegister(void);

#define ClockRot_1_Enable()                         ClockRot_1_Start()
#define ClockRot_1_Disable()                        ClockRot_1_Stop()
#define ClockRot_1_SetDividerRegister(clkDivider, reset)  \
    ClockRot_1_SetFractionalDividerRegister((clkDivider), 0u)
#define ClockRot_1_SetDivider(clkDivider)           ClockRot_1_SetDividerRegister((clkDivider), 1u)
#define ClockRot_1_SetDividerValue(clkDivider)      ClockRot_1_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define ClockRot_1_DIV_ID     ClockRot_1__DIV_ID

#define ClockRot_1_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define ClockRot_1_CTRL_REG   (*(reg32 *)ClockRot_1__CTRL_REGISTER)
#define ClockRot_1_DIV_REG    (*(reg32 *)ClockRot_1__DIV_REGISTER)

#define ClockRot_1_CMD_DIV_SHIFT          (0u)
#define ClockRot_1_CMD_PA_DIV_SHIFT       (8u)
#define ClockRot_1_CMD_DISABLE_SHIFT      (30u)
#define ClockRot_1_CMD_ENABLE_SHIFT       (31u)

#define ClockRot_1_CMD_DISABLE_MASK       ((uint32)((uint32)1u << ClockRot_1_CMD_DISABLE_SHIFT))
#define ClockRot_1_CMD_ENABLE_MASK        ((uint32)((uint32)1u << ClockRot_1_CMD_ENABLE_SHIFT))

#define ClockRot_1_DIV_FRAC_MASK  (0x000000F8u)
#define ClockRot_1_DIV_FRAC_SHIFT (3u)
#define ClockRot_1_DIV_INT_MASK   (0xFFFFFF00u)
#define ClockRot_1_DIV_INT_SHIFT  (8u)

#else 

#define ClockRot_1_DIV_REG        (*(reg32 *)ClockRot_1__REGISTER)
#define ClockRot_1_ENABLE_REG     ClockRot_1_DIV_REG
#define ClockRot_1_DIV_FRAC_MASK  ClockRot_1__FRAC_MASK
#define ClockRot_1_DIV_FRAC_SHIFT (16u)
#define ClockRot_1_DIV_INT_MASK   ClockRot_1__DIVIDER_MASK
#define ClockRot_1_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_ClockRot_1_H) */

/* [] END OF FILE */
