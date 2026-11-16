#include <windows.h>
#include <TCHAR.H>
#include <richedit.h>
#include "..\resource.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
						 WPARAM wParam, LPARAM lParam);
HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPSTR lpszCmdLine, int nCmdShow)
{
	HINSTANCE hRichedit;
	HWND 	  hwnd;
	MSG 	  msg;
	WNDCLASS  WndClass;   
	hInst = hInstance;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;		
	WndClass.cbClsExtra	= 0;		
	WndClass.cbWndExtra	= 0;		
	WndClass.hInstance = hInstance;		
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU7_10);		
	WndClass.lpszClassName = _T("Window Class Name");	
	RegisterClass(&WndClass);	
	hRichedit = LoadLibrary(_T("RICHED20.DLL"));
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
	FreeLibrary(hRichedit);
	return (int)msg.wParam;
}

#define IDC_RICHEDIT 100
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
						 WPARAM wParam, LPARAM lParam)     
{
	static HWND hRichedit;
	RECT rect;
	CHARFORMAT cf;

	switch (iMsg) 
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rect);
		hRichedit = CreateWindow( 
			_T("RichEdit20W"), 
			_T("¿ì¸®´Â ¹ÎÁ· ÁßÈïÀÇ ¿ª»çÀû »ç¸íÀ» ¶ì°í ÀÌ ¶¥¿¡ ÅÂ¾î³µ´Ù."), 
			WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | 
			ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | WS_BORDER, 
			100,
			100,
			rect.right, 
			rect.bottom, 
			hwnd, 
			(HMENU)IDC_RICHEDIT, 
			hInst, 
			NULL
		);
		return 0;
	case WM_SIZE:
		GetClientRect(hwnd, &rect);
		MoveWindow(hRichedit, 0, 0, rect.right, rect.bottom, TRUE);
		return 0;
	case WM_COMMAND:
		switch(LOWORD(wParam)) 
		{
		case ID_FONT:
			cf.cbSize = sizeof (CHARFORMAT);  
			cf.dwMask = CFM_FACE | CFM_SIZE | CFM_COLOR; 
			cf.yHeight = 300; 
			cf.dwEffects = NULL;
			_tcscpy_s(cf.szFaceName, _T("HY¿ï¸ªµµM"));
			cf.crTextColor = RGB(100, 0, 0);
			SendMessage(hRichedit, EM_SETCHARFORMAT, 
					   (WPARAM)(UINT)SCF_SELECTION, (LPARAM)&cf);
			return 0;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	} 
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
