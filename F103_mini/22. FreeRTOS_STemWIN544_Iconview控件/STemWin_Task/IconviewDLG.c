/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.44                          *
*        Compiled Nov 10 2017, 08:53:57                              *
*        (c) 2017 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/
#include <stddef.h>
#include <string.h>
/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
/* STemWIN头文件 */
#include "IconviewDLG.h"
#include "ScreenShot.h"

#include "usart/bsp_usart.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_ICONVIEW_0 (GUI_ID_USER + 0x00)
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x01)
#define ID_TEXT_0     (GUI_ID_USER + 0x02)

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct {
	const GUI_BITMAP* pBitmap;
	const char* pText;
} BITMAP_ITEM;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
char *_acbuffer = NULL;
UINT    f_num;
extern FATFS   fs;								/* FatFs文件系统对象 */
extern FIL     file;							/* file objects */
extern FRESULT result; 
extern DIR     dir;

extern GUI_CONST_STORAGE GUI_BITMAP bmsetting;
extern GUI_CONST_STORAGE GUI_BITMAP bmclock;
extern GUI_CONST_STORAGE GUI_BITMAP bmcalender;
extern GUI_CONST_STORAGE GUI_BITMAP bmmusic;
extern GUI_CONST_STORAGE GUI_BITMAP bmmessege;
extern GUI_CONST_STORAGE GUI_BITMAP bmfolder;
extern GUI_CONST_STORAGE GUI_BITMAP bmnotebook;
extern GUI_CONST_STORAGE GUI_BITMAP bmsearch;
extern GUI_CONST_STORAGE GUI_BITMAP bmhome;
extern GUI_CONST_STORAGE GUI_BITMAP bmimage;

static BITMAP_ITEM _abitmapItem[] = {
	{&bmhome,                "home"},
  {&bmfolder,            "folder"},
	{&bmclock,              "Clock"},
	{&bmmessege,          "messege"},
	{&bmsearch,            "search"},
	{&bmsetting,          "Setting"},
};

//static WM_HMEM hMem;
static GUI_MEMDEV_Handle hJPEG ;
/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/**
  * @brief 使用内存设备加载BMP图片数据
  * @note wu
  * @param sFilename：需要加载的图片名
  * @retval 无
  */
static WM_HMEM LoadJPEG_UsingMEMDEV(const char *sFilename)
{
	WM_HMEM hMem;
	GUI_JPEG_INFO Jpeginfo;
	
	/* 进入临界段 */
	taskENTER_CRITICAL();
	/* 打开图片 */
	result = f_open(&file, sFilename, FA_OPEN_EXISTING | FA_READ);
	if ((result != FR_OK))
	{
		printf("文件打开失败！\r\n");
		_acbuffer[0]='\0';
	}
	
	/* 申请一块动态内存空间 */
	hMem = GUI_ALLOC_AllocZero(file.fsize);
	/* 转换动态内存的句柄为指针 */
	_acbuffer = GUI_ALLOC_h2p(hMem);

	/* 读取图片数据到动态内存中 */
	result = f_read(&file, _acbuffer, file.fsize, &f_num);
	if(result != FR_OK)
	{
		printf("文件读取失败！\r\n");
	}
	/* 读取完毕关闭文件 */
	f_close(&file);
	/* 退出临界段 */
	taskEXIT_CRITICAL();
	
	GUI_JPEG_GetInfo(_acbuffer, file.fsize, &Jpeginfo);
	
	/* 创建内存设备 */
	hJPEG = GUI_MEMDEV_CreateEx(0, 0,                /* 起始坐标 */
														 Jpeginfo.XSize,      /* x方向尺寸 */
														 Jpeginfo.YSize,      /* y方向尺寸 */
														 GUI_MEMDEV_HASTRANS);/* 带透明度的内存设备 */
	/* 选择内存设备 */
	GUI_MEMDEV_Select(hJPEG);
	/* 绘制JPEG到内存设备中 */
	GUI_JPEG_Draw(_acbuffer, file.fsize, 0, 0);
	/* 选择内存设备，0表示选中LCD */
	GUI_MEMDEV_Select(0);
	/* 释放内存 */
	GUI_ALLOC_Free(hMem);
	
	return hJPEG;
}

/**
  * @brief 应用窗口回调函数
  * @note 无
  * @param 无
  * @retval 无
  */
static void _cbICON0(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
    case WM_PAINT:
      /* 设置客户窗口的背景颜色 */
      GUI_SetBkColor(GUI_LIGHTGRAY);
      GUI_Clear();
      break;
		default:
			WM_DefaultProc(pMsg);
		  break;
	}
}

/**
  * @brief 应用窗口创建函数
  * @note 无
  * @param 无
  * @retval 无
  */
