/*******************************************************************************
* File Name: Rot1B.c  
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
#include "Rot1B.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Rot1B_PC =   (Rot1B_PC & \
                                (uint32)(~(uint32)(Rot1B_DRIVE_MODE_IND_MASK << (Rot1B_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Rot1B_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Rot1B_Write
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
void Rot1B_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Rot1B_DR & (uint8)(~Rot1B_MASK));
    drVal = (drVal | ((uint8)(value << Rot1B_SHIFT) & Rot1B_MASK));
    Rot1B_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Rot1B_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Rot1B_DM_STRONG     Strong Drive 
*  Rot1B_DM_OD_HI      Open Drain, Drives High 
*  Rot1B_DM_OD_LO      Open Drain, Drives Low 
*  Rot1B_DM_RES_UP     Resistive Pull Up 
*  Rot1B_DM_RES_DWN    Resistive Pull Down 
*  Rot1B_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Rot1B_DM_DIG_HIZ    High Impedance Digital 
*  Rot1B_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Rot1B_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Rot1B__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Rot1B_Read
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
*  Macro Rot1B_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Rot1B_Read(void) 
{
    return (uint8)((Rot1B_PS & Rot1B_MASK) >> Rot1B_SHIFT);
}


/*******************************************************************************
* Function Name: Rot1B_ReadDataReg
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
uint8 Rot1B_ReadDataReg(void) 
{
    return (uint8)((Rot1B_DR & Rot1B_MASK) >> Rot1B_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Rot1B_INTSTAT) 

    /*******************************************************************************
    * Function Name: Rot1B_ClearInterrupt
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
    uint8 Rot1B_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Rot1B_INTSTAT & Rot1B_MASK);
		Rot1B_INTSTAT = maskedStatus;
        return maskedStatus >> Rot1B_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
