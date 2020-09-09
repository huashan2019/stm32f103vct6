///=========================
#ifndef __MW_GPIO_H
#define __MW_GPIO_H

typedef struct 
{
	SCH_U8 IO_Status;
	SCH_U8 IO_SamplingCounter;
}IO_DET_T;

//extern SCH_BOOL GPIO_ReadInputPin(GPIO_PinType GPIO_Pin);
///=======================================================================================ACC===========
///#define IO_DSP_TEST                 GPIOC
#define GPIO_DSP_TEST_DECT            //GPIO_PTI5///
#define DSP_TEST_DET_LEVEL            //GPIO_ReadInputPin(GPIO_DSP_TEST_DECT)
#define DSP_TEST_DET_LVON             //(LOW_LEVEL==DSP_TEST_DET_LEVEL)
#define DSP_TEST_DET_LVOFF            //(HIGH_LEVEL==DSP_TEST_DET_LEVEL)
extern SCH_BOOL DSP_OFF_FLAG;
extern void DSP_TEST_Init(void);
extern void DSP_Test_Detect(void);
///===================ACC END============================


///==============================================================================================BT========
///#define DSP_RESET_CTL		    
#define IO_BT_RESET                 BT_REST_GPIO_Port//GPIOA
#define GPIO_BT_RESET_CTL           BT_REST_Pin//GPIO_PTA7//////
#define BT_RESET_RELEASE            HAL_GPIO_WritePin(IO_BT_RESET, GPIO_BT_RESET_CTL, GPIO_PIN_SET)//GPIO_PinSet(GPIO_BT_RESET_CTL)
#define BT_RESET_HOLD               HAL_GPIO_WritePin(IO_BT_RESET, GPIO_BT_RESET_CTL, GPIO_PIN_RESET)//GPIO_PinClear(GPIO_BT_RESET_CTL)
///===================BT END========================================   



///==============================================================================================SYS PWR========      
#define IO_SYS_POWER              	 SYS_POW_EN_GPIO_Port//GPIOE
#define GPIO_SYS_POWER_CTL      	 SYS_POW_EN_Pin//GPIO6//////
#define TurnOn_SYS_POWER        	 HAL_GPIO_WritePin(IO_SYS_POWER, GPIO_SYS_POWER_CTL, GPIO_PIN_SET)//GPIO_PinSet(GPIO_SYS_POWER_CTL)
#define TurnOff_SYS_POWER       	 HAL_GPIO_WritePin(IO_SYS_POWER, GPIO_SYS_POWER_CTL, GPIO_PIN_SET)//GPIO_PinClear(GPIO_SYS_POWER_CTL)
extern void SYS_Power_Ctl(SCH_BOOL OnOff);
#define IO_ACC_EN              //GPIOB
#define GPIO_ACC_EN_CTL      	 //GPIO_PTF5//////
#define TurnOn_ACC_EN        	 //GPIO_PinSet(GPIO_ACC_EN_CTL)
#define TurnOff_ACC_EN       	 //GPIO_PinClear(GPIO_ACC_EN_CTL)
extern void ACC_EN_Ctl(SCH_BOOL OnOff);
///========================================SYS PWR END========================= 

///=============================================================================================SYS_3V3=======
#define IO_SYS_3V3               //GPIOB
#define GPIO_SYS_3V3_CTL      	 //GPIO_PTH7//////
#define SYS_3V3_ON          	 //GPIO_PinSet(GPIO_SYS_3V3_CTL)
#define SYS_3V3_OFF         	 //GPIO_PinClear(GPIO_SYS_3V3_CTL)
///===================ACC_3V3 END========================= 

///=============================================================================================SYS_12V=======
#define IO_SYS_12V                  // GPIOB
#define GPIO_SYS_12V_CTL      	    // GPIO_PTE1
#define SYS_12V_ON        	         //GPIO_PinSet(GPIO_SYS_12V_CTL)
#define SYS_12V_OFF       	         //GPIO_PinClear(GPIO_SYS_12V_CTL)
///===================SYS_12V END========================= 

///==========================================================================================AMP===����========      
///#define AMP_CTL		    
#define IO_AMP                 POW_AMP_STANDBY_GPIO_Port//GPIOC
#define GPIO_AMP_CTL           POW_AMP_STANDBY_Pin//GPIO8//////
#define TurnOn_AMP        	   HAL_GPIO_WritePin(POW_AMP_STANDBY_GPIO_Port, POW_AMP_STANDBY_Pin, GPIO_PIN_SET)
#define TurnOff_AMP       	   HAL_GPIO_WritePin(POW_AMP_STANDBY_GPIO_Port, POW_AMP_STANDBY_Pin, GPIO_PIN_RESET);
///#define AMP_BEEP		    
#define IO_AMP_BEEP            //GPIOA
#define GPIO_AMP_BEEP          //GPIO_PTC5//////
#define TurnOn_AMP_BEEP        //GPIO_PinSet(GPIO_AMP_BEEP)
#define TurnOff_AMP_BEEP       //GPIO_PinClear(GPIO_AMP_BEEP)
///#define IO_AMP_DET          //GPIOB
#define GPIO_AMP_DECT          //GPIO_PTB5///
#define AMP_DET_LEVEL          //GPIO_ReadInputPin(GPIO_AMP_DECT)
#define AMP_DET_LVON           //(LOW_LEVEL==AMP_DET_LEVEL)
#define AMP_DET_LVOFF          //(HIGH_LEVEL==AMP_DET_LEVEL)
///===================AMP END========================= 


extern void SCH_GPIO_PinInit(GPIO_TypeDef* GPIOx,SCH_U32 GPIO_Pin,SCH_U32 GPIO_Mode);
extern void GPIOInit(void);
#endif
