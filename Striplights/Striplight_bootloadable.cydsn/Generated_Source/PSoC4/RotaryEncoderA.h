/*******************************************************************************
* File Name: RotaryEncoderA.h  
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

#if !defined(CY_PINS_RotaryEncoderA_H) /* Pins RotaryEncoderA_H */
#define CY_PINS_RotaryEncoderA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "RotaryEncoderA_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    RotaryEncoderA_Write(uint8 value) ;
void    RotaryEncoderA_SetDriveMode(uint8 mode) ;
uint8   RotaryEncoderA_ReadDataReg(void) ;
uint8   RotaryEncoderA_Read(void) ;
uint8   RotaryEncoderA_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RotaryEncoderA_DRIVE_MODE_BITS        (3)
#define RotaryEncoderA_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - RotaryEncoderA_DRIVE_MODE_BITS))

#define RotaryEncoderA_DM_ALG_HIZ         (0x00u)
#define RotaryEncoderA_DM_DIG_HIZ         (0x01u)
#define RotaryEncoderA_DM_RES_UP          (0x02u)
#define RotaryEncoderA_DM_RES_DWN         (0x03u)
#define RotaryEncoderA_DM_OD_LO           (0x04u)
#define RotaryEncoderA_DM_OD_HI           (0x05u)
#define RotaryEncoderA_DM_STRONG          (0x06u)
#define RotaryEncoderA_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define RotaryEncoderA_MASK               RotaryEncoderA__MASK
#define RotaryEncoderA_SHIFT              RotaryEncoderA__SHIFT
#define RotaryEncoderA_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RotaryEncoderA_PS                     (* (reg32 *) RotaryEncoderA__PS)
/* Port Configuration */
#define RotaryEncoderA_PC                     (* (reg32 *) RotaryEncoderA__PC)
/* Data Register */
#define RotaryEncoderA_DR                     (* (reg32 *) RotaryEncoderA__DR)
/* Input Buffer Disable Override */
#define RotaryEncoderA_INP_DIS                (* (reg32 *) RotaryEncoderA__PC2)


#if defined(RotaryEncoderA__INTSTAT)  /* Interrupt Registers */

    #define RotaryEncoderA_INTSTAT                (* (reg32 *) RotaryEncoderA__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define RotaryEncoderA_DRIVE_MODE_SHIFT       (0x00u)
#define RotaryEncoderA_DRIVE_MODE_MASK        (0x07u << RotaryEncoderA_DRIVE_MODE_SHIFT)


#endif /* End Pins RotaryEncoderA_H */


/* [] END OF FILE */
