/*
***************************************************************************************************
**  Copyright   : 
**  Project     : STM32F103VCT6
**  File        : mw_spi.c
**  Description : This file is the middleware.
**  Author      : lvhuashan
**  Created on  : 2020.07.22
**  Note        : NULL
***************************************************************************************************
*/
#include "include.h"
#include "spi.h"

#if SPI0_FUNC == SPI_MODE_INT
#define MAX_SPI0_TX_BUF       300
SCH_U8 Spi0_TX_buf[MAX_SPI0_TX_BUF];
QUEUE_T SPI0_TX_QUEUE = {0,0,0,MAX_SPI0_TX_BUF,1,Spi0_TX_buf};
#define MAX_SPI0_RX_BUF       300
SCH_U8 Spi0_RX_buf[MAX_SPI0_RX_BUF];
QUEUE_T SPI0_RX_QUEUE = {0,0,0,MAX_SPI0_RX_BUF,1,Spi0_RX_buf};
#endif
#if SPI1_FUNC == SPI_MODE_INT
#define MAX_SPI1_TX_BUF       10
SCH_U8 Spi1_TX_buf[MAX_SPI1_TX_BUF];
QUEUE_T SPI1_TX_QUEUE = {0,0,0,MAX_SPI1_TX_BUF,1,Spi1_TX_buf};
#define MAX_SPI1_RX_BUF       300
SCH_U8 Spi1_RX_buf[MAX_SPI1_RX_BUF];
QUEUE_T SPI1_RX_QUEUE = {0,0,0,MAX_SPI1_RX_BUF,1,Spi1_RX_buf};
#endif



QUEUE_T *const SpiBufAddr[][2] = 
{
#if SPI0_FUNC == SPI_MODE_INT
	&SPI0_RX_QUEUE,&SPI0_TX_QUEUE,
#else
	NULL,NULL,
#endif
#if SPI1_FUNC == SPI_MODE_INT
	&SPI1_RX_QUEUE,&SPI1_TX_QUEUE,
#else
	NULL,NULL,
#endif
};

uint8_t spi_tx_buff[10]={0xab,0xff,0xff,0xff,0xff};/*W25X16 read device id para*/
uint8_t spi_rx_buff[10];


SPI_HandleTypeDef *Spi_Arry[]={&hspi1,&hspi2,&hspi3};

SCH_U8 SPI_RW(Spi_T spi,SCH_U8 TxData)
{
	SCH_U8 RxData;
	HAL_SPI_TransmitReceive(Spi_Arry[spi],&TxData,&RxData,1,HAL_MAX_DELAY);
	return RxData;
}

/*test spi demo 20200722 lhs*/
uint8_t SPI_FLASH_ReadDeviceID(void)
{
	
	//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
	//HAL_SPI_Transmit(&hspi1,spi_tx_buff,4,HAL_MAX_DELAY);
	//HAL_SPI_Receive(&hspi1,spi_rx_buff,1,HAL_MAX_DELAY);	
	SPI_RW(SCH_Spi1,spi_tx_buff[0]);
	SPI_RW(SCH_Spi1,spi_tx_buff[1]);
	SPI_RW(SCH_Spi1,spi_tx_buff[1]);
	SPI_RW(SCH_Spi1,spi_tx_buff[1]);
	spi_rx_buff[0]=SPI_RW(SCH_Spi1,spi_tx_buff[1]);
	//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
	//printf("APP Begin -- DeviceId : %x \r\n", spi_rx_buff[0]);
	return(spi_rx_buff[0]);

}

