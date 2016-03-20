/*******************************************************************************
* File Name: ClockRot.h
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

#if !defined(CY_CLOCK_ClockRot_H)
#define CY_CLOCK_ClockRot_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void ClockRot_StartEx(uint32 alignClkDiv);
#define ClockRot_Start() \
    ClockRot_StartEx(ClockRot__PA_DIV_ID)

#else

void ClockRot_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void ClockRot_Stop(void);

void ClockRot_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 ClockRot_GetDividerRegister(void);
uint8  ClockRot_GetFractionalDividerRegister(void);

#define ClockRot_Enable()                         ClockRot_Start()
#define ClockRot_Disable()                        ClockRot_Stop()
#define ClockRot_SetDividerRegister(clkDivider, reset)  \
    ClockRot_SetFractionalDividerRegister((clkDivider), 0u)
#define ClockRot_SetDivider(clkDivider)           ClockRot_SetDividerRegister((clkDivider), 1u)
#define ClockRot_SetDividerValue(clkDivider)      ClockRot_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define ClockRot_DIV_ID     ClockRot__DIV_ID

#define ClockRot_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define ClockRot_CTRL_REG   (*(reg32 *)ClockRot__CTRL_REGISTER)
#define ClockRot_DIV_REG    (*(reg32 *)ClockRot__DIV_REGISTER)

#define ClockRot_CMD_DIV_SHIFT          (0u)
#define ClockRot_CMD_PA_DIV_SHIFT       (8u)
#define ClockRot_CMD_DISABLE_SHIFT      (30u)
#define ClockRot_CMD_ENABLE_SHIFT       (31u)

#define ClockRot_CMD_DISABLE_MASK       ((uint32)((uint32)1u << ClockRot_CMD_DISABLE_SHIFT))
#define ClockRot_CMD_ENABLE_MASK        ((uint32)((uint32)1u << ClockRot_CMD_ENABLE_SHIFT))

#define ClockRot_DIV_FRAC_MASK  (0x000000F8u)
#define ClockRot_DIV_FRAC_SHIFT (3u)
#define ClockRot_DIV_INT_MASK   (0xFFFFFF00u)
#define ClockRot_DIV_INT_SHIFT  (8u)

#else 

#define ClockRot_DIV_REG        (*(reg32 *)ClockRot__REGISTER)
#define ClockRot_ENABLE_REG     ClockRot_DIV_REG
#define ClockRot_DIV_FRAC_MASK  ClockRot__FRAC_MASK
#define ClockRot_DIV_FRAC_SHIFT (16u)
#define ClockRot_DIV_INT_MASK   ClockRot__DIVIDER_MASK
#define ClockRot_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_ClockRot_H) */

/* [] END OF FILE */
