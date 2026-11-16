#include <windows.h>
#include <TCHAR.H>
#include "..\resource.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
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
	WndClass.lpszMenuName = NULL;		
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
						 WPARAM wParam, LPARAM lParam)     
{
	HDC hdc, memdc;
	PAINTSTRUCT ps;
	static HBITMAP hBit, oldBit;
	static RECT rectView;
	static int yPos;
	TCHAR word[] = _T("대한민국 화이팅");

	switch (iMsg) 
	{
	case WM_CREATE: 
		yPos = -30;
		GetClientRect(hwnd,&rectView);
		SetTimer(hwnd, 1, 10, NULL);
		hBit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5_3));
		break;
	case WM_TIMER:
		yPos += 1;
		if (yPos > rectView.bottom) yPos = -30;
		InvalidateRgn(hwnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		GetClientRect(hwnd,&rectView);
		hdc=BeginPaint(hwnd, &ps);
		memdc=CreateCompatibleDC(hdc);
		oldBit=(HBITMAP)SelectObject(memdc, hBit);
		BitBlt(hdc, 0, 0, 1024, 768, memdc, 0, 0, SRCCOPY);
		SelectObject(memdc, oldBit);
		DeleteDC(memdc);
		TextOut(hdc, 200, yPos, word, _tcslen(word));
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hBit);
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		break;
	} 
	return DefWindowProc(hwnd, iMsg, wParam, lParam); 
}