/*
***************************************************************************************************
**  Copyright   : 
**  Project     : STM32F103VCT6
**  File        : bsp.c  ---   
**  Description : 
**  Author      : lvhuashan
**  Created on  : 2017.08.10
**  Note        : NULL
***************************************************************************************************
*/
#include "include.h"

////==============================================================================================Relocation ===================
#define RELOCATION_ADDRESS               0x4000 ///16K
void Bsp_Relocation_Int(void)
{
	//write_vtor(RELOCATION_ADDRESS);
}
////=================================================================================================================
void Bsp_Clock_Init(void)
{
	//sysinit();///40M
	/*ICS_ConfigType sICSConfig = {0};
	sICSConfig.u8ClkMode = ICS_CLK_MODE_FEE;
	sICSConfig.oscConfig.bRange = 1;          
	sICSConfig.oscConfig.bGain = 1;
	sICSConfig.oscConfig.bStopEnable = 1;
    sICSConfig.oscConfig.bEnable = 1;      
    sICSConfig.u32ClkFreq = EXT_CLK_FREQ_KHZ;
	ICS_Init(&sICSConfig);*/
}

////=================================================================================================================
void Bsp_SysTick_Init(void)
{
	SysTick->CTRL  |= SysTick_CTRL_ENABLE_Msk; 
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
	MX_RTC_Init();
}
void Bsp_SysTick_Close(void)
{
	SysTick->CTRL  &= ~SysTick_CTRL_ENABLE_Msk; 
	SysTick->VAL = 0x00;   //���val,��ն�ʱ��
	//RCC_HCLKConfig(RCC_SYSCLK_Div8); 
	//RCC_PCLK2Config(RCC_HCLK_Div8); 			
	//RCC_PCLK1Config(RCC_HCLK_Div8);
	/* Select HSI as system clock source */
	//RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
	/* Wait till HSI is used as system clock source */
	//while(RCC_GetSYSCLKSource() != 0x00);

	///FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Disable);  
	///FLASH_SetLatency(FLASH_Latency_0);
}

////=================================================================================================================
void Bsp_GPIO_Init(void)
{	
	//GPIO_DeInit(GPIOA);
	//GPIO_DeInit(GPIOB);
	//GPIO_DeInit(GPIOC);
	HAL_GPIO_DeInit(GPIOA,0xFFFFFFFF);
	HAL_GPIO_DeInit(GPIOB,0xFFFFFFFF);
	HAL_GPIO_DeInit(GPIOC,0xFFFFFFFF);
	HAL_GPIO_DeInit(GPIOD,0xFFFFFFFF);
	HAL_GPIO_DeInit(GPIOE,0xFFFFFFFF);
	HAL_GPIO_DeInit(GPIOF,0xFFFFFFFF);
	HAL_GPIO_DeInit(GPIOG,0xFFFFFFFF);
	GPIOInit();
}
////=================================================================================================================
/********************************************************************************
**  Function	: WDOG
**  Author		: lvhuashan
**  Created on	: 20170406
**  Description	: 
**  Return		: NULL
********************************************************************************/
#ifdef WDOG_EN
void Bsp_WDOG_Init(void)
{
#if 0
	WDOG_ConfigType t_WDOG_Config;
	t_WDOG_Config.sBits.bWaitEnable   = 1;
	t_WDOG_Config.sBits.bStopEnable   = 0;  
	t_WDOG_Config.sBits.bDbgEnable    = 0; 
	t_WDOG_Config.sBits.bUpdateEnable = 1; 
	t_WDOG_Config.sBits.bDisable      = 0;                     /* enable WDOG */
	t_WDOG_Config.sBits.bClkSrc       = WDOG_CLK_INTERNAL_1KHZ;/*  */
	t_WDOG_Config.u16TimeOut          = 4000;                  /* 1s */
	t_WDOG_Config.u16WinTime          = 0;                     /*  */
	WDOG_Init(&t_WDOG_Config);                                 /*  */
	WDOG_Enable();
#endif
}
void FeedDog(void)
{
	//WDOG_Feed();
}
void Bsp_WDOG_Close(void)
{
	///WDOG_DeInit();
	///WDOG_Disable();
	///WDOG_DisableWDOGEnableUpdate();
}
#endif
////=================================================================================================================
void Bsp_RTC_Init(void)
{
	///SysRtcInit();
}
////=================================================================================================================
void Bsp_PIT_Init(void)
{
#if 0
    PIT_ConfigType  t_PIT_Config;       
	t_PIT_Config.u32LoadValue = 200000; 
    t_PIT_Config.bFreeze      = 0;     
    t_PIT_Config.bModuleDis   = 0;     /* Enable PIT module */
    t_PIT_Config.bInterruptEn = 1;     
    t_PIT_Config.bChainMode   = 1;       
    t_PIT_Config.bTimerEn     = 1;     
    PIT_Init (PIT_CHANNEL0, &t_PIT_Config);
#endif
}
void Bsp_TIM_Init(void)
{
	///Bsp_PIT_Init();
	///FTM0_PWM_Init();////CCFL����PWM
}
////=================================================================================================================
#define UART0_BAUDRATE       115200///
#define UART1_BAUDRATE       115200///
#define UART2_BAUDRATE       115200///
void Bsp_UART_Init(void)
{
	SysUartInit(SCH_Uart0,UART0_BAUDRATE);
	SysUartInit(SCH_Uart1,UART1_BAUDRATE);
	SysUartInit(SCH_Uart2,UART2_BAUDRATE);
}
////=================================================================================================================
#define SPI1_BAUDRATE       400000///* bps */
#define SPI2_BAUDRATE       400000///
#define SPI3_BAUDRATE       400000///

void Bsp_SPI_Init(void)
{
	SysSpiInit(SCH_Spi1,SPI1_BAUDRATE);
	SysSpiInit(SCH_Spi2,SPI2_BAUDRATE);
	SysSpiInit(SCH_Spi3,SPI3_BAUDRATE);
}
////=================================================================================================================
void Bsp_CAN_Init(void)
{
	///SysCanInit(SCH_Can0);
}
////=================================================================================================================
void Bsp_ADC_Init(void)
{
	//SysAdcInit();
}
////=================================================================================================================
void Bsp_I2C_Init(void)
{
	//I2C0Init();
	//I2C1Init();
}
////=================================================================================================================
void Bsp_FLASH_Init(void)
{
	//SysFlashInit();
}



