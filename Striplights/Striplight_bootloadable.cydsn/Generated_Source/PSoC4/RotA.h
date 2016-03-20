/*******************************************************************************
* File Name: RotA.h  
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

#if !defined(CY_PINS_RotA_H) /* Pins RotA_H */
#define CY_PINS_RotA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "RotA_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    RotA_Write(uint8 value) ;
void    RotA_SetDriveMode(uint8 mode) ;
uint8   RotA_ReadDataReg(void) ;
uint8   RotA_Read(void) ;
uint8   RotA_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RotA_DRIVE_MODE_BITS        (3)
#define RotA_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - RotA_DRIVE_MODE_BITS))

#define RotA_DM_ALG_HIZ         (0x00u)
#define RotA_DM_DIG_HIZ         (0x01u)
#define RotA_DM_RES_UP          (0x02u)
#define RotA_DM_RES_DWN         (0x03u)
#define RotA_DM_OD_LO           (0x04u)
#define RotA_DM_OD_HI           (0x05u)
#define RotA_DM_STRONG          (0x06u)
#define RotA_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define RotA_MASK               RotA__MASK
#define RotA_SHIFT              RotA__SHIFT
#define RotA_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RotA_PS                     (* (reg32 *) RotA__PS)
/* Port Configuration */
#define RotA_PC                     (* (reg32 *) RotA__PC)
/* Data Register */
#define RotA_DR                     (* (reg32 *) RotA__DR)
/* Input Buffer Disable Override */
#define RotA_INP_DIS                (* (reg32 *) RotA__PC2)


#if defined(RotA__INTSTAT)  /* Interrupt Registers */

    #define RotA_INTSTAT                (* (reg32 *) RotA__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define RotA_DRIVE_MODE_SHIFT       (0x00u)
#define RotA_DRIVE_MODE_MASK        (0x07u << RotA_DRIVE_MODE_SHIFT)


#endif /* End Pins RotA_H */


/* [] END OF FILE */
