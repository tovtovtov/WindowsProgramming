#include <windows.h>
#include <TCHAR.H>
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
						 WPARAM wParam, LPARAM lParam);
HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPSTR lpszCmdLine, int nCmdShow)
{
	HWND     hwnd;
	MSG      msg;
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
	WndClass.lpszMenuName = NULL;		
	WndClass.lpszClassName = _T("Window Class Name");	
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

#define IDC_BUTTON 100
#define IDC_EDIT   101
#define IDC_COMBO  102
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
						 WPARAM wParam, LPARAM lParam)     
{
	static HWND hButton, hEdit, hCombo;
	TCHAR str[100];

	switch (iMsg) 
	{
	case WM_CREATE:
		hButton = CreateWindow(
			_T("button"), 
			_T("확인"), 
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
			200,
			0,
			100, 
			25, 
			hwnd, 
			(HMENU)IDC_BUTTON, 
			hInst, 
			NULL
		);
		hEdit = CreateWindow(
			_T("edit"), 
			_T("에디팅"), 
			WS_CHILD | WS_VISIBLE | WS_BORDER, 
			0,
			0,
			200, 
			25, 
			hwnd, 
			(HMENU)IDC_EDIT, 
			hInst, 
			NULL
		);
		hCombo = CreateWindow(
			_T("combobox"), 
			NULL, 
			WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 
			0,
			100,
			200, 
			300, 
			hwnd, 
			(HMENU)IDC_COMBO, 
			hInst, 
			NULL
		);
		return 0;
	case WM_COMMAND:
		switch(LOWORD(wParam)) 
		{
		case IDC_BUTTON:
			GetDlgItemText(hwnd, IDC_EDIT, str, 100);
			if (_tcscmp(str, _T(""))) 
					SendMessage(hCombo,CB_ADDSTRING,0,(LPARAM)str);
			return 0;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	} 
  return DefWindowProc(hwnd, iMsg, wParam, lParam);
}