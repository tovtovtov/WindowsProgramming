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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU7_6);		
	WndClass.lpszClassName = _T("Window Class Name");	
	RegisterClass(&WndClass);	
	WndClass.lpfnWndProc = ChildWndProc;
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Child Window Class Name");
	RegisterClass(&WndClass) ;
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
  static BOOL split;  
  static HCURSOR hCursor;
  static int boundary = -1;
  RECT rectView;

  switch (iMsg) 
  {
	case WM_CREATE:
		split = FALSE;
		return 0;
	case WM_COMMAND:
		switch(LOWORD(wParam)) 
		{
		case ID_SPLIT_2x1:
			if (split == TRUE) break;
			split = TRUE;			
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
			boundary = rectView.bottom/2;
			hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS));
			return 0;
		case ID_EXIT : 
			PostQuitMessage(0);
			return 0 ;
		}
		return 0;
	case WM_MOUSEMOVE:
		if (HIWORD(lParam)>=boundary-2 && HIWORD(lParam)<=boundary+2) SetCursor(hCursor);
		if (wParam == MK_LBUTTON && split == TRUE)
		{
			GetClientRect(hwnd, &rectView);
			if (rectView.top+5 < HIWORD(lParam) && HIWORD(lParam) < rectView.bottom-5)
				boundary = HIWORD(lParam);
			MoveWindow(ChildHwnd[0], 0, 0, rectView.right, boundary - 1, TRUE);
			MoveWindow(ChildHwnd[1], 0, boundary+1, rectView.right, rectView.bottom - boundary + 1, TRUE);
		}
		return 0;
	case WM_LBUTTONDOWN:
		if (split == TRUE)
		{
			SetCursor(hCursor);
			SetCapture(hwnd);
		}
		return 0;
	case WM_LBUTTONUP:
		if (split == TRUE) ReleaseCapture();
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
	HDC hdc;
	static int x[2] = {20, 20}, y[2]={20, 20}, flag[2];
	int select;

	switch (iMsg) 
	{
	case WM_CREATE:  
		break;
	case WM_TIMER:
		x[wParam] = x[wParam] + 20;
		hdc = GetDC(hwnd);
		Ellipse(hdc, x[wParam] - 20, y[wParam] - 20, 
				x[wParam] + 20, y[wParam] + 20);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_LBUTTONDOWN:
		if (hwnd == ChildHwnd[0])
			select = 0;
		else 
			select = 1;
		flag[select] = 1 - flag[select];
		if (flag[select])
			SetTimer(hwnd, select, 100, NULL);
		else 
			KillTimer(hwnd, select);
		break;
	case WM_DESTROY:
		return 0;
	} 
	return DefMDIChildProc(hwnd, iMsg, wParam, lParam);
}