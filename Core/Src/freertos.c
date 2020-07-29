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

UART_HandleTypeDef huart1;

uint8_t Data1[4]={0x9f,0xff,0xff,0xff};
uint8_t Data2[2]={0x00,0x00};
uint8_t Rxdata[2];

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myTask03Handle;
osThreadId myPrintfTaskHandle;
osThreadId myTask_4ms_ProHandle;
osThreadId myTask_8ms_ProHandle;
osThreadId myTask_16ms_ProHandle;
osThreadId myTask_100ms_PrHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartTask03(void const * argument);
void PrintfTask(void const * argument);
void StartTask_4ms_Pro(void const * argument);
void StartTask_8ms_Pro(void const * argument);
void StartTask_16ms_Pro(void const * argument);
void StartTask_100ms_Pro(void const * argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

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

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

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
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, StartTask03, osPriorityNormal, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* definition and creation of myPrintfTask */
  osThreadDef(myPrintfTask, PrintfTask, osPriorityBelowNormal, 0, 256);
  myPrintfTaskHandle = osThreadCreate(osThread(myPrintfTask), NULL);

  /* definition and creation of myTask_4ms_Pro */
  osThreadDef(myTask_4ms_Pro, StartTask_4ms_Pro, osPriorityIdle, 0, 256);
  myTask_4ms_ProHandle = osThreadCreate(osThread(myTask_4ms_Pro), NULL);

  /* definition and creation of myTask_8ms_Pro */
  osThreadDef(myTask_8ms_Pro, StartTask_8ms_Pro, osPriorityIdle, 0, 256);
  myTask_8ms_ProHandle = osThreadCreate(osThread(myTask_8ms_Pro), NULL);

  /* definition and creation of myTask_16ms_Pro */
  osThreadDef(myTask_16ms_Pro, StartTask_16ms_Pro, osPriorityIdle, 0, 256);
  myTask_16ms_ProHandle = osThreadCreate(osThread(myTask_16ms_Pro), NULL);

  /* definition and creation of myTask_100ms_Pr */
  osThreadDef(myTask_100ms_Pr, StartTask_100ms_Pro, osPriorityIdle, 0, 256);
  myTask_100ms_PrHandle = osThreadCreate(osThread(myTask_100ms_Pr), NULL);

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
void StartDefaultTask(void const * argument)
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
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */


  /* Infinite loop */
  for(;;)
  {
  
		//printf("Task3 -- Software Version : %s \r\n", MCU_VERSION);
		//printf("Code generation tuint8_time : %s %s \r\n", __DATE__, __TIME__);
		//USB SEND BUFF
		//USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, USB_Tx_Buf, sizeof(USB_Tx_Buf));
		//HAL_Delay(1000);

	  vTaskDelay(200);
	  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
	  vTaskDelay(200);
	  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
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
void PrintfTask(void const * argument)
{
  /* USER CODE BEGIN PrintfTask */
	uint8_t pcWriteBuffer[500];

/* Infinite loop */
  for(;;)
  {
  
  	//printf("PrintfTask -- Software Version : %s \r\n", MCU_VERSION);
#if 0

	printf("=================================================\r\n");
	printf("任务名	    任务状态 优先级   剩余栈 任务序号\r\n");
	vTaskList((char *)&pcWriteBuffer);
	printf("%s\r\n", pcWriteBuffer);
	
	printf("\r\n任务名		运行计数	使用率\r\n");
	vTaskGetRunTimeStats((char *)&pcWriteBuffer);
	printf("%s\r\n", pcWriteBuffer);


#endif
    vTaskDelay(20);
    osDelay(1);
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
void StartTask_4ms_Pro(void const * argument)
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
void StartTask_8ms_Pro(void const * argument)
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
void StartTask_16ms_Pro(void const * argument)
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
void StartTask_100ms_Pro(void const * argument)
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
