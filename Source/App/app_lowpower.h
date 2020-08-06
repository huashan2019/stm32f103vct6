///=========================
#ifndef __APP_LOWPOWER_H
#define __APP_LOWPOWER_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"





#define KBI0_PTD0_SHIFT 29
#define KBI0_PTD0_MASK 0x20000000u

 RTC_AlarmTypeDef salarmstructure;
 RTC_TimeTypeDef stimestructure;
 RTC_HandleTypeDef hrtc;


extern void TASK_AccOff_Pro(void);
#ifdef __cplusplus
}
#endif

#endif
