#ifndef _UICC_DEF_H
#define _UICC_DEF_H
typedef enum  
{
	NO_KEY,
	UICC_MUTE,			//����
	UICC_PLAY_PAUSE,		//������ͣ
	UICC_SKIPF	,		//��һ��
	UICC_SKIPB	,			//��һ��
	UICC_EJECT	,				//����		
	UICC_SOURCE,		//Դ�л�
	UICC_ANGLE_DEC,		//���·�
	UICC_ANGLE_INC,		//���Ϸ�
	UICC_PICTURE,		//�����ȵ��ڲ˵�
	UICC_DISP,				//��ʾ�л�	
	UICC_OPEN,		//����
	UICC_AUDIO_SETUP,			//����Ƶ���ò˵�
	UICC_TUNER,//UICC_AMFM,			//����������
	UICC_ASPS,				//�Զ���̨
	UICC_INFO,			//��ʾ������Ϣ

	UICC_VOLUME_DOWN,		//������	
	UICC_VOLUME_UP,		//������
	UICC_UP	,	//��
	UICC_DOWN,	//��
	UICC_LEFT,		//��
	UICC_RIGHT,		//��
	UICC_POWER,		//��Դ����
	UICC_0	,		//0
	UICC_1	,		//1
	UICC_2	,		//2
	UICC_3	,			//3
	UICC_4,	//4
	UICC_5,			//5
	UICC_6	,		//6	
	UICC_7	,			//7
	UICC_8,		//8
	UICC_9,		//9
	UICC_CLEAR=0x22	,		//���
	UICC_SETUP	,		//����
	UICC_STOP,		//ֹͣ
	UICC_SEARCH,		//����
	UICC_ANGLE,		//�Ƕ�
	UICC_TITLE,		
	UICC_EQ,///UICC_AUDIO,
	UICC_SUBTITLE,
	UICC_HOME,		//�˵�//android ����Ϊhome,�̰�Ϊmenu
	UICC_ZOOM,	
	UICC_FASTR,		//����
	UICC_FASTF,	//���
	UICC_SCAN,		//ɨ��
	UICC_RANDOM,///UICC_SHUFFLE,		//���
	UICC_REPEAT,		//�ظ�
	UICC_MARKAB,		//AB
	UICC_SLOWF,	
	UICC_SLOWB,
	UICC_SEL,			//
	UICC_ENTER=0x36,    	 //OK           
	UICC_1OR2,	
	UICC_SMART_CW=0x39	,	//����ť����
	UICC_SMART_CCW,		//����ť����
	UICC_DISPLAY=0x3d,//��ʾ�л�
	UICC_PLAY,		//����
	UICC_PAUSE	,		//��ͣ
	UICC_FUNCTION,	//���ܰ���
	UICC_MENU,	//���ܰ���(androidר�ã�Wince��Ҫʹ��)  
	UICC_BACK,	//���ذ���
	UICC_CH_UP=0x43,	//��һ��Ƶ��
	UICC_CH_DOWN,	//��һ��Ƶ��
	UICC_AUX,	//Aux
	UICC_APP,	//APP����
	UICC_TIME,	//ʱ������

	UICC_VOLUME_CW=0x50,		//������ť����
	UICC_VOLUME_CCW,		//������ť����

	UICC_ESC,		//�˳�
	UICC_BT,		//BT����
	UICC_SD_CARD,		//����SDģʽ
	UICC_TFT_STANDBY=0x5b	,		//��������˳�Standbyģʽ
	UICC_4S_FUN,			//����IPODģʽ
	UICC_SPEECH,//UICC_VOICE,
	UICC_BT_ACPTCALL,///UICC_DIAL,			//����	
	UICC_BT_HUNGUPCALL,////UICC_DONE,			//�ҵ�?
/*�û��Զ���*/
	UICC_BMW_MODE=0x60,
	UICC_BMW_CD,
	UICC_BMW_RADIO,
	UICC_BMW_MENU,
	UICC_BMW_FMAM,
	UICC_BMW_ORIGINAL,
	UICC_BMW_ANDROID,

	UICC_POWER_ON,
   UICC_POWER_OFF,
   UICC_TFT_AWAKE,
   UICC_LOC_DX,
   UICC_STANDBY,
/****************************/
	UICC_SCREEN=0x77,
	UICC_COMPASS=0x78,
	UICC_MODE=0x79,///UICC_DVD=0x79,	//����DVDģʽ
	UICC_NAVI=0x7B,	//���뵼������
	UICC_MEDIA,
	UICC_SCREEN_OPEN=0x7E,
	UICC_SCREEN_CLOSE=0x7F,

	UICC_MAX=0xff
}UICC_KEY_CODE;







#endif
