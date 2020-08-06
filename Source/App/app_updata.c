/*
***************************************************************************************************
**  Copyright   : 
**  Project     : STM32F103VCT6
**  File        : APP_updata.c  ---   ��������
**  Description : 
**  Author      : lvhuashan
**  Created on  : 2020.08.05
**  Note        : NULL
***************************************************************************************************
*/
#include "include.h"

#define BOOTLOADER_ADDRESS             0x00000004
void AppJumpToBootloader(void)
{
	((pfunction)*(SCH_U32 *)BOOTLOADER_ADDRESS)();
	while(1);
}
///===================================================================================================
#define IAP_MODE_DATA                0xAAAA5555
SCH_BOOL Is_IapMode(void)
{
	SCH_U32 IAP_Data;
	Flash_Quick_RD(FLASH_DATA_IAP, &IAP_Data);
	return (IAP_Data == IAP_MODE_DATA) ? TRUE : FALSE;
}
void In_IapMode(void)
{
	Flash_Quick_WR(FLASH_DATA_IAP, IAP_MODE_DATA);
}
void Out_IapMode(void)
{
	Flash_Quick_SE(FLASH_DATA_IAP);
}
/*************************************************************************************
**  Function    : IAP_Pro
**  Author		: lvhuashan
**  Created on	: 20170425
**  Description	: 
**  Return		: NULL
**************************************************************************************/
void IAP_Pro(void)
{
	SCH_INT_DISABLE;
	SysFlashInit();	
	SysUartExit(SCH_Uart0);
	SysUartExit(SCH_Uart1);
	SysUartExit(SCH_Uart2);
	SysSpiExit(SCH_Spi1);
	SysSpiExit(SCH_Spi2);
	SysSpiExit(SCH_Spi3);
	///SysRtcExit();	
	In_IapMode();
	AppJumpToBootloader();
	Clr_IAP_Mode;
}











