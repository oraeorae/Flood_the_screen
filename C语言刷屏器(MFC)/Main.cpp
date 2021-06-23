// Ë¢ÆÁÉñÆ÷.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "MainDlg.h"
#include <COMMCTRL.H>

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
  
	InitCommonControls();
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, Main_Proc);
	return 0;
}



