/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
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

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include "include.h" 
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "semphr.h"
UART_HandleTypeDef huart0;


/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = BT_TX1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(BT_TX1_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = BT_RX1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(BT_RX1_GPIO_Port, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = MCU_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(MCU_TX_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = MCU_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(MCU_RX_GPIO_Port, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, BT_TX1_Pin|BT_RX1_Pin);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, MCU_TX_Pin|MCU_RX_Pin);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
//实现printf函数重定向到串口1，即支持printf信息到USART1
#if 1
#ifdef __GNUC__

/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf

set to "Yes") calls __io_putchar() */

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

#else

#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

#endif /* __GNUC__ */

/**

* @brief Retargets the C library printf function to the USART.

* @param None

* @retval None

*/

PUTCHAR_PROTOTYPE

{

/* Place your implementation of fputc here */
//if(HAL_UART_GetError(&huart2)){
//    USART1->DR = (uint8_t) ch;
//	HAL_UART_Init(&huart2);

//}


#if 0
/* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
{
    /* 堵塞判断串口是否发送完成 */
    while((USART1->SR & 0X40) == 0);

    /* 串口发送完成，将该字符发送 */
    USART1->DR = (uint8_t) ch;

    return ch;
}
#endif
while(HAL_UART_GetState(&huart2) == HAL_UART_STATE_BUSY_TX){}
HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
return ch;

}


/* 串口发送先写缓存，再发送 用sprintf()

char dat[128];
int len;
len = sprintf(dat, "This is a test %d", HAL_GetTick());
HAL_UART_Transmit_IT(&huart2, dat, len);

*/

char dat_buf[128];		//待打印数据Buffer


int wsd_printf(UART_HandleTypeDef huart, const char *fmt, ...)
{	
	int printed;	
	va_list args;	
	va_start(args, fmt);	
	printed = sprintf((char *)dat_buf, fmt, args);	
	//HAL_UART_Transmit_IT(&huart, dat_buf, printed);	
	va_end(args);	
	return printed;
}



/*
*********************************************************************************************************
*	函 数 名: App_Printf
*	功能说明: 线程安全的printf方式		  			  
*	形    参: 同printf的参数。
*             在C中，当无法列出传递函数的所有实参的类型和数目时,可以用省略号指定参数表
*	返 回 值: 无
*********************************************************************************************************
*/
extern	osMutexId_t myMutex01Handle;

void  App_Printf(char *format, ...)
{
    char  buf_str[500 + 1];
    va_list   v_args;


    va_start(v_args, format);
   (void)vsnprintf((char       *)&buf_str[0],
                   (size_t      ) sizeof(buf_str),
                   (char const *) format,
                                  v_args);
    va_end(v_args);

	/* 互斥信号量 */
	//xSemaphoreTake(xMutex, portMAX_DELAY);
	osMutexAcquire(myMutex01Handle,portMAX_DELAY);

    printf("%s", buf_str);
   	//xSemaphoreGive(xMutex);
   	osMutexRelease(myMutex01Handle);
}


#if 0
/*
SW4STM32的实现方式实际上通过重写两个函数来实现的_io_putchar(),_write(),
但是__io_putchar与printf没有直接的联系，而是通过调用_write函数
间接地调用__io_putchar，实际上我们可以直接重写_write函数来?
迪种囟ㄏ颉Ｏ远准模琠write函数实现的是指定长度数据的
写，因此我们可以通过中断方式或者DMA方式来实现非阻塞式
的数据发送，具体可以通过如下方式来重定向：

*/

int _write(int file, char *ptr, int len)
{	
	int DataIdx;
	#if 1
		HAL_UART_Transmit_IT(&huart2, ptr, len);		//STM32 HAL库中断方式发送数据
		return len;
	#else
		for (DataIdx = 0; DataIdx < len; DataIdx++)	
		{		
			__io_putchar(*ptr++);	
		}	
		return len;
	#endif
}
#endif

#else
/**  * 函数功能: 重定向c库函数printf到DEBUG_USARTx  * 输入参数: 无  * 返 回 值: 无  * 说    明：无  */
int fputc(int ch, FILE *f)
	{  
		HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);  
		return ch;
	} /**  * 函数功能: 重定向c库函数getchar,scanf到DEBUG_USARTx  * 输入参数: 无  * 返 回 值: 无  * 说    明：无  */

int fgetc(FILE *f)
	{  
		uint8_t ch = 0;  
		HAL_UART_Receive(&huart2, &ch, 1, HAL_MAX_DELAY);  
		return ch;
	}
#endif
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
