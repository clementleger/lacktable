/*******************************************************************************
* File Name: Rot2A.h  
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

#if !defined(CY_PINS_Rot2A_H) /* Pins Rot2A_H */
#define CY_PINS_Rot2A_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Rot2A_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Rot2A_Write(uint8 value) ;
void    Rot2A_SetDriveMode(uint8 mode) ;
uint8   Rot2A_ReadDataReg(void) ;
uint8   Rot2A_Read(void) ;
uint8   Rot2A_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Rot2A_DRIVE_MODE_BITS        (3)
#define Rot2A_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Rot2A_DRIVE_MODE_BITS))

#define Rot2A_DM_ALG_HIZ         (0x00u)
#define Rot2A_DM_DIG_HIZ         (0x01u)
#define Rot2A_DM_RES_UP          (0x02u)
#define Rot2A_DM_RES_DWN         (0x03u)
#define Rot2A_DM_OD_LO           (0x04u)
#define Rot2A_DM_OD_HI           (0x05u)
#define Rot2A_DM_STRONG          (0x06u)
#define Rot2A_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Rot2A_MASK               Rot2A__MASK
#define Rot2A_SHIFT              Rot2A__SHIFT
#define Rot2A_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Rot2A_PS                     (* (reg32 *) Rot2A__PS)
/* Port Configuration */
#define Rot2A_PC                     (* (reg32 *) Rot2A__PC)
/* Data Register */
#define Rot2A_DR                     (* (reg32 *) Rot2A__DR)
/* Input Buffer Disable Override */
#define Rot2A_INP_DIS                (* (reg32 *) Rot2A__PC2)


#if defined(Rot2A__INTSTAT)  /* Interrupt Registers */

    #define Rot2A_INTSTAT                (* (reg32 *) Rot2A__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Rot2A_DRIVE_MODE_SHIFT       (0x00u)
#define Rot2A_DRIVE_MODE_MASK        (0x07u << Rot2A_DRIVE_MODE_SHIFT)


#endif /* End Pins Rot2A_H */


/* [] END OF FILE */
