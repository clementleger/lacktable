/*******************************************************************************
* File Name: Rot2SW.h  
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

#if !defined(CY_PINS_Rot2SW_H) /* Pins Rot2SW_H */
#define CY_PINS_Rot2SW_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Rot2SW_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Rot2SW_Write(uint8 value) ;
void    Rot2SW_SetDriveMode(uint8 mode) ;
uint8   Rot2SW_ReadDataReg(void) ;
uint8   Rot2SW_Read(void) ;
uint8   Rot2SW_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Rot2SW_DRIVE_MODE_BITS        (3)
#define Rot2SW_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Rot2SW_DRIVE_MODE_BITS))

#define Rot2SW_DM_ALG_HIZ         (0x00u)
#define Rot2SW_DM_DIG_HIZ         (0x01u)
#define Rot2SW_DM_RES_UP          (0x02u)
#define Rot2SW_DM_RES_DWN         (0x03u)
#define Rot2SW_DM_OD_LO           (0x04u)
#define Rot2SW_DM_OD_HI           (0x05u)
#define Rot2SW_DM_STRONG          (0x06u)
#define Rot2SW_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Rot2SW_MASK               Rot2SW__MASK
#define Rot2SW_SHIFT              Rot2SW__SHIFT
#define Rot2SW_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Rot2SW_PS                     (* (reg32 *) Rot2SW__PS)
/* Port Configuration */
#define Rot2SW_PC                     (* (reg32 *) Rot2SW__PC)
/* Data Register */
#define Rot2SW_DR                     (* (reg32 *) Rot2SW__DR)
/* Input Buffer Disable Override */
#define Rot2SW_INP_DIS                (* (reg32 *) Rot2SW__PC2)


#if defined(Rot2SW__INTSTAT)  /* Interrupt Registers */

    #define Rot2SW_INTSTAT                (* (reg32 *) Rot2SW__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Rot2SW_DRIVE_MODE_SHIFT       (0x00u)
#define Rot2SW_DRIVE_MODE_MASK        (0x07u << Rot2SW_DRIVE_MODE_SHIFT)


#endif /* End Pins Rot2SW_H */


/* [] END OF FILE */
