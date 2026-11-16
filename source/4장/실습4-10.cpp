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
	WndClass.hInstance = hInstance;		
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU4_9);		
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

#include <math.h>
#define BSIZE 40
double LengthPts(int x1, int y1, int x2, int y2)
{
	return(sqrt((float)((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1))));
}

BOOL InCircle(int x, int y, int mx, int my)
{
	if (LengthPts(x, y, mx, my) < BSIZE) return TRUE;
	else return FALSE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
						 WPARAM wParam, LPARAM lParam)     
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HMENU hMenu, hSubMenu;
	int mx, my;
	static BOOL Select;
	static BOOL Copy;
	static int x, y;
	
	switch (iMsg) 
	{
	case WM_CREATE: 
		hMenu = GetMenu(hwnd);
		hSubMenu = GetSubMenu(hMenu, 1);
		Select = FALSE;
		Copy = FALSE;
		x = 50;	y = 50;
		return 0;
	case WM_PAINT:
		EnableMenuItem(hSubMenu, ID_EDITCOPY, 
			Select? MF_ENABLED:MF_GRAYED);
		EnableMenuItem(hSubMenu, ID_EDITPASTE,
			Copy? MF_ENABLED:MF_GRAYED);
		hdc = BeginPaint(hwnd, &ps) ;
		if (Select) 
			Rectangle(hdc, x-BSIZE, y-BSIZE, x+BSIZE, y+BSIZE); 
		Ellipse(hdc, x-BSIZE, y-BSIZE, x+BSIZE, y+BSIZE);
		EndPaint(hwnd, &ps) ;
		return 0 ; 
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_EDITCOPY) 
		{
			Copy = TRUE;
			InvalidateRgn(hwnd, NULL, TRUE);
		}
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if(InCircle(x, y, mx, my)) Select = TRUE;
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	} 
	return DefWindowProc(hwnd, iMsg, wParam, lParam); 
}
