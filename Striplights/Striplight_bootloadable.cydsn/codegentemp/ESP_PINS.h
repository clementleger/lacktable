/*******************************************************************************
* File Name: ESP_PINS.h
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_ESP_H)
#define CY_SCB_PINS_ESP_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define ESP_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define ESP_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define ESP_REMOVE_TX_SDA_MISO_PIN      (1u)
#define ESP_REMOVE_SCLK_PIN      (1u)
#define ESP_REMOVE_SS0_PIN      (1u)
#define ESP_REMOVE_SS1_PIN                 (1u)
#define ESP_REMOVE_SS2_PIN                 (1u)
#define ESP_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define ESP_REMOVE_I2C_PINS                (1u)
#define ESP_REMOVE_SPI_MASTER_PINS         (1u)
#define ESP_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define ESP_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define ESP_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define ESP_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define ESP_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define ESP_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define ESP_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define ESP_REMOVE_SPI_SLAVE_PINS          (1u)
#define ESP_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define ESP_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define ESP_REMOVE_UART_TX_PIN             (0u)
#define ESP_REMOVE_UART_RX_TX_PIN          (1u)
#define ESP_REMOVE_UART_RX_PIN             (0u)
#define ESP_REMOVE_UART_RX_WAKE_PIN        (1u)
#define ESP_REMOVE_UART_RTS_PIN            (1u)
#define ESP_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define ESP_RX_WAKE_SCL_MOSI_PIN (0u == ESP_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define ESP_RX_SCL_MOSI_PIN     (0u == ESP_REMOVE_RX_SCL_MOSI_PIN)
#define ESP_TX_SDA_MISO_PIN     (0u == ESP_REMOVE_TX_SDA_MISO_PIN)
#define ESP_SCLK_PIN     (0u == ESP_REMOVE_SCLK_PIN)
#define ESP_SS0_PIN     (0u == ESP_REMOVE_SS0_PIN)
#define ESP_SS1_PIN                (0u == ESP_REMOVE_SS1_PIN)
#define ESP_SS2_PIN                (0u == ESP_REMOVE_SS2_PIN)
#define ESP_SS3_PIN                (0u == ESP_REMOVE_SS3_PIN)

/* Mode defined pins */
#define ESP_I2C_PINS               (0u == ESP_REMOVE_I2C_PINS)
#define ESP_SPI_MASTER_PINS        (0u == ESP_REMOVE_SPI_MASTER_PINS)
#define ESP_SPI_MASTER_SCLK_PIN    (0u == ESP_REMOVE_SPI_MASTER_SCLK_PIN)
#define ESP_SPI_MASTER_MOSI_PIN    (0u == ESP_REMOVE_SPI_MASTER_MOSI_PIN)
#define ESP_SPI_MASTER_MISO_PIN    (0u == ESP_REMOVE_SPI_MASTER_MISO_PIN)
#define ESP_SPI_MASTER_SS0_PIN     (0u == ESP_REMOVE_SPI_MASTER_SS0_PIN)
#define ESP_SPI_MASTER_SS1_PIN     (0u == ESP_REMOVE_SPI_MASTER_SS1_PIN)
#define ESP_SPI_MASTER_SS2_PIN     (0u == ESP_REMOVE_SPI_MASTER_SS2_PIN)
#define ESP_SPI_MASTER_SS3_PIN     (0u == ESP_REMOVE_SPI_MASTER_SS3_PIN)
#define ESP_SPI_SLAVE_PINS         (0u == ESP_REMOVE_SPI_SLAVE_PINS)
#define ESP_SPI_SLAVE_MOSI_PIN     (0u == ESP_REMOVE_SPI_SLAVE_MOSI_PIN)
#define ESP_SPI_SLAVE_MISO_PIN     (0u == ESP_REMOVE_SPI_SLAVE_MISO_PIN)
#define ESP_UART_TX_PIN            (0u == ESP_REMOVE_UART_TX_PIN)
#define ESP_UART_RX_TX_PIN         (0u == ESP_REMOVE_UART_RX_TX_PIN)
#define ESP_UART_RX_PIN            (0u == ESP_REMOVE_UART_RX_PIN)
#define ESP_UART_RX_WAKE_PIN       (0u == ESP_REMOVE_UART_RX_WAKE_PIN)
#define ESP_UART_RTS_PIN           (0u == ESP_REMOVE_UART_RTS_PIN)
#define ESP_UART_CTS_PIN           (0u == ESP_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (ESP_RX_WAKE_SCL_MOSI_PIN)
    #include "ESP_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (ESP_RX_SCL_MOSI) */