void SpiBufInit(Spi_T spi,Spi_RT TxRx)
{
	if(SpiBufAddr[spi][TxRx])
		Queue_Init(SpiBufAddr[spi][TxRx]);
}
SCH_U16 SpiBufCnt(Spi_T spi,Spi_RT TxRx)
{
	QUEUE_T *pSpiBuf;
	pSpiBuf = SpiBufAddr[spi][TxRx];
	if(pSpiBuf)
		return Queue_Cnt(pSpiBuf);
	return 0;
}
SCH_BOOL SpiGetFromBuf(Spi_T spi, Spi_RT TxRx, SCH_U8 *data, SCH_U16 Len)
{
	QUEUE_T *pSpiBuf;
	pSpiBuf = SpiBufAddr[spi][TxRx];
	if(pSpiBuf)
		return Queue_Out(pSpiBuf, data, Len);
	return FALSE;
}
SCH_BOOL SpiPutToBuf(Spi_T spi, Spi_RT TxRx, SCH_U8 *const data, SCH_U16 Len)
{
	QUEUE_T *pSpiBuf;
	pSpiBuf = SpiBufAddr[spi][TxRx];
	if(pSpiBuf)
		return Queue_In(pSpiBuf, data,Len);
	return FALSE;
}
/********************************************************************************
**  Function	: SpiSendData8
**  Author		: lvhuashan
**  Created on	: 20171218
**  Description	: ����һ��8λ������
**  Return		: void
********************************************************************************/
void SpiSendData8(Spi_T spi,SCH_U8 u8data)
{
	//SPI_WriteDataReg(Spi_Arry[spi], u8data);
	HAL_SPI_Transmit(Spi_Arry[spi],&u8data,1,HAL_MAX_DELAY);
}
/********************************************************************************
**  Function	: SpiTxInt En/Dis
**  Author		: lvhuashan
**  Created on	: 20171218
**  Description	:
**  Return		: void
********************************************************************************/
void SpiTxIntEn(Spi_T spi)
{
	//SPI_TxIntEnable(Spi_Arry[spi]);
	/* Enable TXE and ERR interrupt */
	__HAL_SPI_ENABLE_IT(Spi_Arry[spi], (SPI_IT_TXE | SPI_IT_ERR));
}
void SpiTxIntDis(Spi_T spi)
{
	//SPI_TxIntDisable(Spi_Arry[spi]);
	__HAL_SPI_DISABLE_IT(Spi_Arry[spi], (SPI_IT_TXE | SPI_IT_ERR));
}

/********************************************************************************
**  Function	: SpiRx/TxCnt
**  Author		: lvhuashan
**  Created on	: 20171218
**  Description	:
**  Return		: SCH_U16
********************************************************************************/
SCH_U16 SpiRxCnt(Spi_T spi)
{
	return SpiBufCnt(spi,Spi_Rx);
}
SCH_U16 SpiTxCnt(Spi_T spi)
{
	return SpiBufCnt(spi,Spi_Tx);
}
/********************************************************************************
**  Function    : Spi_Rx_DataPro
**  Author      : lvhuashan
**  Created on  : 20171218
**  Description	:  ---   int������ִ��
**  Return		: NULL
********************************************************************************/
void Spi_Rx_DataPro(Spi_T spi,SCH_U8 data)
{
	SpiPutToBuf(spi,Spi_Rx,&data,1);
}
/********************************************************************************
**  Function    : Spi_Tx_DataPro
**  Author      : lvhuashan
**  Created on  : 20160621
**  Description :   ---   int������ִ��
**  Return      : NULL
********************************************************************************/
void Spi_Tx_DataPro(Spi_T spi)
{
	SCH_U8 u8data;
	if(SpiTxCnt(spi) == 0)
	{
		SpiTxIntDis(spi);
		return;
	}
	if(SpiGetFromBuf(spi,Spi_Tx,&u8data,1))
	{
		SpiSendData8(spi, u8data);
		SpiTxIntEn(spi);
	}
}
/********************************************************************************
**  Function	: SpiRxData
**  Author		: lvhuashan
**  Created on	: 20171218
**  Description	:
**  Return		: BOOL
********************************************************************************/
SCH_BOOL SpiRxData(Spi_T spi, SCH_U8 *data, SCH_U16 Len)
{
	return SpiGetFromBuf(spi,Spi_Rx,data,Len);
}
/********************************************************************************
**  Function         : SpiTxData
**  Author           : lvhuashan
**  Created on       : 20160621
**  Description      :
**  Return           : BOOL
********************************************************************************/
SCH_BOOL SpiTxData(Spi_T spi, SCH_U8 *const data, SCH_U16 Len)
{
	if(SpiTxCnt(spi) != 0)
	{
		if(SpiPutToBuf(spi,Spi_Tx,data,Len))
			return TRUE;
		return FALSE;
	}
	if(SpiPutToBuf(spi,Spi_Tx,data,Len))
	{
		Spi_Tx_DataPro(spi);
		return TRUE;
	}
	return FALSE;
}
SCH_BOOL SpiTxData_Direct(Spi_T spi,const SCH_U8 *data, SCH_U16 Len)
{
#if 0
	while(Len--)
	{
		while(!SPI_IsSPTEF(Spi_Arry[spi]));
		SpiSendData8(spi,*data);
		data++;
	}
	return TRUE;
#endif
}
/********************************************************************************
**  Function    : Spi_IntSerive
**  Author      : lvhuashan
**  Created on  : 20170407
**  Description :  ---   int������ִ��
**  Return      : void
********************************************************************************/
void SPI_IntSerive(Spi_T spi)
{
#if 1
	HAL_SPI_IRQHandler(Spi_Arry[spi]);
#else

	SCH_U8 data;
	if(SPI_IsSPRF(Spi_Arry[spi])) /* Rx interrupt */
	{
		data = SPI_ReadDataReg(Spi_Arry[spi]);
		Spi_Rx_DataPro(spi, data);
	}
	if(SPI_IsSPTEF(Spi_Arry[spi]))/* Tx interrupt */
	{
		Spi_Tx_DataPro(spi);
	}
#endif
}



