// Menu_Sample.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include <stdio.h>
#include "framework.h"
#include "Menu_Sample.h"


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MENUSAMPLE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MENUSAMPLE));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MENUSAMPLE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDR_MYMENU);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void CopyFN()
{

}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
struct CallFN
{
    int paramid;
    void (*fn)() = CopyFN;
};


//#define MYDEF

#ifdef MYDEF
void CallFN2()
#else
void CallFN2(int a)
#endif // MYDEF
{

}






void OutFromFile(TCHAR filename[], HWND hwnd)
{
    FILE* fPtr;
    HDC hdc;
    int line;
    TCHAR buffer[500];
    line = 0;
    
    hdc = GetDC(hwnd);
#ifdef _UNICODE   	// 문자집합이 유니코드일 때
    _tfopen_s(&fPtr, filename, _T("r, ccs = UNICODE"));
#else   		// 문자집합이 멀티바이트일 때
    _tfopen_s(&fPtr, filename, _T("r"));
#endif
    while (_fgetts(buffer, 100, fPtr) != NULL)
    {
        if (buffer[_tcslen(buffer) - 1] == _T('\n'))
            buffer[_tcslen(buffer) - 1] = NULL;
        TextOut(hdc, 0, line * 20, buffer, _tcslen(buffer));
        line++;
    }
    fclose(fPtr);
    ReleaseDC(hwnd, hdc);
}


// 선택 되기전에는 메뉴 비활성화 
// 서클 선택 하면 메뉴 활성화 빨간색 만들기
// 복사를 메뉴 누르면 마우스 따라다니는 원
// 따라다니는 원 상태에서
//   마우스 왼버턴 누르면 붙여넣기
//   마우스 오른버턴 누르면 취소
// 메뉴 전체 비활성화


#include <math.h>
#define SIZE 20
static int x, y;

// 길이 구하기
double LengthPts(int x1, int y1, int x2, int y2)
{
    return(sqrt((float)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))));
}

BOOL InCircle(int x, int y, int mx, int my)
{
    if (LengthPts(x, y, mx, my) < SIZE) return TRUE;
    else return FALSE;
}

#define COUNT 5

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    
    static HMENU hmwnu, hsubmenu;
    static BOOL selected = false;
    static BOOL copy = false;
    static int mx, my;
    static POINT tempcirclepos[10];
    static int top = 0;

    switch (message)
    {
    case WM_MOUSEMOVE:
    {
        mx = LOWORD(lParam);
        my = HIWORD(lParam);
        if (copy)
        {
            InvalidateRgn(hWnd, NULL, TRUE);
        }
    }break;
    case WM_LBUTTONDOWN:
    {
        mx = LOWORD(lParam);
        my = HIWORD(lParam);

        if (copy)
        {
            copy = FALSE;
            
            tempcirclepos[top].x = mx;
            tempcirclepos[top].y = my;
            top = (top + 1) % COUNT;
            InvalidateRgn(hWnd, NULL, TRUE);

            break;
        }

        if (InCircle(x, y, mx, HIWORD(lParam)))
        {
            EnableMenuItem(hsubmenu, ID_MENU_COPY, MF_ENABLED);
            selected = TRUE;
            InvalidateRgn(hWnd, NULL, TRUE);
        }
        
        

    }break;
    case WM_CREATE:
    {
        x = 40;
        y = 40;

        hmwnu = GetMenu(hWnd);
        hsubmenu = GetSubMenu(hmwnu, 0);

        //ID_MENU_COPY
        EnableMenuItem(hsubmenu, ID_MENU_COPY, MF_GRAYED);
        EnableMenuItem(hsubmenu, ID_MENU_PASTE, MF_DISABLED);

    }break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);

            switch (wmId)
            {
            case ID_MENU_COPY:
            {
                OutputDebugString(_T("카피누름"));
                //CopyFN();
                copy = TRUE;
                InvalidateRgn(hWnd, NULL, TRUE);
            }break;
            default:{
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
            }

        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...


            HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
            HBRUSH oldbrush = NULL;
            if (selected)
            {
                oldbrush = (HBRUSH)SelectObject(hdc, brush);
            }

            // 원래구
            // 구 그리기
            Ellipse(hdc, x - SIZE, y - SIZE, x + SIZE, y + SIZE);

            if (oldbrush)
            {
                SelectObject(hdc, oldbrush);
            }


            if (copy)
            {
                Ellipse(hdc, mx - SIZE, my - SIZE, mx + SIZE, my + SIZE);
            }
            
            for (POINT pos : tempcirclepos)
            {
                if (pos.x == 0 && pos.y == 0)
                    continue;
                Ellipse(hdc, pos.x - SIZE, pos.y - SIZE, pos.x + SIZE, pos.y + SIZE);
            }
            


            DeleteObject(brush);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }



    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
