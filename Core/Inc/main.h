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
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f1xx_hal.h"

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
#define REM_CTRL_Pin GPIO_PIN_4
#define REM_CTRL_GPIO_Port GPIOE
#define DSP_ONOFF_CHECK_Pin GPIO_PIN_5
#define DSP_ONOFF_CHECK_GPIO_Port GPIOE
#define SYS_POW_EN_Pin GPIO_PIN_6
#define SYS_POW_EN_GPIO_Port GPIOE
#define LED1_Pin GPIO_PIN_3
#define LED1_GPIO_Port GPIOC
#define ACC_CHECK_Pin GPIO_PIN_0
#define ACC_CHECK_GPIO_Port GPIOA
#define SPI1_CS_Pin GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
#define SPI1_SCLK_Pin GPIO_PIN_5
#define SPI1_SCLK_GPIO_Port GPIOA
#define SPI1_MISO_Pin GPIO_PIN_6
#define SPI1_MISO_GPIO_Port GPIOA
#define SPI1_MOSI_Pin GPIO_PIN_7
#define SPI1_MOSI_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_4
#define LED2_GPIO_Port GPIOC
#define BAT_CHECK_Pin GPIO_PIN_5
#define BAT_CHECK_GPIO_Port GPIOC
#define TEMP_CHECK_Pin GPIO_PIN_0
#define TEMP_CHECK_GPIO_Port GPIOB
#define AUDIO_CHECK_Pin GPIO_PIN_1
#define AUDIO_CHECK_GPIO_Port GPIOB
#define POW_AMP1_CHECK_Pin GPIO_PIN_2
#define POW_AMP1_CHECK_GPIO_Port GPIOB
#define PWR_AMP2_CHECK_Pin GPIO_PIN_7
#define PWR_AMP2_CHECK_GPIO_Port GPIOE
#define POW_AMP3_CHECK_Pin GPIO_PIN_8
#define POW_AMP3_CHECK_GPIO_Port GPIOE
#define POW_AMP4_CHECK_Pin GPIO_PIN_9
#define POW_AMP4_CHECK_GPIO_Port GPIOE
#define I2C2_SCL_Pin GPIO_PIN_10
#define I2C2_SCL_GPIO_Port GPIOB
#define I2C2_SDA_Pin GPIO_PIN_11
#define I2C2_SDA_GPIO_Port GPIOB
#define SPI0_CS_Pin GPIO_PIN_12
#define SPI0_CS_GPIO_Port GPIOB
#define SPI0_SCLK_Pin GPIO_PIN_13
#define SPI0_SCLK_GPIO_Port GPIOB
#define SPI0_MISO_Pin GPIO_PIN_14
#define SPI0_MISO_GPIO_Port GPIOB
#define SPI0_MISI_Pin GPIO_PIN_15
#define SPI0_MISI_GPIO_Port GPIOB
#define USB_TX_Pin GPIO_PIN_8
#define USB_TX_GPIO_Port GPIOD
#define USB_RX_Pin GPIO_PIN_9
#define USB_RX_GPIO_Port GPIOD
#define AD1938_RESET_Pin GPIO_PIN_11
#define AD1938_RESET_GPIO_Port GPIOD
#define DSP_RESET_Pin GPIO_PIN_12
#define DSP_RESET_GPIO_Port GPIOD
#define ADAU1978_RESET_Pin GPIO_PIN_13
#define ADAU1978_RESET_GPIO_Port GPIOD
#define LED_CTRL1_Pin GPIO_PIN_6
#define LED_CTRL1_GPIO_Port GPIOC
#define LED_CTRL2_Pin GPIO_PIN_7
#define LED_CTRL2_GPIO_Port GPIOC
#define POW_AMP_STANDBY_Pin GPIO_PIN_8
#define POW_AMP_STANDBY_GPIO_Port GPIOC
#define MUTE_Pin GPIO_PIN_9
#define MUTE_GPIO_Port GPIOC
#define BT_REST_Pin GPIO_PIN_8
#define BT_REST_GPIO_Port GPIOA
#define MCU_TX1_Pin GPIO_PIN_9
#define MCU_TX1_GPIO_Port GPIOA
#define MCU_RX1_Pin GPIO_PIN_10
#define MCU_RX1_GPIO_Port GPIOA
#define SPI3_CS_Pin GPIO_PIN_15
#define SPI3_CS_GPIO_Port GPIOA
#define SPI3_SCLK_Pin GPIO_PIN_3
#define SPI3_SCLK_GPIO_Port GPIOB
#define SPI3_MISO_Pin GPIO_PIN_4
#define SPI3_MISO_GPIO_Port GPIOB
#define SPI3_MOSI_Pin GPIO_PIN_5
#define SPI3_MOSI_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
