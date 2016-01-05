/*******************************************************************************
* File Name: RotaryEncoder_PM.c
* Version 2.0
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "RotaryEncoder.h"

static RotaryEncoder_BACKUP_STRUCT RotaryEncoder_backup;


/*******************************************************************************
* Function Name: RotaryEncoder_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: RotaryEncoder_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_Sleep(void)
{
    if(0u != (RotaryEncoder_BLOCK_CONTROL_REG & RotaryEncoder_MASK))
    {
        RotaryEncoder_backup.enableState = 1u;
    }
    else
    {
        RotaryEncoder_backup.enableState = 0u;
    }

    RotaryEncoder_Stop();
    RotaryEncoder_SaveConfig();
}


/*******************************************************************************
* Function Name: RotaryEncoder_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: RotaryEncoder_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RotaryEncoder_Wakeup(void)
{
    RotaryEncoder_RestoreConfig();

    if(0u != RotaryEncoder_backup.enableState)
    {
        RotaryEncoder_Enable();
    }
}


/* [] END OF FILE */
