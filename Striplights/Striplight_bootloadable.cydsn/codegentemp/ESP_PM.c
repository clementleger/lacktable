/*******************************************************************************
* File Name: ESP_PM.c
* Version 3.0
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ESP.h"
#include "ESP_PVT.h"

#if(ESP_SCB_MODE_I2C_INC)
    #include "ESP_I2C_PVT.h"
#endif /* (ESP_SCB_MODE_I2C_INC) */

#if(ESP_SCB_MODE_EZI2C_INC)
    #include "ESP_EZI2C_PVT.h"
#endif /* (ESP_SCB_MODE_EZI2C_INC) */

#if(ESP_SCB_MODE_SPI_INC || ESP_SCB_MODE_UART_INC)
    #include "ESP_SPI_UART_PVT.h"
#endif /* (ESP_SCB_MODE_SPI_INC || ESP_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(ESP_SCB_MODE_UNCONFIG_CONST_CFG || \
   (ESP_SCB_MODE_I2C_CONST_CFG   && (!ESP_I2C_WAKE_ENABLE_CONST))   || \
   (ESP_SCB_MODE_EZI2C_CONST_CFG && (!ESP_EZI2C_WAKE_ENABLE_CONST)) || \
   (ESP_SCB_MODE_SPI_CONST_CFG   && (!ESP_SPI_WAKE_ENABLE_CONST))   || \
   (ESP_SCB_MODE_UART_CONST_CFG  && (!ESP_UART_WAKE_ENABLE_CONST)))

    ESP_BACKUP_STRUCT ESP_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: ESP_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component to enter Deep Sleep.
*  The "Enable wakeup from Sleep Mode" selection has an influence on
*  this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ESP_Sleep(void)
{
#if(ESP_SCB_MODE_UNCONFIG_CONST_CFG)

    if(ESP_SCB_WAKE_ENABLE_CHECK)
    {
        if(ESP_SCB_MODE_I2C_RUNTM_CFG)
        {
            ESP_I2CSaveConfig();
        }
        else if(ESP_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            ESP_EzI2CSaveConfig();
        }
    #if(!ESP_CY_SCBIP_V1)
        else if(ESP_SCB_MODE_SPI_RUNTM_CFG)
        {
            ESP_SpiSaveConfig();
        }
        else if(ESP_SCB_MODE_UART_RUNTM_CFG)
        {
            ESP_UartSaveConfig();
        }
    #endif /* (!ESP_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        ESP_backup.enableState = (uint8) ESP_GET_CTRL_ENABLED;

        if(0u != ESP_backup.enableState)
        {
            ESP_Stop();
        }
    }

#else

    #if (ESP_SCB_MODE_I2C_CONST_CFG && ESP_I2C_WAKE_ENABLE_CONST)
        ESP_I2CSaveConfig();

    #elif (ESP_SCB_MODE_EZI2C_CONST_CFG && ESP_EZI2C_WAKE_ENABLE_CONST)
        ESP_EzI2CSaveConfig();

    #elif (ESP_SCB_MODE_SPI_CONST_CFG && ESP_SPI_WAKE_ENABLE_CONST)
        ESP_SpiSaveConfig();

    #elif (ESP_SCB_MODE_UART_CONST_CFG && ESP_UART_WAKE_ENABLE_CONST)
        ESP_UartSaveConfig();

    #else

        ESP_backup.enableState = (uint8) ESP_GET_CTRL_ENABLED;

        if(0u != ESP_backup.enableState)
        {
            ESP_Stop();
        }

    #endif /* defined (ESP_SCB_MODE_I2C_CONST_CFG) && (ESP_I2C_WAKE_ENABLE_CONST) */

#endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ESP_Wakeup
********************************************************************************
*
* Summary:
*  Prepares the component for the Active mode operation after exiting
*  Deep Sleep. The "Enable wakeup from Sleep Mode" option has an influence
*  on this function implementation.
*  This function should not be called after exiting Sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ESP_Wakeup(void)
{
#if(ESP_SCB_MODE_UNCONFIG_CONST_CFG)

    if(ESP_SCB_WAKE_ENABLE_CHECK)
    {
        if(ESP_SCB_MODE_I2C_RUNTM_CFG)
        {
            ESP_I2CRestoreConfig();
        }
        else if(ESP_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            ESP_EzI2CRestoreConfig();
        }
    #if(!ESP_CY_SCBIP_V1)
        else if(ESP_SCB_MODE_SPI_RUNTM_CFG)
        {
            ESP_SpiRestoreConfig();
        }
        else if(ESP_SCB_MODE_UART_RUNTM_CFG)
        {
            ESP_UartRestoreConfig();
        }
    #endif /* (!ESP_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != ESP_backup.enableState)
        {
            ESP_Enable();
        }
    }

#else

    #if (ESP_SCB_MODE_I2C_CONST_CFG  && ESP_I2C_WAKE_ENABLE_CONST)
        ESP_I2CRestoreConfig();

    #elif (ESP_SCB_MODE_EZI2C_CONST_CFG && ESP_EZI2C_WAKE_ENABLE_CONST)
        ESP_EzI2CRestoreConfig();

    #elif (ESP_SCB_MODE_SPI_CONST_CFG && ESP_SPI_WAKE_ENABLE_CONST)
        ESP_SpiRestoreConfig();

    #elif (ESP_SCB_MODE_UART_CONST_CFG && ESP_UART_WAKE_ENABLE_CONST)
        ESP_UartRestoreConfig();

    #else

        if(0u != ESP_backup.enableState)
        {
            ESP_Enable();
        }

    #endif /* (ESP_I2C_WAKE_ENABLE_CONST) */

#endif /* (ESP_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
