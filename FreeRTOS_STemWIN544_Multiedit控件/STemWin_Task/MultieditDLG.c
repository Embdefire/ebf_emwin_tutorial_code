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

#include "MultieditDLG.h"
#include "./usart/bsp_debug_usart.h"

#include <stdio.h>

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0   (GUI_ID_USER + 0x00)
#define ID_MULTIEDIT_0   (GUI_ID_USER + 0x01)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x64, 0 },
  { MULTIEDIT_CreateIndirect, "Multiedit0", ID_MULTIEDIT_0, 125, 40, 550, 140, 0, 0x0, 0 },
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

/**
  * @brief 对话框回调函数
  * @note 无
  * @param pMsg：消息指针
  * @retval 无
  */
static void _cbDialog(WM_MESSAGE* pMsg) {
	WM_HWIN hItem;
	int     NCode;
	int     Id;
  
	switch (pMsg->MsgId) {
	case WM_INIT_DIALOG:
		/* 初始化Framewin控件 */
		hItem = pMsg->hWin;
		FRAMEWIN_SetTitleHeight(hItem, 32);
		FRAMEWIN_SetText(hItem, "STemWIN@EmbedFire STM32F429");
		FRAMEWIN_SetFont(hItem, GUI_FONT_32_ASCII);
		/* 初始化MULTIEDIT控件 */
		hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIEDIT_0);
		MULTIEDIT_SetText(hItem, "Multiedit0");
		MULTIEDIT_SetReadOnly(hItem, 1);
		MULTIEDIT_ShowCursor(hItem, 0);
		MULTIEDIT_SetBufferSize(hItem, 500);
		MULTIEDIT_SetAutoScrollV(hItem, 1);
		MULTIEDIT_SetFont(hItem, GUI_FONT_COMIC24B_ASCII);
		MULTIEDIT_SetBkColor(hItem, MULTIEDIT_CI_READONLY, GUI_BLACK);
		MULTIEDIT_SetTextColor(hItem, MULTIEDIT_CI_READONLY, GUI_GREEN);
		MULTIEDIT_SetTextAlign(hItem, GUI_TA_LEFT);
		/* 显示内容 */
		MULTIEDIT_AddText(hItem, "\\******************************\\\r\n");
		MULTIEDIT_AddText(hItem, "www.wildfire.com\r\nwww.fireBBS.cn\r\n");
		MULTIEDIT_AddText(hItem, "STemWIN Version: ");
		MULTIEDIT_AddText(hItem, GUI_GetVersionString());
		MULTIEDIT_AddText(hItem, "\r\n\\******************************\\\r\n");
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (Id) {
		case ID_MULTIEDIT_0: // Notifications sent by 'Multiedit'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				break;
			case WM_NOTIFICATION_VALUE_CHANGED:
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
  * @brief CreateFramewin
  * @note 间接模式创建对话框
  * @param 无
  * @retval 无
  */
WM_HWIN CreateFramewin(void);
WM_HWIN CreateFramewin(void) {
	WM_HWIN hWin;

	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	return hWin;
}

/**
  * @brief GUI主任务
  * @note 无
  * @param 无
  * @retval 无
  */
void MainTask(void)
{
	CreateFramewin();
	
	while(1)
	{
		GUI_Delay(10);
	}
}
/*************************** End of file ****************************/
