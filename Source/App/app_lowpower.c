/*
***************************************************************************************************
**  Copyright   : 
**  Project     : STM32F103VCT6
**  File        : APP_lowpower.c  ---   �͹���
**  Description : 
**  Author      : lvhuashan
**  Created on  : 2020.08.05
**  Note        : NULL
***************************************************************************************************
*/

#include "include.h"

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim5;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;
DMA_HandleTypeDef hdma_usart2_tx;
DMA_HandleTypeDef hdma_usart2_rx;

void SysWakeUpInit_FromACC(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/*Configure GPIO pins : PC0  */
	GPIO_InitStruct.Pin = GPIO_ACC_DECT;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(IO_ACC, &GPIO_InitStruct);
	
	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI0_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
void SysWakeUpExit_FromACC(void)
{
	ACC_Init();
}

void SysWakeUpInit_FromKBI(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/*Configure GPIO pins : PB1  */
	GPIO_InitStruct.Pin = GPIO_AUDIO_DECT;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(IO_AUDIO, &GPIO_InitStruct);
	
	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI1_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);

}
void SysWakeUpExit_FromKBI(void)
{
	Audio_Init();
}

void SysWakeUpInit_FromRTC(void)
{
	
}
void SysWakeUpExit_FromRTC(void)
{
	if(Get_RtcWorkStatus == ON)
	HAL_RTC_DeactivateAlarm(&hrtc,RTC_ALARM_A);
}
void SysWakeUp_SetAlarm(SCH_U8 index)
{

	if(Get_RtcWorkStatus == ON)
	{
	    /*##-1- Configure the RTC Alarm peripheral #################################*/
	    /* Set Alarm to 00:00:00+index
	       RTC Alarm Generation: Alarm on Hours, Minutes and Seconds */
		HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BIN);
		stimestructure.Seconds = stimestructure.Seconds+index;
		
	    salarmstructure.Alarm = RTC_ALARM_A;
	    salarmstructure.AlarmTime.Hours = stimestructure.Hours;
	    salarmstructure.AlarmTime.Minutes = stimestructure.Minutes;
	    salarmstructure.AlarmTime.Seconds = stimestructure.Seconds;

	    if(HAL_RTC_SetAlarm_IT(&hrtc,&salarmstructure,RTC_FORMAT_BCD) != HAL_OK)
	    {
	        /* Initialization Error */
	        Error_Handler();
	    }
		
	}
}


/*******************************************************************************\
* Function    : Reset I/O.          											*
* Input       :                                                                 *
* Output      :                                                                 *
* description :ACC off mode,reduce power consumption to lowest,reset all I/O	*
\*-----------------------------------------------------------------------------*/
void ResetIO(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin=GPIO_PIN_All;
	GPIO_InitStructure.Mode=GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOA,&GPIO_InitStructure);
	HAL_GPIO_Init(GPIOB,&GPIO_InitStructure);
	HAL_GPIO_Init(GPIOC,&GPIO_InitStructure);
	HAL_GPIO_Init(GPIOD,&GPIO_InitStructure);
	HAL_GPIO_Init(GPIOE,&GPIO_InitStructure);
	HAL_GPIO_Init(GPIOF,&GPIO_InitStructure);
	HAL_GPIO_Init(GPIOG,&GPIO_InitStructure);
}
void SysLowPowerInit(void)
{
	ResetIO();
	HAL_TIM_Base_DeInit(&htim1);
	HAL_TIM_Base_DeInit(&htim5);
	HAL_UART_MspDeInit(&huart1);
	HAL_UART_MspDeInit(&huart2);
	HAL_DMA_DeInit(&hdma_adc1);
	HAL_DMA_DeInit(&hdma_usart2_rx);
	HAL_DMA_DeInit(&hdma_usart2_tx);
	Bsp_SysTick_Close();
	///SysRtcExit();
	Bsp_WDOG_Close();
	SysUartExit(SCH_Uart0);
	SysUartExit(SCH_Uart1);
	SysUartExit(SCH_Uart2);
	SysSpiExit(SCH_Spi1);
	SysSpiExit(SCH_Spi2);
	SysSpiExit(SCH_Spi3);
	///SysCanExit(SCH_Can0);
	///FTM0_PWM_Exit();
	SysAdcExit();
}
void SysLowPowerExit(void)
{
	Bsp_SysTick_Init();
	///Bsp_RTC_Init();
	Bsp_WDOG_Init();
	Bsp_UART_Init();
	Bsp_SPI_Init();
	///Bsp_CAN_Init();
	///Bsp_TIM_Init();
	Bsp_ADC_Init();
	Print_Init();
}
/**************************************************************************************
* FunctionName   : TASK_AccOff_Pro()
* Description    : ������   ---     lowpower
* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
void TASK_AccOff_Pro(void)
{
	while(Get_SLEEP_Mode)
	{
		Printf("Enter lowerpowermode \n");
		FeedDog();
		SysLowPowerInit();
		Clr_AccWakeUP_Flag;
		SysWakeUpInit_FromACC();
	#if AUDIO_START == ENABLE
		if(!Get_ACC_Has)
			SysWakeUpInit_FromKBI();
	#endif
		SysWakeUpInit_FromRTC();
		while(!Get_AccWakeUP_Flag)
		{
			FeedDog();
			SysWakeUp_SetAlarm(2);
			__DSB();
			
			if((Get_ACC_Has&&ACC_DET_LVOFF)||(!Get_ACC_Has&&AUDIO_DET_LVOFF))
				HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFI);
			if(AUDIO_DET_LVON||ACC_DET_LVON)
				Set_AccWakeUP_Flag;
		}
		portENTER_CRITICAL();
		FeedDog();
		SysWakeUpExit_FromRTC();
	#if AUDIO_START == ENABLE
		if(!Get_ACC_Has)
			SysWakeUpExit_FromKBI();
	#endif
		SysWakeUpExit_FromACC();
		SysLowPowerExit();
		Clr_SLEEP_Mode;
		Printf("Enter Normalmode \n");
		portEXIT_CRITICAL();
		return;
	}
}




