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

#include "ListviewDLG.h"

#include <stdio.h>

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_LISTVIEW_0 (GUI_ID_USER + 0x01)
#define ID_BUTTON_0 (GUI_ID_USER + 0x02)
#define ID_BUTTON_1 (GUI_ID_USER + 0x03)
#define ID_BUTTON_2 (GUI_ID_USER + 0x04)
#define ID_BUTTON_3 (GUI_ID_USER + 0x05)
#define ID_TEXT_0 (GUI_ID_USER + 0x06)
#define ID_TEXT_1 (GUI_ID_USER + 0x07)
#define ID_TEXT_2 (GUI_ID_USER + 0x08)
#define ID_TEXT_3 (GUI_ID_USER + 0x09)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static const char * _Table[][4] = {
  { "A00", "Item AAA", "123-A", "378" },
  { "A01", "Item BBB", "123-B", "308" },
  { "A02", "Item CCC", "123-C", "344" },
  { "A03", "Item DDD", "123-D", "451" },
  { "A04", "Item EEE", "123-E", "364" },
  { "A05", "Item FFF", "123-F", "194" },
  { "A06", "Item GGG", "123-G", "774" },
  { "A07", "Item HHH", "123-H", "339" }
};

typedef struct 
{
  char Col0[10];
	char Col1[10];
	char Col2[10];
	char Col3[10];
}_ListviewItem;
_ListviewItem ListviewItem;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_0, 200, 15, 400, 190, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button0", ID_BUTTON_0, 199, 215, 95, 30, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button1", ID_BUTTON_1, 302, 215, 95, 30, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button2", ID_BUTTON_2, 404, 215, 95, 30, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button3", ID_BUTTON_3, 506, 215, 95, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text0", ID_TEXT_0, 200, 255, 400, 32, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text1", ID_TEXT_1, 200, 290, 400, 32, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text2", ID_TEXT_2, 200, 325, 400, 32, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text3", ID_TEXT_3, 200, 360, 400, 32, 0, 0x64, 0 },
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
  * @param 无
  * @retval 无
  */
static void _cbDialog(WM_MESSAGE* pMsg) {
	WM_HWIN hItem;
	int     NCode;
	int     Id;
	char    buf[20];
  static  U8 listview_RowIndex = 1, listview_ColumnIndex = 1;
	U8      i;
  int     Listview_RowNum;
	
	switch (pMsg->MsgId) {
	case WM_INIT_DIALOG:
		/* 初始化Framewin控件 */
		hItem = pMsg->hWin;
		FRAMEWIN_SetTitleHeight(hItem, 32);
		FRAMEWIN_SetText(hItem, "STemWIN@EmbedFire STM32H750");
		FRAMEWIN_SetFont(hItem, GUI_FONT_32_ASCII);
		/* 初始化Listview控件 */
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
		LISTVIEW_SetHeaderHeight(hItem, 20);
		LISTVIEW_AddColumn(hItem, 70, "Col 0", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_AddColumn(hItem, 70, "Col 1", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_AddColumn(hItem, 70, "Col 2", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_AddColumn(hItem, 70, "Col 3", GUI_TA_HCENTER | GUI_TA_VCENTER);	
		for(i = 0; i < GUI_COUNTOF(_Table); i++)
		{
			LISTVIEW_AddRow(hItem, _Table[i]);
		}	
		LISTVIEW_SetGridVis(hItem, 1);
		LISTVIEW_SetFont(hItem, GUI_FONT_16_ASCII);
		LISTVIEW_SetAutoScrollH(hItem, 1);
		LISTVIEW_SetAutoScrollV(hItem, 1);
		
		/* 初始化Button0 */
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
		BUTTON_SetText(hItem, "Add Row");
		BUTTON_SetFont(hItem, GUI_FONT_COMIC18B_ASCII);
		/* 初始化Button1 */
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
		BUTTON_SetText(hItem, "Del Row");
		BUTTON_SetFont(hItem, GUI_FONT_COMIC18B_ASCII);
		/* 初始化Button2 */
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
		BUTTON_SetText(hItem, "Add Column");
		BUTTON_SetFont(hItem, GUI_FONT_COMIC18B_ASCII);
		/* 初始化Button3 */
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
		BUTTON_SetText(hItem, "Del Column");
		BUTTON_SetFont(hItem, GUI_FONT_COMIC18B_ASCII);
		/* 初始化Text0 */
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
		TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
		TEXT_SetText(hItem, "Col 0: ");
		TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
		/* 初始化Text1 */
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
		TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
		TEXT_SetText(hItem, "Col 1: ");
		TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
		/* 初始化Text2 */
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
		TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
		TEXT_SetText(hItem, "Col 2: ");
		TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
		/* 初始化Text3 */
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
		TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
		TEXT_SetText(hItem, "Col 3: ");
		TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (Id) {
		case ID_LISTVIEW_0: // Notifications sent by 'Listview'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
        hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
				Listview_RowNum = LISTVIEW_GetSel(hItem);
				LISTVIEW_GetItemText(hItem, 0, Listview_RowNum, ListviewItem.Col0, 10);
				LISTVIEW_GetItemText(hItem, 1, Listview_RowNum, ListviewItem.Col1, 10);
				LISTVIEW_GetItemText(hItem, 2, Listview_RowNum, ListviewItem.Col2, 10);
				LISTVIEW_GetItemText(hItem, 3, Listview_RowNum, ListviewItem.Col3, 10);
				break;
			case WM_NOTIFICATION_RELEASED:
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
        sprintf(buf, "Col 0: %s", ListviewItem.Col0);
        TEXT_SetText(hItem, buf);
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
        sprintf(buf, "Col 1: %s", ListviewItem.Col1);
        TEXT_SetText(hItem, buf);
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
        sprintf(buf, "Col 2: %s", ListviewItem.Col2);
        TEXT_SetText(hItem, buf);
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
        sprintf(buf, "Col 3: %s", ListviewItem.Col3);
        TEXT_SetText(hItem, buf);
				break;
			case WM_NOTIFICATION_SEL_CHANGED:
				break;
			}
			break;
		case ID_BUTTON_0: // Notifications sent by 'Add Row'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
				LISTVIEW_AddRow(hItem, _Table[7]);
				break;
			}
			break;
		case ID_BUTTON_1: // Notifications sent by 'Del Row'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
				listview_RowIndex = LISTVIEW_GetNumRows(hItem);
				if(listview_RowIndex == 1)
				{break;}
				listview_RowIndex = listview_RowIndex - 1;
				LISTVIEW_DeleteRow(hItem, listview_RowIndex);
				break;
			}
			break;
		case ID_BUTTON_2: // Notifications sent by 'Add column'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
				listview_ColumnIndex = LISTVIEW_GetNumColumns(hItem);
				sprintf(buf, "Col %d", listview_ColumnIndex);
				LISTVIEW_AddColumn(hItem, 40, buf, GUI_TA_HCENTER | GUI_TA_VCENTER);
				break;
			}
			break;
		case ID_BUTTON_3: // Notifications sent by 'Del column'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
				listview_ColumnIndex = LISTVIEW_GetNumColumns(hItem);
				if(listview_ColumnIndex == 1){break;}
				listview_ColumnIndex = listview_ColumnIndex - 1;
				LISTVIEW_DeleteColumn(hItem, listview_ColumnIndex);
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
  * @brief 以对话框方式间接创建控件
  * @note 无
  * @param 无
  * @retval hWin：资源表中第一个控件的句柄
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
		GUI_Delay(100);
	}
}

/*************************** End of file ****************************/
