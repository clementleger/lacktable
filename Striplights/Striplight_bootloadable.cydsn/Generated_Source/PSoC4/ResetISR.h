/*******************************************************************************
* File Name: ResetISR.h
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
#if !defined(CY_ISR_ResetISR_H)
#define CY_ISR_ResetISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ResetISR_Start(void);
void ResetISR_StartEx(cyisraddress address);
void ResetISR_Stop(void);

CY_ISR_PROTO(ResetISR_Interrupt);

void ResetISR_SetVector(cyisraddress address);
cyisraddress ResetISR_GetVector(void);

void ResetISR_SetPriority(uint8 priority);
uint8 ResetISR_GetPriority(void);

void ResetISR_Enable(void);
uint8 ResetISR_GetState(void);
void ResetISR_Disable(void);

void ResetISR_SetPending(void);
void ResetISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ResetISR ISR. */
#define ResetISR_INTC_VECTOR            ((reg32 *) ResetISR__INTC_VECT)

/* Address of the ResetISR ISR priority. */
#define ResetISR_INTC_PRIOR             ((reg32 *) ResetISR__INTC_PRIOR_REG)

/* Priority of the ResetISR interrupt. */
#define ResetISR_INTC_PRIOR_NUMBER      ResetISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ResetISR interrupt. */
#define ResetISR_INTC_SET_EN            ((reg32 *) ResetISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ResetISR interrupt. */
#define ResetISR_INTC_CLR_EN            ((reg32 *) ResetISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ResetISR interrupt state to pending. */
#define ResetISR_INTC_SET_PD            ((reg32 *) ResetISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ResetISR interrupt. */
#define ResetISR_INTC_CLR_PD            ((reg32 *) ResetISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_ResetISR_H */


/* [] END OF FILE */
