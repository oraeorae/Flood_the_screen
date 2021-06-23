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



void CALLBACK Timer1(HWND hwnd,UINT message,UINT iTimerID,DWORD dwTime)	 //��ʱ��1�ص�����
{
	/*
	ԭ���������еļ����ı�����ģ�ⰴ����Ctrl+V[ճ��]
	QQ�����ַ��Ϳ�ݼ���Ctrl+Enter��Enter
	*/
		keybd_event(0x11,0,0,0);					//����ctrl��
		keybd_event(86,0,0,0);						//����V��
		keybd_event(86,0,KEYEVENTF_KEYUP,0);		//�ɿ�v��
		keybd_event(0x11,0,KEYEVENTF_KEYUP,0);		//�ɿ�ctrl��
		keybd_event(0x11,0,0,0);					//����ctrl��
		keybd_event(0xD,0,0,0);						//����Enter��
		keybd_event(0xD,0,KEYEVENTF_KEYUP,0);		//�ɿ�Enter����
		keybd_event(0x11,0,KEYEVENTF_KEYUP,0);		//�ɿ�ctrl��
		keybd_event(0xD,0,0,0);						//����Enter��
		keybd_event(0xD,0,KEYEVENTF_KEYUP,0);		//�ɿ�Enter��
}




BOOL Main_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)		//���ڴ������
{ 	

	SetDlgItemText(hwnd,IDC_TEXT2,"1000");		//�����ı���2������

	/*

	��������CreateFont,CreateFontIndirect - ���ɵ���˷� - ����Ƶ�� 
	http://blog.csdn.net/zh634455283/article/details/7823656

	�޸�static�ؼ�������ɫ��������ɫ_C���������� 
	http://c.biancheng.net/cpp/html/2965.html

	*/
	HFONT hFont=CreateFont(28,10,0,0,FW_THIN,false,false,false,
	CHINESEBIG5_CHARSET,OUT_CHARACTER_PRECIS,
	CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
	FF_MODERN,"΢���ź�");						//��������
	HWND Lable = GetDlgItem(hwnd,IDC_LABLE1);	//��ȡ��ǩ1�ؼ����
	SendMessage(Lable, WM_SETFONT, (WPARAM)hFont, NULL);//���ñ�ǩ1������
    return TRUE;
}


void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch(id)
    {
        case IDC_COMMAND1:
		{ 
		TCHAR message_1[150] = {0};		//�洢�ı���1������
		TCHAR message_2[10] = {0};		//�洢�ı���2������
	 
		int interval;					//ʱ����
		GetDlgItemText(hwnd,IDC_TEXT1,message_1,sizeof(message_1));//��ȡ�ı���2������
		GetDlgItemText(hwnd,IDC_TEXT2,message_2,sizeof(message_2));//��ȡ�ı���2������
	
		interval=atoi(message_2);				//�ַ���ת��Ϊ����
		int id = MessageBox(hwnd,TEXT("ȷ����10�뿪ʼˢ�� �뽫����Ƶ���Ҫˢ���Ĵ���"),TEXT("��ʾ"),MB_YESNO);
		if ( IDYES == id)
		{
				
				HWND Check = GetDlgItem(hwnd,IDC_CHECK1);	//��ȡ��ѡ��1�ؼ����
			if( SendMessage(Check, BM_GETCHECK, 0, 0) != BST_CHECKED ) 
											//��ѡ��1ѡ��Ϊ��
			{
					HGLOBAL hMemory;
					LPTSTR lpMemory;
                 	OpenClipboard(NULL);	//�򿪼��а�
					EmptyClipboard();		// ��ռ��а�
					hMemory = GlobalAlloc(GMEM_MOVEABLE,strlen(message_1)+1);
											// �Լ��а�����ڴ�
					lpMemory = (LPTSTR)GlobalLock(hMemory);			
											// ���ڴ���������
					memcpy(lpMemory, message_1, strlen(message_1)+1);   
											// �����ݸ��ƽ����ڴ����� 
					GlobalUnlock(hMemory);                  // ����ڴ�����
					SetClipboardData(CF_TEXT,hMemory);
					CloseClipboard();						//�رռ��а�
			}
			Sleep(10000);
			SetTimer(hwnd,1,interval,Timer1);				//������ʱ��1
			
		}
		else if( IDNO == id)
		{
				 MessageBox(hwnd,TEXT("��ȡ��ˢ��"),TEXT("��ʾ"),MB_OK);
		}
		}
        break;

		case IDC_COMMAND2:
		{
		KillTimer(hwnd,1);		//ֹͣʹ�ö�ʱ��2
		MessageBox(hwnd,TEXT("��ֹͣˢ��"),TEXT("��ʾ"),MB_OK);
		}
		break;

		case ID_MENUITEM40002:
		{
		exit(0);					//��������
		}
		break;

		case ID_MENUITEM40003:
		{
			MessageBox(hwnd,TEXT("ʹ��˵���Ѷ�ʧ ��������������ѯ"),TEXT("ʹ��˵��"),MB_OK);
		}
		break;

		case ID_MENUITEM40004:				//������Ϣ
		{
			MessageBox(hwnd,TEXT("�������ɰ�����C��������  QQ 2783608988"),TEXT("������Ϣ"),MB_OK);
		}
		break;
    }
}

void Main_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}
