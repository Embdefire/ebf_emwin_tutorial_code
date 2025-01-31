/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   FreeRTOS v9.0.0 + STM32 工程模版
  *********************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F767 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
/*******************************************************************************
 * 包含的头文件
 ******************************************************************************/
#include "ScreenShot.h"
#include "./usart/bsp_debug_usart.h"
/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"

/*******************************************************************************
 * 全局变量
 ******************************************************************************/ 
FATFS   fs;								/* FatFs文件系统对象 */
FIL     file;							/* file objects */
UINT    bw;            		/* File R/W count */
FRESULT result; 
FILINFO fno;
DIR dir;

uint16_t  file_num = 0;

/**
  * @brief AP6181_PDN_INIT
  * @note 禁止WIFI模块
  * @param 无
  * @retval 无
  */
static void AP6181_PDN_INIT(void)
{
  /*定义一个GPIO_InitTypeDef类型的结构体*/
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOG, ENABLE); 							   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);	
  
  GPIO_ResetBits(GPIOB,GPIO_Pin_13);  //禁用WiFi模块
}

/**
  * @brief FS_Init
  * @note 文件系统初始化
  * @param 无
  * @retval 无
  */
void FS_Init(void)
{
	const TCHAR *ScreenShotPATH  = "0:/ScreenShot";
	
	/* 禁用WiFi模块 */
//	AP6181_PDN_INIT();
	
	/* 挂载文件系统，挂载时会对SD卡初始化 */
  result = f_mount(&fs,"0:",1);
	if(result != FR_OK)
	{
		printf("SD卡初始化失败，请确保SD卡已正确接入开发板，或换一张SD卡测试！\n");
		while(1);
	}
	/*  如果路径不存在，则创建路径  */
	result = f_opendir(&dir, ScreenShotPATH);
	while(result != FR_OK)
	{
		f_mkdir(ScreenShotPATH);
		result = f_opendir(&dir, ScreenShotPATH);
	}
	/* 扫描已存在的截图文件个数 */
	while(f_readdir(&dir, &fno) == FR_OK)
	{
		if(fno.fname[0] == 0)
			break;
		if(fno.fattrib == AM_ARC)
			file_num++;
		vTaskDelay(1);
	}
}

/**
  * @brief ScreenShot
  * @note 截取LCD屏幕当前的显示内容
  * @param 无
  * @retval 无
  */
void ScreenShot(void)
{
  char filename[35] = {0};

  sprintf(filename, "0:/ScreenShot/ScreenShot_%03d.bmp", file_num);
  result = f_open(&file, (const char*)filename, FA_WRITE | FA_CREATE_ALWAYS);
  if(result == FR_OK)
  {
#if LCD_NUM_LAYERS == 2
    GUI_SelectLayer(1);
#endif 
    printf("开始创建截屏文件\r\n");
    
    taskENTER_CRITICAL();
    GUI_BMP_Serialize(_WriteByte2File, &file);
    taskEXIT_CRITICAL();
    result = f_close(&file);
    
    printf("截屏文件创建成功\r\n");
    file_num++;
  }
  else
  {
    printf("截屏文件创建失败\r\n");
  }
}

/**
  * @brief _WriteByte2File
  * @note 写入数据到指定存储介质
  * @param 无
  * @retval 无
  */
void _WriteByte2File(U8 Data, void *p)
{
	f_write(p, &Data, 1, &bw);
}
