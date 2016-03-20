/*******************************************************************************
* File Name: RotA.c  
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
#include "RotA.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        RotA_PC =   (RotA_PC & \
                                (uint32)(~(uint32)(RotA_DRIVE_MODE_IND_MASK << (RotA_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (RotA_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: RotA_Write
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
void RotA_Write(uint8 value) 
{
    uint8 drVal = (uint8)(RotA_DR & (uint8)(~RotA_MASK));
    drVal = (drVal | ((uint8)(value << RotA_SHIFT) & RotA_MASK));
    RotA_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: RotA_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  RotA_DM_STRONG     Strong Drive 
*  RotA_DM_OD_HI      Open Drain, Drives High 
*  RotA_DM_OD_LO      Open Drain, Drives Low 
*  RotA_DM_RES_UP     Resistive Pull Up 
*  RotA_DM_RES_DWN    Resistive Pull Down 
*  RotA_DM_RES_UPDWN  Resistive Pull Up/Down 
*  RotA_DM_DIG_HIZ    High Impedance Digital 
*  RotA_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void RotA_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(RotA__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: RotA_Read
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
*  Macro RotA_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 RotA_Read(void) 
{
    return (uint8)((RotA_PS & RotA_MASK) >> RotA_SHIFT);
}


/*******************************************************************************
* Function Name: RotA_ReadDataReg
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
uint8 RotA_ReadDataReg(void) 
{
    return (uint8)((RotA_DR & RotA_MASK) >> RotA_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(RotA_INTSTAT) 

    /*******************************************************************************
    * Function Name: RotA_ClearInterrupt
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
    uint8 RotA_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(RotA_INTSTAT & RotA_MASK);
		RotA_INTSTAT = maskedStatus;
        return maskedStatus >> RotA_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
