/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "stm32f4xx_hal.h"

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
#define ID_BTN_Pin GPIO_PIN_2
#define ID_BTN_GPIO_Port GPIOE
#define CS_I2C_SPI_Pin GPIO_PIN_3
#define CS_I2C_SPI_GPIO_Port GPIOE
#define M1_MBL_Pin GPIO_PIN_4
#define M1_MBL_GPIO_Port GPIOE
#define MD_MAH_Pin GPIO_PIN_5
#define MD_MAH_GPIO_Port GPIOE
#define M1_MAL_Pin GPIO_PIN_6
#define M1_MAL_GPIO_Port GPIOE
#define M0_MBL_Pin GPIO_PIN_13
#define M0_MBL_GPIO_Port GPIOC
#define PC14_OSC32_IN_Pin GPIO_PIN_14
#define PC14_OSC32_IN_GPIO_Port GPIOC
#define PC15_OSC32_OUT_Pin GPIO_PIN_15
#define PC15_OSC32_OUT_GPIO_Port GPIOC
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH
#define VBat_Pin GPIO_PIN_0
#define VBat_GPIO_Port GPIOC
#define M0_INA_Pin GPIO_PIN_1
#define M0_INA_GPIO_Port GPIOC
#define M2_MAL_Pin GPIO_PIN_2
#define M2_MAL_GPIO_Port GPIOC
#define PDM_OUT_Pin GPIO_PIN_3
#define PDM_OUT_GPIO_Port GPIOC
#define M2_ENCA_Pin GPIO_PIN_0
#define M2_ENCA_GPIO_Port GPIOA
#define M2_ENCB_Pin GPIO_PIN_1
#define M2_ENCB_GPIO_Port GPIOA
#define M1_INA_Pin GPIO_PIN_2
#define M1_INA_GPIO_Port GPIOA
#define M3_INA_Pin GPIO_PIN_3
#define M3_INA_GPIO_Port GPIOA
#define MD_INA_Pin GPIO_PIN_4
#define MD_INA_GPIO_Port GPIOA
#define SPI1_SCK_Pin GPIO_PIN_5
#define SPI1_SCK_GPIO_Port GPIOA
#define SPI1_MISO_Pin GPIO_PIN_6
#define SPI1_MISO_GPIO_Port GPIOA
#define SPI1_MOSI_Pin GPIO_PIN_7
#define SPI1_MOSI_GPIO_Port GPIOA
#define M2_INA_Pin GPIO_PIN_4
#define M2_INA_GPIO_Port GPIOC
#define NRF_IRQ_Pin GPIO_PIN_5
#define NRF_IRQ_GPIO_Port GPIOC
#define CE_KB_Pin GPIO_PIN_0
#define CE_KB_GPIO_Port GPIOB
#define M2_MBL_Pin GPIO_PIN_1
#define M2_MBL_GPIO_Port GPIOB
#define IRQ_MPU_Pin GPIO_PIN_2
#define IRQ_MPU_GPIO_Port GPIOB
#define M2_MBH_Pin GPIO_PIN_11
#define M2_MBH_GPIO_Port GPIOE
#define M3_MBH_Pin GPIO_PIN_13
#define M3_MBH_GPIO_Port GPIOE
#define M3_MAH_Pin GPIO_PIN_14
#define M3_MAH_GPIO_Port GPIOE
#define CLK_IN_Pin GPIO_PIN_10
#define CLK_IN_GPIO_Port GPIOB
#define M3_MBL_Pin GPIO_PIN_11
#define M3_MBL_GPIO_Port GPIOB
#define M3_MAL_Pin GPIO_PIN_12
#define M3_MAL_GPIO_Port GPIOB
#define CA_Pin GPIO_PIN_8
#define CA_GPIO_Port GPIOD
#define CB_Pin GPIO_PIN_10
#define CB_GPIO_Port GPIOD
#define LED_GREEN_Pin GPIO_PIN_12
#define LED_GREEN_GPIO_Port GPIOD
#define LED_ORANGE_Pin GPIO_PIN_13
#define LED_ORANGE_GPIO_Port GPIOD
#define LED_RED_Pin GPIO_PIN_14
#define LED_RED_GPIO_Port GPIOD
#define LED_BLUE_Pin GPIO_PIN_15
#define LED_BLUE_GPIO_Port GPIOD
#define M2_MAH_Pin GPIO_PIN_6
#define M2_MAH_GPIO_Port GPIOC
#define M0_MBH_Pin GPIO_PIN_7
#define M0_MBH_GPIO_Port GPIOC
#define M1_MBH_Pin GPIO_PIN_8
#define M1_MBH_GPIO_Port GPIOC
#define M0_MAH_Pin GPIO_PIN_9
#define M0_MAH_GPIO_Port GPIOC
#define M1_MAH_Pin GPIO_PIN_8
#define M1_MAH_GPIO_Port GPIOA
#define VBUS_FS_Pin GPIO_PIN_9
#define VBUS_FS_GPIO_Port GPIOA
#define OTG_FS_ID_Pin GPIO_PIN_10
#define OTG_FS_ID_GPIO_Port GPIOA
#define OTG_FS_DM_Pin GPIO_PIN_11
#define OTG_FS_DM_GPIO_Port GPIOA
#define OTG_FS_DP_Pin GPIO_PIN_12
#define OTG_FS_DP_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define M1_ENCA_Pin GPIO_PIN_15
#define M1_ENCA_GPIO_Port GPIOA
#define MPU_CS_Pin GPIO_PIN_10
#define MPU_CS_GPIO_Port GPIOC
#define SEN_2_Pin GPIO_PIN_11
#define SEN_2_GPIO_Port GPIOC
#define NRF_CE_Pin GPIO_PIN_12
#define NRF_CE_GPIO_Port GPIOC
#define NRF_CS_Pin GPIO_PIN_0
#define NRF_CS_GPIO_Port GPIOD
#define SEN_1_Pin GPIO_PIN_1
#define SEN_1_GPIO_Port GPIOD
#define SD_CS_Pin GPIO_PIN_3
#define SD_CS_GPIO_Port GPIOD
#define Audio_RST_Pin GPIO_PIN_4
#define Audio_RST_GPIO_Port GPIOD
#define OTG_FS_OverCurrent_Pin GPIO_PIN_5
#define OTG_FS_OverCurrent_GPIO_Port GPIOD
#define M0_MAL_Pin GPIO_PIN_7
#define M0_MAL_GPIO_Port GPIOD
#define M1_ENCB_Pin GPIO_PIN_3
#define M1_ENCB_GPIO_Port GPIOB
#define M0_ENCA_Pin GPIO_PIN_4
#define M0_ENCA_GPIO_Port GPIOB
#define M0_ENCB_Pin GPIO_PIN_5
#define M0_ENCB_GPIO_Port GPIOB
#define M3_ENCA_Pin GPIO_PIN_6
#define M3_ENCA_GPIO_Port GPIOB
#define M3_ENCB_Pin GPIO_PIN_7
#define M3_ENCB_GPIO_Port GPIOB
#define I2C_SCL_Pin GPIO_PIN_8
#define I2C_SCL_GPIO_Port GPIOB
#define I2C_SDA_Pin GPIO_PIN_9
#define I2C_SDA_GPIO_Port GPIOB
#define MEMS_INT2_Pin GPIO_PIN_1
#define MEMS_INT2_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
