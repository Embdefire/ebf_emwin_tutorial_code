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

#include "usart/bsp_debug_usart.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
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
static WM_HMEM hMem;
static GUI_MEMDEV_Handle hBMP;

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
	{&bmcalender,        "calender"},
	{&bmsearch,            "search"},
	{&bmmusic,              "music"},
	{&bmimage,              "image"},
	{&bmsetting,          "Setting"},
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 100, 0, 600, 480, 0, 0x64, 0 },
};

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
static GUI_HMEM LoadBMP_UsingMEMDEV(const char *sFilename)
{
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
	/* 创建内存设备 */
	hBMP = GUI_MEMDEV_Create(0, 0,                        /* 起始坐标 */
													 GUI_BMP_GetXSize(_acbuffer), /* x方向尺寸 */
													 GUI_BMP_GetYSize(_acbuffer));/* y方向尺寸 */
	/* 选择内存设备 */
	GUI_MEMDEV_Select(hBMP);
	/* 绘制BMP到内存设备中 */
	GUI_BMP_Draw(_acbuffer, 0, 0);
	/* 切换内存设备到LCD */
	GUI_MEMDEV_Select(0);
	/* 释放内存 */
	GUI_ALLOC_Free(hMem);
	
	return hBMP;
}

/**
  * @brief 对话框回调函数
  * @note 无
  * @param pMsg：消息指针
  * @retval 无
  */
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
		/* 初始化Framewin控件 */
    hItem = pMsg->hWin;
    FRAMEWIN_SetFont(hItem, GUI_FONT_24B_1);
    FRAMEWIN_SetText(hItem, "HOME");
	  FRAMEWIN_AddCloseButton(hItem, FRAMEWIN_BUTTON_RIGHT, 0);
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/**
  * @brief 框架窗口创建函数
  * @note 无
  * @param 无
  * @retval 无
  */
static void FUN_ICON0Clicked(void)
{
	WM_HWIN hWin;
	
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
}

/**
  * @brief 背景窗口回调函数
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
			GUI_MEMDEV_WriteOpaqueAt(hBMP, 0, 0);
//			/* 删除内存设备 */
//			GUI_MEMDEV_Delete(hBMP);
		  break;
		case WM_NOTIFY_PARENT:
			id = WM_GetId(pMsg->hWinSrc);
		  NCode = pMsg->Data.v;
		  switch(id)
			{
				case GUI_ID_ICONVIEW0:
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

  WM_SetCreateFlags(WM_CF_MEMDEV);
  GUI_EnableAlpha(1);
  
	/* 加载BMP图片数据到内存设备 */
	LoadBMP_UsingMEMDEV("0:/image/wallpaper.bmp");
	/* 重定向背景窗口回调函数 */
	WM_SetCallback(WM_HBKWIN, _cbBkWindow);
	/* 在指定位置创建ICONVIEW控件 */
	hWin = ICONVIEW_CreateEx(30,                       /* 相对于父窗口坐标的最左像素 */
	                         20,                       /* 相对于父窗口坐标的最上像素 */
	                         800,                      /* 水平尺寸 */
	                         272,                      /* 垂直尺寸 */
	                         WM_HBKWIN,                /* 父窗口的句柄，为0时ICONVIEW成为桌面的子窗口 */
	                         WM_CF_SHOW|WM_CF_HASTRANS,/* 窗口创建标记，为使控件立即可见，通常使用WM_CF_SHOW */
	                         0,                        /* 默认是0，如果不够可设置增减垂直滚动条 */
	                         GUI_ID_ICONVIEW0,         /* 控件ID */
	                         64,                       /* 单个图标的水平尺寸 */
	                         64+16);                   /* 单个图标的垂直尺寸，需包含文字部分 */
	/* 向控件中添加新图标 */
	for(i = 0; i< GUI_COUNTOF(_abitmapItem); i++)
	{
		ICONVIEW_AddBitmapItem(hWin, _abitmapItem[i].pBitmap, _abitmapItem[i].pText);
		ICONVIEW_SetTextColor(hWin, i, GUI_WHITE);
	}
	/* 设置初始选择的图标，-1表示不选中任何图标 */
	ICONVIEW_SetSel(hWin, -1);
	/* 设置图标标题的字体 */
	ICONVIEW_SetFont(hWin, GUI_FONT_16B_1);
	/* 设置标题的对齐方式 */
	ICONVIEW_SetTextAlign(hWin, GUI_TA_HCENTER | GUI_TA_BOTTOM);
	/* 设置图标被选中时的背景色 */
	ICONVIEW_SetBkColor(hWin, ICONVIEW_CI_SEL, GUI_MAKE_COLOR((0x40uL << 24) | 0xFFFFFF));
	/* 设置图标的对齐方式 */
	ICONVIEW_SetIconAlign(hWin, ICONVIEW_IA_HCENTER|ICONVIEW_IA_TOP);
	/* 设置图标在X和Y方向上的间距 */
	ICONVIEW_SetSpace(hWin, GUI_COORD_X, 70);
	ICONVIEW_SetSpace(hWin, GUI_COORD_Y, 50);

	while (1)
	{
		GUI_Delay(50);
	}
}

/*************************** End of file ****************************/