#if (ESP_RX_SCL_MOSI_PIN)
    #include "ESP_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (ESP_RX_SCL_MOSI) */

#if (ESP_TX_SDA_MISO_PIN)
    #include "ESP_uart_tx_i2c_sda_spi_miso.h"
#endif /* (ESP_TX_SDA_MISO) */

#if (ESP_SCLK_PIN)
    #include "ESP_spi_sclk.h"
#endif /* (ESP_SCLK) */

#if (ESP_SS0_PIN)
    #include "ESP_spi_ss0.h"
#endif /* (ESP_SS0_PIN) */

#if (ESP_SS1_PIN)
    #include "ESP_spi_ss1.h"
#endif /* (ESP_SS1_PIN) */

#if (ESP_SS2_PIN)
    #include "ESP_spi_ss2.h"
#endif /* (ESP_SS2_PIN) */

#if (ESP_SS3_PIN)
    #include "ESP_spi_ss3.h"
#endif /* (ESP_SS3_PIN) */

#if (ESP_I2C_PINS)
    #include "ESP_scl.h"
    #include "ESP_sda.h"
#endif /* (ESP_I2C_PINS) */

#if (ESP_SPI_MASTER_PINS)
#if (ESP_SPI_MASTER_SCLK_PIN)
    #include "ESP_sclk_m.h"
#endif /* (ESP_SPI_MASTER_SCLK_PIN) */

#if (ESP_SPI_MASTER_MOSI_PIN)
    #include "ESP_mosi_m.h"
#endif /* (ESP_SPI_MASTER_MOSI_PIN) */

#if (ESP_SPI_MASTER_MISO_PIN)
    #include "ESP_miso_m.h"
#endif /*(ESP_SPI_MASTER_MISO_PIN) */
#endif /* (ESP_SPI_MASTER_PINS) */

#if (ESP_SPI_SLAVE_PINS)
    #include "ESP_sclk_s.h"
    #include "ESP_ss_s.h"

#if (ESP_SPI_SLAVE_MOSI_PIN)
    #include "ESP_mosi_s.h"
#endif /* (ESP_SPI_SLAVE_MOSI_PIN) */

#if (ESP_SPI_SLAVE_MISO_PIN)
    #include "ESP_miso_s.h"
#endif /*(ESP_SPI_SLAVE_MISO_PIN) */
#endif /* (ESP_SPI_SLAVE_PINS) */

#if (ESP_SPI_MASTER_SS0_PIN)
    #include "ESP_ss0_m.h"
#endif /* (ESP_SPI_MASTER_SS0_PIN) */

#if (ESP_SPI_MASTER_SS1_PIN)
    #include "ESP_ss1_m.h"
#endif /* (ESP_SPI_MASTER_SS1_PIN) */

#if (ESP_SPI_MASTER_SS2_PIN)
    #include "ESP_ss2_m.h"
#endif /* (ESP_SPI_MASTER_SS2_PIN) */

#if (ESP_SPI_MASTER_SS3_PIN)
    #include "ESP_ss3_m.h"
#endif /* (ESP_SPI_MASTER_SS3_PIN) */

#if (ESP_UART_TX_PIN)
    #include "ESP_tx.h"
#endif /* (ESP_UART_TX_PIN) */

#if (ESP_UART_RX_TX_PIN)
    #include "ESP_rx_tx.h"
#endif /* (ESP_UART_RX_TX_PIN) */

#if (ESP_UART_RX_PIN)
    #include "ESP_rx.h"
#endif /* (ESP_UART_RX_PIN) */

#if (ESP_UART_RX_WAKE_PIN)
    #include "ESP_rx_wake.h"
#endif /* (ESP_UART_RX_WAKE_PIN) */

#if (ESP_UART_RTS_PIN)
    #include "ESP_rts.h"
#endif /* (ESP_UART_RTS_PIN) */

#if (ESP_UART_CTS_PIN)
    #include "ESP_cts.h"
