/*
***************************************************************************************************
**  Copyright   : 
**  Project     : STM32F103VCT6
**  File        : app_amp.c  ---   ����
**  Description : 
**  Author      : lvhuashan
**  Created on  : 2017.09.02
**  Note        : NULL
***************************************************************************************************
*/
#include "include.h"
extern osMutexId_t myMutex03Handle;

AMP_T App_Amp;

const SCH_U8 AmpChipAddr[MAX_AMP_TYPE]=
{
	0xdc,
	0xda,
	0xde,
	0xd4,
};
const pfunction AmpDllLoader[MAX_AMP_TYPE]=
{///SCH_NULL
	Amp8541_DLL_Loader,
	Amp8541_DLL_Loader,
	Amp8541_DLL_Loader,
	Amp8541_DLL_Loader
};
void AmpMute(SCH_BOOL OnOff)
{
	if(App_Amp.AmpState==AMP_NORMAL)
	{
		if(App_Amp.pAmpMute)
			App_Amp.pAmpMute(OnOff);
	}
}
SCH_BOOL AmpTypeCheck(void)
{
	SCH_U8 i;
	App_Amp.AmpTypeCheck = FALSE;
	
	//osMutexAcquire(myMutex03Handle,portMAX_DELAY);
	for(i=0;i<MAX_AMP_TYPE;i++)
	{
		if(I2C0_IsFindAddr(AmpChipAddr[i]))
		{
			if(App_Amp.AmpTypeCheck == FALSE)
			{
				App_Amp.AmpAddr = AmpChipAddr[i];
				App_Printf("AmpAddrCheck OK --- %X \r\n",App_Amp.AmpAddr);
				App_Amp.AmpTypeCheck = TRUE;
				App_Amp.AmpType = (_AmpSysType_t)i;
			}
			else
			{
				App_Amp.AmpAddr1 = AmpChipAddr[i];
				App_Amp.AmpType1 = (_AmpSysType_t)i;
				App_Printf("AmpAddrCheck OK --- %X \r\n",App_Amp.AmpAddr1);
				break;
			}
		}
	}
	
	//osMutexRelease(myMutex03Handle);
	if(App_Amp.AmpType == MAX_AMP_TYPE)
	{
		App_Printf("AmpAddrCheck fail \r\n");
		return FALSE;
	}
	if(AmpDllLoader[App_Amp.AmpType])
		(*AmpDllLoader[App_Amp.AmpType])();
	return TRUE;
}
/********************************************************************************
**  Function      : TASK_Amp_Pro
**  Author        : 
**  Created on    : 
**  Description   : 16MSִ��һ��
**  Return        : 
********************************************************************************/
void TASK_Amp_Pro(void)
{
#if 1
	switch(App_Amp.AmpState)
	{
		case AMP_IDLE:
			break;
		case AMP_ENABLE:
			///if(App_Radio.RadioPwrState == RADIO_NORMAL)
			{
				App_Amp.AmpState = AMP_CHECK;
				App_Amp.AmpAddr = AmpChipAddr[0];
				App_Amp.AmpType = (_AmpSysType_t)0;
				App_Amp.AmpAddr = AmpChipAddr[1];
				App_Amp.AmpType = (_AmpSysType_t)1;
				TurnOn_AMP;
			}
			break;
		case AMP_CHECK:
			if(AmpTypeCheck())
			{
				if(App_Amp.pAmpInit)
					App_Amp.pAmpInit();
				App_Amp.AmpState = AMP_NORMAL;
			}
			break;
		case AMP_NORMAL:
			break;
		case AMP_DISABLE:
			if(App_Amp.pAmpMute)
				App_Amp.pAmpMute(ON);
			TurnOff_AMP;
			App_Amp.AmpState = AMP_CLOSE;
			break;
		case AMP_CLOSE:
			break;
		default:break;
	}
#endif
}

