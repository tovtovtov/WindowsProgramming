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
	HWND hwnd;
	MSG msg;
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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU8_5);		
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
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);	
		DispatchMessage(&msg);	
	}
	FreeLibrary(hRichedit);
	return (int)msg.wParam;
}

DWORD CALLBACK StreamInCallback(DWORD dwCookie, LPBYTE buffer, 
								LONG size, LONG *CharNum)
{
	HANDLE hFile = (HANDLE)dwCookie;
	ReadFile(hFile, buffer, size, (LPDWORD)CharNum, NULL);
	return(0);
}

DWORD CALLBACK StreamOutCallback(DWORD dwCookie, 
								 LPBYTE buffer, LONG size, LONG *CharNum)
{
	HANDLE hFile = (HANDLE)dwCookie;
	WriteFile(hFile, buffer, size, (LPDWORD)CharNum, NULL);
	return(0);
}

void FileRead(HWND hwnd, LPTSTR filename)
{
	HANDLE hFile;
	EDITSTREAM es;
	hFile=CreateFile(filename, GENERIC_READ, 0, 0, 
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,0);
	if (hFile == INVALID_HANDLE_VALUE) return;
	es.dwCookie = (DWORD)hFile;
	es.pfnCallback = StreamInCallback;
	SendMessage(hwnd, EM_STREAMIN, (WPARAM)SF_RTF, (LPARAM)&es);
	CloseHandle(hFile);
}

void FileSave(HWND hwnd, LPTSTR filename)
{
	HANDLE hFile;
	EDITSTREAM es;
	hFile = CreateFile(
		filename, 
		GENERIC_WRITE, 
		0, 
		0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0
	);
	es.dwCookie = (DWORD)hFile;
	es.pfnCallback = StreamOutCallback;
	SendMessage(hwnd, EM_STREAMOUT, (WPARAM)SF_RTF, (LPARAM)&es);
	CloseHandle(hFile);
}

#define IDC_RICHEDIT 100
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
						 WPARAM wParam, LPARAM lParam)     
{
	static HWND hRichedit;
	CHOOSEFONT FONT;  
	LOGFONT LogFont;
	RECT rect;
	CHARFORMAT cf;

	switch (iMsg) 
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rect);
		hRichedit = CreateWindow( 
	         _T("RichEdit20W"), 
			 NULL, 
			 WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | 
			   ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE, 
			 0, 100, 
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
		case ID_FILEOPEN:
			FileRead(hRichedit, _T("test3.txt"));
			break;
		case ID_FILESAVE:
			FileSave(hRichedit, _T("test3.txt"));
			break;
		case ID_FONTDLG:
			memset(&FONT, 0, sizeof(CHOOSEFONT));
			FONT.lStructSize = sizeof(CHOOSEFONT);
			FONT.hwndOwner = hwnd;
			FONT.lpLogFont= &LogFont;
			FONT.Flags = CF_EFFECTS | CF_SCREENFONTS;
			if(ChooseFont(&FONT)!=0) 
			{	
				cf.cbSize = sizeof (CHARFORMAT);  
				cf.dwMask = CFM_FACE | CFM_SIZE | CFM_COLOR; 
				cf.yHeight = FONT.iPointSize * 3; 
				cf.dwEffects = NULL;
				_tcscpy_s(cf.szFaceName, FONT.lpLogFont -> lfFaceName);
				cf.crTextColor = FONT.rgbColors;
				SendMessage(hRichedit, EM_SETCHARFORMAT, 
					(WPARAM)(UINT)SCF_SELECTION, (LPARAM)&cf);
			}
			return 0;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	} 
  return DefWindowProc(hwnd, iMsg, wParam, lParam);
}