#endif /* (ESP_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (ESP_RX_WAKE_SCL_MOSI_PIN)
    #define ESP_RX_WAKE_SCL_MOSI_HSIOM_REG \
                            (*(reg32 *) ESP_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define ESP_RX_WAKE_SCL_MOSI_HSIOM_PTR \
                            ( (reg32 *) ESP_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define ESP_RX_WAKE_SCL_MOSI_HSIOM_MASK \
                            (ESP_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define ESP_RX_WAKE_SCL_MOSI_HSIOM_POS \
                            (ESP_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)

    #define ESP_RX_WAKE_SCL_MOSI_INTCFG_REG \
                            (*(reg32 *) ESP_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define ESP_RX_WAKE_SCL_MOSI_INTCFG_PTR \
                            ( (reg32 *) ESP_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define ESP_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (ESP_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define ESP_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK \
                            ((uint32) ESP_INTCFG_TYPE_MASK << \
                                      ESP_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#endif /* (ESP_RX_WAKE_SCL_MOSI_PIN) */

#if (ESP_RX_SCL_MOSI_PIN)
    #define ESP_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) ESP_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define ESP_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) ESP_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define ESP_RX_SCL_MOSI_HSIOM_MASK  (ESP_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define ESP_RX_SCL_MOSI_HSIOM_POS   (ESP_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
#endif /* (ESP_RX_SCL_MOSI_PIN) */

#if (ESP_TX_SDA_MISO_PIN)
    #define ESP_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) ESP_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define ESP_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) ESP_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define ESP_TX_SDA_MISO_HSIOM_MASK  (ESP_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define ESP_TX_SDA_MISO_HSIOM_POS   (ESP_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
#endif /* (ESP_TX_SDA_MISO_PIN) */

#if (ESP_SCLK_PIN)
    #define ESP_SCLK_HSIOM_REG   (*(reg32 *) ESP_spi_sclk__0__HSIOM)
    #define ESP_SCLK_HSIOM_PTR   ( (reg32 *) ESP_spi_sclk__0__HSIOM)
    #define ESP_SCLK_HSIOM_MASK  (ESP_spi_sclk__0__HSIOM_MASK)
    #define ESP_SCLK_HSIOM_POS   (ESP_spi_sclk__0__HSIOM_SHIFT)
#endif /* (ESP_SCLK_PIN) */

#if (ESP_SS0_PIN)
    #define ESP_SS0_HSIOM_REG   (*(reg32 *) ESP_spi_ss0__0__HSIOM)
    #define ESP_SS0_HSIOM_PTR   ( (reg32 *) ESP_spi_ss0__0__HSIOM)
    #define ESP_SS0_HSIOM_MASK  (ESP_spi_ss0__0__HSIOM_MASK)
    #define ESP_SS0_HSIOM_POS   (ESP_spi_ss0__0__HSIOM_SHIFT)
#endif /* (ESP_SS0_PIN) */

#if (ESP_SS1_PIN)
    #define ESP_SS1_HSIOM_REG      (*(reg32 *) ESP_spi_ss1__0__HSIOM)
    #define ESP_SS1_HSIOM_PTR      ( (reg32 *) ESP_spi_ss1__0__HSIOM)
    #define ESP_SS1_HSIOM_MASK     (ESP_spi_ss1__0__HSIOM_MASK)
    #define ESP_SS1_HSIOM_POS      (ESP_spi_ss1__0__HSIOM_SHIFT)
#endif /* (ESP_SS1_PIN) */

#if (ESP_SS2_PIN)
    #define ESP_SS2_HSIOM_REG     (*(reg32 *) ESP_spi_ss2__0__HSIOM)
    #define ESP_SS2_HSIOM_PTR     ( (reg32 *) ESP_spi_ss2__0__HSIOM)
    #define ESP_SS2_HSIOM_MASK    (ESP_spi_ss2__0__HSIOM_MASK)
    #define ESP_SS2_HSIOM_POS     (ESP_spi_ss2__0__HSIOM_SHIFT)
#endif /* (ESP_SS2_PIN) */

#if (ESP_SS3_PIN)
    #define ESP_SS3_HSIOM_REG     (*(reg32 *) ESP_spi_ss3__0__HSIOM)
    #define ESP_SS3_HSIOM_PTR     ( (reg32 *) ESP_spi_ss3__0__HSIOM)
    #define ESP_SS3_HSIOM_MASK    (ESP_spi_ss3__0__HSIOM_MASK)
    #define ESP_SS3_HSIOM_POS     (ESP_spi_ss3__0__HSIOM_SHIFT)
#endif /* (ESP_SS3_PIN) */

#if (ESP_I2C_PINS)
    #define ESP_SCL_HSIOM_REG     (*(reg32 *) ESP_scl__0__HSIOM)
    #define ESP_SCL_HSIOM_PTR     ( (reg32 *) ESP_scl__0__HSIOM)
    #define ESP_SCL_HSIOM_MASK    (ESP_scl__0__HSIOM_MASK)
    #define ESP_SCL_HSIOM_POS     (ESP_scl__0__HSIOM_SHIFT)

    #define ESP_SDA_HSIOM_REG     (*(reg32 *) ESP_sda__0__HSIOM)
    #define ESP_SDA_HSIOM_PTR     ( (reg32 *) ESP_sda__0__HSIOM)
    #define ESP_SDA_HSIOM_MASK    (ESP_sda__0__HSIOM_MASK)
    #define ESP_SDA_HSIOM_POS     (ESP_sda__0__HSIOM_SHIFT)
#endif /* (ESP_I2C_PINS) */

#if (ESP_SPI_MASTER_SCLK_PIN)
    #define ESP_SCLK_M_HSIOM_REG   (*(reg32 *) ESP_sclk_m__0__HSIOM)
    #define ESP_SCLK_M_HSIOM_PTR   ( (reg32 *) ESP_sclk_m__0__HSIOM)
    #define ESP_SCLK_M_HSIOM_MASK  (ESP_sclk_m__0__HSIOM_MASK)
    #define ESP_SCLK_M_HSIOM_POS   (ESP_sclk_m__0__HSIOM_SHIFT)
#endif /* (ESP_SPI_MASTER_SCLK_PIN) */

#if (ESP_SPI_MASTER_SS0_PIN)
    #define ESP_SS0_M_HSIOM_REG    (*(reg32 *) ESP_ss0_m__0__HSIOM)
    #define ESP_SS0_M_HSIOM_PTR    ( (reg32 *) ESP_ss0_m__0__HSIOM)
    #define ESP_SS0_M_HSIOM_MASK   (ESP_ss0_m__0__HSIOM_MASK)
    #define ESP_SS0_M_HSIOM_POS    (ESP_ss0_m__0__HSIOM_SHIFT)
#endif /* (ESP_SPI_MASTER_SS0_PIN) */

#if (ESP_SPI_MASTER_SS1_PIN)
    #define ESP_SS1_M_HSIOM_REG    (*(reg32 *) ESP_ss1_m__0__HSIOM)
    #define ESP_SS1_M_HSIOM_PTR    ( (reg32 *) ESP_ss1_m__0__HSIOM)
    #define ESP_SS1_M_HSIOM_MASK   (ESP_ss1_m__0__HSIOM_MASK)
    #define ESP_SS1_M_HSIOM_POS    (ESP_ss1_m__0__HSIOM_SHIFT)
#endif /* (ESP_SPI_MASTER_SS1_PIN) */

#if (ESP_SPI_MASTER_SS2_PIN)
    #define ESP_SS2_M_HSIOM_REG    (*(reg32 *) ESP_ss2_m__0__HSIOM)
    #define ESP_SS2_M_HSIOM_PTR    ( (reg32 *) ESP_ss2_m__0__HSIOM)
    #define ESP_SS2_M_HSIOM_MASK   (ESP_ss2_m__0__HSIOM_MASK)
    #define ESP_SS2_M_HSIOM_POS    (ESP_ss2_m__0__HSIOM_SHIFT)
#endif /* (ESP_SPI_MASTER_SS2_PIN) */

#if (ESP_SPI_MASTER_SS3_PIN)
    #define ESP_SS3_M_HSIOM_REG    (*(reg32 *) ESP_ss3_m__0__HSIOM)
    #define ESP_SS3_M_HSIOM_PTR    ( (reg32 *) ESP_ss3_m__0__HSIOM)
    #define ESP_SS3_M_HSIOM_MASK   (ESP_ss3_m__0__HSIOM_MASK)
    #define ESP_SS3_M_HSIOM_POS    (ESP_ss3_m__0__HSIOM_SHIFT)
#endif /* (ESP_SPI_MASTER_SS3_PIN) */

#if (ESP_UART_TX_PIN)
    #define ESP_TX_HSIOM_REG   (*(reg32 *) ESP_tx__0__HSIOM)
    #define ESP_TX_HSIOM_PTR   ( (reg32 *) ESP_tx_0__HSIOM)
    #define ESP_TX_HSIOM_MASK  (ESP_tx__0__HSIOM_MASK)
    #define ESP_TX_HSIOM_POS   (ESP_tx__0__HSIOM_SHIFT)
#endif /* (ESP_UART_TX_PIN) */

#if (ESP_UART_RTS_PIN)
    #define ESP_RTS_HSIOM_REG  (*(reg32 *) ESP_rts__0__HSIOM)
    #define ESP_RTS_HSIOM_PTR  ( (reg32 *) ESP_rts__0__HSIOM)
    #define ESP_RTS_HSIOM_MASK (ESP_rts__0__HSIOM_MASK)
    #define ESP_RTS_HSIOM_POS  (ESP_rts__0__HSIOM_SHIFT)
#endif /* (ESP_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define ESP_HSIOM_DEF_SEL      (0x00u)
#define ESP_HSIOM_GPIO_SEL     (0x00u)
#define ESP_HSIOM_UART_SEL     (0x09u)
#define ESP_HSIOM_I2C_SEL      (0x0Eu)
#define ESP_HSIOM_SPI_SEL      (0x0Fu)

#define ESP_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define ESP_RX_SCL_MOSI_PIN_INDEX       (0u)
#define ESP_TX_SDA_MISO_PIN_INDEX       (1u)
#define ESP_SCLK_PIN_INDEX       (2u)
#define ESP_SS0_PIN_INDEX       (3u)
#define ESP_SS1_PIN_INDEX                  (4u)
#define ESP_SS2_PIN_INDEX                  (5u)
#define ESP_SS3_PIN_INDEX                  (6u)

#define ESP_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << ESP_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define ESP_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << ESP_RX_SCL_MOSI_PIN_INDEX)
#define ESP_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << ESP_TX_SDA_MISO_PIN_INDEX)
#define ESP_SCLK_PIN_MASK     ((uint32) 0x01u << ESP_SCLK_PIN_INDEX)
#define ESP_SS0_PIN_MASK     ((uint32) 0x01u << ESP_SS0_PIN_INDEX)
#define ESP_SS1_PIN_MASK                ((uint32) 0x01u << ESP_SS1_PIN_INDEX)
#define ESP_SS2_PIN_MASK                ((uint32) 0x01u << ESP_SS2_PIN_INDEX)
#define ESP_SS3_PIN_MASK                ((uint32) 0x01u << ESP_SS3_PIN_INDEX)

/* Pin interrupt constants */
#define ESP_INTCFG_TYPE_MASK           (0x03u)
#define ESP_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants */
#define ESP_PIN_DM_ALG_HIZ  (0u)
#define ESP_PIN_DM_DIG_HIZ  (1u)
#define ESP_PIN_DM_OD_LO    (4u)
#define ESP_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define ESP_DM_MASK    (0x7u)
#define ESP_DM_SIZE    (3)
#define ESP_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) ESP_DM_MASK << (ESP_DM_SIZE * (pos)))) >> \
                                                              (ESP_DM_SIZE * (pos)) )

#if (ESP_TX_SDA_MISO_PIN)
    #define ESP_CHECK_TX_SDA_MISO_PIN_USED \
                (ESP_PIN_DM_ALG_HIZ != \
                    ESP_GET_P4_PIN_DM(ESP_uart_tx_i2c_sda_spi_miso_PC, \
                                                   ESP_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (ESP_TX_SDA_MISO_PIN) */

#if (ESP_SS0_PIN)
    #define ESP_CHECK_SS0_PIN_USED \
                (ESP_PIN_DM_ALG_HIZ != \
                    ESP_GET_P4_PIN_DM(ESP_spi_ss0_PC, \
                                                   ESP_spi_ss0_SHIFT))
#endif /* (ESP_SS0_PIN) */

/* Set bits-mask in register */
#define ESP_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define ESP_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define ESP_SET_HSIOM_SEL(reg, mask, pos, sel) ESP_SET_REGISTER_BITS(reg, mask, pos, sel)
#define ESP_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        ESP_SET_REGISTER_BITS(reg, mask, pos, intType)
#define ESP_SET_INP_DIS(reg, mask, val) ESP_SET_REGISTER_BIT(reg, mask, val)

/* ESP_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  ESP_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (ESP_CY_SCBIP_V0)
#if (ESP_I2C_PINS)
    #define ESP_SET_I2C_SCL_DR(val) ESP_scl_Write(val)

    #define ESP_SET_I2C_SCL_HSIOM_SEL(sel) \
                          ESP_SET_HSIOM_SEL(ESP_SCL_HSIOM_REG,  \
                                                         ESP_SCL_HSIOM_MASK, \
                                                         ESP_SCL_HSIOM_POS,  \
                                                         (sel))
    #define ESP_WAIT_SCL_SET_HIGH  (0u == ESP_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (ESP_RX_WAKE_SCL_MOSI_PIN)
    #define ESP_SET_I2C_SCL_DR(val) \
                            ESP_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define ESP_SET_I2C_SCL_HSIOM_SEL(sel) \
                    ESP_SET_HSIOM_SEL(ESP_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   ESP_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   ESP_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define ESP_WAIT_SCL_SET_HIGH  (0u == ESP_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (ESP_RX_SCL_MOSI_PIN)
    #define ESP_SET_I2C_SCL_DR(val) \
                            ESP_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define ESP_SET_I2C_SCL_HSIOM_SEL(sel) \
                            ESP_SET_HSIOM_SEL(ESP_RX_SCL_MOSI_HSIOM_REG,  \
                                                           ESP_RX_SCL_MOSI_HSIOM_MASK, \
                                                           ESP_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define ESP_WAIT_SCL_SET_HIGH  (0u == ESP_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define ESP_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define ESP_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define ESP_WAIT_SCL_SET_HIGH  (0u)
#endif /* (ESP_I2C_PINS) */

/* SCB I2C: sda signal */
#if (ESP_I2C_PINS)
    #define ESP_WAIT_SDA_SET_HIGH  (0u == ESP_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (ESP_TX_SDA_MISO_PIN)
    #define ESP_WAIT_SDA_SET_HIGH  (0u == ESP_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define ESP_WAIT_SDA_SET_HIGH  (0u)
#endif /* (ESP_MOSI_SCL_RX_PIN) */
#endif /* (ESP_CY_SCBIP_V0) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define ESP_REMOVE_MOSI_SCL_RX_WAKE_PIN    ESP_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define ESP_REMOVE_MOSI_SCL_RX_PIN         ESP_REMOVE_RX_SCL_MOSI_PIN
#define ESP_REMOVE_MISO_SDA_TX_PIN         ESP_REMOVE_TX_SDA_MISO_PIN
#ifndef ESP_REMOVE_SCLK_PIN
#define ESP_REMOVE_SCLK_PIN                ESP_REMOVE_SCLK_PIN
#endif /* ESP_REMOVE_SCLK_PIN */
#ifndef ESP_REMOVE_SS0_PIN
#define ESP_REMOVE_SS0_PIN                 ESP_REMOVE_SS0_PIN
#endif /* ESP_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define ESP_MOSI_SCL_RX_WAKE_PIN   ESP_RX_WAKE_SCL_MOSI_PIN
#define ESP_MOSI_SCL_RX_PIN        ESP_RX_SCL_MOSI_PIN
#define ESP_MISO_SDA_TX_PIN        ESP_TX_SDA_MISO_PIN
#ifndef ESP_SCLK_PIN
#define ESP_SCLK_PIN               ESP_SCLK_PIN
#endif /* ESP_SCLK_PIN */
#ifndef ESP_SS0_PIN
#define ESP_SS0_PIN                ESP_SS0_PIN
#endif /* ESP_SS0_PIN */

#if (ESP_MOSI_SCL_RX_WAKE_PIN)
    #define ESP_MOSI_SCL_RX_WAKE_HSIOM_REG     ESP_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define ESP_MOSI_SCL_RX_WAKE_HSIOM_PTR     ESP_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define ESP_MOSI_SCL_RX_WAKE_HSIOM_MASK    ESP_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define ESP_MOSI_SCL_RX_WAKE_HSIOM_POS     ESP_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define ESP_MOSI_SCL_RX_WAKE_INTCFG_REG    ESP_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define ESP_MOSI_SCL_RX_WAKE_INTCFG_PTR    ESP_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define ESP_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   ESP_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define ESP_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  ESP_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (ESP_RX_WAKE_SCL_MOSI_PIN) */

#if (ESP_MOSI_SCL_RX_PIN)
    #define ESP_MOSI_SCL_RX_HSIOM_REG      ESP_RX_SCL_MOSI_HSIOM_REG
    #define ESP_MOSI_SCL_RX_HSIOM_PTR      ESP_RX_SCL_MOSI_HSIOM_PTR
    #define ESP_MOSI_SCL_RX_HSIOM_MASK     ESP_RX_SCL_MOSI_HSIOM_MASK
    #define ESP_MOSI_SCL_RX_HSIOM_POS      ESP_RX_SCL_MOSI_HSIOM_POS
#endif /* (ESP_MOSI_SCL_RX_PIN) */

#if (ESP_MISO_SDA_TX_PIN)
    #define ESP_MISO_SDA_TX_HSIOM_REG      ESP_TX_SDA_MISO_HSIOM_REG
    #define ESP_MISO_SDA_TX_HSIOM_PTR      ESP_TX_SDA_MISO_HSIOM_REG
    #define ESP_MISO_SDA_TX_HSIOM_MASK     ESP_TX_SDA_MISO_HSIOM_REG
    #define ESP_MISO_SDA_TX_HSIOM_POS      ESP_TX_SDA_MISO_HSIOM_REG
#endif /* (ESP_MISO_SDA_TX_PIN_PIN) */

#if (ESP_SCLK_PIN)
    #ifndef ESP_SCLK_HSIOM_REG
    #define ESP_SCLK_HSIOM_REG     ESP_SCLK_HSIOM_REG
    #define ESP_SCLK_HSIOM_PTR     ESP_SCLK_HSIOM_PTR
    #define ESP_SCLK_HSIOM_MASK    ESP_SCLK_HSIOM_MASK
    #define ESP_SCLK_HSIOM_POS     ESP_SCLK_HSIOM_POS
    #endif /* ESP_SCLK_HSIOM_REG */
#endif /* (ESP_SCLK_PIN) */

#if (ESP_SS0_PIN)
    #ifndef ESP_SS0_HSIOM_REG
    #define ESP_SS0_HSIOM_REG      ESP_SS0_HSIOM_REG
    #define ESP_SS0_HSIOM_PTR      ESP_SS0_HSIOM_PTR
    #define ESP_SS0_HSIOM_MASK     ESP_SS0_HSIOM_MASK
    #define ESP_SS0_HSIOM_POS      ESP_SS0_HSIOM_POS
    #endif /* ESP_SS0_HSIOM_REG */
#endif /* (ESP_SS0_PIN) */

#define ESP_MOSI_SCL_RX_WAKE_PIN_INDEX ESP_RX_WAKE_SCL_MOSI_PIN_INDEX
#define ESP_MOSI_SCL_RX_PIN_INDEX      ESP_RX_SCL_MOSI_PIN_INDEX
#define ESP_MISO_SDA_TX_PIN_INDEX      ESP_TX_SDA_MISO_PIN_INDEX
#ifndef ESP_SCLK_PIN_INDEX
#define ESP_SCLK_PIN_INDEX             ESP_SCLK_PIN_INDEX
#endif /* ESP_SCLK_PIN_INDEX */
#ifndef ESP_SS0_PIN_INDEX
#define ESP_SS0_PIN_INDEX              ESP_SS0_PIN_INDEX
#endif /* ESP_SS0_PIN_INDEX */

#define ESP_MOSI_SCL_RX_WAKE_PIN_MASK ESP_RX_WAKE_SCL_MOSI_PIN_MASK
#define ESP_MOSI_SCL_RX_PIN_MASK      ESP_RX_SCL_MOSI_PIN_MASK
#define ESP_MISO_SDA_TX_PIN_MASK      ESP_TX_SDA_MISO_PIN_MASK
#ifndef ESP_SCLK_PIN_MASK
#define ESP_SCLK_PIN_MASK             ESP_SCLK_PIN_MASK
#endif /* ESP_SCLK_PIN_MASK */
#ifndef ESP_SS0_PIN_MASK
#define ESP_SS0_PIN_MASK              ESP_SS0_PIN_MASK
#endif /* ESP_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_ESP_H) */


/* [] END OF FILE */
