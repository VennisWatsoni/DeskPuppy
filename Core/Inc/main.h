/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
void PWM_Init(void);
void Servo_SetAngle(uint8_t ch, uint8_t angle);
void USART1_Send_DMA(char *str);
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
#define BATTERYVAL_PB0_Pin GPIO_PIN_0
#define BATTERYVAL_PB0_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_12
#define LED1_GPIO_Port GPIOB
#define MUP_SDA_Pin GPIO_PIN_13
#define MUP_SDA_GPIO_Port GPIOB
#define MUP_SCL_Pin GPIO_PIN_14
#define MUP_SCL_GPIO_Port GPIOB
#define MUP_INT_Pin GPIO_PIN_15
#define MUP_INT_GPIO_Port GPIOB
#define RGB2_Pin GPIO_PIN_8
#define RGB2_GPIO_Port GPIOA
#define RGB1_Pin GPIO_PIN_11
#define RGB1_GPIO_Port GPIOA
#define KEY_Pin GPIO_PIN_12
#define KEY_GPIO_Port GPIOA
#define KEY_EXTI_IRQn EXTI15_10_IRQn
#define OLED_SCL_Pin GPIO_PIN_15
#define OLED_SCL_GPIO_Port GPIOA
#define OLED_SDA_Pin GPIO_PIN_3
#define OLED_SDA_GPIO_Port GPIOB
#define OLED_RES_Pin GPIO_PIN_4
#define OLED_RES_GPIO_Port GPIOB
#define OLED_DC_Pin GPIO_PIN_5
#define OLED_DC_GPIO_Port GPIOB
#define AHT20_SCL_Pin GPIO_PIN_6
#define AHT20_SCL_GPIO_Port GPIOB
#define AHT20_SDA_Pin GPIO_PIN_7
#define AHT20_SDA_GPIO_Port GPIOB
#define SR04_PB8_Pin GPIO_PIN_8
#define SR04_PB8_GPIO_Port GPIOB
#define SR04_PB9_Pin GPIO_PIN_9
#define SR04_PB9_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define SERVO_CH0	0	// PA4
#define SERVO_CH1	1	// PA5
#define SERVO_CH2	2	// PA6
#define SERVO_CH3	3	// PA7
#define USART1_RX_MAX_LEN 64
#define USART2_RX_MAX_LEN 64

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
