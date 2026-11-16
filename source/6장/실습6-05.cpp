#include <windows.h>
#include <TCHAR.H>
#include <stdio.h>
#include "..\resource.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
						 WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_5Proc(HWND hDlg, UINT iMsg, 
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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU_CHAPTER_6);
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
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);	
		DispatchMessage(&msg);	
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
						 WPARAM wParam, LPARAM lParam)     
{
	switch (iMsg) 
	{
	case WM_CREATE: 
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam)) 
		{
		case ID_6_5_MENU:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG6_5), hwnd, Dlg6_5Proc);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	} 
	return DefWindowProc(hwnd, iMsg, wParam, lParam); 
}

BOOL CALLBACK Dlg6_5Proc(HWND hDlg, UINT iMsg, 
						 WPARAM wParam, LPARAM lParam)
{
	static int Check[3], Radio;
	TCHAR hobby[][30] = {_T("독서"), _T("음악감상"), _T("인터넷")};
	TCHAR sex[][30] = {_T("여자"), _T("남자")};
	TCHAR output[200];

	switch(iMsg)
	{
	case WM_INITDIALOG:
		CheckRadioButton(hDlg, IDC_RADIO_FEMALE, IDC_RADIO_MALE, 
			IDC_RADIO_FEMALE);
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_CHECK_READING:
			Check[0] = 1 - Check[0];
			break;
		case IDC_CHECK_MUSIC:
			Check[1] = 1 - Check[1];
			break;
		case IDC_CHECK_INTERNET:
			Check[2] = 1 - Check[2];
			break;
		case IDC_RADIO_FEMALE:
			Radio = 0;
			break;
		case IDC_RADIO_MALE:
			Radio = 1;
			break;
		case IDC_BUTTON_OUTPUT:
			_stprintf_s(output, _T("선택한 취미는 %s %s %s입니다.\r\n")
				_T("선택한 성별은 %s입니다."), 
				Check[0]?hobby[0]:_T(""), Check[1]?hobby[1]:_T(""), 
				Check[2]?hobby[2]:_T(""), sex[Radio]);
			SetDlgItemText(hDlg, IDC_EDIT_OUTPUT, output);
			break;
		case IDC_BUTTON_CLOSE:
			EndDialog(hDlg, 0);
			break;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;
		}
		break;
	}
	return 0;
}
