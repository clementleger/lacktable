/*******************************************************************************
* File Name: ESP_SCBCLK.h
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

#if !defined(CY_CLOCK_ESP_SCBCLK_H)
#define CY_CLOCK_ESP_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void ESP_SCBCLK_StartEx(uint32 alignClkDiv);
#define ESP_SCBCLK_Start() \
    ESP_SCBCLK_StartEx(ESP_SCBCLK__PA_DIV_ID)

#else

void ESP_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void ESP_SCBCLK_Stop(void);

void ESP_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 ESP_SCBCLK_GetDividerRegister(void);
uint8  ESP_SCBCLK_GetFractionalDividerRegister(void);

#define ESP_SCBCLK_Enable()                         ESP_SCBCLK_Start()
#define ESP_SCBCLK_Disable()                        ESP_SCBCLK_Stop()
#define ESP_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    ESP_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define ESP_SCBCLK_SetDivider(clkDivider)           ESP_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define ESP_SCBCLK_SetDividerValue(clkDivider)      ESP_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define ESP_SCBCLK_DIV_ID     ESP_SCBCLK__DIV_ID

#define ESP_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define ESP_SCBCLK_CTRL_REG   (*(reg32 *)ESP_SCBCLK__CTRL_REGISTER)
#define ESP_SCBCLK_DIV_REG    (*(reg32 *)ESP_SCBCLK__DIV_REGISTER)

#define ESP_SCBCLK_CMD_DIV_SHIFT          (0u)
#define ESP_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define ESP_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define ESP_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define ESP_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << ESP_SCBCLK_CMD_DISABLE_SHIFT))
#define ESP_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << ESP_SCBCLK_CMD_ENABLE_SHIFT))

#define ESP_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define ESP_SCBCLK_DIV_FRAC_SHIFT (3u)
#define ESP_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define ESP_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define ESP_SCBCLK_DIV_REG        (*(reg32 *)ESP_SCBCLK__REGISTER)
#define ESP_SCBCLK_ENABLE_REG     ESP_SCBCLK_DIV_REG
#define ESP_SCBCLK_DIV_FRAC_MASK  ESP_SCBCLK__FRAC_MASK
#define ESP_SCBCLK_DIV_FRAC_SHIFT (16u)
#define ESP_SCBCLK_DIV_INT_MASK   ESP_SCBCLK__DIVIDER_MASK
#define ESP_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_ESP_SCBCLK_H) */

/* [] END OF FILE */
