///=========================
#ifndef __APP_VOLTAGE_H
#define __APP_VOLTAGE_H

#define	N_8V	0
#define	N_9V	1
#define	N_16V	2
#define	N_17V	3

#define	PWRON_VOLT_8V       0x618///0x5E0///
#define	PWRON_VOLT_9V       0x6E0///0x69D///
#define	PWRON_VOLT_16V      0xCA0///0xBC1///
#define	PWRON_VOLT_17V      0xD50///0xC7D///
///20180530  �ߵ�ѹ���ػ��޸ĳ� 17V  18V
#define	PWROFF_VOLT_8V      0x618///0x618ʵ��ֵ8///0x5E0����ֵ8///---
#define	PWROFF_VOLT_9V      0x6E0///0x6E0ʵ��ֵ9///0x69D����ֵ9///
#define	PWROFF_VOLT_16V     0xCA0///0xBF0ʵ��ֵ16///0xBC1����ֵ16///
#define	PWROFF_VOLT_17V     0xD50///0xCA0ʵ��ֵ17///0xC7D����ֵ17///0xD50ʵ��ֵ18///0xD39����ֵ18///



typedef enum
{
	LOW_ERROR,	
	V_NORMAL,	
	HIGHT_ERROR	
}VOLTAGE_STATE;

typedef struct 
{
	SCH_U16 ADC_current;
	SCH_U8 BUTimerOut;
	VOLTAGE_STATE VoltageState;
}Vol_Det_T;
extern Vol_Det_T VolDet;

#define BATTERY_VOLT_DET_AD     	 ADC_CHANNEL_15

extern void TASK_Voltage_Det(void);

#endif
