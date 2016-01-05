/*******************************************************************************
* File Name: RotaryEncoderB.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_RotaryEncoderB_H) /* Pins RotaryEncoderB_H */
#define CY_PINS_RotaryEncoderB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "RotaryEncoderB_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    RotaryEncoderB_Write(uint8 value) ;
void    RotaryEncoderB_SetDriveMode(uint8 mode) ;
uint8   RotaryEncoderB_ReadDataReg(void) ;
uint8   RotaryEncoderB_Read(void) ;
uint8   RotaryEncoderB_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RotaryEncoderB_DRIVE_MODE_BITS        (3)
#define RotaryEncoderB_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - RotaryEncoderB_DRIVE_MODE_BITS))

#define RotaryEncoderB_DM_ALG_HIZ         (0x00u)
#define RotaryEncoderB_DM_DIG_HIZ         (0x01u)
#define RotaryEncoderB_DM_RES_UP          (0x02u)
#define RotaryEncoderB_DM_RES_DWN         (0x03u)
#define RotaryEncoderB_DM_OD_LO           (0x04u)
#define RotaryEncoderB_DM_OD_HI           (0x05u)
#define RotaryEncoderB_DM_STRONG          (0x06u)
#define RotaryEncoderB_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define RotaryEncoderB_MASK               RotaryEncoderB__MASK
#define RotaryEncoderB_SHIFT              RotaryEncoderB__SHIFT
#define RotaryEncoderB_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RotaryEncoderB_PS                     (* (reg32 *) RotaryEncoderB__PS)
/* Port Configuration */
#define RotaryEncoderB_PC                     (* (reg32 *) RotaryEncoderB__PC)
/* Data Register */
#define RotaryEncoderB_DR                     (* (reg32 *) RotaryEncoderB__DR)
/* Input Buffer Disable Override */
#define RotaryEncoderB_INP_DIS                (* (reg32 *) RotaryEncoderB__PC2)


#if defined(RotaryEncoderB__INTSTAT)  /* Interrupt Registers */

    #define RotaryEncoderB_INTSTAT                (* (reg32 *) RotaryEncoderB__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define RotaryEncoderB_DRIVE_MODE_SHIFT       (0x00u)
#define RotaryEncoderB_DRIVE_MODE_MASK        (0x07u << RotaryEncoderB_DRIVE_MODE_SHIFT)


#endif /* End Pins RotaryEncoderB_H */


/* [] END OF FILE */