static void FUN_ICON0Clicked(void)
{
	WM_HWIN hWin;
  WM_HWIN hChild;
  WM_HWIN hText;
	
  /* 创建框架窗口 */
	hWin = FRAMEWIN_CreateEx(70,        /* 相对于父窗口坐标的最左像素 */
                         20,           /* 相对于父窗口坐标的最上像素 */
                         150,          /* 水平尺寸 */
                         100,          /* 垂直尺寸 */
                         WM_HBKWIN,    /* 父窗口句柄 */
                         WM_CF_SHOW,   /* 窗口创建标志 */
                         0,            /* 额外创建标志 */
                         ID_FRAMEWIN_0,/* 控件ID */
                         "",           /* 标题栏文本 */
                         &_cbICON0);   /* 客户窗口回调函数 */
  FRAMEWIN_SetFont(hWin, GUI_FONT_20B_1);
  FRAMEWIN_SetText(hWin, "HOME");
  FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 0);
  /* 设置为模态窗口 */
  WM_MakeModal(hWin);
  /* 获取客户窗口句柄 */
  hChild = WM_GetClientWindow(hWin);
  /* 在客户窗口中创建子控件 */
  hText = TEXT_CreateEx(0, 0, 100, 34, hChild, WM_CF_SHOW, 0, ID_TEXT_0, "HOME APP");
  TEXT_SetFont(hText, GUI_FONT_20B_1);
  TEXT_SetTextColor(hText, GUI_GRAY);
}

/**
  * @brief 桌面窗口回调函数
  * @note 无
  * @param pMsg：消息指针
  * @retval 无
  */
static void _cbBkWindow(WM_MESSAGE *pMsg)
{
	int id;
	int NCode;
	
	switch(pMsg->MsgId)
	{
		case WM_PAINT:
			/* 将背景图片从内存设备写入LCD */
//			GUI_MEMDEV_WriteOpaqueAt(hJPEG , 0, 0);
			GUI_SetBkColor(GUI_GRAY);
			GUI_Clear();
		  break;
		case WM_NOTIFY_PARENT:
			id = WM_GetId(pMsg->hWinSrc);
		  NCode = pMsg->Data.v;
		  switch(id)
			{
				case ID_ICONVIEW_0:
					switch(NCode)
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED:
							switch(ICONVIEW_GetSel(pMsg->hWinSrc))
							{
								case 0:
									FUN_ICON0Clicked();
								  break;
								default:
									break;
							}
							break;
					}
					break;
			}
			break;
		default:
			WM_DefaultProc(pMsg);
		  break;
	}
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/**
  * @brief GUI主任务
  * @note 无
  * @param 无
  * @retval 无
  */
void MainTask(void)
{
	U8 i;
	WM_HWIN  hWin;
  /*F103MINI由于内存过小，无法加载图片作为背景，故使用纯色背景*/
	/* 加载JPEG图片数据到内存设备 */
//	LoadJPEG_UsingMEMDEV("0:/image/wallpaper.jpg");
	/* 在指定位置创建ICONVIEW控件 */
	hWin = ICONVIEW_CreateEx(10,                     /* 相对于父窗口坐标的最左像素 */
	                       10,                       /* 相对于父窗口坐标的最上像素 */
	                       240,                      /* 水平尺寸 */
	                       320,                      /* 垂直尺寸 */
	                       WM_HBKWIN,                /* 父窗口句柄 */
	                       WM_CF_SHOW|WM_CF_HASTRANS,/* 窗口创建标志 */
	                       0,                        /* 不设置自动滚动条 */
	                       ID_ICONVIEW_0,            /* 控件ID */
	                       64,                       /* 单个图标的水平尺寸 */
	                       64+16);                   /* 单个图标的垂直尺寸 */
	/* 向控件中添加新图标 */
	for(i = 0; i< GUI_COUNTOF(_abitmapItem); i++)
	{
		ICONVIEW_AddBitmapItem(hWin, _abitmapItem[i].pBitmap, _abitmapItem[i].pText);
		ICONVIEW_SetTextColor(hWin, i, GUI_WHITE);
	}
	/* 设置初始选择的图标，-1表示不选中任何图标 */
	ICONVIEW_SetSel(hWin, -1);
	/* 设置图标标题的字体 */
	ICONVIEW_SetFont(hWin, GUI_FONT_13B_1);
	/* 设置标题的对齐方式 */
	ICONVIEW_SetTextAlign(hWin, GUI_TA_HCENTER | GUI_TA_BOTTOM);
	/* 设置图标被选中时的背景色 */
	ICONVIEW_SetBkColor(hWin, ICONVIEW_CI_SEL, GUI_MAKE_COLOR(0x40ul << 24 | 0xFFFFFF));
	/* 设置图标的对齐方式 */
	ICONVIEW_SetIconAlign(hWin, ICONVIEW_IA_HCENTER|ICONVIEW_IA_TOP);
	/* 设置图标在X和Y方向上的间距 */
	ICONVIEW_SetSpace(hWin, GUI_COORD_X, 35);
	ICONVIEW_SetSpace(hWin, GUI_COORD_Y, 25);

  /* 重定向桌面窗口回调函数 */
	WM_SetCallback(WM_HBKWIN, _cbBkWindow);
  
	while (1)
	{
		GUI_Delay(50);
	}
}

/*************************** End of file ****************************/
