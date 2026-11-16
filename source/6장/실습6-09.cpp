#include <windows.h>
#include <TCHAR.H>
#include <commctrl.h>
#include "..\resource.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
						 WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_9Proc(HWND hDlg, UINT iMsg, 
						 WPARAM wParam, LPARAM lParam);
HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPSTR lpszCmdLine, int nCmdShow)
{
	HWND 	 hwnd;
	MSG 	 msg;
	WNDCLASS WndClass;     
	hInst = hInstance;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;		
	WndClass.cbClsExtra	= 0;		
	WndClass.cbWndExtra	= 0;		
	WndClass.hInstance = hInstance;		
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU_CHAPTER_6);
	WndClass.lpszClassName = _T("Window Class Name");	
	RegisterClass(&WndClass);	
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("Window Title Name"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,	
		CW_USEDEFAULT,	
		CW_USEDEFAULT,	
		CW_USEDEFAULT,	
		NULL,	
		NULL,	
		hInstance,	
		NULL	 
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);	
		DispatchMessage(&msg);	
	}   
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
						 WPARAM wParam, LPARAM lParam)     
{
	HWND hDlg = NULL;

	switch (iMsg) 
	{
	case WM_CREATE: 
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam)) 
		{
		case ID_6_9_MENU:
			if (!IsWindow(hDlg)) 
			{
				hDlg=CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG6_9), hwnd, Dlg6_9Proc);
				ShowWindow(hDlg,SW_SHOW);
			}
			break;
		}
		break;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	} 
	return DefWindowProc(hwnd, iMsg, wParam, lParam); 
}

void MakeColumn(HWND hDlg)
{
	LPTSTR name[2] = {_T("이름"), _T("전화번호")};
	LVCOLUMN lvCol = {0,};
	HWND hList;
	int i;
	hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvCol.fmt = LVCFMT_LEFT;

	for (i=0; i<2; i++)
	{
		lvCol.cx = 90;
		lvCol.iSubItem = i;
		lvCol.pszText = name[i];
		SendMessage(hList, LVM_INSERTCOLUMN, (WPARAM)i, (LPARAM)&lvCol);		
	}
}

BOOL CALLBACK Dlg6_9Proc(HWND hDlg, UINT iMsg, 
						 WPARAM wParam, LPARAM lParam)
{
	switch(iMsg)
	{
	case WM_INITDIALOG:
		MakeColumn(hDlg);
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCLOSE:
			DestroyWindow(hDlg);
			hDlg=NULL;
			return 0;
		case IDCANCEL:
			DestroyWindow(hDlg);
			hDlg=NULL;
			return 0;
		}
		break;
	}
	return 0;
}