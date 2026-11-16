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
	HWND 	 hwnd;
	MSG 	 msg;
	WNDCLASS WndClass;   
	hInst = hInstance;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = FrameWndProc;		
	WndClass.cbClsExtra	= 0;		
	WndClass.cbWndExtra	= 0;		
	WndClass.hInstance = hInstance;		
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU7_3);		
	WndClass.lpszClassName = _T("Window Class Name");	
	RegisterClass(&WndClass);	
	WndClass.lpfnWndProc = ChildWndProc;
	WndClass.lpszMenuName = NULL ;
	WndClass.lpszClassName = _T("Child Window Class Name");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
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

HWND	ChildHwnd[2];
LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT iMsg, 
							  WPARAM wParam, LPARAM lParam)     
{
	RECT rectView;

	switch (iMsg) 
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rectView);
		ChildHwnd[0] = CreateWindowEx( 
			WS_EX_CLIENTEDGE,
			_T("Child Window Class Name"), 
			NULL,  
			WS_CHILD | WS_VISIBLE, 
			0,	
			0,	
			rectView.right, 
			rectView.bottom/2-1, 
			hwnd, 
			NULL, 
			hInst, 
			NULL
		);

		ChildHwnd[1] = CreateWindowEx( 
			WS_EX_CLIENTEDGE,
			_T("Child Window Class Name"), 
			NULL,  
			WS_CHILD | WS_VISIBLE,
			0, 
			rectView.bottom/2+1, 
			rectView.right, 
			rectView.bottom/2-1,
			hwnd, 
			NULL,
			hInst,
			NULL 
		);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam); 
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