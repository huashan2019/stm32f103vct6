///=========================
#ifndef __MW_FLASH_H
#define __MW_FLASH_H

/* flash 128k
+--------------------------------------------------------------------+
| boot program                  | 16k| 0x000 0000   ---   0x000 3FFF |
|--------------------------------------------------------------------|
| app program                   |100k| 0x000 4000   ---   0x001 CFFF |
|--------------------------------------------------------------------|
| flash data                    | 10k| 0x001 D000   ---   0x001 F7FF |
|--------------------------------------------------------------------|
| Password  data                | 512| 0x001 F800   ---   0x001 FBFF |
|--------------------------------------------------------------------|
| DspNum data                   | 512| 0x001 FA00   ---   0x001 FBFF |
|--------------------------------------------------------------------|
| iap flag                      | 512| 0x001 FC00   ---   0x001 FDFF |
|--------------------------------------------------------------------|
| Uart flag                     | 512| 0x001 FE00   ---   0x001 FFFF |
+--------------------------------------------------------------------+
*/

//#define FLASH_PAGE_SIZE               0x800///2k
#define FLASH_PAGE_CNT                5///The amount of data per page
#define FLASH_DATA_ADDR               0x08038000///Flash data basic addr
#define FLASH_DATA_ADDR_END			  0x08040000	


typedef enum
{
	FLASH_DATA_0,
	FLASH_DATA_1,
	FLASH_DATA_2,
	FLASH_DATA_3,	
	FLASH_DATA_MAX=0xA00
}FLASH_DATA;

typedef enum///���ٴ�ȡ - ÿ��ռ512�ֽ�
{
	FLASH_DATA_IDLE,
	FLASH_DATA_UART,
	FLASH_DATA_IAP,
	FLASH_DATA_DSPNUM,
	FLASH_DATA_PASSWORD
}FLASH_QUICK_DATA;

extern SCH_BOOL Flash_RD(FLASH_DATA flash_data, SCH_U32 *u32data);
extern SCH_BOOL Flash_RD_NUM(FLASH_DATA flash_data, void *data, SCH_U16 num);
extern SCH_BOOL Flash_WR(FLASH_DATA flash_data, SCH_U32 u32data);
extern SCH_BOOL Flash_WR_NUM(FLASH_DATA flash_data, void *data, SCH_U16 num);
extern SCH_BOOL Flash_Quick_RD(FLASH_QUICK_DATA flash_data, SCH_U32 *u32data);
extern SCH_BOOL Flash_Quick_RD_U8(FLASH_QUICK_DATA flash_data, SCH_U8 *u8data, SCH_U16 num);
extern SCH_BOOL Flash_Quick_WR(FLASH_QUICK_DATA flash_data, SCH_U32 u32data);
extern SCH_BOOL Flash_Quick_WR_U8(FLASH_QUICK_DATA flash_data, SCH_U8 *u8data, SCH_U16 num);
extern SCH_BOOL Flash_Quick_SE(FLASH_QUICK_DATA flash_data);
extern void SysFlashInit(void);
#endif
