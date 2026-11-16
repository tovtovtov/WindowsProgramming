#include <windows.h>
#include <TCHAR.H>
#include <tchar.h>
#include "..\resource.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
HINSTANCE hInst;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG  msg;
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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU8_4);		
	WndClass.lpszClassName= _T("Window Class Name");	
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

void FileRead(HWND hwnd, LPTSTR filename)
{
	HANDLE hFile;
	LPTSTR buffer;
	DWORD size, CharNum;
	int fileSize;
	hFile=CreateFile(
		filename, 
		GENERIC_READ, 
		0, 
		0, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL,
		0
	);
	if (hFile == INVALID_HANDLE_VALUE) 
		return;
	fileSize = GetFileSize(hFile, &size);
	buffer = new TCHAR[(int)fileSize/sizeof(TCHAR) + 1]; 
	memset(buffer, 0, fileSize);
	ReadFile(hFile, buffer, fileSize, &CharNum, NULL);
	buffer[(int)fileSize/sizeof(TCHAR)] = NULL;
	SetWindowText(hwnd, buffer);
	free(buffer);
	CloseHandle(hFile);
}

void FileSave(HWND hwnd, LPTSTR filename)
{
	HANDLE hFile;
	LPTSTR buffer;
	int size;
#ifdef _UNICODE
	WORD uni = 0xFEFF;
	DWORD nSize;
#endif
	hFile = CreateFile(
		filename, 
		GENERIC_WRITE, 
		0, 
		0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0
		);
#ifdef _UNICODE
	WriteFile(hFile, &uni, 2, &nSize, NULL);
#endif
	size = GetWindowTextLength(hwnd);
	buffer = new TCHAR[size + 1]; 
	memset(buffer, 0, (size+1)*sizeof(TCHAR));
	size = GetWindowText(hwnd, (LPTSTR)buffer, size+1);	
	buffer[size] = NULL;
	WriteFile(hFile, buffer, size*sizeof(TCHAR), (LPDWORD)&size, NULL);
	free(buffer);
	CloseHandle(hFile);
}

#define IDC_EDIT8_4 100
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
						WPARAM wParam, LPARAM lParam)     
{
	static HWND hEdit;
	RECT rect;

	switch (iMsg) 
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rect);
		hEdit = CreateWindow( 
			_T("edit"), 
			NULL, 
			WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | 
			   ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE, 
			0, 
			100,
			rect.right,
			rect.bottom,
			hwnd, 
			(HMENU)IDC_EDIT8_4,
			hInst,
			NULL
		);
		return 0;
	case WM_SIZE:
		GetClientRect(hwnd, &rect);
		MoveWindow(hEdit, 0, 0, rect.right, rect.bottom, TRUE);
		return 0;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_FILEOPEN:
			FileRead(hEdit, _T("test2.txt"));
			break;
		case ID_FILESAVE:
			FileSave(hEdit, _T("test2.txt"));
			break;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	} 
  return DefWindowProc(hwnd, iMsg, wParam, lParam);
}