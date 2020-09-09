/*
***************************************************************************************************
**  Copyright   : 
**  Project     : STM32F103VCT6
**  File        : sch_queue.c
**  Description : This file is the SCH.
**  Author      : lvhuashan
**  Created on  : 2017.06.30
**  Note        : NULL
***************************************************************************************************
*/
#include "sch_config.h"
#include "FreeRTOS.h"
#include "task.h"

void Queue_Init(QUEUE_T *p_queue)
{
	p_queue->Cnt = 0;
	p_queue->Head = 0;
	p_queue->Tail = 0;
	sch_memset(p_queue->Pbuf, 0x00, p_queue->Qsize*p_queue->Isize);
}
QUE_U16 Queue_Cnt(QUEUE_T *p_queue)
{
	return p_queue->Cnt;
}
QUE_BOOL Queue_IsFull(QUEUE_T *p_queue)
{
	return (p_queue->Cnt == p_queue->Qsize) ? TRUE : FALSE;
}
QUE_BOOL Queue_IsEmpty(QUEUE_T *p_queue)
{
	return (p_queue->Cnt == 0) ? TRUE : FALSE;
}
QUE_BOOL Queue_In(QUEUE_T *p_queue, void *p_data, QUE_U16 Len)
{
	QUE_U16 Length = 0,ulReturn;
	if(p_queue->Cnt > p_queue->Qsize - Len)///
		return FALSE;
	//QUEUE_INT_DISABLE;
	ulReturn = taskENTER_CRITICAL_FROM_ISR();
	while(Length < Len)
	{
		sch_memcpy((QUE_U8 *)p_queue->Pbuf+(p_queue->Head+Length)%p_queue->Qsize*p_queue->Isize, (QUE_U8 *)p_data+Length*p_queue->Isize, p_queue->Isize);
		Length++;
	}
	p_queue->Head = (p_queue->Head+Len)%p_queue->Qsize;
	p_queue->Cnt += Len;
	
	//App_Printf("\r\n QueueIn size %x",p_queue->Cnt);
	//QUEUE_INT_ENABLE;
	taskEXIT_CRITICAL_FROM_ISR( ulReturn );
	return TRUE;
}

QUE_BOOL Queue_Out(QUEUE_T *p_queue, void *p_data, QUE_U16 Len)
{
	QUE_U16 Length = 0,ulReturn;
	if(p_queue->Cnt < Len)///
		return FALSE;
	//QUEUE_INT_DISABLE;
	ulReturn = taskENTER_CRITICAL_FROM_ISR();
	while(Length < Len)
	{
		sch_memcpy((QUE_U8 *)p_data+Length*p_queue->Isize, (QUE_U8 *)p_queue->Pbuf+(p_queue->Tail+Length)%p_queue->Qsize*p_queue->Isize, p_queue->Isize);
		Length++;
	}
	p_queue->Tail = (p_queue->Tail+Len)%p_queue->Qsize;
	p_queue->Cnt -= Len;
	//QUEUE_INT_ENABLE;
	taskEXIT_CRITICAL_FROM_ISR( ulReturn );
	return TRUE;
}
QUE_BOOL Queue_Insert(QUEUE_T *p_queue, void *p_data, QUE_U16 Len)
{
	QUE_U16 Length = Len,ulReturn;
	if(p_queue->Cnt > p_queue->Qsize - Len)///
		return FALSE;
	//QUEUE_INT_DISABLE;
	ulReturn = taskENTER_CRITICAL_FROM_ISR();
	while(Length)
	{
		sch_memcpy((QUE_U8 *)p_queue->Pbuf+(p_queue->Tail+p_queue->Qsize-Length)%p_queue->Qsize*p_queue->Isize, (QUE_U8 *)p_data+(Len - Length)*p_queue->Isize, p_queue->Isize);
		Length --;
	}
	p_queue->Tail = (p_queue->Tail+p_queue->Qsize-Len)%p_queue->Qsize;
	p_queue->Cnt += Len;
	//QUEUE_INT_ENABLE;
	taskEXIT_CRITICAL_FROM_ISR( ulReturn );
	return TRUE;
}
