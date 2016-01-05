/*******************************************************************************
* File Name: PC_Uart_BOOT.c
* Version 3.0
*
* Description:
*  This file provides the source code of the bootloader communication APIs
*  for the SCB Component Unconfigured mode.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PC_Uart_BOOT.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (PC_Uart_BTLDR_COMM_ENABLED) && \
                                (PC_Uart_SCB_MODE_UNCONFIG_CONST_CFG)

/*******************************************************************************
* Function Name: PC_Uart_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStart function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PC_Uart_CyBtldrCommStart(void)
{
    if (PC_Uart_SCB_MODE_I2C_RUNTM_CFG)
    {
        PC_Uart_I2CCyBtldrCommStart();
    }
    else if (PC_Uart_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        PC_Uart_EzI2CCyBtldrCommStart();
    }
#if (!PC_Uart_CY_SCBIP_V1)
    else if (PC_Uart_SCB_MODE_SPI_RUNTM_CFG)
    {
        PC_Uart_SpiCyBtldrCommStart();
    }
    else if (PC_Uart_SCB_MODE_UART_RUNTM_CFG)
    {
        PC_Uart_UartCyBtldrCommStart();
    }
#endif /* (!PC_Uart_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: PC_Uart_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStop function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PC_Uart_CyBtldrCommStop(void)
{
    if (PC_Uart_SCB_MODE_I2C_RUNTM_CFG)
    {
        PC_Uart_I2CCyBtldrCommStop();
    }
    else if (PC_Uart_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        PC_Uart_EzI2CCyBtldrCommStop();
    }
#if (!PC_Uart_CY_SCBIP_V1)
    else if (PC_Uart_SCB_MODE_SPI_RUNTM_CFG)
    {
        PC_Uart_SpiCyBtldrCommStop();
    }
    else if (PC_Uart_SCB_MODE_UART_RUNTM_CFG)
    {
        PC_Uart_UartCyBtldrCommStop();
    }
#endif /* (!PC_Uart_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: PC_Uart_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommReset function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PC_Uart_CyBtldrCommReset(void)
{
    if(PC_Uart_SCB_MODE_I2C_RUNTM_CFG)
    {
        PC_Uart_I2CCyBtldrCommReset();
    }
    else if(PC_Uart_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        PC_Uart_EzI2CCyBtldrCommReset();
    }
#if (!PC_Uart_CY_SCBIP_V1)
    else if(PC_Uart_SCB_MODE_SPI_RUNTM_CFG)
    {
        PC_Uart_SpiCyBtldrCommReset();
    }
    else if(PC_Uart_SCB_MODE_UART_RUNTM_CFG)
    {
        PC_Uart_UartCyBtldrCommReset();
    }
#endif /* (!PC_Uart_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: PC_Uart_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommRead function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to storage for the block of data to be read from the
*            bootloader host
*  size:     Number of bytes to be read.
*  count:    Pointer to the variable to write the number of bytes actually
*            read.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus PC_Uart_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(PC_Uart_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = PC_Uart_I2CCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(PC_Uart_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = PC_Uart_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
    }
#if (!PC_Uart_CY_SCBIP_V1)
    else if(PC_Uart_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = PC_Uart_SpiCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(PC_Uart_SCB_MODE_UART_RUNTM_CFG)
    {
        status = PC_Uart_UartCyBtldrCommRead(pData, size, count, timeOut);
    }
#endif /* (!PC_Uart_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}


/*******************************************************************************
* Function Name: PC_Uart_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommWrite  function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus PC_Uart_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(PC_Uart_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = PC_Uart_I2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(PC_Uart_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = PC_Uart_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
#if (!PC_Uart_CY_SCBIP_V1)
    else if(PC_Uart_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = PC_Uart_SpiCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(PC_Uart_SCB_MODE_UART_RUNTM_CFG)
    {
        status = PC_Uart_UartCyBtldrCommWrite(pData, size, count, timeOut);
    }
#endif /* (!PC_Uart_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (PC_Uart_BTLDR_COMM_MODE_ENABLED) */


/* [] END OF FILE */
