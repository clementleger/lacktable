/*******************************************************************************
* File Name: RotaryEncoderA.c  
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
#include "RotaryEncoderA.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        RotaryEncoderA_PC =   (RotaryEncoderA_PC & \
                                (uint32)(~(uint32)(RotaryEncoderA_DRIVE_MODE_IND_MASK << (RotaryEncoderA_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (RotaryEncoderA_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: RotaryEncoderA_Write
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
void RotaryEncoderA_Write(uint8 value) 
{
    uint8 drVal = (uint8)(RotaryEncoderA_DR & (uint8)(~RotaryEncoderA_MASK));
    drVal = (drVal | ((uint8)(value << RotaryEncoderA_SHIFT) & RotaryEncoderA_MASK));
    RotaryEncoderA_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: RotaryEncoderA_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  RotaryEncoderA_DM_STRONG     Strong Drive 
*  RotaryEncoderA_DM_OD_HI      Open Drain, Drives High 
*  RotaryEncoderA_DM_OD_LO      Open Drain, Drives Low 
*  RotaryEncoderA_DM_RES_UP     Resistive Pull Up 
*  RotaryEncoderA_DM_RES_DWN    Resistive Pull Down 
*  RotaryEncoderA_DM_RES_UPDWN  Resistive Pull Up/Down 
*  RotaryEncoderA_DM_DIG_HIZ    High Impedance Digital 
*  RotaryEncoderA_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void RotaryEncoderA_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(RotaryEncoderA__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: RotaryEncoderA_Read
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
*  Macro RotaryEncoderA_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 RotaryEncoderA_Read(void) 
{
    return (uint8)((RotaryEncoderA_PS & RotaryEncoderA_MASK) >> RotaryEncoderA_SHIFT);
}


/*******************************************************************************
* Function Name: RotaryEncoderA_ReadDataReg
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
uint8 RotaryEncoderA_ReadDataReg(void) 
{
    return (uint8)((RotaryEncoderA_DR & RotaryEncoderA_MASK) >> RotaryEncoderA_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(RotaryEncoderA_INTSTAT) 

    /*******************************************************************************
    * Function Name: RotaryEncoderA_ClearInterrupt
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
    uint8 RotaryEncoderA_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(RotaryEncoderA_INTSTAT & RotaryEncoderA_MASK);
		RotaryEncoderA_INTSTAT = maskedStatus;
        return maskedStatus >> RotaryEncoderA_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
