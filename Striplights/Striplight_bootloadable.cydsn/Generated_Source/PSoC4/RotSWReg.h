/*******************************************************************************
* File Name: RotSWReg.h  
* Version 1.90
*
* Description:
*  This file containts Status Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_STATUS_REG_RotSWReg_H) /* CY_STATUS_REG_RotSWReg_H */
#define CY_STATUS_REG_RotSWReg_H

#include "cytypes.h"
#include "CyLib.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 statusState;

} RotSWReg_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8 RotSWReg_Read(void) ;
void RotSWReg_InterruptEnable(void) ;
void RotSWReg_InterruptDisable(void) ;
void RotSWReg_WriteMask(uint8 mask) ;
uint8 RotSWReg_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define RotSWReg_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define RotSWReg_INPUTS              2


/***************************************
*             Registers
***************************************/

/* Status Register */
#define RotSWReg_Status             (* (reg8 *) RotSWReg_sts_sts_reg__STATUS_REG )
#define RotSWReg_Status_PTR         (  (reg8 *) RotSWReg_sts_sts_reg__STATUS_REG )
#define RotSWReg_Status_Mask        (* (reg8 *) RotSWReg_sts_sts_reg__MASK_REG )
#define RotSWReg_Status_Aux_Ctrl    (* (reg8 *) RotSWReg_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_RotSWReg_H */


/* [] END OF FILE */
