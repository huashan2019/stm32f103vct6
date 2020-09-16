///=========================
#ifndef __APP_DSP_DRIVER_H
#define __APP_DSP_DRIVER_H
typedef enum
{
	SCH_DSP1,
	SCH_DSP2,
	SCH_DSP_Num
}DspNum_T;


#define DEVICE_ADDR_IC_1                          0x0
//DSP1端口定义
///=========================================================================DSP IO========  
#define Spi_DSP            SCH_Spi2

#define SPI_DSP_SS          SPI2_CS_GPIO_Port//GPIOB12
#define GPIO_DSP_SS_CTL           SPI2_CS_Pin//
#define DSP_SS_HIGH()       HAL_GPIO_WritePin(SPI_DSP_SS, GPIO_DSP_SS_CTL, GPIO_PIN_SET)//GPIO_PinSet(SPI_DSP_SS)
#define DSP_SS_LOW()        HAL_GPIO_WritePin(SPI_DSP_SS, GPIO_DSP_SS_CTL, GPIO_PIN_RESET)//GPIO_PinClear(SPI_DSP_SS)
///#define DSP_RESET_CTL		    
#define IO_DSP_RESET                 DSP_RESET_GPIO_Port//GPIOD12
#define GPIO_DSP_RESET_CTL           DSP_RESET_Pin//
#define DSP_RESET_RELEASE        	 HAL_GPIO_WritePin(IO_DSP_RESET,GPIO_DSP_RESET_CTL,GPIO_PIN_SET)//GPIO_PinSet(GPIO_DSP_RESET_CTL)
#define DSP_RESET_HOLD               HAL_GPIO_WritePin(IO_DSP_RESET,GPIO_DSP_RESET_CTL,GPIO_PIN_RESET)//GPIO_PinClear(GPIO_DSP_RESET_CTL)


//DSP2端口定义
///=========================================================================DSP IO========  
#define Spi_DSP2            	SCH_Spi3

#define SPI_DSP2_SS          	SPI3_CS_GPIO_Port//GPIOA15
#define GPIO_DSP2_SS_CTL     	SPI3_CS_Pin//
#define DSP2_SS_HIGH()       	HAL_GPIO_WritePin(SPI_DSP2_SS, GPIO_DSP2_SS_CTL, GPIO_PIN_SET)//GPIO_PinSet(SPI_DSP_SS)
#define DSP2_SS_LOW()        	HAL_GPIO_WritePin(SPI_DSP2_SS, GPIO_DSP2_SS_CTL, GPIO_PIN_RESET)//GPIO_PinClear(SPI_DSP_SS)
///#define DSP_RESET_CTL		    
//#define IO_DSP3_RESET                 DSP_RESET_GPIO_Port//GPIOD
//#define GPIO_DSP3_RESET_CTL           DSP_RESET_Pin//GPIO12//////
//#define DSP3_RESET_RELEASE        	 HAL_GPIO_WritePin(IO_DSP_RESET,GPIO_DSP_RESET_CTL,GPIO_PIN_SET)//GPIO_PinSet(GPIO_DSP_RESET_CTL)
//#define DSP3_RESET_HOLD               HAL_GPIO_WritePin(IO_DSP_RESET,GPIO_DSP_RESET_CTL,GPIO_PIN_RESET)//GPIO_PinClear(GPIO_DSP_RESET_CTL)

//REM端口定义
///=========================================================================DSP IO========  
//#define GPIO_REM_EN_CTL      	     //GPIO4///
#define TurnOn_REM_EN        	     HAL_GPIO_WritePin(REM_CTRL_GPIO_Port,REM_CTRL_Pin,GPIO_PIN_SET);//GPIO_PinSet(GPIO_REM_EN_CTL)
#define TurnOff_REM_EN       	     HAL_GPIO_WritePin(REM_CTRL_GPIO_Port,REM_CTRL_Pin,GPIO_PIN_RESET);//GPIO_PinClear(GPIO_REM_EN_CTL)








extern void DSP_IO_Init(void);
///===================DSP END=============================================================
extern void default_download_IC_1(void);
extern void SIGMA_READ(DspNum_T DspNum, SCH_U8 devAddress, SCH_U16 address, SCH_U8 *pData);
extern void SIGMA_WRITE_DELAY(DspNum_T DspNum,SCH_U8 devAddress, SCH_U16 length, const SCH_U8 *pData);
extern void SIGMA_WRITE_REGISTER_BLOCK(DspNum_T DspNum,SCH_U8 devAddress, SCH_U16 address, SCH_U16 length, const SCH_U8 *pData);
extern void SIGMA_SAFELOAD_WRITE_REGISTER(DspNum_T DspNum,SCH_U8 devAddress, SCH_U16 address, SCH_U16 length, SCH_U8 *pData);
#endif
