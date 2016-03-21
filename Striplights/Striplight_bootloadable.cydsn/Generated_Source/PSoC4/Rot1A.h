/*******************************************************************************
* File Name: Rot1A.h  
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

#if !defined(CY_PINS_Rot1A_H) /* Pins Rot1A_H */
#define CY_PINS_Rot1A_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Rot1A_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Rot1A_Write(uint8 value) ;
void    Rot1A_SetDriveMode(uint8 mode) ;
uint8   Rot1A_ReadDataReg(void) ;
uint8   Rot1A_Read(void) ;
uint8   Rot1A_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Rot1A_DRIVE_MODE_BITS        (3)
#define Rot1A_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Rot1A_DRIVE_MODE_BITS))

#define Rot1A_DM_ALG_HIZ         (0x00u)
#define Rot1A_DM_DIG_HIZ         (0x01u)
#define Rot1A_DM_RES_UP          (0x02u)
#define Rot1A_DM_RES_DWN         (0x03u)
#define Rot1A_DM_OD_LO           (0x04u)
#define Rot1A_DM_OD_HI           (0x05u)
#define Rot1A_DM_STRONG          (0x06u)
#define Rot1A_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Rot1A_MASK               Rot1A__MASK
#define Rot1A_SHIFT              Rot1A__SHIFT
#define Rot1A_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Rot1A_PS                     (* (reg32 *) Rot1A__PS)
/* Port Configuration */
#define Rot1A_PC                     (* (reg32 *) Rot1A__PC)
/* Data Register */
#define Rot1A_DR                     (* (reg32 *) Rot1A__DR)
/* Input Buffer Disable Override */
#define Rot1A_INP_DIS                (* (reg32 *) Rot1A__PC2)


#if defined(Rot1A__INTSTAT)  /* Interrupt Registers */

    #define Rot1A_INTSTAT                (* (reg32 *) Rot1A__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Rot1A_DRIVE_MODE_SHIFT       (0x00u)
#define Rot1A_DRIVE_MODE_MASK        (0x07u << Rot1A_DRIVE_MODE_SHIFT)


#endif /* End Pins Rot1A_H */


/* [] END OF FILE */
