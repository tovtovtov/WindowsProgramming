// 2026_10_14.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "2026_10_14.h"

#pragma comment(lib, "msimg32.lib")

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
    LoadStringW(hInstance, IDC_MY20261014, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY20261014));

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

    return (int)msg.wParam;
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY20261014));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY20261014);
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

HBITMAP g_hBitmap;
HBITMAP g_hChar;
HBITMAP g_hCharMask;
HBITMAP g_hCharAnim[10];
int g_index = 0;

static HDC mem1dc, mem2dc;
void Doublebuffer(HWND hWnd, HDC hdc)
{
    RECT rect;

    GetClientRect(hWnd, &rect);

    int clientWidth = rect.right - rect.left;
    int clientHeight = rect.bottom - rect.top;

    mem2dc = CreateCompatibleDC(hdc);

    HDC bitmaphdc = CreateCompatibleDC(mem2dc);
    SelectObject(bitmaphdc, g_hBitmap);
    
    BitBlt(mem2dc, 0, 0, 200, 200, bitmaphdc, 100, 100, SRCCOPY);

    BitBlt(hdc, 0, 0, clientWidth, clientHeight, mem2dc, 0, 0, SRCCOPY);

    DeleteObject(bitmaphdc);
    DeleteDC(mem2dc);

    
}

// 특정 색상만 지우기
void BlendKeySample(HWND hWnd, HDC hdc)
{
    // 배경
    HDC bitmaphdc = CreateCompatibleDC(hdc);
    SelectObject(bitmaphdc, g_hBitmap);

    // 캐릭터
    HDC charhdc = CreateCompatibleDC(hdc);
    SelectObject(charhdc, g_hChar);

    BitBlt(hdc, 0, 0, 200, 200, bitmaphdc, 100, 100, SRCCOPY);

    TransparentBlt(hdc, 0, 0, 240, 180, charhdc, 0, 0, 240, 180, RGB(255, 0, 255));

    DeleteDC(bitmaphdc);
    DeleteDC(charhdc);
}

void BlendMode(HWND hWnd, HDC hdc)
{
    // 배경
    HDC bitmaphdc = CreateCompatibleDC(hdc);
    SelectObject(bitmaphdc, g_hBitmap);
    // 캐릭터
    HDC charhdc = CreateCompatibleDC(hdc);
    SelectObject(charhdc, g_hChar);
    // 마스크
    HDC charmaskhdc = CreateCompatibleDC(hdc);
    SelectObject(charmaskhdc, g_hCharMask);

    BitBlt(hdc, 0, 0, 200, 200, bitmaphdc, 100, 100, SRCCOPY);

    BitBlt(hdc, 0, 0, 240, 180, charmaskhdc, 0, 0, SRCAND);

    BitBlt(hdc, 0, 0, 240, 180, charhdc, 0, 0, SRCPAINT);

    DeleteDC(charhdc);
    DeleteDC(bitmaphdc);
    DeleteDC(charmaskhdc);
}

void CharacterAnimation(HWND hWnd, HDC hdc)
{
    HDC bitmaphdc = CreateCompatibleDC(hdc);
    SelectObject(bitmaphdc, g_hBitmap);

    // 캐릭터
    HDC charhdc = CreateCompatibleDC(hdc);
    SelectObject(charhdc, g_hCharAnim[g_index]);

    BitBlt(hdc, 0, 0, 500, 500, bitmaphdc, 0, 0, SRCCOPY);

    BitBlt(hdc, 0, 0, 240, 180, charhdc, 0, 0, SRCCOPY);

    DeleteDC(bitmaphdc);
    DeleteDC(charhdc);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_KEYDOWN:
    {
        g_index = (g_index + 1) % 10;
        InvalidateRect(hWnd, NULL, true);
    }break;
    case WM_CREATE:
    {
        g_hBitmap = (HBITMAP)LoadBitmap(
            hInst, MAKEINTRESOURCE(IDB_BITMAP3)
        );

        // 파일 직접 로드
        g_hChar = (HBITMAP)LoadImage(NULL, _T("images/maskpink.bmp"), IMAGE_BITMAP, 0, 0
            , LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        g_hCharMask = (HBITMAP)LoadImage(NULL, _T("images/mask00.bmp"), IMAGE_BITMAP, 0, 0
            , LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        TCHAR loadpath[256] = _T("images/run00.bmp");
        for (int i = 0; i < 10; i++)
        {
            loadpath[11] = '0' + i;
            g_hCharAnim[i] = (HBITMAP)LoadImage(NULL, loadpath, IMAGE_BITMAP, 0, 0
                , LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        }
        

    }break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            // BlendMode(hWnd, hdc);

            // BlendKeySample(hWnd, hdc);

            // Doublebuffer(hWnd, hdc);

            CharacterAnimation(hWnd, hdc);

            //HDC bitmaphdc = CreateCompatibleDC(hdc);
            //SelectObject(bitmaphdc, g_hBitmap); // bmp -> bit hdc 선택적용

            //BitBlt(hdc, 100, 100, 400, 400, bitmaphdc, 100, 100, SRCCOPY);

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
