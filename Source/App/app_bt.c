/*
***************************************************************************************************
**  Copyright   : 
**  Project     : STM32F103VCT6
**  File        : app_bt.c  ---   ��BTͨѶ
**  Description : 
**  Author      : lvhuashan
**  Created on  : 2017.04.27
**  Note        : NULL
***************************************************************************************************
*/
#include "include.h"
#include "usb_device.h"

extern unsigned char USB_Rx_Buf[64];
extern USBD_HandleTypeDef hUsbDeviceFS;
extern uint8_t USBD_CUSTOM_HID_SendReport(USBD_HandleTypeDef *pdev,
                                   uint8_t *report,
                                   uint16_t len);

typedef struct
{
	SCH_U8 TxData[100];
	SCH_U8 TxData_Length;
	SCH_U8 TxData_Parity;
	SCH_U8 Check_ResendCounte;
	SCH_U8 Check_ResendTimer;
	SCH_U8 Check_Busy;
	SCH_U8 Check_Ack;
}BT_Tx_MODUEL_S;
BT_Tx_MODUEL_S BtTxModuel;
Rx_MODUEL_S      BtRxModuel;
Rx_MODUEL_S      PcRxModuel_0;
Rx_MODUEL_S      PcRxModuel_1;

///======================================================================================
SCH_U8 set_query_password;
#define PasswordCnt    6
const SCH_U8 DefaultPassword[PasswordCnt] = {0x32,0x35,0x37,0x30,0x38,0x39};
SCH_BOOL Is_PASSWORD(SCH_U8 *Data)
{
	SCH_U8 password[PasswordCnt];
	if(sch_compare(Data,DefaultPassword,PasswordCnt)==TRUE)
		return TRUE;
	Flash_Quick_RD_U8(FLASH_DATA_PASSWORD, password, PasswordCnt);
	if(sch_compare(Data,password,PasswordCnt)==TRUE)
		return TRUE;
	return FALSE;
}
SCH_BOOL Set_PASSWORD(SCH_U8 *Data)
{
	return Flash_Quick_WR_U8(FLASH_DATA_PASSWORD, Data, PasswordCnt);
}
///======================================================================================
void Bt_ACK(SCH_U8 ack_type)
{
	SCH_U8 buf[6+11];
	#if 1
	
	buf[0] = 'A';
	buf[1] = 'T';
	buf[2] = '>';
	buf[3] = 0x01;/*DATA TYPE:0X0102 SPP���ݣ�0x0101 BLE����*/

	if(BtGATTCONFlag)
		buf[4] = 0x01;
	else if(BtSPPCONFlag)
		buf[4] = 0x02;
	else
	{
		buf[4] = 0x00;
		//printf("\n\n--DATA TYPE ERR--\n\n");
	}

	
	buf[5] = 0x00;/*length H:��0x80��ʼ��0x0d����*/
	buf[6] = 9;/*length L*/
	buf[7] = 0x80;
	buf[8] = 0x00;
	buf[9] = 0x0d;/*\r*/

	buf[10]=HEAD_ADDRESS_MCU;
	buf[11]=HEAD_ADDRESS_BT;
	buf[12]=6;
	buf[13]=BtRx_Sequence; 
	buf[14]=ack_type;
	buf[15]=GetCheckData_Xor(&buf[10], 5);
	buf[16] = 0x0d;/*\r*/
	UartTxData(Uart_CONNECT, buf, 6+11);


	#else
	buf[0]=HEAD_ADDRESS_MCU;
	buf[1]=HEAD_ADDRESS_BT;
	buf[2]=6;
	buf[3]=BtRx_Sequence; 
	buf[4]=ack_type;
	buf[5]=GetCheckData_Xor(buf, 5);
	UartTxData(Uart_CONNECT, buf, 6);
	#endif
}
/********************************************************************************
**  Function	: BtDataAnalyse
**  Author		: 
**  Created on	: 20190402
**  Description	:
**  Return		: 
********************************************************************************/
EQ_T EQ_Rx;
SCH_U8 Mix_Mixer_data[11];

