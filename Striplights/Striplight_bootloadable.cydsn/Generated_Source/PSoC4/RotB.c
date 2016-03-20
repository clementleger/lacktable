/*******************************************************************************
* File Name: RotB.c  
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
#include "RotB.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        RotB_PC =   (RotB_PC & \
                                (uint32)(~(uint32)(RotB_DRIVE_MODE_IND_MASK << (RotB_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (RotB_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: RotB_Write
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
void RotB_Write(uint8 value) 
{
    uint8 drVal = (uint8)(RotB_DR & (uint8)(~RotB_MASK));
    drVal = (drVal | ((uint8)(value << RotB_SHIFT) & RotB_MASK));
    RotB_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: RotB_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  RotB_DM_STRONG     Strong Drive 
*  RotB_DM_OD_HI      Open Drain, Drives High 
*  RotB_DM_OD_LO      Open Drain, Drives Low 
*  RotB_DM_RES_UP     Resistive Pull Up 
*  RotB_DM_RES_DWN    Resistive Pull Down 
*  RotB_DM_RES_UPDWN  Resistive Pull Up/Down 
*  RotB_DM_DIG_HIZ    High Impedance Digital 
*  RotB_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void RotB_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(RotB__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: RotB_Read
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
*  Macro RotB_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 RotB_Read(void) 
{
    return (uint8)((RotB_PS & RotB_MASK) >> RotB_SHIFT);
}


/*******************************************************************************
* Function Name: RotB_ReadDataReg
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
uint8 RotB_ReadDataReg(void) 
{
    return (uint8)((RotB_DR & RotB_MASK) >> RotB_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(RotB_INTSTAT) 

    /*******************************************************************************
    * Function Name: RotB_ClearInterrupt
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
    uint8 RotB_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(RotB_INTSTAT & RotB_MASK);
		RotB_INTSTAT = maskedStatus;
        return maskedStatus >> RotB_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
