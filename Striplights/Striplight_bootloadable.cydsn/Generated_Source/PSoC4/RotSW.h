/*******************************************************************************
* File Name: RotSW.h  
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

#if !defined(CY_PINS_RotSW_H) /* Pins RotSW_H */
#define CY_PINS_RotSW_H

#include "cytypes.h"
#include "cyfitter.h"
#include "RotSW_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    RotSW_Write(uint8 value) ;
void    RotSW_SetDriveMode(uint8 mode) ;
uint8   RotSW_ReadDataReg(void) ;
uint8   RotSW_Read(void) ;
uint8   RotSW_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RotSW_DRIVE_MODE_BITS        (3)
#define RotSW_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - RotSW_DRIVE_MODE_BITS))

#define RotSW_DM_ALG_HIZ         (0x00u)
#define RotSW_DM_DIG_HIZ         (0x01u)
#define RotSW_DM_RES_UP          (0x02u)
#define RotSW_DM_RES_DWN         (0x03u)
#define RotSW_DM_OD_LO           (0x04u)
#define RotSW_DM_OD_HI           (0x05u)
#define RotSW_DM_STRONG          (0x06u)
#define RotSW_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define RotSW_MASK               RotSW__MASK
#define RotSW_SHIFT              RotSW__SHIFT
#define RotSW_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RotSW_PS                     (* (reg32 *) RotSW__PS)
/* Port Configuration */
#define RotSW_PC                     (* (reg32 *) RotSW__PC)
/* Data Register */
#define RotSW_DR                     (* (reg32 *) RotSW__DR)
/* Input Buffer Disable Override */
#define RotSW_INP_DIS                (* (reg32 *) RotSW__PC2)


#if defined(RotSW__INTSTAT)  /* Interrupt Registers */

    #define RotSW_INTSTAT                (* (reg32 *) RotSW__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define RotSW_DRIVE_MODE_SHIFT       (0x00u)
#define RotSW_DRIVE_MODE_MASK        (0x07u << RotSW_DRIVE_MODE_SHIFT)


#endif /* End Pins RotSW_H */


/* [] END OF FILE */
