/*
***************************************************************************************************
**  Copyright   : 
**  Project     : STM32F103VCT6
**  File        : system.c
**  Description : This file is the SYS.
**  Author      : lvhuashan
**  Created on  : 2017.06.30
**  Note        : NULL
***************************************************************************************************
*/
#include "include.h"

/********************************************************************************
**  Function	: SysDataInit
**  Author		: lvhuashan
**  Created on	: 20160623
**  Description	: 
**  Return		: NULL
********************************************************************************/
SYS_T Sys;
void SysDataInit(void)
{
	sch_memset(&Sys,0x00,sizeof(Sys));
	Set_SYS_MUTE;
	Set_VolErr_Flag;
	Set_START_Flag;
	///Set_ACC_Has;
}

void SysTick_Handler1(void)
{

	Sys.TimeCounter++;
	/*F_1ms_Set;
	if(Sys.TimeCounter%2==0)
		F_2ms_Set;
	if(Sys.TimeCounter%4==0)*/
		F_4ms_Set;
	if(Sys.TimeCounter%2==0)
		F_8ms_Set;
	if(Sys.TimeCounter%4==0)
		F_16ms_Set;
	if(Sys.TimeCounter%8==0)
		F_32ms_Set;
	if(Sys.TimeCounter%25==0)
		F_100ms_Set;
	if(Sys.TimeCounter==3000)
		Sys.TimeCounter=0;

}



