#include <windows.h>
#include <TCHAR.H>
#include "..\resource.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
						 WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPSTR lpszCmdLine, int nCmdShow)
{
	HWND 	 hwnd;
	MSG 	 msg;
	WNDCLASS WndClass;   
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;		
	WndClass.cbClsExtra = 0;		
	WndClass.cbWndExtra = 0;		
	WndClass.hInstance  = hInstance;		
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU4_6);		
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
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);	
		DispatchMessage(&msg);	
	}   
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, 
						  WPARAM wParam, LPARAM lParam)     
{
	HDC hdc;
	PAINTSTRUCT ps;
	CHOOSEFONT FONT;
	static COLORREF   fColor;
	HFONT  hFont, OldFont;
	static LOGFONT    LogFont;

	switch (iMsg) 
	{
	case WM_CREATE:  
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hFont = CreateFontIndirect(&LogFont);
		OldFont = (HFONT)SelectObject(hdc, hFont);
		SetTextColor(hdc, fColor);
		TextOut(hdc, 10, 10, _T("HelloWorld"), 10);
		SelectObject(hdc, OldFont);
		DeleteObject(hFont);
		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) 
		{
		case ID_FONTDLG:
			memset(&FONT, 0, sizeof(CHOOSEFONT));
			FONT.lStructSize = sizeof(CHOOSEFONT);
			FONT.hwndOwner = hwnd;
			FONT.lpLogFont= &LogFont;
			FONT.Flags = CF_EFFECTS | CF_SCREENFONTS;
			if (ChooseFont(&FONT)!=0) 
			{
				fColor = FONT.rgbColors;
				InvalidateRgn(hwnd, NULL, TRUE);
			}
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	} 
	return DefWindowProc (hwnd, iMsg, wParam, lParam); 
}