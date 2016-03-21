/*******************************************************************************
* File Name: Rot2A.c  
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
#include "Rot2A.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Rot2A_PC =   (Rot2A_PC & \
                                (uint32)(~(uint32)(Rot2A_DRIVE_MODE_IND_MASK << (Rot2A_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Rot2A_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Rot2A_Write
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
void Rot2A_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Rot2A_DR & (uint8)(~Rot2A_MASK));
    drVal = (drVal | ((uint8)(value << Rot2A_SHIFT) & Rot2A_MASK));
    Rot2A_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Rot2A_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Rot2A_DM_STRONG     Strong Drive 
*  Rot2A_DM_OD_HI      Open Drain, Drives High 
*  Rot2A_DM_OD_LO      Open Drain, Drives Low 
*  Rot2A_DM_RES_UP     Resistive Pull Up 
*  Rot2A_DM_RES_DWN    Resistive Pull Down 
*  Rot2A_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Rot2A_DM_DIG_HIZ    High Impedance Digital 
*  Rot2A_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Rot2A_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Rot2A__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Rot2A_Read
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
*  Macro Rot2A_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Rot2A_Read(void) 
{
    return (uint8)((Rot2A_PS & Rot2A_MASK) >> Rot2A_SHIFT);
}


/*******************************************************************************
* Function Name: Rot2A_ReadDataReg
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
uint8 Rot2A_ReadDataReg(void) 
{
    return (uint8)((Rot2A_DR & Rot2A_MASK) >> Rot2A_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Rot2A_INTSTAT) 

    /*******************************************************************************
    * Function Name: Rot2A_ClearInterrupt
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
    uint8 Rot2A_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Rot2A_INTSTAT & Rot2A_MASK);
		Rot2A_INTSTAT = maskedStatus;
        return maskedStatus >> Rot2A_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
