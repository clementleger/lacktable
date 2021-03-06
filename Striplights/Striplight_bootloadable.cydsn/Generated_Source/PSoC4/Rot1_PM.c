/*******************************************************************************
* File Name: Rot1_PM.c
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

#include "Rot1.h"

static Rot1_BACKUP_STRUCT Rot1_backup;


/*******************************************************************************
* Function Name: Rot1_SaveConfig
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
void Rot1_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: Rot1_Sleep
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
void Rot1_Sleep(void)
{
    if(0u != (Rot1_BLOCK_CONTROL_REG & Rot1_MASK))
    {
        Rot1_backup.enableState = 1u;
    }
    else
    {
        Rot1_backup.enableState = 0u;
    }

    Rot1_Stop();
    Rot1_SaveConfig();
}


/*******************************************************************************
* Function Name: Rot1_RestoreConfig
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
void Rot1_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: Rot1_Wakeup
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
void Rot1_Wakeup(void)
{
    Rot1_RestoreConfig();

    if(0u != Rot1_backup.enableState)
    {
        Rot1_Enable();
    }
}


/* [] END OF FILE */
