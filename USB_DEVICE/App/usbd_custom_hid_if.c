/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_custom_hid_if.c
  * @version        : v2.0_Cube
  * @brief          : USB Device Custom HID interface file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_custom_hid_if.h"

/* USER CODE BEGIN INCLUDE */
#include "include.h"

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @addtogroup USBD_CUSTOM_HID
  * @{
  */

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions USBD_CUSTOM_HID_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Defines USBD_CUSTOM_HID_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */

/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Macros USBD_CUSTOM_HID_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Variables USBD_CUSTOM_HID_Private_Variables
  * @brief Private variables.
  * @{
  */

/** Usb HID report descriptor. */
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
  /* USER CODE BEGIN 0 */
 /* USER CODE BEGIN 0 */
 // 0x00,
  0x06, 0x00, 0xff, 			 // USAGE_PAGE (Vendor Defined Page 1) ��ʾһ�����ı�ǩ֮�����;���?
  0x09, 0x01,					 // USAGE (Vendor Usage 1) ��ʾһ������ID��־
  0xa1, 0x01,					 // COLLECTION (Application) ��ʾӦ�ü��ϣ�Ҫ����������0xc0������
  
  
  0x09, 0x01,					 //   USAGE (Vendor Usage 1)ͬ��ͬ������
  0x15, 0x00,					 //   LOGICAL_MINIMUM (0)  ͬ��ͬ������
  0x26, 0xff, 0x00, 			 //   LOGICAL_MAXIMUM (255) ͬ��ͬ������
  0x95, 0x40,					 //   REPORT_COUNT (64)����ͬ��REPORT_COUNT
  0x75, 0x08,					 //   REPORT_SIZE (8)������ͬ��REPORT_SIZE
  0x81, 0x02,					 //   INPUT (Data,Var,Abs)����ʾUSBҪ�������ݵ�PC�Ĺ���
  
  
  0x09, 0x01,					 //   USAGE (Vendor Usage 1) ÿ�����ܵ�һ������?
  0x15, 0x00,					 //   LOGICAL_MINIMUM (0)	 ��ʾÿ�����������޶�Ϊ0
  0x26, 0xff, 0x00, 			 //   LOGICAL_MAXIMUM (255)    ��ʾÿ���������ݵ����ֵ�޶��?255
  0x95, 0x40,					 //   REPORT_COUNT (64) ÿ�ν��յ����ݳ��ȣ�������64λ
  0x75, 0x08,					 //   REPORT_SIZE (8)		 �����ֶεĿ���?8bit����ʾÿ����������ݷ�Χ�?0~ffff ffff
  0x91, 0x02,					 //   OUTPUT (Data,Var,Abs) ��ʾUSB�豸Ҫ����PC�����ݵĹ���

  /* USER CODE END 0 */
  0xC0    /*     END_COLLECTION	             */
};

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Exported_Variables USBD_CUSTOM_HID_Exported_Variables
  * @brief Public variables.
  * @{
  */
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */
extern unsigned char USB_Rx_Buf[64];
extern unsigned char USB_Received_Count;

/* USER CODE END EXPORTED_VARIABLES */
/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes USBD_CUSTOM_HID_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state);

/**
  * @}
  */

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
{
  CUSTOM_HID_ReportDesc_FS,
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS
};

/** @defgroup USBD_CUSTOM_HID_Private_Functions USBD_CUSTOM_HID_Private_Functions
  * @brief Private functions.
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  DeInitializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Manage the CUSTOM HID class events
  * @param  event_idx: Event index
  * @param  state: Event state
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state)
{
  /* USER CODE BEGIN 6 */
     char i;
     //HAL_GPIO_TogglePin(GPIOE,LED1_Pin);
    
    /*�鿴�������ݳ���
    USB_Received_Count = USBD_GetRxCount( &hUsbDeviceFS,CUSTOM_HID_EPOUT_ADDR );
    printf("USB_Received_Count = %d \r\n",USB_Received_Count);
    
    USB_Received_Count = USBD_GetRxCount( &hUsbDeviceFS,CUSTOM_HID_EPIN_ADDR  );
    printf("USB_Received_Count_in = %d \r\n",USB_Received_Count);
    */
    
  USBD_CUSTOM_HID_HandleTypeDef   *hhid;
  hhid = (USBD_CUSTOM_HID_HandleTypeDef*)hUsbDeviceFS.pClassData;
    for(i=0;i<64;i++) 
    {   
        USB_Rx_Buf[i]=hhid->Report_buf[i];
		Uart_Rx_DataPro(SCH_Uart0, hhid->Report_buf[i]);
        printf("USB_Rx_Buf[%d] = 0x%x \r\n",i,USB_Rx_Buf[i]);
		USB_Received_Count = 64;
		if(i>=hhid->Report_buf[2]-1) break;
    } 
	
  return (USBD_OK);
  /* USER CODE END 6 */
}

/* USER CODE BEGIN 7 */
/**
  * @brief  Send the report to the Host
  * @param  report: The report to be sent
  * @param  len: The report length
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
/*
static int8_t USBD_CUSTOM_HID_SendReport_FS(uint8_t *report, uint16_t len)
{
  return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, report, len);
}
*/
/* USER CODE END 7 */

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

