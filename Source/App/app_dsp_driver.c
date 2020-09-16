/*
***************************************************************************************************
**  Copyright   : 
**  Project     : STM32F103VCT6
**  File        : app_dsp_driver.c  ---   ��dsp����
**  Description : 
**  Author      : lvhuashan
**  Created on  : 2019.04.02
**  Note        : NULL
***************************************************************************************************
*/
#include "include.h"
extern osMutexId_t myMutex05Handle;
extern osMutexId_t myMutex06Handle;
extern osMutexId_t myMutex07Handle;

/********************************************************************************
**  Function	: DSP_IO_Ctl
**  Author		: 
**  Created on	: 20171220
**  Description	:
**  Return		: 
********************************************************************************/
void DSP_IO_Init(void)
{///===
	//GPIO_PinInit(GPIO_DSP_RESET_CTL, GPIO_PinOutput);
	//GPIO_PinInit(GPIO_REM_EN_CTL,    GPIO_PinOutput);
	//HAL_GPIO_Init(SPI_DSP_SS,SPI2_CS_Pin);
	//DSP_SS_HIGH();
}
/********************************************************************************
**  Function	: SIGMA_READ SIGMA_WRITE
**  Author		: 
**  Created on	: 20190402
**  Description	: ��д
**  Return		: 
********************************************************************************/
void SIGMA_READ(DspNum_T DspNum, SCH_U8 devAddress, SCH_U16 address, SCH_U8 *pData)
{
	SCH_U8 length = 4;
	static Spi_T spi;
	
	if(DspNum == SCH_DSP1)	
	{
		spi = Spi_DSP;
		DSP_SS_LOW();///DSP1
	}
	else
	{
		spi = Spi_DSP2;
		DSP2_SS_LOW();///DSP2
	}

	SPI_RW(spi,devAddress);
	SPI_RW(spi,address>>8);
	SPI_RW(spi,address);
	while(length--)
	{
		*pData++ = SPI_RW(spi,0xFF);
	}
	if(DspNum == SCH_DSP1)
	{
		DSP_SS_HIGH();
		App_Printf("\r\n DSP1 RD:Adr=%x,Data:=%x",address,*pData,*(pData+1),*(pData+2),*(pData+3));
	}
	else
	{
		DSP2_SS_HIGH();
		App_Printf("\r\n DSP2 RD:Adr=%x,Data:=%x",address,*pData,*(pData+1),*(pData+2),*(pData+3));
	}
	
}
void SIGMA_WRITE(DspNum_T DspNum, SCH_U8 devAddress, SCH_U16 address, SCH_U8 *pData)
{
	static Spi_T spi;
	SCH_U8 length = 4;
	if(DspNum == SCH_DSP1)
	{
		App_Printf("\r\n DSP1 WR:Adr=%x,Data:=%x",address,*pData,*(pData+1),*(pData+2),*(pData+3));
		spi = Spi_DSP;
		DSP_SS_LOW();///DSP1
	}
	else
	{
		App_Printf("\r\n DSP2 WR:Adr=%x,Data:=%x",address,*pData,*(pData+1),*(pData+2),*(pData+3));
		spi = Spi_DSP2;
		DSP2_SS_LOW();///DSP2
	}

	SPI_RW(spi,devAddress);
	SPI_RW(spi,address>>8);
	SPI_RW(spi,address);
	while(length--)
	{
		SPI_RW(spi,*pData++);
	}
	if(DspNum == SCH_DSP1)	
		DSP_SS_HIGH();
	else
		DSP2_SS_HIGH();
	SysWaitUs(50);
	
}
/********************************************************************************
**  Function	: SIGMA_SAFELOAD_WRITE_REGISTER
**  Author		: 
**  Created on	: 20190402
**  Description	: ��ȫд
**  Return		: 
********************************************************************************/
void SIGMA_SAFELOAD_WRITE_REGISTER(DspNum_T DspNum,SCH_U8 devAddress, SCH_U16 address, SCH_U16 length, SCH_U8 *pData)
{
	SCH_U8 spiBuff[4];
	SCH_U8 index;
	for(index=0;index<length;index++)
	{
		SIGMA_WRITE(DspNum,devAddress,MOD_SAFELOADMODULE_DATA_SAFELOAD0_ADDR+index,  pData);
		pData+=4;
	}
	spiBuff[0] = 0x00;
	spiBuff[1] = 0x00;
	spiBuff[2] = address>>8;
	spiBuff[3] = address;
	SIGMA_WRITE(DspNum,devAddress,MOD_SAFELOADMODULE_ADDRESS_SAFELOAD_ADDR,spiBuff);
	spiBuff[0] = 0x00;
	spiBuff[1] = 0x00;
	spiBuff[2] = 0x00;
	spiBuff[3] = length;
	SIGMA_WRITE(DspNum,devAddress,MOD_SAFELOADMODULE_NUM_SAFELOAD_ADDR,spiBuff);
	SysWaitUs(50);
}
/********************************************************************************
**  Function	: SIGMA_WRITE_REGISTER_BLOCK
**  Author		: 
**  Created on	: 20190402
**  Description	: ֱ��д
**  Return		: 
********************************************************************************/
void SIGMA_WRITE_REGISTER_BLOCK(DspNum_T DspNum,SCH_U8 devAddress, SCH_U16 address, SCH_U16 length, const SCH_U8 *pData)
{
	static Spi_T spi;
	if(DspNum == SCH_DSP1)	
	{
		App_Printf("\r\n DSP1 BLOCK:Add=%x Data:=%x,%x,%x,%x",address,*pData,*(pData+1),*(pData+2),*(pData+3));
		spi = Spi_DSP;
		DSP_SS_LOW();///DSP1
	}
	else
	{
		App_Printf("\r\n DSP2 BLOCK:Add=%x Data:=%x,%x,%x,%x",address,*pData,*(pData+1),*(pData+2),*(pData+3));
		spi = Spi_DSP2;
		DSP2_SS_LOW();///DSP2
	}

	SPI_RW(spi,devAddress);
	SPI_RW(spi,address>>8);
	SPI_RW(spi,address);
	while(length--)
	{
		SPI_RW(spi,*pData++);
	}
	if(DspNum == SCH_DSP1)	
		DSP_SS_HIGH();
	else
		DSP2_SS_HIGH();
	SysWaitUs(500);
}

void SIGMA_WRITE_DELAY(DspNum_T DspNum,SCH_U8 devAddress, SCH_U16 length, const SCH_U8 *pData)
{
	static Spi_T spi;
	if(DspNum == SCH_DSP1)	
	{
		App_Printf("\r\n DSP1 DELAY:devAddress=%x Data:=%x",devAddress,*pData,*(pData+1),*(pData+2),*(pData+3));
		spi = Spi_DSP;
		DSP_SS_LOW();///DSP1
	}
	else
	{
		App_Printf("\r\n DSP2 DELAY:devAddress=%x Data:=%x",devAddress,*pData,*(pData+1),*(pData+2),*(pData+3));
		spi = Spi_DSP2;
		DSP2_SS_LOW();///DSP2
	}

	SPI_RW(spi,devAddress);
	while(length--)
	{
		SPI_RW(spi,*pData++);
	}
	if(DspNum == SCH_DSP1)	
		DSP_SS_HIGH();
	else
		DSP2_SS_HIGH();

	SysWaitUs(500);
}







