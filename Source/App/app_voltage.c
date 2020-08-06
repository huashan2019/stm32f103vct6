/*
***************************************************************************************************
**  Copyright   : 
**  Project     : STM32F103VCT6
**  File        : APP_voltage.c  ---   B+���
**  Description : 
**  Author      : lvhuashan
**  Created on  : 2020.08.05
**  Note        : NULL
***************************************************************************************************
*/

#include "include.h"

Vol_Det_T VolDet;
extern unsigned int AD_DMA[2];

const SCH_U16 VoltageTable[2][4]=
{
	{PWROFF_VOLT_8V,PWROFF_VOLT_9V,PWROFF_VOLT_16V,PWROFF_VOLT_17V},
	{PWRON_VOLT_8V, PWRON_VOLT_9V, PWRON_VOLT_16V, PWRON_VOLT_17V}
};

void TASK_Voltage_Init(void)
{
	sch_memset(&VolDet, 0x00, sizeof(VolDet));
}

void EmergencyPowerDown(void)
{
	Printf("voltage error \n");
	ClearMessage(ARM_MODULE);
	PostMessage(POWER_MODULE,EVT_POWER_OFF,POWEROFF_FROM_VOLTAGE);
}

#define BU_CONFIRM_TIMER	T120MS_4
void TASK_Voltage_Det(void)
{
	VolDet.ADC_current = AD_DMA[1];

	if(!VolDet.ADC_current)
		return;
	
	//printf("AD_DMA_0 = %d\r\n",AD_DMA[0]);
	//printf("AD_DMA_1 = %d\r\n",AD_DMA[1]);
	//printf("\r\n");

	
	if(VolDet.BUTimerOut)
		VolDet.BUTimerOut--;
	if(VolDet.ADC_current<VoltageTable[Get_SysPower_Flag][N_8V])///9V
	{	 
		if(VolDet.VoltageState!=LOW_ERROR||Get_VolErr_Flag==NORMAL)
		{    
			VolDet.VoltageState=LOW_ERROR;
			Get_VolErr_Flag=ERROR;
			EmergencyPowerDown();
		}
		VolDet.BUTimerOut=BU_CONFIRM_TIMER;
	}
	else if(VolDet.ADC_current<VoltageTable[Get_SysPower_Flag][N_9V])///
	{	
		VolDet.BUTimerOut=BU_CONFIRM_TIMER;
	}
	else if(VolDet.ADC_current<=VoltageTable[Get_SysPower_Flag][N_16V])///
	{
		if(VolDet.BUTimerOut==0)
		{
			//printf("voltage normal \n");
			//VolDet.VoltageState=V_NORMAL;
			//Get_VolErr_Flag=NORMAL;
		}	
	}
	else if(VolDet.ADC_current<VoltageTable[Get_SysPower_Flag][N_17V])///
	{	
		VolDet.BUTimerOut=BU_CONFIRM_TIMER;
	}
	else
	{
		if(VolDet.VoltageState!=HIGHT_ERROR||Get_VolErr_Flag==NORMAL)
		{
			VolDet.VoltageState=HIGHT_ERROR;
			Get_VolErr_Flag=ERROR;
			EmergencyPowerDown();
		}
		VolDet.BUTimerOut=BU_CONFIRM_TIMER;
	}
}


