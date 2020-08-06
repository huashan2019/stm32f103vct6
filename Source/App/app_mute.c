/*
***************************************************************************************************
**  Copyright   : 
**  Project     : STM32F103VCT6
**  File        : app_mute.c  ---   ����
**  Description : 
**  Author      : lvhuashan
**  Created on  : 2020.08.05
**  Note        : NULL
***************************************************************************************************
*/
#include "include.h"
/********************************************************************************
**  Function	: MUTE
**  Author		: 
**  Created on	: 20160909
**  Description	:
**  Return		: 
********************************************************************************/
void MUTE_IO_Init(void)
{///===
	//GPIO_PinInit(GPIO_MUTE_CTL, GPIO_PinOutput);
}
void MUTE_Ctl(SCH_BOOL OnOff)
{
	if(OnOff == ON)
	{
		TurnOn_MUTE;
		if(!Get_MUTE_Flag)
			AmpMute(ON);
		Set_MUTE_Flag;
	}
	else
	{
		TurnOff_MUTE;
		if(Get_MUTE_Flag)
			AmpMute(OFF);
		Clr_MUTE_Flag;
	}
}
///==================================================================================================
MUTE_STATE Mute_State;
void AudioMute(MUTE_T MUTE_Type)
{
	if(MUTE_Type==SOFTON)
	{
		///AdjustVolumeStepper(SLOW_DOWN);
	}
	else if(MUTE_Type== SOFTOFF)
	{
		///AdjustVolumeStepper(SLOW_UP);
	}	
	else if(MUTE_Type== HARDON)
	{
		MUTE_Ctl(ON);
	}
	else if(MUTE_Type==HARDOFF)
	{
		MUTE_Ctl(OFF);
	}
}

