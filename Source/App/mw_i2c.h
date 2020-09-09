///=========================
#ifndef __MW_I2C_H
#define __MW_I2C_H

/**************************************************************************************
* FunctionName   : I2C0
**************************************************************************************/
#define IO_I2C0_SCL                   	GPIO_PIN_10///
#define IO_I2C0_SDA                  	GPIO_PIN_11///
#define I2C0_GPIO_Port                	GPIOB///

#define I2C0_SCL_OUT_1        		HAL_GPIO_WritePin(I2C0_GPIO_Port, IO_I2C0_SCL, GPIO_PIN_SET)
#define I2C0_SCL_OUT_0              HAL_GPIO_WritePin(I2C0_GPIO_Port, IO_I2C0_SCL, GPIO_PIN_RESET)
#define I2C0_SCL_IN                 HAL_GPIO_ReadPin(I2C0_GPIO_Port,IO_I2C0_SCL)
#define I2C0_SCL_DDR_1              SCH_GPIO_PinInit(I2C0_GPIO_Port,IO_I2C0_SCL, GPIO_MODE_OUTPUT_PP)
#define I2C0_SCL_DDR_0              SCH_GPIO_PinInit(I2C0_GPIO_Port,IO_I2C0_SCL, GPIO_MODE_INPUT)
#define I2C0_SDA_OUT_1              HAL_GPIO_WritePin(I2C0_GPIO_Port, IO_I2C0_SDA, GPIO_PIN_SET)
#define I2C0_SDA_OUT_0              HAL_GPIO_WritePin(I2C0_GPIO_Port, IO_I2C0_SDA, GPIO_PIN_RESET)
#define I2C0_SDA_IN                 HAL_GPIO_ReadPin(I2C0_GPIO_Port,IO_I2C0_SDA)//(GPIOA->PDIR & (1<<(IO_I2C0_SDA%32)))///GPIO_ReadInputPin(IO_I2C0_SDA)
#define I2C0_SDA_DDR_1              SCH_GPIO_PinInit(I2C0_GPIO_Port,IO_I2C0_SDA, GPIO_MODE_OUTPUT_PP)
#define I2C0_SDA_DDR_0              SCH_GPIO_PinInit(I2C0_GPIO_Port,IO_I2C0_SDA, GPIO_MODE_INPUT)
/**************************************************************************************
* FunctionName   : I2C1
**************************************************************************************/
#define IO_I2C1_SCL                   GPIO_PIN_8///
#define IO_I2C1_SDA                   GPIO_PIN_9///
#define I2C1_GPIO_Port                GPIOB///

#define I2C1_SCL_OUT_1                HAL_GPIO_WritePin(I2C1_GPIO_Port, IO_I2C1_SCL, GPIO_PIN_SET)
#define I2C1_SCL_OUT_0                HAL_GPIO_WritePin(I2C1_GPIO_Port, IO_I2C1_SCL, GPIO_PIN_RESET)
#define I2C1_SCL_IN                   HAL_GPIO_ReadPin(I2C1_GPIO_Port,IO_I2C1_SCL)
#define I2C1_SCL_DDR_1                SCH_GPIO_PinInit(I2C1_GPIO_Port,IO_I2C1_SCL, GPIO_MODE_OUTPUT_PP)
#define I2C1_SCL_DDR_0                SCH_GPIO_PinInit(I2C1_GPIO_Port,IO_I2C1_SCL, GPIO_MODE_INPUT)

#define I2C1_SDA_OUT_1                HAL_GPIO_WritePin(I2C1_GPIO_Port, IO_I2C1_SDA, GPIO_PIN_SET)
#define I2C1_SDA_OUT_0                HAL_GPIO_WritePin(I2C1_GPIO_Port, IO_I2C1_SDA, GPIO_PIN_RESET)
#define I2C1_SDA_IN                   HAL_GPIO_ReadPin(I2C1_GPIO_Port,IO_I2C1_SDA)
#define I2C1_SDA_DDR_1                SCH_GPIO_PinInit(I2C1_GPIO_Port,IO_I2C1_SDA, GPIO_MODE_OUTPUT_PP)
#define I2C1_SDA_DDR_0                SCH_GPIO_PinInit(I2C1_GPIO_Port,IO_I2C1_SDA, GPIO_MODE_INPUT)


typedef enum{
   NACK=0,
   ACK
}ACK_STATE;

///=======================================================================================
extern void I2C0_Rx(SCH_U8 dest_add,SCH_U8 *buff,SCH_U8 nb);
extern void I2C0_Rx_A (SCH_U8 dest_add,SCH_U8 sub_add,SCH_U8 *buff,SCH_U8 nb);
extern SCH_BOOL I2C0_Tx(SCH_U8 dest_add,SCH_U8 *buff,SCH_U8 nb);
extern SCH_BOOL I2C0_Tx_A (SCH_U8 dest_add,SCH_U8 sub_add,SCH_U8 *buff,SCH_U8 nb);
extern void I2C0Init(void);
extern SCH_BOOL I2C0_IsFindAddr(SCH_U8 Addr);
///=======================================================================================
extern void I2C1_Rx(SCH_U8 dest_add,SCH_U8 *buff,SCH_U8 nb);
extern void I2C1_Rx_A (SCH_U8 dest_add,SCH_U8 sub_add,SCH_U8 *buff,SCH_U8 nb);
extern SCH_BOOL I2C1_Tx(SCH_U8 dest_add,SCH_U8 *buff,SCH_U8 nb);
extern SCH_BOOL I2C1_Tx_A (SCH_U8 dest_add,SCH_U8 sub_add,SCH_U8 *buff,SCH_U8 nb);
extern void I2C1Init(void);
extern SCH_BOOL I2C1_IsFindAddr(SCH_U8 Addr);

#endif
