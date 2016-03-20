/*******************************************************************************
* File Name: RotSW.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "RotSW.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        RotSW_PC =   (RotSW_PC & \
                                (uint32)(~(uint32)(RotSW_DRIVE_MODE_IND_MASK << (RotSW_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (RotSW_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: RotSW_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void RotSW_Write(uint8 value) 
{
    uint8 drVal = (uint8)(RotSW_DR & (uint8)(~RotSW_MASK));
    drVal = (drVal | ((uint8)(value << RotSW_SHIFT) & RotSW_MASK));
    RotSW_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: RotSW_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  RotSW_DM_STRONG     Strong Drive 
*  RotSW_DM_OD_HI      Open Drain, Drives High 
*  RotSW_DM_OD_LO      Open Drain, Drives Low 
*  RotSW_DM_RES_UP     Resistive Pull Up 
*  RotSW_DM_RES_DWN    Resistive Pull Down 
*  RotSW_DM_RES_UPDWN  Resistive Pull Up/Down 
*  RotSW_DM_DIG_HIZ    High Impedance Digital 
*  RotSW_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void RotSW_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(RotSW__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: RotSW_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro RotSW_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 RotSW_Read(void) 
{
    return (uint8)((RotSW_PS & RotSW_MASK) >> RotSW_SHIFT);
}


/*******************************************************************************
* Function Name: RotSW_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 RotSW_ReadDataReg(void) 
{
    return (uint8)((RotSW_DR & RotSW_MASK) >> RotSW_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(RotSW_INTSTAT) 

    /*******************************************************************************
    * Function Name: RotSW_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 RotSW_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(RotSW_INTSTAT & RotSW_MASK);
		RotSW_INTSTAT = maskedStatus;
        return maskedStatus >> RotSW_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
