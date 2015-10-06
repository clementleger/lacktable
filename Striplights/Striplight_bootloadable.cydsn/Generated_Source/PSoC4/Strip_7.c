/*******************************************************************************
* File Name: Strip_7.c  
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
#include "Strip_7.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Strip_7_PC =   (Strip_7_PC & \
                                (uint32)(~(uint32)(Strip_7_DRIVE_MODE_IND_MASK << (Strip_7_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Strip_7_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Strip_7_Write
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
void Strip_7_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Strip_7_DR & (uint8)(~Strip_7_MASK));
    drVal = (drVal | ((uint8)(value << Strip_7_SHIFT) & Strip_7_MASK));
    Strip_7_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Strip_7_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Strip_7_DM_STRONG     Strong Drive 
*  Strip_7_DM_OD_HI      Open Drain, Drives High 
*  Strip_7_DM_OD_LO      Open Drain, Drives Low 
*  Strip_7_DM_RES_UP     Resistive Pull Up 
*  Strip_7_DM_RES_DWN    Resistive Pull Down 
*  Strip_7_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Strip_7_DM_DIG_HIZ    High Impedance Digital 
*  Strip_7_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Strip_7_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Strip_7__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Strip_7_Read
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
*  Macro Strip_7_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Strip_7_Read(void) 
{
    return (uint8)((Strip_7_PS & Strip_7_MASK) >> Strip_7_SHIFT);
}


/*******************************************************************************
* Function Name: Strip_7_ReadDataReg
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
uint8 Strip_7_ReadDataReg(void) 
{
    return (uint8)((Strip_7_DR & Strip_7_MASK) >> Strip_7_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Strip_7_INTSTAT) 

    /*******************************************************************************
    * Function Name: Strip_7_ClearInterrupt
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
    uint8 Strip_7_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Strip_7_INTSTAT & Strip_7_MASK);
		Strip_7_INTSTAT = maskedStatus;
        return maskedStatus >> Strip_7_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
