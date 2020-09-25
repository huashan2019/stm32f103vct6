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
#include "semphr.h"

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
  .priority = (osPriority_t) osPriorityNormal2,
  .stack_size = 512 * 4
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
  .priority = (osPriority_t) osPriorityNormal1,
  .stack_size = 512 * 4
};
/* Definitions for myTask_16ms_Pro */
osThreadId_t myTask_16ms_ProHandle;
const osThreadAttr_t myTask_16ms_Pro_attributes = {
  .name = "myTask_16ms_Pro",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 512 * 4
};
/* Definitions for myTask_100ms_Pr */
osThreadId_t myTask_100ms_PrHandle;
const osThreadAttr_t myTask_100ms_Pr_attributes = {
  .name = "myTask_100ms_Pr",
  .priority = (osPriority_t) osPriorityNormal3,
  .stack_size = 512 * 4
};
/* Definitions for myQueue01 */
osMessageQueueId_t myQueue01Handle;
const osMessageQueueAttr_t myQueue01_attributes = {
  .name = "myQueue01"
};
/* Definitions for myMutex01 */
osMutexId_t myMutex01Handle;
const osMutexAttr_t myMutex01_attributes = {
  .name = "myMutex01"
};
/* Definitions for myMutex02 */
osMutexId_t myMutex02Handle;
const osMutexAttr_t myMutex02_attributes = {
  .name = "myMutex02"
};
/* Definitions for myMutex03 */
osMutexId_t myMutex03Handle;
const osMutexAttr_t myMutex03_attributes = {
  .name = "myMutex03"
};
/* Definitions for myMutex04 */
osMutexId_t myMutex04Handle;
const osMutexAttr_t myMutex04_attributes = {
  .name = "myMutex04"
};
/* Definitions for myBinarySem01 */
osSemaphoreId_t myBinarySem01Handle;
const osSemaphoreAttr_t myBinarySem01_attributes = {
  .name = "myBinarySem01"
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

/*
*********************************************************************************************************
*	函 数 名: AppObjCreate
*	功能说明: 创建任务通信机制
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/

static void AppObjCreate (void)
{
	/* 创建互斥信号量 */
    xMutex = xSemaphoreCreateMutex();
	
	if(xMutex == NULL)
    {
        /* 没有创建成功，用户可以在这里加入创建失败的处理机制 */
    }
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
  /* Create the mutex(es) */
  /* creation of myMutex01 */
  myMutex01Handle = osMutexNew(&myMutex01_attributes);

  /* creation of myMutex02 */
  myMutex02Handle = osMutexNew(&myMutex02_attributes);

  /* creation of myMutex03 */
  myMutex03Handle = osMutexNew(&myMutex03_attributes);

  /* creation of myMutex04 */
  myMutex04Handle = osMutexNew(&myMutex04_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  
  /* 创建任务通信机制 */
  AppObjCreate();
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of myBinarySem01 */
  myBinarySem01Handle = osSemaphoreNew(1, 1, &myBinarySem01_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of myQueue01 */
  myQueue01Handle = osMessageQueueNew (16, sizeof(uint16_t), &myQueue01_attributes);

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
	//SPI_FLASH_ReadDeviceID();
	
	//App_Printf("LED on: %s \r\n", 1);
    //vTaskDelay(500);
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
	//HAL_GPIO_WritePin(LED_CTRL2_GPIO_Port, LED_CTRL2_Pin, GPIO_PIN_SET);
    //vTaskDelay(500);
	//xLastWakeTime = xTaskGetTickCountFromISR();
	//vTaskDelayUntil(&xLastWakeTime,10);
	//SysWaitUs(100);
	
	SysWaitMs(500);
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
    //vTaskDelay(10);
	//xLastWakeTime = xTaskGetTickCountFromISR();
	//vTaskDelayUntil(&xLastWakeTime,10);
	//SysWaitUs(100);
	SysWaitMs(500);
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
    //vTaskDelay(10);
	//xLastWakeTime = xTaskGetTickCountFromISR();
	//vTaskDelayUntil(&xLastWakeTime,10);
	//SysWaitUs(100);
	
	SysWaitMs(500);
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
    vTaskDelay(500);
    //osDelay(1);
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
  
  		//taskENTER_CRITICAL();
  		BT_DataRxPro(Uart_CONNECT,	 &BtRxModuel);
  		BT_DataRxPro(Uart_OTHER,&PcRxModuel_0);
  		BT_DataRxPro(Uart_OTHER1,&PcRxModuel_1);
		
  		//taskEXIT_CRITICAL();
	 	 //vTaskDelay(500);
		// printf("Task3 -- Software Version : %s \r\n", MCU_VERSION);
		/* Call HAL_RTC_GetTime function to update date if counter higher than 24 hours */
		//if (HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BIN) != HAL_OK)
		//{
		//	printf("rx_time err=%d,%d,%d\r\n",stimestructure.Hours,stimestructure.Minutes,stimestructure.Seconds);//锟斤拷印锟斤拷锟秸筹拷锟斤拷
		//	return ;
		//}
		//printf("rx_time=%d,%d,%d,%d\r\n",stimestructure.Hours,stimestructure.Minutes,stimestructure.Seconds,rtc_alarm_flag);//锟斤拷印锟斤拷锟秸筹拷锟斤拷

		
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
  
#if 0
	taskENTER_CRITICAL();
  	App_Printf("PrintfTask -- Software Version : %s \r\n", MCU_VERSION);
	App_Printf("=================================================\r\n");
	App_Printf("任务名	    任务状态 优先级   剩余栈 任务序号\r\n");
	vTaskList((char *)&pcWriteBuffer);
	App_Printf("%s\r\n", pcWriteBuffer);
	
	App_Printf("\r\n任务名		 运行计数		  使用率\r\n");
	vTaskGetRunTimeStats((char *)&pcWriteBuffer);
	App_Printf("%s\r\n", pcWriteBuffer);
	taskEXIT_CRITICAL();


#endif
    osDelay(500);
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
	
	//if(F_4ms_Val)
	{
		//App_Printf("Task_4ms_Pro -- Software Version : %s \r\n", MCU_VERSION);
		//F_4ms_Clr;
  		Task_4ms_Pro();
	}
    osDelay(4);
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
	//if(F_8ms_Val)
	{
		//App_Printf("Task_8ms_Pro -- Software Version : %s \r\n", MCU_VERSION);
		//F_8ms_Clr;
	  	Task_8ms_Pro();
	}
    osDelay(8);
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
		static U8 F_FLAG;
	//if(F_16ms_Val)
	{
		//App_Printf("Task_16ms_Pro -- Software Version : %s \r\n", MCU_VERSION);
		//F_16ms_Clr;
		Task_16ms_Pro();
		//if(F_FLAG)	
		{
			//	F_FLAG = 0;
			//HAL_GPIO_WritePin(LED1_GPIO_Port, LED_CTRL1_Pin, GPIO_PIN_RESET);
		}
		//else
		{
			//	F_FLAG = 1;
			//HAL_GPIO_WritePin(LED1_GPIO_Port, LED_CTRL1_Pin, GPIO_PIN_SET);
		}		
	}
    osDelay(16);
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
	//if(F_100ms_Val)
	{
		//App_Printf("Task_100ms_Pro -- Software Version : %s \r\n", MCU_VERSION);
		//F_100ms_Clr;
		Task_100ms_Pro();
	}
    osDelay(100);
  }
  /* USER CODE END StartTask_100ms_Pro */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
