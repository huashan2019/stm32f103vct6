/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "include.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
unsigned char USB_Rx_Buf[64]; //USB½ÓÊÕ»º´æ
unsigned char USB_Received_Count = 0;//USB½ÓÊÕÊý¾Ý¼ÆÊý
unsigned int AD_DMA[2];

UART_HandleTypeDef huart2;

void SysHardware_Init(void)
{
	//Bsp_Clock_Init();
	//Bsp_SysTick_Init();
	//Bsp_GPIO_Init();
	//Bsp_WDOG_Init();  
	//Bsp_UART_Init();
	//Bsp_SPI_Init();
	//Bsp_ADC_Init();
	//Bsp_FLASH_Init();
	//Print_Init();
}
void SysSoftware_Init(void)
{
	SysDataInit();
	DspInit();
	Check_Uart();
}

HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(recv_end_flag ==1)	printf("Rec end \r\n");
	{
		printf("rx_len=%d\r\n",rx_len);//ï¿½ï¿½Ó¡ï¿½ï¿½ï¿½Õ³ï¿½ï¿½ï¿½
		HAL_UART_Transmit(&huart2,rx_buffer, rx_len,0xFFFF);//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý´ï¿½Ó¡ï¿½ï¿½ï¿½ï¿½
		for(uint8_t i=0;i<BUFFER_SIZE;i++)
			{
				printf("rx_buffer%d %x\r\n",i,rx_buffer[i]);//ï¿½ï¿½Ó¡ï¿½ï¿½ï¿½Õ³ï¿½ï¿½ï¿½
				//rx_buffer[i]=0;//ï¿½ï¿½ï¿½ï¿½Õ»ï¿½ï¿½ï¿?
			}
		rx_len=0;//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?
		//recv_end_flag=0;//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Õ½ï¿½ï¿½ï¿½ï¿½ï¿½Ö¾Î?
	}
	HAL_UART_Receive_DMA(&huart2,rx_buffer,BUFFER_SIZE);//ï¿½ï¿½ï¿½Â´ï¿½DMAï¿½ï¿½ï¿½ï¿½ 

}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  //SysHardware_Init();
  SysSoftware_Init();
  
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_SPI3_Init();
  MX_USART1_UART_Init();
  MX_TIM5_Init();
  MX_ADC1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_ADCEx_Calibration_Start(&hadc1);
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&AD_DMA,2); //ÆôÓÃDMAµÄADC×ª»»£¬AD_DMA 0~3 ¶ÔÓ¦ADC 0~3£¬ÕâÀï×¢Òâ×îºóÒ»¸ö²ÎÊýµÄ´óÐ¡

  //HAL_TIM_Base_Start_IT(&htim5);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);

	//ÉÏÃæµÄusartÅäÖÃ´úÂëÎªcubemx×Ô¶¯Éú³ÉµÄ£¬ÔÚÏÂ·½Ìí¼ÓÊ¹ÄÜidleÖÐ¶ÏºÍ´ò¿ª´®¿ÚDMA½ÓÊÕÓï¾ä
  __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);//Ê¹ÄÜidleÖÐ¶Ï
  HAL_UART_Receive_DMA(&huart2,rx_buffer,BUFFER_SIZE);//´ò¿ªDMA½ÓÊÕ£¬Êý¾Ý´æÈërx_bufferÊý×éÖÐ¡£

  printf("APP Begin -- Software Version : %s \n", MCU_VERSION);
  printf("Code generation time : %s %s \n", __DATE__, __TIME__);
  //SPI_FLASH_ReadDeviceID();

  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init(); 
  /* Start scheduler */
  osKernelStart();
 
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC|RCC_PERIPHCLK_USB;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
