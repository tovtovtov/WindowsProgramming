#include <windows.h>
#include <TCHAR.H>
#include "..\resource.h"
HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
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

void TextPrint(HDC hdc, int x, int y, TCHAR text[])
{
	int i, j;
	SetTextColor(hdc, RGB(255, 255, 255));
	for (i=-1;i<=1;i++)
		for (j=-1;j<=1;j++)
			TextOut(hdc, x+i, y+j, text, _tcslen(text));
		SetTextColor(hdc, RGB(0, 0, 0));
		TextOut(hdc, x, y, text, _tcslen(text));
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	static HDC hdc, mem1dc, mem2dc;
	PAINTSTRUCT ps;
	static HBITMAP hBit1, hBit2, oldBit1, oldBit2;
	static RECT rectView;
	static int yPos;
	TCHAR word[] = _T("대한민국 화이팅");

	switch (iMsg)
	{
	case WM_CREATE:
		yPos = -30;
		GetClientRect(hwnd, &rectView);
		SetTimer(hwnd, 1, 70, NULL);
		hBit2 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5_3));
		break;
	case WM_TIMER:
		yPos += 5;
		if (yPos > rectView.bottom) yPos = -30;
		InvalidateRgn(hwnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		GetClientRect(hwnd, &rectView);
		hdc = BeginPaint(hwnd, &ps);
		mem1dc = CreateCompatibleDC(hdc);
		mem2dc = CreateCompatibleDC(mem1dc);
		if (hBit1 == NULL)
			hBit1 = CreateCompatibleBitmap(hdc, 530, 530);
		oldBit1 = (HBITMAP)SelectObject(mem1dc, hBit1);
		oldBit2 = (HBITMAP)SelectObject(mem2dc, hBit2);
		BitBlt(mem1dc, 0, 0, 530, 530, mem2dc, 0, 0, SRCCOPY);
		SetBkMode(mem1dc, TRANSPARENT);
		TextPrint(mem1dc, 200, yPos, word);
		BitBlt(hdc, 0, 0, 530, 530, mem1dc, 0, 0, SRCCOPY);
		SelectObject(mem1dc, oldBit1);
		SelectObject(mem2dc, oldBit2);
		DeleteDC(mem2dc);
		DeleteDC(mem1dc);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		if (hBit1) DeleteObject(hBit1);
		DeleteObject(hBit2);
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}