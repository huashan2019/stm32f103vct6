///=========================
#ifndef __APP_DSP_ADAU1452_H
#define __APP_DSP_ADAU1452_H


///==============================================
typedef enum  
{
	DSP_CHANNEL_ALL_NONE = 0x00,
	DSP_CHANNEL_1   = 0x01,
	DSP_CHANNEL_2   = 0x02,
	DSP_CHANNEL_3   = 0x03,
	DSP_CHANNEL_4   = 0x04,
	DSP_CHANNEL_5   = 0x05,
	DSP_CHANNEL_6   = 0x06,
	DSP_CHANNEL_7   = 0x07,
	DSP_CHANNEL_8   = 0x08,
}DSP_CHANNEL_T;
#define DSP_CHANNEL_CNT          8
#define DSP_OUTPUT_CNT           8
#define DSP_INPUT_CNT           10

#define DSP_MODE_CNT             8
#define DSP_NAME_SIZE            8///BYTE

#define DSP_FREQ_MAX         96000
#define DSP_FREQ_MIN             0
///===============================================================================================
typedef enum  
{
	UpData_Idle,    ///0--����
	Curr_TO_Flash,  ///1--�洢��ǰ��FLASH
	Flash_TO_Curr,  ///2--����FLASH����ǰ 
	Flash_TO_File,  ///3--FLASH�洢��FILE 
	File_TO_Flash,  ///4--FILE�����FLASH
	Load_Mode_Name,
	Store_Mode_Name,
}Dsp_UpData_S;
///==================================================================================================
typedef enum  
{
	DSP_INIT_IDLE,
	DSP_POWER_EN,
	DSP_INIT,
	DSP_NORMAL, 
	DSP_CLOSE,
	DSP_POWER_DIS
} DspPowerState_t;
///===============================================================================================
typedef union
{
	SCH_U8 byte;
	struct
	{
		SCH_U8 EN_DIS   :1;	
		SCH_U8 Reverse0 :3;
		SCH_U8 PHASE    :1;	
		SCH_U8 Reverse1 :3;
	}bit;
}OTHER;
typedef enum  
{
	HIGH_PASS_FILTER,
	LOW_PASS_FILTER,
	HPLP_FILTER_CNT
}Filter_HPLP;
typedef enum  
{
	MODE0_IDLE,
	MODE0_LINKWITZ,
	MODE0_BESSEL,
	MODE0_BUTTERWORTH
}Filter_MODE0;
typedef enum  
{
	MODE1_IDLE,
	MODE1_12dB_Oct,
	MODE1_18dB_Oct,
	MODE1_24dB_Oct,
	MODE1_30dB_Oct,
	MODE1_36dB_Oct,
	MODE1_42dB_Oct,
	MODE1_48dB_Oct,
}Filter_MODE1;
typedef struct 
{
	OTHER        Other;
	Filter_MODE0 MODE0;
	Filter_MODE1 MODE1;
	SCH_U32 Freq;
	SCH_U16 Gain;
}Filters_T;
///=============================================
typedef enum  
{
	EQ_NUM_0,
	EQ_NUM_1,
	EQ_NUM_2,
	EQ_NUM_3,
	EQ_NUM_4,
	EQ_NUM_5,
	EQ_NUM_6,
	EQ_NUM_7,
	EQ_NUM_8,
	EQ_NUM_9,
	EQ_NUM_10,
	EQ_NUM_11,
	EQ_NUM_12,
	EQ_NUM_13,
	EQ_NUM_14,
	EQ_NUM_15,
	EQ_NUM_16,
	EQ_NUM_17,
	EQ_NUM_18,
	EQ_NUM_19,
	EQ_NUM_20,
	EQ_NUM_21,
	EQ_NUM_22,
	EQ_NUM_23,
	EQ_NUM_24,
	EQ_NUM_25,
	EQ_NUM_26,
	EQ_NUM_27,
	EQ_NUM_28,
	EQ_NUM_29,
	EQ_NUM_30,
	EQ_NUM_31,	
	EQ_NUM_CNT
}EQ_NUM_T;
typedef enum  
{
	PEAKING_EQ,
	SHELVING_EQ
}EQ_MODE0;
typedef struct 
{
	OTHER     Other;
	EQ_MODE0  MODE0;
	SCH_U16   Boost;
	SCH_U32    Freq;
	SCH_U16    Gain;
	SCH_U16 Q_Factor;
}EQ_T;
///=============================================
typedef enum  
{
	DSP_MUTE   = 0x00,
	DSP_UNMUTE = 0x01
}MUTE_MODE;
///==================================================================================
typedef struct 
{
	SCH_U32         CheckSum;
	SCH_U8          ReName[DSP_CHANNEL_CNT+1][DSP_NAME_SIZE];
	SCH_U8          MixData[DSP_CHANNEL_CNT+1][DSP_INPUT_CNT+1];
	Filters_T       FiltersData[DSP_CHANNEL_CNT][HPLP_FILTER_CNT];
	EQ_T            EQ_Data[DSP_CHANNEL_CNT][EQ_NUM_CNT];
	SCH_U16         DelayData[DSP_CHANNEL_CNT+1];
	SCH_U16         SingleData[DSP_CHANNEL_CNT+1+1];
	SCH_U16         SingleMaxData;///�����������ֵ
	MUTE_MODE       Mute[DSP_CHANNEL_CNT+1];
	DSP_CHANNEL_T   OutPutChl[DSP_OUTPUT_CNT+1];
}Dsp_Data_T;
typedef struct 
{
	SCH_U32         CheckSum;
	SCH_U8          Name[DSP_MODE_CNT][DSP_NAME_SIZE];
}ModeName_T;
typedef struct 
{
	Dsp_Data_T      Dsp_Data;
	ModeName_T      Dsp_ModeName;
	DspPowerState_t DspPwrState;
	SCH_U8          DspNum;
	SCH_U16         RequestEQ_Left;
	SCH_U16         RequestEQ_Right;
	Dsp_UpData_S    DSP_Updata_State;///       
	SCH_U8          DspUpdataNum;///��Ҫ���µı��
	SCH_U8          DspUpdataSn; ///��ǰ�����к�
	SCH_U8          DspUpdataCnt;///��ǰ���ĳ���
	SCH_U8          DspUpdata_DataOk;///�յ������ݱ�ʶ
	SCH_U32         DspUpdataLen;///�ܳ���
	SCH_U32         DspUpdataChecksum;///У��λ
	SCH_U8          DspUniteChannel0;
	SCH_U8          DspUniteChannel1;
}Dsp_T;
extern Dsp_T App_Dsp;
extern EQ_T EQ_Rx;

extern const double Fs;
extern const double pi;

extern void Dsp_Updata(SCH_BOOL MixEnable,SCH_BOOL SingleEnable);
extern void Flash_Set_DspNum(void);
extern void DspModeNameInit(void);
extern void SIGMASTUDIOTYPE(double data,SCH_U8 *buff);
extern void Dsp_Delay_Init(void);
extern void Dsp_Delay(SCH_U8 Channel,SCH_U32 data);
extern void Dsp_OutPutChl_Init(void);
extern void Dsp_OutPutChl(SCH_U8 OutPut,SCH_U8 data);
extern void Dsp_ReName_Init(void);
extern void Dsp_ReName(SCH_U8 Channel,SCH_U8 *data);
extern SCH_BOOL Dsp_Unite(SCH_U8 Channel0,SCH_U8 Channel1);
extern void Dsp_Data_Reset(void);
extern void Dsp_TestMode(void);
extern void Dsp_OFF(void);
extern void Dsp_ON(void);
extern void TASK_Dsp_Pro(void);
extern void DspInit(void);
#endif
