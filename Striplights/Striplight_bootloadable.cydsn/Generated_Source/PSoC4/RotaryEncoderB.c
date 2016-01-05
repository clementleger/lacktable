/*******************************************************************************
* File Name: RotaryEncoderB.c  
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
#include "RotaryEncoderB.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        RotaryEncoderB_PC =   (RotaryEncoderB_PC & \
                                (uint32)(~(uint32)(RotaryEncoderB_DRIVE_MODE_IND_MASK << (RotaryEncoderB_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (RotaryEncoderB_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: RotaryEncoderB_Write
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
void RotaryEncoderB_Write(uint8 value) 
{
    uint8 drVal = (uint8)(RotaryEncoderB_DR & (uint8)(~RotaryEncoderB_MASK));
    drVal = (drVal | ((uint8)(value << RotaryEncoderB_SHIFT) & RotaryEncoderB_MASK));
    RotaryEncoderB_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: RotaryEncoderB_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  RotaryEncoderB_DM_STRONG     Strong Drive 
*  RotaryEncoderB_DM_OD_HI      Open Drain, Drives High 
*  RotaryEncoderB_DM_OD_LO      Open Drain, Drives Low 
*  RotaryEncoderB_DM_RES_UP     Resistive Pull Up 
*  RotaryEncoderB_DM_RES_DWN    Resistive Pull Down 
*  RotaryEncoderB_DM_RES_UPDWN  Resistive Pull Up/Down 
*  RotaryEncoderB_DM_DIG_HIZ    High Impedance Digital 
*  RotaryEncoderB_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void RotaryEncoderB_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(RotaryEncoderB__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: RotaryEncoderB_Read
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
*  Macro RotaryEncoderB_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 RotaryEncoderB_Read(void) 
{
    return (uint8)((RotaryEncoderB_PS & RotaryEncoderB_MASK) >> RotaryEncoderB_SHIFT);
}


/*******************************************************************************
* Function Name: RotaryEncoderB_ReadDataReg
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
uint8 RotaryEncoderB_ReadDataReg(void) 
{
    return (uint8)((RotaryEncoderB_DR & RotaryEncoderB_MASK) >> RotaryEncoderB_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(RotaryEncoderB_INTSTAT) 

    /*******************************************************************************
    * Function Name: RotaryEncoderB_ClearInterrupt
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
    uint8 RotaryEncoderB_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(RotaryEncoderB_INTSTAT & RotaryEncoderB_MASK);
		RotaryEncoderB_INTSTAT = maskedStatus;
        return maskedStatus >> RotaryEncoderB_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
