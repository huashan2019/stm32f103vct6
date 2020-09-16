/*
***************************************************************************************************
**  Copyright   : 
**  Project     : STM32F103VCT6
**  File        : sch_common.c
**  Description : This file is the SCH.
**  Author      : lvhuashan
**  Created on  : 2017.06.30
**  Note        : NULL
***************************************************************************************************
*/
#include "include.h"



/*************************************************************************************
**  Function    : SysWaitXXX
**  Author		: lvhuashan
**  Created on	: 
**  Description	: �ȴ�ʱ�� Delay
**  Return		: NULL
**************************************************************************************/
void SysWait1Us(void)
{
#if 1
#if 1
	SCH_U8 index = 4;
	while(index--)
		SCH_NOP;
	SCH_NOP;SCH_NOP;SCH_NOP;
	SCH_NOP;SCH_NOP;SCH_NOP;
	SCH_NOP;SCH_NOP;SCH_NOP;
	SCH_NOP;SCH_NOP;SCH_NOP;
#else
	SCH_NOP;SCH_NOP;SCH_NOP;
	SCH_NOP;SCH_NOP;SCH_NOP;
	SCH_NOP;SCH_NOP;SCH_NOP;
	SCH_NOP;SCH_NOP;SCH_NOP;
	SCH_NOP;SCH_NOP;SCH_NOP;
	SCH_NOP;SCH_NOP;SCH_NOP;
	SCH_NOP;SCH_NOP;SCH_NOP;
	SCH_NOP;SCH_NOP;SCH_NOP;
	SCH_NOP;SCH_NOP;SCH_NOP;
#endif
#endif
}
void SysWaitUs(SCH_U32 Time)
{
	while(Time--)
		SysWait1Us();
}
void SysWaitMs(SCH_U32 Time)
{
	while(Time--)
		SysWaitUs(1000);
}
/*************************************************************************************
**  Function    : GetMax GetMin
**  Author		: lvhuashan
**  Created on	: 20170608
**  Description	: �Ƚϴ�С����
**  Return		: NULL
**************************************************************************************/
SCH_U32 GetMax(SCH_U32 m,SCH_U32 n)
{
	return (m>n)?m:n;
}
SCH_U32 GetMin(SCH_U32 m,SCH_U32 n)
{
	return (m>n)?n:m;
}
SCH_U32 LimitMaxMin(SCH_U32 min,SCH_U32 Data,SCH_U32 max)
{
	Data = GetMax(min,Data);
	Data = GetMin(max,Data);
	return Data;
}
SCH_U8 LimitMaxMin_U8(SCH_U8 min,SCH_U8 Data,SCH_U8 max)
{
	Data = (min>Data)?min:Data;
	Data = (max<Data)?max:Data;
	return Data;
}
SCH_S8 LimitMaxMin_S8(SCH_S8 min,SCH_S8 Data,SCH_S8 max)
{
	Data = (min>Data)?min:Data;
	Data = (max<Data)?max:Data;
	return Data;
}
/*************************************************************************************
**  Function    : sch_memxxx
**  Author		: lvhuashan
**  Created on	: 20170608
**  Description	: ��������
**  Return		: NULL
**************************************************************************************/
void sch_memset(void *s,const SCH_U8 c,SCH_U16 n)  
{
    SCH_U8 *su = (SCH_U8 *)s;
	while(n--)
	{
		*su++ = c;
	}
}  
void sch_memcpy(void *to,  void const *from, SCH_U16 n)  
{
	SCH_U8 *t = (SCH_U8 *)to;
	SCH_U8 *f = (SCH_U8 *)from;
	while(n--)
	{
		*t++ = *f++;
	}
}
SCH_U8 sch_compare(void const *COM_A, void const *COM_B, SCH_U16 n)  
{
	SCH_U8 *t = (SCH_U8 *)COM_A;
	SCH_U8 *f = (SCH_U8 *)COM_B;
	while(n--)
	{
		if(*t++ != *f++)
			return FALSE;
	}
	return TRUE;
}
/*************************************************************************************
**  Function    : GetCheckData 
**  Author		: lvhuashan
**  Created on	: 20170608
**  Description	: ��ȡУ����
**  Return		: NULL
**************************************************************************************/
SCH_U8 GetCheckData_Add(SCH_U8 *data, SCH_U8 Len)
{
	SCH_U8 index=0;
	while(Len--)
		index += *data++;
	return index;
}
SCH_U8 GetCheckData_Xor(SCH_U8 *data, SCH_U8 Len)
{
	SCH_U8 index=0;
	while(Len--)
		index ^= *data++;
	return index;
}
/*************************************************************************************
**  Function    :  IsInXXX
**  Author		: lvhuashan
**  Created on	: 20170703
**  Description	: �ж�һ�������Ƿ���ĳ����Χ��
**  Return		: NULL
**************************************************************************************/
SCH_BOOL IsInRange(SCH_U32 min,SCH_U32 data,SCH_U32 max)
{
	if(min > max)
		return FALSE;
	return (data >= min && data <= max) ? TRUE : FALSE;
}
SCH_BOOL IsInData(SCH_U32 data0,SCH_U32 data1,SCH_U32 step)
{
	SCH_U32 index;
	index = (data0 > data1) ? (data0 - data1) : (data1 - data0);
	return (index <= step) ? TRUE : FALSE;
}
/*************************************************************************************
**  Function    : GetAverage_UXX
**  Author		: lvhuashan
**  Created on	: 20170803
**  Description	: ��һ�������ƽ��ֵ
**  Return		: NULL
**************************************************************************************/
SCH_U16 GetAverage_U16(SCH_U16 *pTable, SCH_U8 Array_Cnt)
{
	SCH_U32 Data = 0x00000000;
	SCH_U8 index;
	for(index=0;index<Array_Cnt;index++)
	{
		Data += pTable[index];
	}
	return (SCH_U16)(Data/Array_Cnt);
}
SCH_U8 GetAverage_U8(SCH_U8 *pTable, SCH_U8 Array_Cnt)
{
	SCH_U16 Data = 0x0000;
	SCH_U8 index;
	for(index=0;index<Array_Cnt;index++)
	{
		Data += pTable[index];
	}
	return (SCH_U8)(Data/Array_Cnt);
}
/*************************************************************************************
**  Function    : IsInArray_UXX
**  Author		: lvhuashan
**  Created on	: 20170803
**  Description	: ��һ�����������λ��(�±�)
**  Return		: NULL
**************************************************************************************/
SCH_BOOL IsInArray_U8(SCH_U8 Data,SCH_U8 *pTable,SCH_U8 Array_Cnt,SCH_U8 *num)
{
	SCH_U8 index;
	for(index=0;index<Array_Cnt;index++)
	{
		if(pTable[index] == Data)
		{
			*num = index;
			return TRUE;
		}
	}
	return FALSE;
}
SCH_BOOL IsInArray_U16(SCH_U16 Data,SCH_U16 *pTable,SCH_U8 Array_Cnt,SCH_U8 *num)
{
	SCH_U8 index;
	for(index=0;index<Array_Cnt;index++)
	{
		if(pTable[index] == Data)
		{
			*num = index;
			return TRUE;
		}
	}
	return FALSE;
}
/*************************************************************************************
**  Function    : ExchangeTwoVariable_UXX
**  Author		: lvhuashan
**  Created on	: 20180131
**  Description	: ��������������ֵ
**  Return		: NULL
**************************************************************************************/
void ExchangeTwoVariable_U8(SCH_U8 *Data0,SCH_U8 *Data1)
{
	*Data0 ^= *Data1;
	*Data1 ^= *Data0;
	*Data0 ^= *Data1;
}
void ExchangeTwoVariable_U16(SCH_U16 *Data0,SCH_U16 *Data1)
{
	*Data0 ^= *Data1;
	*Data1 ^= *Data0;
	*Data0 ^= *Data1;
}
void ExchangeTwoVariable_U32(SCH_U32 *Data0,SCH_U32 *Data1)
{
	*Data0 ^= *Data1;
	*Data1 ^= *Data0;
	*Data0 ^= *Data1;
}








