/*******************************************************************************
* File Name: Strip_6.c  
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
#include "Strip_6.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Strip_6_PC =   (Strip_6_PC & \
                                (uint32)(~(uint32)(Strip_6_DRIVE_MODE_IND_MASK << (Strip_6_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Strip_6_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Strip_6_Write
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
void Strip_6_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Strip_6_DR & (uint8)(~Strip_6_MASK));
    drVal = (drVal | ((uint8)(value << Strip_6_SHIFT) & Strip_6_MASK));
    Strip_6_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Strip_6_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Strip_6_DM_STRONG     Strong Drive 
*  Strip_6_DM_OD_HI      Open Drain, Drives High 
*  Strip_6_DM_OD_LO      Open Drain, Drives Low 
*  Strip_6_DM_RES_UP     Resistive Pull Up 
*  Strip_6_DM_RES_DWN    Resistive Pull Down 
*  Strip_6_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Strip_6_DM_DIG_HIZ    High Impedance Digital 
*  Strip_6_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Strip_6_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Strip_6__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Strip_6_Read
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
*  Macro Strip_6_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Strip_6_Read(void) 
{
    return (uint8)((Strip_6_PS & Strip_6_MASK) >> Strip_6_SHIFT);
}


/*******************************************************************************
* Function Name: Strip_6_ReadDataReg
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
uint8 Strip_6_ReadDataReg(void) 
{
    return (uint8)((Strip_6_DR & Strip_6_MASK) >> Strip_6_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Strip_6_INTSTAT) 

    /*******************************************************************************
    * Function Name: Strip_6_ClearInterrupt
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
    uint8 Strip_6_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Strip_6_INTSTAT & Strip_6_MASK);
		Strip_6_INTSTAT = maskedStatus;
        return maskedStatus >> Strip_6_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
