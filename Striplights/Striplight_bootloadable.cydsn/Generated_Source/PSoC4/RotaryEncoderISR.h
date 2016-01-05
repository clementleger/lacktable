/*******************************************************************************
* File Name: RotaryEncoderISR.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_RotaryEncoderISR_H)
#define CY_ISR_RotaryEncoderISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void RotaryEncoderISR_Start(void);
void RotaryEncoderISR_StartEx(cyisraddress address);
void RotaryEncoderISR_Stop(void);

CY_ISR_PROTO(RotaryEncoderISR_Interrupt);

void RotaryEncoderISR_SetVector(cyisraddress address);
cyisraddress RotaryEncoderISR_GetVector(void);

void RotaryEncoderISR_SetPriority(uint8 priority);
uint8 RotaryEncoderISR_GetPriority(void);

void RotaryEncoderISR_Enable(void);
uint8 RotaryEncoderISR_GetState(void);
void RotaryEncoderISR_Disable(void);

void RotaryEncoderISR_SetPending(void);
void RotaryEncoderISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the RotaryEncoderISR ISR. */
#define RotaryEncoderISR_INTC_VECTOR            ((reg32 *) RotaryEncoderISR__INTC_VECT)

/* Address of the RotaryEncoderISR ISR priority. */
#define RotaryEncoderISR_INTC_PRIOR             ((reg32 *) RotaryEncoderISR__INTC_PRIOR_REG)

/* Priority of the RotaryEncoderISR interrupt. */
#define RotaryEncoderISR_INTC_PRIOR_NUMBER      RotaryEncoderISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable RotaryEncoderISR interrupt. */
#define RotaryEncoderISR_INTC_SET_EN            ((reg32 *) RotaryEncoderISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the RotaryEncoderISR interrupt. */
#define RotaryEncoderISR_INTC_CLR_EN            ((reg32 *) RotaryEncoderISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the RotaryEncoderISR interrupt state to pending. */
#define RotaryEncoderISR_INTC_SET_PD            ((reg32 *) RotaryEncoderISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the RotaryEncoderISR interrupt. */
#define RotaryEncoderISR_INTC_CLR_PD            ((reg32 *) RotaryEncoderISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_RotaryEncoderISR_H */


/* [] END OF FILE */
