///=========================
#ifndef __APP_START_H
#define __APP_START_H

///=======================================================================================ACC===========
#define IO_ACC                  GPIOC
#define GPIO_ACC_DECT           GPIO_PIN_0
#define ACC_DET_LEVEL           HAL_GPIO_ReadPin(IO_ACC,GPIO_ACC_DECT)
#define ACC_DET_LVON            (HIGH_LEVEL==ACC_DET_LEVEL)
#define ACC_DET_LVOFF           (LOW_LEVEL==ACC_DET_LEVEL)
extern void ACC_Init(void);
///===================ACC END============================

///=======================================================================================AUDIO===========
#define IO_AUDIO               GPIOB
#define GPIO_AUDIO_DECT            GPIO_PIN_1
#define AUDIO_DET_LEVEL            HAL_GPIO_ReadPin(IO_AUDIO,GPIO_AUDIO_DECT)
#define AUDIO_DET_LVON             (LOW_LEVEL==AUDIO_DET_LEVEL)
#define AUDIO_DET_LVOFF            (HIGH_LEVEL==AUDIO_DET_LEVEL)
extern void AUDIO_Init(void);
///===================AUDIO END============================

extern void Start_IO_Init(void);
extern void Start_Detect(void);
extern void Audio_Init(void);

#endif
