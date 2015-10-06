/*******************************************************************************
* File Name: Strip_7.h  
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

#if !defined(CY_PINS_Strip_7_H) /* Pins Strip_7_H */
#define CY_PINS_Strip_7_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Strip_7_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Strip_7_Write(uint8 value) ;
void    Strip_7_SetDriveMode(uint8 mode) ;
uint8   Strip_7_ReadDataReg(void) ;
uint8   Strip_7_Read(void) ;
uint8   Strip_7_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Strip_7_DRIVE_MODE_BITS        (3)
#define Strip_7_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Strip_7_DRIVE_MODE_BITS))

#define Strip_7_DM_ALG_HIZ         (0x00u)
#define Strip_7_DM_DIG_HIZ         (0x01u)
#define Strip_7_DM_RES_UP          (0x02u)
#define Strip_7_DM_RES_DWN         (0x03u)
#define Strip_7_DM_OD_LO           (0x04u)
#define Strip_7_DM_OD_HI           (0x05u)
#define Strip_7_DM_STRONG          (0x06u)
#define Strip_7_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Strip_7_MASK               Strip_7__MASK
#define Strip_7_SHIFT              Strip_7__SHIFT
#define Strip_7_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Strip_7_PS                     (* (reg32 *) Strip_7__PS)
/* Port Configuration */
#define Strip_7_PC                     (* (reg32 *) Strip_7__PC)
/* Data Register */
#define Strip_7_DR                     (* (reg32 *) Strip_7__DR)
/* Input Buffer Disable Override */
#define Strip_7_INP_DIS                (* (reg32 *) Strip_7__PC2)


#if defined(Strip_7__INTSTAT)  /* Interrupt Registers */

    #define Strip_7_INTSTAT                (* (reg32 *) Strip_7__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Strip_7_DRIVE_MODE_SHIFT       (0x00u)
#define Strip_7_DRIVE_MODE_MASK        (0x07u << Strip_7_DRIVE_MODE_SHIFT)


#endif /* End Pins Strip_7_H */


/* [] END OF FILE */
