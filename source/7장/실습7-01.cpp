#include <windows.h>
#include <TCHAR.H>
#include "..\resource.h"
LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT iMsg, 
							  WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWndProc(HWND hDlg, UINT iMsg, 
							  WPARAM wParam, LPARAM lParam);
HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPSTR lpszCmdLine, int nCmdShow)
{
	HWND     hwnd;
	MSG 	 msg;
	WNDCLASS WndClass;   
	hInst = hInstance;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = FrameWndProc;		
	WndClass.cbClsExtra = 0;		
	WndClass.cbWndExtra = 0;		
	WndClass.hInstance = hInstance;		
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU7_1);		
	WndClass.lpszClassName = _T("Window Class Name");	
	RegisterClass(&WndClass);	
	WndClass.lpfnWndProc = ChildWndProc;
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Child Window Class Name"); 
	RegisterClass(&WndClass);
	hwnd = CreateWindow(
		_T("Window Class Name"),
		_T("Main Window Title"),
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
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);	
		DispatchMessage(&msg);	
	}   
	return (int)msg.wParam;
}

LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT iMsg, 
							  WPARAM wParam, LPARAM lParam)     
{
	static HWND hwndClient;
	CLIENTCREATESTRUCT clientcreate;
	MDICREATESTRUCT mdicreate;
	HWND hwndChild;

	switch (iMsg)
	{
	case WM_CREATE:
		clientcreate.hWindowMenu = GetSubMenu(GetMenu(hwnd),0);
		clientcreate.idFirstChild = 100;
		hwndClient = CreateWindow (
			_T("MDICLIENT"), NULL, 
			WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE, 
			0, 0, 0, 0, 
			hwnd, 
			NULL, 
			hInst, 
			(LPSTR) &clientcreate
		); 
		ShowWindow(hwndClient, SW_SHOW);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
			{
			case ID_FILENEW : 
				mdicreate.szClass = _T("Child Window Class Name");
				mdicreate.szTitle = _T("Child Window Title Name");
				mdicreate.hOwner  = hInst;
				mdicreate.x = CW_USEDEFAULT;
				mdicreate.y = CW_USEDEFAULT;
				mdicreate.cx = CW_USEDEFAULT;
				mdicreate.cy = CW_USEDEFAULT;
				mdicreate.style = 0;
				mdicreate.lParam = 0;
				hwndChild = (HWND)SendMessage(hwndClient, 
					WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT) &mdicreate);
				return 0;
			}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefFrameProc(hwnd, hwndClient, iMsg, wParam, lParam); 
}

LRESULT CALLBACK ChildWndProc(HWND hwnd, UINT iMsg, 
							  WPARAM wParam, LPARAM lParam)
{
	switch (iMsg) 
	{
	case WM_CREATE:  
		break;
	case WM_DESTROY:
		return 0;
	} 
	return DefMDIChildProc(hwnd, iMsg, wParam, lParam);
}
