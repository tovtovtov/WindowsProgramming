#include <windows.h>
#include <TCHAR.H>
#include "..\resource.h"
LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT iMsg, 
							  WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWndProc(HWND hDlg, UINT iMsg, 
							  WPARAM wParam, LPARAM lParam);
void ReadFromFile(int WndIndex, TCHAR filename[]);
HWND hwndChild[100] ;
TCHAR WinBuff[100][1000];
int WndCount;
HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG  msg;
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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU8_3);		
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
	static TCHAR filepath[1000], folder[100], filename[100];
	LPTSTR pStr;
	TCHAR filter[] = _T("텍스트 파일 (*.txt)\0*.txt\0모든 파일 (*.*)\0*.*\0");
	OPENFILENAME OFN;
	switch (iMsg)
	{
	case WM_CREATE:
		clientcreate.hWindowMenu = GetSubMenu(GetMenu(hwnd), 1);
		clientcreate.idFirstChild = 100;
		hwndClient = CreateWindow(
			_T("MDICLIENT"), 
			NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
			0, 0, 0, 0, 
			hwnd, 
			NULL, 
			hInst,
			(LPSTR)&clientcreate
		); 
		ShowWindow(hwndClient, SW_SHOW);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILEOPEN:
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hwnd;
			OFN.lpstrFile = filepath;
			OFN.nMaxFileTitle = 100;
			OFN.lpstrFileTitle = filename;
			OFN.nMaxFile = 1000;
			OFN.lpstrFilter = filter;
			OFN.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;
			GetOpenFileName(&OFN);
			pStr = filepath;
			if (!*pStr) break;
			_tcscpy_s(folder, pStr);
			pStr = pStr + _tcslen(pStr) + 1;
			if (!*pStr)
			{	
				WndCount++;
				ReadFromFile(WndCount, filepath);
				mdicreate.szClass = _T("Child Window Class Name");
				mdicreate.szTitle = folder;
				mdicreate.hOwner = hInst;
				mdicreate.x = CW_USEDEFAULT;
				mdicreate.y = CW_USEDEFAULT;
				mdicreate.cx = CW_USEDEFAULT;
				mdicreate.cy = CW_USEDEFAULT;
				mdicreate.style = 0;
				mdicreate.lParam = 0;
				hwndChild[WndCount] = (HWND) SendMessage (hwndClient,
					WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT) &mdicreate);
				return 0;
			}
			while (*pStr)
			{
				_tcscpy_s(filename, pStr);
				pStr = pStr + _tcslen(pStr) + 1;
				WndCount++;
				ReadFromFile(WndCount, filename);
				mdicreate.szClass = _T("Child Window Class Name");
				mdicreate.szTitle = filename;
				mdicreate.hOwner = hInst;
				mdicreate.x = CW_USEDEFAULT;
				mdicreate.y = CW_USEDEFAULT;
				mdicreate.cx = CW_USEDEFAULT;
				mdicreate.cy = CW_USEDEFAULT;
				mdicreate.style = 0;
				mdicreate.lParam = 0;
				hwndChild[WndCount] = (HWND) SendMessage (hwndClient,
						WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mdicreate);
			}
			return 0;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefFrameProc(hwnd, hwndClient, iMsg, wParam, lParam);
}

void ReadFromFile(int WndIndex, TCHAR filename[])
{
	HANDLE hFile;
	DWORD size = 1000;
	hFile = CreateFile(
		filename, 
		GENERIC_READ, 
		FILE_SHARE_READ, 
		NULL, OPEN_EXISTING, 0, 0
	);
	ReadFile(hFile, WinBuff[WndIndex], size*sizeof(TCHAR), &size, NULL);
	WinBuff[WndIndex][size] = NULL;
	CloseHandle(hFile);
}

LRESULT CALLBACK ChildWndProc(HWND hwnd, UINT iMsg, 
							  WPARAM wParam, LPARAM lParam)
{
    int i, SelectWnd;
	HDC hdc;
	RECT rt;
	PAINTSTRUCT ps;

	for(i=1; i<=WndCount; i++)
		if (hwnd == hwndChild[i])
		{
			SelectWnd = i;
			break;
		}

	switch (iMsg)
	{
	    case WM_CREATE:
			break;
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			GetClientRect(hwnd, &rt);
			DrawText(hdc, WinBuff[SelectWnd], (int)_tcslen(WinBuff[SelectWnd]),
				&rt, DT_TOP | DT_LEFT);
			EndPaint(hwnd, &ps);
			break;
		case WM_DESTROY:
			return 0;
	} 
	return DefMDIChildProc(hwnd, iMsg, wParam, lParam);
}
