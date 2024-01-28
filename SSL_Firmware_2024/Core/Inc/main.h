/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SDA_OLED_Pin GPIO_PIN_0
#define SDA_OLED_GPIO_Port GPIOF
#define SCL_OLED_Pin GPIO_PIN_1
#define SCL_OLED_GPIO_Port GPIOF
#define KICK_HIGH_Pin GPIO_PIN_3
#define KICK_HIGH_GPIO_Port GPIOF
#define INT_KICK_DONE_Pin GPIO_PIN_4
#define INT_KICK_DONE_GPIO_Port GPIOF
#define KICK_CHIP_Pin GPIO_PIN_5
#define KICK_CHIP_GPIO_Port GPIOF
#define KICK_CHARGE_Pin GPIO_PIN_10
#define KICK_CHARGE_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define RMII_MDC_Pin GPIO_PIN_1
#define RMII_MDC_GPIO_Port GPIOC
#define MISO_RADIO_0_Pin GPIO_PIN_2
#define MISO_RADIO_0_GPIO_Port GPIOC
#define MOSI_RADIO_0_Pin GPIO_PIN_3
#define MOSI_RADIO_0_GPIO_Port GPIOC
#define INT_RADIO_0_Pin GPIO_PIN_0
#define INT_RADIO_0_GPIO_Port GPIOA
#define RMII_REF_CLK_Pin GPIO_PIN_1
#define RMII_REF_CLK_GPIO_Port GPIOA
#define RMII_MDIO_Pin GPIO_PIN_2
#define RMII_MDIO_GPIO_Port GPIOA
#define BUZZER_Pin GPIO_PIN_3
#define BUZZER_GPIO_Port GPIOA
#define NSS_RADIO_1_Pin GPIO_PIN_4
#define NSS_RADIO_1_GPIO_Port GPIOA
#define SCK_RADIO_1_Pin GPIO_PIN_5
#define SCK_RADIO_1_GPIO_Port GPIOA
#define MISO_RADIO_1_Pin GPIO_PIN_6
#define MISO_RADIO_1_GPIO_Port GPIOA
#define RMII_CRS_DV_Pin GPIO_PIN_7
#define RMII_CRS_DV_GPIO_Port GPIOA
#define RMII_RXD0_Pin GPIO_PIN_4
#define RMII_RXD0_GPIO_Port GPIOC
#define RMII_RXD1_Pin GPIO_PIN_5
#define RMII_RXD1_GPIO_Port GPIOC
#define LED_GREEN_Pin GPIO_PIN_0
#define LED_GREEN_GPIO_Port GPIOB
#define INT_RADIO_1_Pin GPIO_PIN_1
#define INT_RADIO_1_GPIO_Port GPIOB
#define RST_RADIO_1_Pin GPIO_PIN_2
#define RST_RADIO_1_GPIO_Port GPIOB
#define SCL_NFC_Pin GPIO_PIN_14
#define SCL_NFC_GPIO_Port GPIOF
#define SDA_NFC_Pin GPIO_PIN_15
#define SDA_NFC_GPIO_Port GPIOF
#define LED_G_Pin GPIO_PIN_1
#define LED_G_GPIO_Port GPIOG
#define NSS_RADIO_0_Pin GPIO_PIN_12
#define NSS_RADIO_0_GPIO_Port GPIOB
#define RMII_TXD1_Pin GPIO_PIN_13
#define RMII_TXD1_GPIO_Port GPIOB
#define LED_RED_Pin GPIO_PIN_14
#define LED_RED_GPIO_Port GPIOB
#define STLK_VCP_RX_Pin GPIO_PIN_8
#define STLK_VCP_RX_GPIO_Port GPIOD
#define STLK_VCP_TX_Pin GPIO_PIN_9
#define STLK_VCP_TX_GPIO_Port GPIOD
#define USB_FS_PWR_EN_Pin GPIO_PIN_10
#define USB_FS_PWR_EN_GPIO_Port GPIOD
#define LED_B_Pin GPIO_PIN_2
#define LED_B_GPIO_Port GPIOG
#define USB_FS_OVCR_Pin GPIO_PIN_7
#define USB_FS_OVCR_GPIO_Port GPIOG
#define INT_BTNS_Pin GPIO_PIN_8
#define INT_BTNS_GPIO_Port GPIOC
#define SDA_BTNS_Pin GPIO_PIN_9
#define SDA_BTNS_GPIO_Port GPIOC
#define SCL_BTNS_Pin GPIO_PIN_8
#define SCL_BTNS_GPIO_Port GPIOA
#define USB_FS_VBUS_Pin GPIO_PIN_9
#define USB_FS_VBUS_GPIO_Port GPIOA
#define USB_FS_ID_Pin GPIO_PIN_10
#define USB_FS_ID_GPIO_Port GPIOA
#define USB_FS_DM_Pin GPIO_PIN_11
#define USB_FS_DM_GPIO_Port GPIOA
#define USB_FS_DP_Pin GPIO_PIN_12
#define USB_FS_DP_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define RST_RADIO_0_Pin GPIO_PIN_15
#define RST_RADIO_0_GPIO_Port GPIOA
#define BUSY_RADIO_0_Pin GPIO_PIN_2
#define BUSY_RADIO_0_GPIO_Port GPIOD
#define SCK_RADIO_0_Pin GPIO_PIN_3
#define SCK_RADIO_0_GPIO_Port GPIOD
#define RMII_TX_EN_Pin GPIO_PIN_11
#define RMII_TX_EN_GPIO_Port GPIOG
#define RMII_TXD0_Pin GPIO_PIN_13
#define RMII_TXD0_GPIO_Port GPIOG
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define BUSY_RADIO_1_Pin GPIO_PIN_4
#define BUSY_RADIO_1_GPIO_Port GPIOB
#define MOSI_RADIO_1_Pin GPIO_PIN_5
#define MOSI_RADIO_1_GPIO_Port GPIOB
#define SCL_IMU_Pin GPIO_PIN_6
#define SCL_IMU_GPIO_Port GPIOB
#define SDA_IMU_Pin GPIO_PIN_7
#define SDA_IMU_GPIO_Port GPIOB
#define LED_YELLOW_Pin GPIO_PIN_1
#define LED_YELLOW_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
