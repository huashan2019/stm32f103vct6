///=========================
#ifndef __APP_DSP_DRIVER_H
#define __APP_DSP_DRIVER_H

#define DEVICE_ADDR_IC_1                          0x0

///=========================================================================DSP IO========  
#define Spi_DSP            SCH_Spi2

#define SPI_DSP_SS          SPI2_CS_GPIO_Port//GPIOB12
#define DSP_SS_HIGH()       HAL_GPIO_WritePin(SPI_DSP_SS, SPI2_CS_Pin, GPIO_PIN_SET)//GPIO_PinSet(SPI_DSP_SS)
#define DSP_SS_LOW()        HAL_GPIO_WritePin(SPI_DSP_SS, SPI2_CS_Pin, GPIO_PIN_RESET)//GPIO_PinClear(SPI_DSP_SS)
///#define DSP_RESET_CTL		    
#define IO_DSP_RESET                 DSP_RESET_GPIO_Port//GPIOD
#define GPIO_DSP_RESET_CTL           DSP_RESET_Pin//GPIO12//////
#define DSP_RESET_RELEASE        	 HAL_GPIO_WritePin(IO_DSP_RESET,GPIO_DSP_RESET_CTL,GPIO_PIN_SET)//GPIO_PinSet(GPIO_DSP_RESET_CTL)
#define DSP_RESET_HOLD               HAL_GPIO_WritePin(IO_DSP_RESET,GPIO_DSP_RESET_CTL,GPIO_PIN_RESET)//GPIO_PinClear(GPIO_DSP_RESET_CTL)
///#define IO_REM_EN                 REM_CTRL_Pin//GPIOE
#define GPIO_REM_EN_CTL      	     //GPIO4///
#define TurnOn_REM_EN        	     HAL_GPIO_WritePin(REM_CTRL_GPIO_Port,REM_CTRL_Pin,GPIO_PIN_SET);//GPIO_PinSet(GPIO_REM_EN_CTL)
#define TurnOff_REM_EN       	     HAL_GPIO_WritePin(REM_CTRL_GPIO_Port,REM_CTRL_Pin,GPIO_PIN_RESET);//GPIO_PinClear(GPIO_REM_EN_CTL)
extern void DSP_IO_Init(void);
///===================DSP END=============================================================
extern void default_download_IC_1(void);
extern void SIGMA_READ(SCH_U8 devAddress, SCH_U16 address, SCH_U8 *pData);
extern void SIGMA_WRITE_DELAY(SCH_U8 devAddress, SCH_U16 length, const SCH_U8 *pData);
extern void SIGMA_WRITE_REGISTER_BLOCK(SCH_U8 devAddress, SCH_U16 address, SCH_U16 length, const SCH_U8 *pData);
extern void SIGMA_SAFELOAD_WRITE_REGISTER(SCH_U8 devAddress, SCH_U16 address, SCH_U16 length, SCH_U8 *pData);
#endif
