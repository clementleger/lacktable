/*******************************************************************************
* File Name: RotB.h  
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

#if !defined(CY_PINS_RotB_H) /* Pins RotB_H */
#define CY_PINS_RotB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "RotB_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    RotB_Write(uint8 value) ;
void    RotB_SetDriveMode(uint8 mode) ;
uint8   RotB_ReadDataReg(void) ;
uint8   RotB_Read(void) ;
uint8   RotB_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RotB_DRIVE_MODE_BITS        (3)
#define RotB_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - RotB_DRIVE_MODE_BITS))

#define RotB_DM_ALG_HIZ         (0x00u)
#define RotB_DM_DIG_HIZ         (0x01u)
#define RotB_DM_RES_UP          (0x02u)
#define RotB_DM_RES_DWN         (0x03u)
#define RotB_DM_OD_LO           (0x04u)
#define RotB_DM_OD_HI           (0x05u)
#define RotB_DM_STRONG          (0x06u)
#define RotB_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define RotB_MASK               RotB__MASK
#define RotB_SHIFT              RotB__SHIFT
#define RotB_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RotB_PS                     (* (reg32 *) RotB__PS)
/* Port Configuration */
#define RotB_PC                     (* (reg32 *) RotB__PC)
/* Data Register */
#define RotB_DR                     (* (reg32 *) RotB__DR)
/* Input Buffer Disable Override */
#define RotB_INP_DIS                (* (reg32 *) RotB__PC2)


#if defined(RotB__INTSTAT)  /* Interrupt Registers */

    #define RotB_INTSTAT                (* (reg32 *) RotB__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define RotB_DRIVE_MODE_SHIFT       (0x00u)
#define RotB_DRIVE_MODE_MASK        (0x07u << RotB_DRIVE_MODE_SHIFT)


#endif /* End Pins RotB_H */


/* [] END OF FILE */
