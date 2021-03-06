/*******************************************************************************
* File Name: Strip_5.h  
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

#if !defined(CY_PINS_Strip_5_H) /* Pins Strip_5_H */
#define CY_PINS_Strip_5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Strip_5_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Strip_5_Write(uint8 value) ;
void    Strip_5_SetDriveMode(uint8 mode) ;
uint8   Strip_5_ReadDataReg(void) ;
uint8   Strip_5_Read(void) ;
uint8   Strip_5_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Strip_5_DRIVE_MODE_BITS        (3)
#define Strip_5_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Strip_5_DRIVE_MODE_BITS))

#define Strip_5_DM_ALG_HIZ         (0x00u)
#define Strip_5_DM_DIG_HIZ         (0x01u)
#define Strip_5_DM_RES_UP          (0x02u)
#define Strip_5_DM_RES_DWN         (0x03u)
#define Strip_5_DM_OD_LO           (0x04u)
#define Strip_5_DM_OD_HI           (0x05u)
#define Strip_5_DM_STRONG          (0x06u)
#define Strip_5_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Strip_5_MASK               Strip_5__MASK
#define Strip_5_SHIFT              Strip_5__SHIFT
#define Strip_5_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Strip_5_PS                     (* (reg32 *) Strip_5__PS)
/* Port Configuration */
#define Strip_5_PC                     (* (reg32 *) Strip_5__PC)
/* Data Register */
#define Strip_5_DR                     (* (reg32 *) Strip_5__DR)
/* Input Buffer Disable Override */
#define Strip_5_INP_DIS                (* (reg32 *) Strip_5__PC2)


#if defined(Strip_5__INTSTAT)  /* Interrupt Registers */

    #define Strip_5_INTSTAT                (* (reg32 *) Strip_5__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Strip_5_DRIVE_MODE_SHIFT       (0x00u)
#define Strip_5_DRIVE_MODE_MASK        (0x07u << Strip_5_DRIVE_MODE_SHIFT)


#endif /* End Pins Strip_5_H */


/* [] END OF FILE */
