#include <windows.h>
#include <TCHAR.H>
#include <commctrl.h>
#include "..\resource.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
						 WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_12Proc(HWND hDlg, UINT iMsg, 
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
	HWND hDlg = NULL;

	switch (iMsg) 
	{
	case WM_CREATE: 
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam)) 
		{
		case ID_6_12_MENU:
			if (!IsWindow(hDlg)) 
			{
				hDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG6_12), hwnd, Dlg6_12Proc);
				ShowWindow(hDlg, SW_SHOW);
			}
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	} 
	return DefWindowProc(hwnd, iMsg, wParam, lParam); 
}

void MakeColumn(HWND hDlg)
{
	LPTSTR name[2] = {_T("이름"), _T("전화번호")};
	LVCOLUMN lvCol = {0,};
	HWND hList;
	int i;
	hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvCol.fmt = LVCFMT_LEFT;

	for (i=0; i<2; i++)
	{
		lvCol.cx = 90;
		lvCol.iSubItem = i;
		lvCol.pszText = name[i];
		SendMessage(hList, LVM_INSERTCOLUMN, (WPARAM)i, (LPARAM)&lvCol);			
	}
}
void InsertData(HWND hDlg)
{
	int count;
	LVITEM item;
	HWND hList;
	TCHAR name[20], phone[20];
	
	GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 20);
	SetDlgItemText(hDlg, IDC_EDIT_NAME, _T(""));
	if (_tcscmp(name, _T("")) == 0) return;
	GetDlgItemText(hDlg, IDC_EDIT_PHONE, phone, 20);   
	SetDlgItemText(hDlg, IDC_EDIT_PHONE, _T(""));
	
	hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
	count = ListView_GetItemCount(hList);
	item.mask = LVIF_TEXT;
	item.iItem = count;
	item.iSubItem = 0;  
	item.pszText = name; 
	ListView_InsertItem(hList,&item);
	ListView_SetItemText(hList, count, 1, phone);
}

int SelectItem(HWND hDlg, LPARAM lParam)
{
	LPNMLISTVIEW nlv;
	HWND hList;
	TCHAR name[20], phone[20];
	hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
	nlv = (LPNMLISTVIEW)lParam;
	ListView_GetItemText(hList, nlv->iItem, 0, name, 20);
	SetDlgItemText(hDlg, IDC_EDIT_NAME, name);
	ListView_GetItemText(hList, nlv->iItem, 1, phone, 20);
	SetDlgItemText(hDlg, IDC_EDIT_PHONE, phone);
	return(nlv->iItem);
}

BOOL CALLBACK Dlg6_12Proc(HWND hDlg, UINT iMsg, 
						  WPARAM wParam, LPARAM lParam)
{
	LPNMHDR hdr;
	HWND hList;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		MakeColumn(hDlg);
		return 1;	
	case WM_NOTIFY:
		hdr = (LPNMHDR)lParam;
		hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
		if (hdr->hwndFrom == hList && 
			hdr->code == LVN_ITEMCHANGING) SelectItem(hDlg, lParam);
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_INSERT:
			InsertData(hDlg);
			return 0;
		case IDCLOSE:
			DestroyWindow(hDlg);
			hDlg = NULL;
			return 0;
		case IDCANCEL:
			DestroyWindow(hDlg);
			hDlg = NULL;
			return 0;
		}
		break;
	}
	return 0;
}
