/*
***************************************************************************************************
**  Copyright   : 
**  Project     : STM32F103VCT6
**  File        : app_debug.c  ---  
**  Description : 
**  Author      : lvhuashan
**  Created on  : 2018.10.19
**  Note        : NULL
***************************************************************************************************
*/
#include "include.h"



void Debug_CMD(SCH_U8 cmd)
{
	switch(cmd) 
	{
		case 0x00:
			break;
		case 0x01:///dsp��ʼ��
			default_download_IC_1();
			break;
		case 0x02:///dsp��λ
			DSP_RESET_HOLD;
			SysWaitMs(500);
			DSP_RESET_RELEASE;
			break;
		case 0x03:///ad1938��λ
			AD1938_RESET_HOLD;
			SysWaitMs(500);
			AD1938_RESET_RELEASE;
			break;
		case 0x04:///ad1978��λ
			AD1978_RESET_HOLD;
			SysWaitMs(500);
			AD1978_RESET_RELEASE;
			break;
		case 0x05:///BT��λ
			BT_RESET_HOLD;
			SysWaitMs(500);
			BT_RESET_RELEASE;
			break;
		case 0x06:///ARM��λ
			break;
		case 0x10:
			{
				SCH_U8 index;
				for(index=0; index <= DSP_MODE_CNT; index++)
				{
					Flash_Dsp_SE(index);
					FeedDog();
					SysWaitMs(8);
				}
			}
			break;
		default:break;
	}
}





















