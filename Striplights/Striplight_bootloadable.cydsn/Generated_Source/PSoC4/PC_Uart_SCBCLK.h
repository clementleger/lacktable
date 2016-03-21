/*******************************************************************************
* File Name: PC_Uart_SCBCLK.h
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

#if !defined(CY_CLOCK_PC_Uart_SCBCLK_H)
#define CY_CLOCK_PC_Uart_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void PC_Uart_SCBCLK_StartEx(uint32 alignClkDiv);
#define PC_Uart_SCBCLK_Start() \
    PC_Uart_SCBCLK_StartEx(PC_Uart_SCBCLK__PA_DIV_ID)

#else

void PC_Uart_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void PC_Uart_SCBCLK_Stop(void);

void PC_Uart_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 PC_Uart_SCBCLK_GetDividerRegister(void);
uint8  PC_Uart_SCBCLK_GetFractionalDividerRegister(void);

#define PC_Uart_SCBCLK_Enable()                         PC_Uart_SCBCLK_Start()
#define PC_Uart_SCBCLK_Disable()                        PC_Uart_SCBCLK_Stop()
#define PC_Uart_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    PC_Uart_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define PC_Uart_SCBCLK_SetDivider(clkDivider)           PC_Uart_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define PC_Uart_SCBCLK_SetDividerValue(clkDivider)      PC_Uart_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define PC_Uart_SCBCLK_DIV_ID     PC_Uart_SCBCLK__DIV_ID

#define PC_Uart_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define PC_Uart_SCBCLK_CTRL_REG   (*(reg32 *)PC_Uart_SCBCLK__CTRL_REGISTER)
#define PC_Uart_SCBCLK_DIV_REG    (*(reg32 *)PC_Uart_SCBCLK__DIV_REGISTER)

#define PC_Uart_SCBCLK_CMD_DIV_SHIFT          (0u)
#define PC_Uart_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define PC_Uart_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define PC_Uart_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define PC_Uart_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << PC_Uart_SCBCLK_CMD_DISABLE_SHIFT))
#define PC_Uart_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << PC_Uart_SCBCLK_CMD_ENABLE_SHIFT))

#define PC_Uart_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define PC_Uart_SCBCLK_DIV_FRAC_SHIFT (3u)
#define PC_Uart_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define PC_Uart_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define PC_Uart_SCBCLK_DIV_REG        (*(reg32 *)PC_Uart_SCBCLK__REGISTER)
#define PC_Uart_SCBCLK_ENABLE_REG     PC_Uart_SCBCLK_DIV_REG
#define PC_Uart_SCBCLK_DIV_FRAC_MASK  PC_Uart_SCBCLK__FRAC_MASK
#define PC_Uart_SCBCLK_DIV_FRAC_SHIFT (16u)
#define PC_Uart_SCBCLK_DIV_INT_MASK   PC_Uart_SCBCLK__DIVIDER_MASK
#define PC_Uart_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_PC_Uart_SCBCLK_H) */

/* [] END OF FILE */
