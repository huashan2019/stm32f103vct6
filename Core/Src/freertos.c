/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "include.h"
#include "spi.h"
#include "usbd_customhid.h" //
#include "adc.h"
#include "stm32f1xx_hal_rtc.h"

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
/* USER CODE BEGIN Variables */
volatile unsigned long ulHighFrequencyTimerTicks;
volatile unsigned long ulHighFrequencyTimerTicks1;


uint8_t Data1[4]={0x9f,0xff,0xff,0xff};
uint8_t Data2[2]={0x00,0x00};
uint8_t Rxdata[2];

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 4
};
/* Definitions for myTask03 */
osThreadId_t myTask03Handle;
const osThreadAttr_t myTask03_attributes = {
  .name = "myTask03",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 4
};
/* Definitions for myPrintfTask */
osThreadId_t myPrintfTaskHandle;
const osThreadAttr_t myPrintfTask_attributes = {
  .name = "myPrintfTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 1024 * 4
};
/* Definitions for myTask_4ms_Pro */
osThreadId_t myTask_4ms_ProHandle;
const osThreadAttr_t myTask_4ms_Pro_attributes = {
  .name = "myTask_4ms_Pro",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 4
};
/* Definitions for myTask_8ms_Pro */
osThreadId_t myTask_8ms_ProHandle;
const osThreadAttr_t myTask_8ms_Pro_attributes = {
  .name = "myTask_8ms_Pro",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 4
};
/* Definitions for myTask_16ms_Pro */
osThreadId_t myTask_16ms_ProHandle;
const osThreadAttr_t myTask_16ms_Pro_attributes = {
  .name = "myTask_16ms_Pro",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 4
};
/* Definitions for myTask_100ms_Pr */
osThreadId_t myTask_100ms_PrHandle;
const osThreadAttr_t myTask_100ms_Pr_attributes = {
  .name = "myTask_100ms_Pr",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask03(void *argument);
void PrintfTask(void *argument);
void StartTask_4ms_Pro(void *argument);
void StartTask_8ms_Pro(void *argument);
void StartTask_16ms_Pro(void *argument);
void StartTask_100ms_Pro(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{
	ulHighFrequencyTimerTicks = 0ul;
}

__weak unsigned long getRunTimeCounterValue(void)
{
return ulHighFrequencyTimerTicks;
}
/* USER CODE END 1 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of myTask03 */
  myTask03Handle = osThreadNew(StartTask03, NULL, &myTask03_attributes);

  /* creation of myPrintfTask */
  myPrintfTaskHandle = osThreadNew(PrintfTask, NULL, &myPrintfTask_attributes);

  /* creation of myTask_4ms_Pro */
  myTask_4ms_ProHandle = osThreadNew(StartTask_4ms_Pro, NULL, &myTask_4ms_Pro_attributes);

  /* creation of myTask_8ms_Pro */
  myTask_8ms_ProHandle = osThreadNew(StartTask_8ms_Pro, NULL, &myTask_8ms_Pro_attributes);

  /* creation of myTask_16ms_Pro */
  myTask_16ms_ProHandle = osThreadNew(StartTask_16ms_Pro, NULL, &myTask_16ms_Pro_attributes);

  /* creation of myTask_100ms_Pr */
  myTask_100ms_PrHandle = osThreadNew(StartTask_100ms_Pro, NULL, &myTask_100ms_Pr_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	//printf("TaskDefault -- Software Version : %s \r\n", MCU_VERSION);
	SPI_FLASH_ReadDeviceID();
    vTaskDelay(200);
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
    vTaskDelay(200);
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask03 */
//RTC_AlarmTypeDef salarmstructure;
//RTC_TimeTypeDef stime;

/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */


  /* Infinite loop */
  for(;;)
  {
  
  		BT_DataRxPro(Uart_CONNECT,	 &BtRxModuel);
  		BT_DataRxPro(Uart_OTHER,	 &PcRxModuel_0);
	 	 //vTaskDelay(500);
		 //printf("Task3 -- Software Version : %s \r\n", MCU_VERSION);
		/* Call HAL_RTC_GetTime function to update date if counter higher than 24 hours */
		//if (HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BIN) != HAL_OK)
		//{
		//	printf("rx_time err=%d,%d,%d\r\n",stimestructure.Hours,stimestructure.Minutes,stimestructure.Seconds);//ï¿½ï¿½Ó¡ï¿½ï¿½ï¿½Õ³ï¿½ï¿½ï¿½
		//	return ;
		//}
		//printf("rx_time=%d,%d,%d,%d\r\n",stimestructure.Hours,stimestructure.Minutes,stimestructure.Seconds,rtc_alarm_flag);//ï¿½ï¿½Ó¡ï¿½ï¿½ï¿½Õ³ï¿½ï¿½ï¿½

		
	  osDelay(1);
  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_PrintfTask */
/**
* @brief Function implementing the myPrintfTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_PrintfTask */
void PrintfTask(void *argument)
{
  /* USER CODE BEGIN PrintfTask */
	uint8_t pcWriteBuffer[500];

/* Infinite loop */
  for(;;)
  {
  
  	//printf("PrintfTask -- Software Version : %s \r\n", MCU_VERSION);
#if 1

	printf("=================================================\r\n");
	printf("ÈÎÎñÃû	    ÈÎÎñ×´Ì¬ ÓÅÏÈ¼¶   Ê£ÓàÕ» ÈÎÎñÐòºÅ\r\n");
	vTaskList((char *)&pcWriteBuffer);
	printf("%s\r\n", pcWriteBuffer);
	
	printf("\r\nÈÎÎñÃû		 ÔËÐÐ¼ÆÊý		  Ê¹ÓÃÂÊ\r\n");
	vTaskGetRunTimeStats((char *)&pcWriteBuffer);
	printf("%s\r\n", pcWriteBuffer);


#endif
    //vTaskDelay(20);
    osDelay(100);
  }
  /* USER CODE END PrintfTask */
}

/* USER CODE BEGIN Header_StartTask_4ms_Pro */
/**
* @brief Function implementing the myTask_4ms_Pro thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_4ms_Pro */
void StartTask_4ms_Pro(void *argument)
{
  /* USER CODE BEGIN StartTask_4ms_Pro */
  /* Infinite loop */
  for(;;)
  {
  	Task_4ms_Pro();
    osDelay(1);
  }
  /* USER CODE END StartTask_4ms_Pro */
}

/* USER CODE BEGIN Header_StartTask_8ms_Pro */
/**
* @brief Function implementing the myTask_8ms_Pro thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_8ms_Pro */
void StartTask_8ms_Pro(void *argument)
{
  /* USER CODE BEGIN StartTask_8ms_Pro */
  /* Infinite loop */
  for(;;)
  {
  	Task_8ms_Pro();
    osDelay(1);
  }
  /* USER CODE END StartTask_8ms_Pro */
}

/* USER CODE BEGIN Header_StartTask_16ms_Pro */
/**
* @brief Function implementing the myTask_16ms_Pro thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_16ms_Pro */
void StartTask_16ms_Pro(void *argument)
{
  /* USER CODE BEGIN StartTask_16ms_Pro */
  /* Infinite loop */
  for(;;)
  {
	Task_16ms_Pro();
    osDelay(1);
  }
  /* USER CODE END StartTask_16ms_Pro */
}

/* USER CODE BEGIN Header_StartTask_100ms_Pro */
/**
* @brief Function implementing the myTask_100ms_Pr thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_100ms_Pro */
void StartTask_100ms_Pro(void *argument)
{
  /* USER CODE BEGIN StartTask_100ms_Pro */
  /* Infinite loop */
  for(;;)
  {
	Task_100ms_Pro();
    osDelay(1);
  }
  /* USER CODE END StartTask_100ms_Pro */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
