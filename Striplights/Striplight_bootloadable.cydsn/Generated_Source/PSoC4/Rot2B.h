/*******************************************************************************
* File Name: Rot2B.h  
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

#if !defined(CY_PINS_Rot2B_H) /* Pins Rot2B_H */
#define CY_PINS_Rot2B_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Rot2B_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Rot2B_Write(uint8 value) ;
void    Rot2B_SetDriveMode(uint8 mode) ;
uint8   Rot2B_ReadDataReg(void) ;
uint8   Rot2B_Read(void) ;
uint8   Rot2B_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Rot2B_DRIVE_MODE_BITS        (3)
#define Rot2B_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Rot2B_DRIVE_MODE_BITS))

#define Rot2B_DM_ALG_HIZ         (0x00u)
#define Rot2B_DM_DIG_HIZ         (0x01u)
#define Rot2B_DM_RES_UP          (0x02u)
#define Rot2B_DM_RES_DWN         (0x03u)
#define Rot2B_DM_OD_LO           (0x04u)
#define Rot2B_DM_OD_HI           (0x05u)
#define Rot2B_DM_STRONG          (0x06u)
#define Rot2B_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Rot2B_MASK               Rot2B__MASK
#define Rot2B_SHIFT              Rot2B__SHIFT
#define Rot2B_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Rot2B_PS                     (* (reg32 *) Rot2B__PS)
/* Port Configuration */
#define Rot2B_PC                     (* (reg32 *) Rot2B__PC)
/* Data Register */
#define Rot2B_DR                     (* (reg32 *) Rot2B__DR)
/* Input Buffer Disable Override */
#define Rot2B_INP_DIS                (* (reg32 *) Rot2B__PC2)


#if defined(Rot2B__INTSTAT)  /* Interrupt Registers */

    #define Rot2B_INTSTAT                (* (reg32 *) Rot2B__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Rot2B_DRIVE_MODE_SHIFT       (0x00u)
#define Rot2B_DRIVE_MODE_MASK        (0x07u << Rot2B_DRIVE_MODE_SHIFT)


#endif /* End Pins Rot2B_H */


/* [] END OF FILE */