void BtDataAnalyse(void)
{
	SCH_U8 *pData=&BtRx_Data;
	if(BtRx_GroupID<COMM_NACK_NG)           
		Bt_ACK(COMM_ACK);
	switch(BtRx_GroupID)
	{
		case A2M_ACK:///===========================================================================================ACK================
			if(BtRx_Sequence==BtTx_Sequence)
			{
				BtTxModuel.Check_Ack=0;
				BtTxModuel.Check_Busy=0;
			}
			break;
		case A2M_SYS_CMD:
			switch(BtRx_SubID)
			{
				case A2M_MCU_VER:
					PostMessage(BT_MODULE, M2A_SYS_CMD, M2A_MCU_VER);
					break;
			}
			break;
		case B2M_DSP_DATA:///A2M_DSP_DATA
			switch(BtRx_SubID)
			{
				case 0x00:
					if(App_Dsp.DSP_Updata_State == UpData_Idle)
					{
						if(pData[0]==0x00)
						{
							PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(0x00,BtRx_SubID));							
						} 
						else if(pData[0]==0x01)
						{
							if(!Get_DSP_OFF_Flag)
							{
								App_Dsp.DSP_Updata_State = Curr_TO_Flash;
								App_Dsp.DspUpdataNum = pData[1];
							}
							PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(0x01,BtRx_SubID));							
						}
						else if(pData[0]==0x02)
						{
							if(!Get_DSP_OFF_Flag)
							{
								App_Dsp.DSP_Updata_State = Flash_TO_Curr;
								App_Dsp.DspUpdataNum = pData[1];
							}
							PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(0x02,BtRx_SubID));							
						}
					}
					else
					{
						PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(0x00,BtRx_SubID));
					}
					break;
				case 0x01:///DSP״̬
					if(pData[0]==0)
					{
						PostMessage(BT_MODULE,M2B_DSP_DATA,0x01);
					}
					else if(pData[0]==1)
					{
						if(!Get_DSP_OFF_Flag)
							Dsp_Data_Reset();
					}
					else if(pData[0]==2)
					{
						if(pData[1])
						{
							if(!Get_DSP_OFF_Flag)
								Dsp_EQ_Reset(pData[1]);
							if(pData[1] % 2)
								App_Dsp.RequestEQ_Left = 0x8000|((pData[1]-1)*32);
							else
								App_Dsp.RequestEQ_Right = 0x8000|((pData[1]-1)*32);
						}
					}
					else if(pData[0]==3)
					{
						if(pData[1])
						{
							if(!Get_DSP_OFF_Flag)
								Dsp_EQ_Direct(pData[1],SCH_ENABLE);
							if(pData[1] % 2)
								App_Dsp.RequestEQ_Left = 0x8000|((pData[1]-1)*32);
							else
								App_Dsp.RequestEQ_Right = 0x8000|((pData[1]-1)*32);
						}
					}
					else if(pData[0]==4)
					{
						if(pData[1])
						{
							if(!Get_DSP_OFF_Flag)
								Dsp_Filter_Reset(pData[1]);
							PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD((pData[1]-1)*HPLP_FILTER_CNT,0x03));
							PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD((pData[1]-1)*HPLP_FILTER_CNT+1,0x03));
						}
					}
					else if(pData[0]==5)
					{
						if(pData[1])
						{
							if(!Get_DSP_OFF_Flag)
								Dsp_EQ_Direct(pData[1],SCH_DISABLE);
							if(pData[1] % 2)
								App_Dsp.RequestEQ_Left = 0x8000|((pData[1]-1)*32);
							else
								App_Dsp.RequestEQ_Right = 0x8000|((pData[1]-1)*32);
						}
					}
					else if(pData[0]==6)
					{
						Dsp_TestMode();
					}
					break;
				case 0x02:///����״̬
					if(!Get_DSP_OFF_Flag)
						Dsp_Mix_Mixer(pData[0],&pData[2]);
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],BtRx_SubID));
					break;

				case 0x12:///����״̬1
					if(!Get_DSP_OFF_Flag)
					{
						sch_memcpy(Mix_Mixer_data,&pData[2],5);
						Dsp_Mix_Mixer(pData[0],&pData[2]);
					}
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],BtRx_SubID));
					break;
					
				case 0x13:///����״̬2
					if(!Get_DSP_OFF_Flag)
					{
						sch_memcpy(&Mix_Mixer_data[5],&pData[2],5);
						//Dsp_Mix_Mixer(pData[0],&pData[2]);
						Dsp_Mix_Mixer(pData[0],Mix_Mixer_data);
					}
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],BtRx_SubID));
					break;
					
				case 0x82:///�������״̬
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],0x02));
					break;

				case 0x92:///�������״̬1
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],0x12));
					break;
					
				case 0x93:///�������״̬2
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],0x13));
					break;

					
				case 0x03:///Filters
					if(!Get_DSP_OFF_Flag)
					{
						Filters_T Filter;
						Filter.Other.byte = pData[1];
						Filter.MODE0 = (Filter_MODE0)pData[2];
						Filter.MODE1 = (Filter_MODE1)pData[3];
						Filter.Freq = (pData[4]<<24)+(pData[5]<<16)+(pData[6]<<8)+pData[7];
						Filter.Gain = (pData[8]<<8)+pData[9];
						Dsp_GEN_Filter(pData[0]/HPLP_FILTER_CNT,(Filter_HPLP)(pData[0]%HPLP_FILTER_CNT),&Filter);
					}
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],BtRx_SubID));
					break;
				case 0x83:///����Filters
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],0x03));
					break;
				case 0x04:///EQ
					if(!Get_DSP_OFF_Flag)
					{
						EQ_T EQ;
						EQ.Other.byte = pData[1];
						EQ.MODE0    = (EQ_MODE0)pData[2];
						EQ.Boost    = (pData[3]<<8 )+pData[4];
						EQ.Freq     = (pData[5]<<24)+(pData[6]<<16)+(pData[7]<<8)+pData[8];
						EQ.Gain     = (pData[9]<<8 )+pData[10];
						EQ.Q_Factor = (pData[11]<<8)+pData[12];
						Dsp_EQ_Set(pData[0]/EQ_NUM_CNT,(EQ_NUM_T)(pData[0]%EQ_NUM_CNT),&EQ);
					}
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],BtRx_SubID));
					break;
				case 0x84:///����EQ
					if(pData[0]%32==31)
					{
						if(pData[0]%64 < 32)
							App_Dsp.RequestEQ_Left = 0x8000|(pData[0]/32*32);
						else
							App_Dsp.RequestEQ_Right = 0x8000|(pData[0]/32*32);
					}
					else
						PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],0x04));
					break;

				case 0x94:///����EQ
					if(pData[0]%32==31)
					{
						if(pData[0]%64 < 32)
							App_Dsp.RequestEQ_Left = 0x8000|(pData[0]/32*32);
						else
							App_Dsp.RequestEQ_Right = 0x8000|(pData[0]/32*32);
					}
					else
					{
						//PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],0x14));
						//PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],0x15));
					}
					break;
				case 0x15:///����EQ
					if(!Get_DSP_OFF_Flag)
					{
						//EQ_T EQ_Rx;
						//EQ_Rx.Other.byte = pData[1];
						//EQ_Rx.MODE0    = (EQ_MODE0)pData[2];
						//EQ_Rx.Boost    = (pData[3]<<8 )+pData[4];
						//EQ_Rx.Freq     = (pData[5]<<24)+(pData[6]<<16)+(pData[7]<<8)+pData[8];
						EQ_Rx.Gain     = (pData[9-8]<<8 )+pData[10-8];
						EQ_Rx.Q_Factor = (pData[11-8]<<8)+pData[12-8];
						Dsp_EQ_Set(pData[0]/EQ_NUM_CNT,(EQ_NUM_T)(pData[0]%EQ_NUM_CNT),&EQ_Rx);
					}
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],BtRx_SubID));
					break;
					
				case 0x14:///����EQ
					if(!Get_DSP_OFF_Flag)
					{
						//EQ_T EQ_Rx;
						EQ_Rx.Other.byte = pData[1];
						EQ_Rx.MODE0	= (EQ_MODE0)pData[2];
						EQ_Rx.Boost	= (pData[3]<<8 )+pData[4];
						EQ_Rx.Freq 	= (pData[5]<<24)+(pData[6]<<16)+(pData[7]<<8)+pData[8];
						//EQ.Gain	  = (pData[9]<<8 )+pData[10];
						//EQ.Q_Factor = (pData[11]<<8)+pData[12];
						Dsp_EQ_Set(pData[0]/EQ_NUM_CNT,(EQ_NUM_T)(pData[0]%EQ_NUM_CNT),&EQ_Rx);
					}
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],BtRx_SubID));
					break;

					
				case 0x05:///Delay
					if(!Get_DSP_OFF_Flag)
					{
						Dsp_Delay(pData[0],(pData[1]<<8)+pData[2]);
					}
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],BtRx_SubID));
					break;
				case 0x85:///����Delay
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],0x05));
					break;
				case 0x06:///Single
					if(!Get_DSP_OFF_Flag)
					{
						if((pData[0] == DSP_CHANNEL_ALL_NONE)/*&&(Uart_CONNECT == SCH_Uart_PC)*/)
							App_Dsp.Dsp_Data.SingleMaxData = (pData[3]<<8)+pData[4];
						Dsp_Single(pData[0],(pData[1]<<8)+pData[2]);
					}
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],BtRx_SubID));
					if(pData[0] == DSP_CHANNEL_ALL_NONE)
						CheckVol();
					break;
				case 0x86:///����Single
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],0x06));
					break;
				case 0x07:///output
					if(!Get_DSP_OFF_Flag)
					{
						Dsp_OutPutChl(pData[0],pData[1]);
					}
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],BtRx_SubID));
					break;
				case 0x87:///����output
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],0x07));
					break;
				case 0x08:///mute
					if(!Get_DSP_OFF_Flag)
					{
						Dsp_Mute(pData[0],pData[1]);
					}
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],BtRx_SubID));
					break;
				case 0x88:///����mute
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],0x08));
					break;
				case 0x09:///ReName
					if(!Get_DSP_OFF_Flag)
					{
						Dsp_ReName(pData[0],&pData[1]);
					}
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],BtRx_SubID));
					break;
				case 0x89:///����ReName
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],0x09));
					break;
				case 0x0A:///����
					App_Dsp.DspUniteChannel0 = pData[0];
					App_Dsp.DspUniteChannel1 = pData[1];
					if(Dsp_Unite(pData[0],pData[1]))
						PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(0x01,BtRx_SubID));
					else
						PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(0x02,BtRx_SubID));
					break;
				case 0x0B:///����
					if(pData[0] == 0x01)
					{
						set_query_password = pData[0];
						if(Is_PASSWORD(&pData[1]))
						{
							if(Set_PASSWORD(&pData[7]))
								PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(0x01,BtRx_SubID));
							else
								PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(0x03,BtRx_SubID));
						}
						else
							PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(0x02,BtRx_SubID));
					}
					else if(pData[0] == 0x02)
					{
						set_query_password = pData[0];
						if(Is_PASSWORD(&pData[1]))
							PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(0x01,BtRx_SubID));
						else
							PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(0x02,BtRx_SubID));
					}
					break;
				case 0x0C:///bt info
					if(pData[0] == 0x01)///addr
					{
						if(Uart_CONNECT == SCH_Uart_BT)
							PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(0x01,0x0C));
						else
							{
								//UartTxData(SCH_Uart_BT,BT_LBDADDR_GET,sizeof(BT_LBDADDR_GET));
								if(/*BtSPPCONFlag || BtGATTCONFlag || */!PCSTATFlag)
								PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(0x01,0x0C));
							}
					}
					else if(pData[0] == 0x02)
					{
						if(Uart_CONNECT == SCH_Uart_BT)
							PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(0x02,0x0C));
						else
						{
							//if(/*BtSPPCONFlag || BtGATTCONFlag || */!PCSTATFlag)
							//PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(0x02,0x0C));
							UartTxData(SCH_Uart_BT,BT_VER_GET,sizeof(BT_VER_GET));
						}
					}
					break;
				case 0x0D:///������
					if(pData[0] == 0x01)///��������
					{
						if(!Get_DSP_OFF_Flag)
						{
							Vol_Ctl(pData[1]);
						}
						PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],BtRx_SubID));
						PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(DSP_CHANNEL_ALL_NONE,0x06));
					}
					break;
				case 0x8D:///����������
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],0x0D));
					break;
				case 0x0E:
					if(pData[0]==0x01)///DSP OFF
					{
						Dsp_OFF();
						Set_DSP_OFF_Flag;
					}
					else if(pData[0]==0x02)///DSP ON
					{
						Dsp_ON();
						Clr_DSP_OFF_Flag;
					}
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],BtRx_SubID));
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(0xFE,0x00));///ˢ��
					break;
				case 0x8E:
					PostMessage(BT_MODULE,M2B_DSP_DATA,SCH_WORD(pData[0],0x0E));

					
				default:break;
			}
			break;
		case B2M_DSP_UPDATA:
			switch(BtRx_SubID)
			{
				case 0x00:
					if(pData[0]==0x01)
					{
						if((App_Dsp.DSP_Updata_State == UpData_Idle)&&(pData[1]!=0))
						{
							App_Dsp.DspUpdataNum = pData[1];
							App_Dsp.DSP_Updata_State = Flash_TO_File;
						}
						else
						{
							PostMessage(BT_MODULE,M2B_DSP_UPDATA,SCH_WORD(0xFF,0x00));///ERROR
						}
					}
					else if(pData[0]==0x02)
					{
						if((App_Dsp.DSP_Updata_State == UpData_Idle)&&(pData[1]!=0))
						{
							App_Dsp.DspUpdataNum = pData[1];
							App_Dsp.DSP_Updata_State = File_TO_Flash;
						}
						else
						{
							PostMessage(BT_MODULE,M2B_DSP_UPDATA,SCH_WORD(0xFF,0x00));///ERROR
						}
					}
					else if(pData[0]==0x81)
					{
						App_Dsp.DspUpdataNum = 0x00;
						App_Dsp.DspUpdataLen = 0x00000000;
						App_Dsp.DspUpdataSn  = 0x00;
						App_Dsp.DspUpdataCnt = 0x00;
						App_Dsp.DspUpdata_DataOk  = 0x00;
						App_Dsp.DspUpdataChecksum = 0x00;
					}
					break;
				case 0x01:///���󳤶�
					if((App_Dsp.DSP_Updata_State == Flash_TO_File)&&(pData[0] == App_Dsp.DspUpdataNum))
					{
						App_Dsp.DspUpdataLen = DSP_SPI_DATA_LENGTH;
						PostMessage(BT_MODULE,M2B_DSP_UPDATA,SCH_WORD(App_Dsp.DspUpdataNum,BtRx_SubID));
					}
					break;
				case 0x02:///���������
					if((App_Dsp.DSP_Updata_State == Flash_TO_File)&&(pData[0] == App_Dsp.DspUpdataNum))
					{
						App_Dsp.DspUpdataSn = pData[1];
						if((App_Dsp.DspUpdataSn+1) >= (App_Dsp.DspUpdataLen+63)/64)
							App_Dsp.DspUpdataCnt = App_Dsp.DspUpdataLen%64;
						else
							App_Dsp.DspUpdataCnt = 64;
						PostMessage(BT_MODULE,M2B_DSP_UPDATA,SCH_WORD(App_Dsp.DspUpdataNum,BtRx_SubID));
					}
					break;
				case 0x03:///��Ӧ���Ⱥ�У��
					if((App_Dsp.DSP_Updata_State == File_TO_Flash)&&(pData[0] == App_Dsp.DspUpdataNum))
					{
						App_Dsp.DspUpdataLen      = (pData[1]<<24)+(pData[2]<<16)+(pData[3]<<8)+pData[4];
						App_Dsp.DspUpdataChecksum = (pData[5]<<24)+(pData[6]<<16)+(pData[7]<<8)+pData[8];
					}
					break;
				case 0x04:///���ͱ�����
					if((App_Dsp.DSP_Updata_State == File_TO_Flash)&&(pData[0] == App_Dsp.DspUpdataNum))
					{
						if(pData[1] == App_Dsp.DspUpdataSn)
						{
							SCH_U8 *UpData = (SCH_U8 *)(&App_Dsp.Dsp_Data);
							UpData += (64*App_Dsp.DspUpdataSn);
							sch_memcpy(UpData,&pData[2],BtRx_Length-9);
							App_Dsp.DspUpdata_DataOk = 1;
						}
					}
					break;
				default:break;
			}
			break;
			case A2M_BT_IAP_CMD:
				UartTxData(SCH_Uart_BT,"AT+B SOTA 1\r\n",sizeof("AT+B SOTA 1\r\n"));
				break;
			case A2M_IAP_CMD:///===========================================================================================A2M_IAP_CMD 0x08================
				if(BtRx_SubID==0x01)
				{
					Set_IAP_Mode;
				}
				break;

		default:break;
	}
}
/********************************************************************************
**  Function	: M2B_TxService
**  Author		: 
**  Created on	: 20190402
**  Description	:
**  Return		: 
********************************************************************************/
void M2B_TxService(void)
{
	MESSAGE pMsg;
	SCH_U8 *pData=&BtTx_Data;
	SCH_U8 length_data = 0;
	SCH_U8 sub_id,index,i;
	if(FALSE==GetMessage(BT_MODULE,&pMsg))
		return;
	sub_id=LSB(pMsg.prm);
	index =MSB(pMsg.prm);
	switch(pMsg.ID)
	{
		case M2A_IAP_CMD:
			switch(sub_id)
			{
				case M2A_IAP_REQ_C_L:
					pData[length_data++]=0x00;
					pData[length_data++]=0x00;
					break;
				case M2A_IAP_REQ_DATA:
					//pData[length_data++]=(SCH_U8)(Iap.IAP_Sn>>8);
					//pData[length_data++]=(SCH_U8)Iap.IAP_Sn;
					break;
				case M2A_IAP_REQ_RESET:
					pData[length_data++]=0x00;
					pData[length_data++]=0x00;
					break;
				default:break;
			}
			break;



	
		case M2A_SYS_CMD:
			switch(sub_id)
			{
				case M2A_MCU_VER:
					length_data=sizeof(MCU_VERSION);
					sch_memcpy(pData,MCU_VERSION,length_data);
					break;
			}
			break;
		case M2B_DSP_DATA:///
			switch(sub_id)
			{
				case 0x00:
					pData[length_data++] = index;
					if(App_Dsp.DspNum == 0xff) 
						pData[length_data++] = 0;
					else
						pData[length_data++] = App_Dsp.DspNum;
					break;
				case 0x01:///DSP״̬
					pData[length_data++] = (App_Dsp.DspPwrState == DSP_NORMAL) ? 1 : 0;
					break;
				case 0x02:///����״̬
					pData[length_data++] = index;
					sch_memcpy(pData+1,App_Dsp.Dsp_Data.MixData[index],DSP_INPUT_CNT+1);
					length_data += (DSP_INPUT_CNT+1);	
					break;
					
				case 0x12:///����״̬1
					pData[length_data++] = index;
					sch_memcpy(pData+1,App_Dsp.Dsp_Data.MixData[index],DSP_INPUT_CNT/2+1);
					length_data += (DSP_INPUT_CNT/2+1);	
					break;
					
				case 0x13:///����״̬2
					pData[length_data++] = index;
					sch_memcpy(pData+1,App_Dsp.Dsp_Data.MixData[index],1);
					sch_memcpy(pData+2,&App_Dsp.Dsp_Data.MixData[index][6],DSP_INPUT_CNT/2);
					length_data += (DSP_INPUT_CNT/2+1);	
					break;

					
				case 0x03:///General 2nd-Order Filters
					pData[length_data++] = index;
					{
						SCH_U8 Channel = index/HPLP_FILTER_CNT;
						Filter_HPLP HPLP = (Filter_HPLP)(index%HPLP_FILTER_CNT);
						pData[length_data++] = App_Dsp.Dsp_Data.FiltersData[Channel][HPLP].Other.byte;
						pData[length_data++] = App_Dsp.Dsp_Data.FiltersData[Channel][HPLP].MODE0;
						pData[length_data++] = App_Dsp.Dsp_Data.FiltersData[Channel][HPLP].MODE1;
						pData[length_data++] = App_Dsp.Dsp_Data.FiltersData[Channel][HPLP].Freq>>24;
						pData[length_data++] = App_Dsp.Dsp_Data.FiltersData[Channel][HPLP].Freq>>16;
						pData[length_data++] = App_Dsp.Dsp_Data.FiltersData[Channel][HPLP].Freq>>8;
						pData[length_data++] = App_Dsp.Dsp_Data.FiltersData[Channel][HPLP].Freq;
						pData[length_data++] = App_Dsp.Dsp_Data.FiltersData[Channel][HPLP].Gain>>8;
						pData[length_data++] = App_Dsp.Dsp_Data.FiltersData[Channel][HPLP].Gain;
					}
					break;
				case 0x04:///EQ
					pData[length_data++] = index;
					{
						SCH_U8 Channel = index/EQ_NUM_CNT;
						EQ_NUM_T EQ_NUM = (EQ_NUM_T)(index%EQ_NUM_CNT);
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Other.byte;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].MODE0;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Boost>>8;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Boost;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Freq>>24;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Freq>>16;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Freq>>8;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Freq;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Gain>>8;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Gain;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Q_Factor>>8;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Q_Factor;
					}
					break;
				case 0x05:///Delay
					pData[length_data++] = index;
					pData[length_data++] = App_Dsp.Dsp_Data.DelayData[index]>>8;
					pData[length_data++] = App_Dsp.Dsp_Data.DelayData[index];
					break;
				case 0x06:///Single
					pData[length_data++] = index;
					pData[length_data++] = App_Dsp.Dsp_Data.SingleData[index]>>8;
					pData[length_data++] = App_Dsp.Dsp_Data.SingleData[index];
					if(index == DSP_CHANNEL_ALL_NONE)
					{
						pData[length_data++] = App_Dsp.Dsp_Data.SingleMaxData>>8;
						pData[length_data++] = App_Dsp.Dsp_Data.SingleMaxData;
					}
					break;
				case 0x07:///output
					pData[length_data++] = index;
					pData[length_data++] = App_Dsp.Dsp_Data.OutPutChl[index];
					break;
				case 0x08:///Mute
					pData[length_data++] = index;
					pData[length_data++] = App_Dsp.Dsp_Data.Mute[index];
					break;
				case 0x09:///ReName
					pData[length_data++] = index;
					if(index <= DSP_CHANNEL_CNT)
					{
						sch_memcpy(pData+1,App_Dsp.Dsp_Data.ReName[index],DSP_NAME_SIZE);
					}
					else if(index >= 0x81 && index <= 0x88)
					{
						index = index&0x7F;
						sch_memcpy(pData+1,App_Dsp.Dsp_ModeName.Name[index-1],DSP_NAME_SIZE);
					}
					length_data += DSP_NAME_SIZE;
					break;
				case 0x0A:
					pData[length_data++] = App_Dsp.DspUniteChannel0;
					pData[length_data++] = App_Dsp.DspUniteChannel1;
					pData[length_data++] = index;
					break;
				case 0x0B:
					pData[length_data++] = set_query_password;
					pData[length_data++] = index;
					break;
				case 0x0C:
					pData[length_data++] = index;
					if(index == 0x01)
					{
						BT_Addr[12] = 0;
						if(BtSPPCONFlag || BtGATTCONFlag || BtPHFCONFlag) 
						{
							if(BtPHFCONFlag)BT_Addr[12] = 1;/*phone connect*/
							if(BtSPPCONFlag)BT_Addr[12] = 2;/*spp connect*/
							if(BtGATTCONFlag)BT_Addr[12] = 3;/*ble connect*/
						}

						sch_memcpy(pData+1,BT_Addr,sizeof(BT_Addr));
						
							
						length_data += sizeof(BT_Addr);
					}
					else if(index == 0x02)
					{
						sch_memcpy(pData+1,BLE_GVER,sizeof(BLE_GVER));
						length_data += sizeof(BLE_GVER);
					}
					break;
				case 0x0D:///������
					pData[length_data++] = index;
					if(index == 0x01)
					{
						pData[length_data++] = VolData;
						pData[length_data++] = DSP_VOL_MAX;
					}
					break;
				case 0x0E:
					pData[length_data++] = Get_DSP_OFF_Flag ? 0x01 : 0x02;
					break;

				case 0x14:///EQ_1 first 8byte
					pData[length_data++] = index;
					{
						SCH_U8 Channel = index/EQ_NUM_CNT;
						EQ_NUM_T EQ_NUM = (EQ_NUM_T)(index%EQ_NUM_CNT);
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Other.byte;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].MODE0;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Boost>>8;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Boost;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Freq>>24;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Freq>>16;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Freq>>8;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Freq;
					}
					break;
				case 0x15:///EQ_2 last 4byte
					pData[length_data++] = index;
					{
						SCH_U8 Channel = index/EQ_NUM_CNT;
						EQ_NUM_T EQ_NUM = (EQ_NUM_T)(index%EQ_NUM_CNT);

						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Gain>>8;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Gain;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Q_Factor>>8;
						pData[length_data++] = App_Dsp.Dsp_Data.EQ_Data[Channel][EQ_NUM].Q_Factor;
					}
					break;
						
				default:break;
			}
			break;
		case M2B_DSP_UPDATA:///
			switch(sub_id)
			{
				case 0x00:
					pData[length_data++] = index;
					if(index==0x82)///����FLASH�ɹ�
						pData[length_data++] = App_Dsp.DspNum;
					else
						pData[length_data++] = App_Dsp.DspUpdataNum;
					break;
				case 0x01:///��Ӧ����
					pData[length_data++] = index;
					pData[length_data++] = App_Dsp.DspUpdataLen>>24;
					pData[length_data++] = App_Dsp.DspUpdataLen>>16;
					pData[length_data++] = App_Dsp.DspUpdataLen>>8;
					pData[length_data++] = App_Dsp.DspUpdataLen;
					break;
				case 0x02:///��Ӧ����
					pData[length_data++] = index;
					pData[length_data++] = App_Dsp.DspUpdataSn;
					{
						SCH_U8 i;
						SCH_U8 *UpData = (SCH_U8 *)(&App_Dsp.Dsp_Data);
						UpData += (64*App_Dsp.DspUpdataSn);
						///length_data += App_Dsp.DspUpdataCnt;
						///sch_memcpy(pData+2,UpData,App_Dsp.DspUpdataCnt);
						for(i=0;i<App_Dsp.DspUpdataCnt;i++)
						{
							pData[length_data++] = *UpData;
							UpData++;
						}
					}
					break;
				case 0x03:///���󳤶Ⱥ�У��
					pData[length_data++] = index;
					break;
				case 0x04:///���������
					pData[length_data++] = index;
					pData[length_data++] = App_Dsp.DspUpdataSn;
					break;
				default:break;
			}
			break;
		default:break;
	}
	
	BtTxModuel.TxData[0] = 'A';
	BtTxModuel.TxData[1] = 'T';
	BtTxModuel.TxData[2] = '>';
	BtTxModuel.TxData[3] = 0x01;/*DATA TYPE:0X0102 SPP���ݣ�0x0101 BLE����*/
	
	if(BtGATTCONFlag)
		BtTxModuel.TxData[4] = 0x01;
	else if(BtSPPCONFlag)
		BtTxModuel.TxData[4] = 0x02;
	else
	{
		BtTxModuel.TxData[4] = 0x02;
		//printf("\n\n--DATA TYPE ERR--\n\n");
	}
	BtTxModuel.TxData[5] = 0x00;/*length H:��0x80��ʼ��0x0d����*/
	BtTxModuel.TxData[6] = length_data+7+3;/*length L*/
	BtTxModuel.TxData[7] = 0x80;
	BtTxModuel.TxData[8] = 0x00;
	BtTxModuel.TxData[9] = 0x0d;/*\r*/

	BtTx_Head1 = HEAD_ADDRESS_MCU;
	BtTx_Head2 = HEAD_ADDRESS_BT;
	BtTx_Length = length_data+7;//+1+10;
	BtTx_Sequence++;
	BtTx_GroupID = pMsg.ID;
	BtTx_SubID = sub_id;
	BtTxModuel.TxData_Parity = GetCheckData_Xor(&BtTx_Head1,BtTx_Length-1);
	BtTxModuel.TxData[BtTx_Length+10-1] = BtTxModuel.TxData_Parity;
	BtTxModuel.TxData[BtTx_Length+10] = 0x0d;/*\r*/
	//UartTxData(Uart_CONNECT, BtTxModuel.TxData, BtTx_Length+1+10);
	if(Uart_CONNECT == SCH_Uart_BT)
	{
		for(i = 0;i<(BtTx_Length+1+10);i++)
		USB_Rx_Buf[i] = BtTxModuel.TxData[i];
		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, USB_Rx_Buf, sizeof(USB_Rx_Buf));
	}
	else if(Uart_CONNECT == SCH_Uart_PC)
	HAL_UART_Transmit_IT(&huart2, BtTxModuel.TxData, BtTx_Length+1+10);
	
	Printf("Tx data : ");
	for(i = 0;i<BtTx_Length+1+10;i++)
	Printf(" %x",BtTxModuel.TxData[i]);
	
	BtTxModuel.Check_Ack=1;
	BtTxModuel.Check_ResendCounte=0;
	BtTxModuel.Check_ResendTimer=0;
	BtTxModuel.Check_Busy=1;
}
/********************************************************************************
**  Function	: TASK_Bt_Pro
**  Author		: 
**  Created on	: 20190402
**  Description	:
**  Return		: 
********************************************************************************/
void TASK_Bt_Pro(void)
{
#if 1
	if(/*Get_OsStartOk==OFF||*/Get_SysPower_Flag==OFF)  
	{
		return;
	}
	if(BtTxModuel.Check_Ack)
	{
		BtTxModuel.Check_ResendTimer++;
		if(((BtTxModuel.Check_ResendTimer==T200MS_8)&&(Uart_CONNECT == SCH_Uart_PC))
			||((BtTxModuel.Check_ResendTimer==T200MS_8)&&(Uart_CONNECT == SCH_Uart_PC1))
			||((BtTxModuel.Check_ResendTimer==T2S_8)&&(Uart_CONNECT == SCH_Uart_BT)))
		{  	
			BtTxModuel.Check_ResendTimer=0;
			if(++BtTxModuel.Check_ResendCounte<3)
			{
				 UartTxData(Uart_CONNECT, BtTxModuel.TxData, BtTx_Length+11);
			}
			else
			{
				BtTxModuel.Check_ResendCounte=0;
				BtTxModuel.Check_Busy=0;
				BtTxModuel.Check_Ack=0;
			}
		}
	}
	else if(!BtTxModuel.Check_Busy)
	{
		M2B_TxService();
	}
 #endif
}

