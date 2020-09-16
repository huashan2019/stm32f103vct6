/*
***************************************************************************************************
**  Copyright   : 
**  Project     : STM32F103VCT6
**  File        : task.c
**  Description : This file is the SYS.
**  Author      : lvhuashan
**  Created on  : 2017.06.30
**  Note        : NULL
***************************************************************************************************
*/
#include "include.h"


///===================================================
void Task_1ms_Pro(void)
{
	
}

void Task_2ms_Pro(void)
{
	
}

void Task_4ms_Pro(void)
{
	TASK_Voltage_Det();
}

void Task_8ms_Pro(void)
{
	TASK_Bt_Pro();
	TASK_Dsp_Pro();
	DSP_Test_Detect();
}

void Task_16ms_Pro(void)
{
	TASK_Amp_Pro();
}

void Task_100ms_Pro(void)
{
	Start_Detect();
	TASK_Power_Pro();
	if(Get_IAP_Mode)
		IAP_Pro();
}


