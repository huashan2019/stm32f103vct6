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
#include "usbd_customhid.h" //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Íºï¿½ï¿½ï¿½Í·ï¿½Ä¼ï¿½
extern USBD_HandleTypeDef hUsbDeviceFS; //ï¿½â²¿ï¿½ï¿½ï¿½ï¿½USBï¿½ï¿½ï¿½Íºï¿½ï¿½ï¿½

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
osThreadId myTask02Handle;
osThreadId myTask03Handle;
osThreadId myPrintfTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);
void PrintfTask(void const * argument);

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
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 512);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityNormal, 0, 512);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, StartTask03, osPriorityNormal, 0, 512);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* definition and creation of myPrintfTask */
  osThreadDef(myPrintfTask, PrintfTask, osPriorityBelowNormal, 0, 512);
  myPrintfTaskHandle = osThreadCreate(osThread(myPrintfTask), NULL);

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
    //osDelay(10);
    
  	vTaskDelay(20);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {
	//printf("Task2 -- Software Version : %s \r\n", MCU_VERSION);
	//printf("Code generation tuint8_time : %s %s \r\n", __DATE__, __TIME__);
  	//vTaskDelay(500);
	SPI_FLASH_ReadDeviceID();
  	//vTaskDelay(100);
  	
    //vTaskDelay(20);
	//HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
    //vTaskDelay(50);
	//HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
	//osDelay(1);
	
	vTaskDelay(20);
  }
  
  /* USER CODE END StartTask02 */
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

  uint8_t USB_Tx_Buf[64] = {
                         1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
                         17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,
                         40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64}; 

  /* Infinite loop */
  for(;;)
  {
  
  	  //printf("Task3 -- Software Version : %s \r\n", MCU_VERSION);
  	  //printf("Code generation tuint8_time : %s %s \r\n", __DATE__, __TIME__);
		//USB SEND BUFF
	  //USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, USB_Tx_Buf, sizeof(USB_Tx_Buf));
	  //HAL_Delay(1000);

	  //HAL_UART_Transmit(&huart1, (uint8_t *)"hello DISCO\r\n" , sizeof("hello DISCO\r\n"), 0xFFFF);
	  //vTaskDelay(20);
	  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
	  //vTaskDelay(100);
	  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
	  //osDelay(1);
	  vTaskDelay(20);
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
	uint8_t pcWriteBuffer[200];

/* Infinite loop */
  for(;;)
  {
  
  	//printf("PrintfTask -- Software Version : %s \r\n", MCU_VERSION);
#if 0
	printf("=================================================\r\n");

	printf("\r\ntask_name \tstate\t prior\trtack\t Id\r\n");

	vTaskList((char *)&pcWriteBuffer);

	printf("%s\r\n", pcWriteBuffer);

	 

	printf("\r\ntask_name time_count(10us) usage_pec\r\n");

	vTaskGetRunTimeStats((char *)&pcWriteBuffer);

	printf("%s\r\n", pcWriteBuffer);

#else
	printf("=================================================\r\n");
	printf("ÈÎÎñÃû		ÈÎÎñ×´Ì¬ ÓÅÏÈ¼¶   Ê£ÓàÕ» ÈÎÎñÐòºÅ\r\n");
	vTaskList((char *)&pcWriteBuffer);
	printf("%s\r\n", pcWriteBuffer);
	
	printf("\r\nÈÎÎñÃû		 ÔËÐÐ¼ÆÊý		  Ê¹ÓÃÂÊ\r\n");
	vTaskGetRunTimeStats((char *)&pcWriteBuffer);
	printf("%s\r\n", pcWriteBuffer);


#endif
    vTaskDelay(20);
	//osDelay(10);
  }
  /* USER CODE END PrintfTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