/********************************************************************************
**  Function    : SysSpiExit
**  Author      : 
**  Created on  : 20171215
**  Description :
**  Return      : BOOL
********************************************************************************/
void SysSpiExit(Spi_T spi)
{
	//SPI_ConfigType sSPIConfig = {0};
	switch(spi)
	{
		case SCH_Spi1:
#if 1
			MX_SPI1_Init();
#else
			SIM->SCGC &= ~SIM_SCGC_SPI0_MASK;
		    sSPIConfig.sSettings.bModuleEn             = 0;
		    sSPIConfig.sSettings.bMasterMode           = 0;
		    sSPIConfig.sSettings.bClkPhase1            = 0;
		    sSPIConfig.sSettings.bMasterAutoDriveSS    = 0;
		    SPI_Init(SPI0, &sSPIConfig);
			SPI_DeInit(Spi_Arry[spi]);
#endif
			break;
		case SCH_Spi2:
#if 1
			MX_SPI2_Init();
#else
			SIM->SCGC &= ~SIM_SCGC_SPI1_MASK;
		    sSPIConfig.sSettings.bModuleEn             = 0;
		    sSPIConfig.sSettings.bMasterMode           = 0;
		    sSPIConfig.sSettings.bClkPhase1            = 0;
		    sSPIConfig.sSettings.bMasterAutoDriveSS    = 0;
		    SPI_Init(SPI1, &sSPIConfig);
			SPI_DeInit(Spi_Arry[spi]);
#endif
			break;
		default:break;
	}
}

/********************************************************************************
**  Function    : SysSpiInit
**  Author      : 
**  Created on  : 20171215
**  Description :
**  Return      : BOOL
********************************************************************************/
SCH_BOOL SysSpiInit(Spi_T spi,SCH_U32 Baudrate)
{
	//SPI_ConfigType sSPIConfig = {0};
	switch(spi)
	{
		case SCH_Spi1:
#if 1
		MX_SPI1_Init();
#endif
			break;
		case SCH_Spi2:
#if 1
		MX_SPI2_Init();
#endif
			break;
		case SCH_Spi3:
#if 1
		MX_SPI3_Init();
#endif
			break;


		default:break;
	}		 
	SpiBufInit(spi, Spi_Tx);
	SpiBufInit(spi, Spi_Rx);
	return TRUE;
}

