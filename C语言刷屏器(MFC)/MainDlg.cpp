#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <string.h>
#include "resource.h"
#include "MainDlg.h"

BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd,WM_INITDIALOG, Main_OnInitDialog);
        HANDLE_MSG(hWnd,WM_COMMAND, Main_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, Main_OnClose);
    }

    return FALSE;
}



void CALLBACK Timer1(HWND hwnd,UINT message,UINT iTimerID,DWORD dwTime)	 //定时器1回调函数
{
	/*
	原理：利用已有的剪辑文本进行模拟按键，Ctrl+V[粘贴]
	QQ的两种发送快捷键：Ctrl+Enter和Enter
	*/
		keybd_event(0x11,0,0,0);					//按下ctrl键
		keybd_event(86,0,0,0);						//按下V键
		keybd_event(86,0,KEYEVENTF_KEYUP,0);		//松开v键
		keybd_event(0x11,0,KEYEVENTF_KEYUP,0);		//松开ctrl键
		keybd_event(0x11,0,0,0);					//按下ctrl键
		keybd_event(0xD,0,0,0);						//按下Enter键
		keybd_event(0xD,0,KEYEVENTF_KEYUP,0);		//松开Enter键　
		keybd_event(0x11,0,KEYEVENTF_KEYUP,0);		//松开ctrl键
		keybd_event(0xD,0,0,0);						//按下Enter键
		keybd_event(0xD,0,KEYEVENTF_KEYUP,0);		//松开Enter键
}




BOOL Main_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)		//窗口创建完毕
{ 	

	SetDlgItemText(hwnd,IDC_TEXT2,"1000");		//设置文本框2的内容

	/*

	创建字体CreateFont,CreateFontIndirect - 阿飞的麦克风 - 博客频道 
	http://blog.csdn.net/zh634455283/article/details/7823656

	修改static控件背景颜色和文字颜色_C语言中文网 
	http://c.biancheng.net/cpp/html/2965.html

	*/
	HFONT hFont=CreateFont(28,10,0,0,FW_THIN,false,false,false,
	CHINESEBIG5_CHARSET,OUT_CHARACTER_PRECIS,
	CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
	FF_MODERN,"微软雅黑");						//创建字体
	HWND Lable = GetDlgItem(hwnd,IDC_LABLE1);	//获取标签1控件句柄
	SendMessage(Lable, WM_SETFONT, (WPARAM)hFont, NULL);//设置标签1的字体
    return TRUE;
}


void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch(id)
    {
        case IDC_COMMAND1:
		{ 
		TCHAR message_1[150] = {0};		//存储文本框1的内容
		TCHAR message_2[10] = {0};		//存储文本框2的内容
	 
		int interval;					//时间间隔
		GetDlgItemText(hwnd,IDC_TEXT1,message_1,sizeof(message_1));//获取文本框2的内容
		GetDlgItemText(hwnd,IDC_TEXT2,message_2,sizeof(message_2));//获取文本框2的内容
	
		interval=atoi(message_2);				//字符串转换为整数
		int id = MessageBox(hwnd,TEXT("确定后10秒开始刷屏 请将光标移到所要刷屏的窗口"),TEXT("提示"),MB_YESNO);
		if ( IDYES == id)
		{
				
				HWND Check = GetDlgItem(hwnd,IDC_CHECK1);	//获取复选框1控件句柄
			if( SendMessage(Check, BM_GETCHECK, 0, 0) != BST_CHECKED ) 
											//复选框1选中为假
			{
					HGLOBAL hMemory;
					LPTSTR lpMemory;
                 	OpenClipboard(NULL);	//打开剪切板
					EmptyClipboard();		// 清空剪切板
					hMemory = GlobalAlloc(GMEM_MOVEABLE,strlen(message_1)+1);
											// 对剪切板分配内存
					lpMemory = (LPTSTR)GlobalLock(hMemory);			
											// 将内存区域锁定
					memcpy(lpMemory, message_1, strlen(message_1)+1);   
											// 将数据复制进入内存区域 
					GlobalUnlock(hMemory);                  // 解除内存锁定
					SetClipboardData(CF_TEXT,hMemory);
					CloseClipboard();						//关闭剪切板
			}
			Sleep(10000);
			SetTimer(hwnd,1,interval,Timer1);				//创建定时器1
			
		}
		else if( IDNO == id)
		{
				 MessageBox(hwnd,TEXT("已取消刷屏"),TEXT("提示"),MB_OK);
		}
		}
        break;

		case IDC_COMMAND2:
		{
		KillTimer(hwnd,1);		//停止使用定时器2
		MessageBox(hwnd,TEXT("已停止刷屏"),TEXT("提示"),MB_OK);
		}
		break;

		case ID_MENUITEM40002:
		{
		exit(0);					//结束程序
		}
		break;

		case ID_MENUITEM40003:
		{
			MessageBox(hwnd,TEXT("使用说明已丢失 详情请向作者咨询"),TEXT("使用说明"),MB_OK);
		}
		break;

		case ID_MENUITEM40004:				//作者信息
		{
			MessageBox(hwnd,TEXT("本程序由奥利奥C语言制作  QQ 2783608988"),TEXT("作者信息"),MB_OK);
		}
		break;
    }
}

void Main_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}
