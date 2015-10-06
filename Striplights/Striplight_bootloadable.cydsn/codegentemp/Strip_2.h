/*******************************************************************************
* File Name: Strip_2.h  
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

#if !defined(CY_PINS_Strip_2_H) /* Pins Strip_2_H */
#define CY_PINS_Strip_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Strip_2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Strip_2_Write(uint8 value) ;
void    Strip_2_SetDriveMode(uint8 mode) ;
uint8   Strip_2_ReadDataReg(void) ;
uint8   Strip_2_Read(void) ;
uint8   Strip_2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Strip_2_DRIVE_MODE_BITS        (3)
#define Strip_2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Strip_2_DRIVE_MODE_BITS))

#define Strip_2_DM_ALG_HIZ         (0x00u)
#define Strip_2_DM_DIG_HIZ         (0x01u)
#define Strip_2_DM_RES_UP          (0x02u)
#define Strip_2_DM_RES_DWN         (0x03u)
#define Strip_2_DM_OD_LO           (0x04u)
#define Strip_2_DM_OD_HI           (0x05u)
#define Strip_2_DM_STRONG          (0x06u)
#define Strip_2_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Strip_2_MASK               Strip_2__MASK
#define Strip_2_SHIFT              Strip_2__SHIFT
#define Strip_2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Strip_2_PS                     (* (reg32 *) Strip_2__PS)
/* Port Configuration */
#define Strip_2_PC                     (* (reg32 *) Strip_2__PC)
/* Data Register */
#define Strip_2_DR                     (* (reg32 *) Strip_2__DR)
/* Input Buffer Disable Override */
#define Strip_2_INP_DIS                (* (reg32 *) Strip_2__PC2)


#if defined(Strip_2__INTSTAT)  /* Interrupt Registers */

    #define Strip_2_INTSTAT                (* (reg32 *) Strip_2__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Strip_2_DRIVE_MODE_SHIFT       (0x00u)
#define Strip_2_DRIVE_MODE_MASK        (0x07u << Strip_2_DRIVE_MODE_SHIFT)


#endif /* End Pins Strip_2_H */


/* [] END OF FILE */
