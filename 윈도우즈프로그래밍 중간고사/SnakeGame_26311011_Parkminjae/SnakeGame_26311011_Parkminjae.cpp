// SnakeGame_26311011_Parkminjae.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "SnakeGame_26311011_Parkminjae.h"

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
    LoadStringW(hInstance, IDC_SNAKEGAME26311011PARKMINJAE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SNAKEGAME26311011PARKMINJAE));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SNAKEGAME26311011PARKMINJAE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SNAKEGAME26311011PARKMINJAE);
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

const int rad = 20; // 반지름 20 원
int snakeLen = 3;
// 머리 중심 좌표
int headX;
int headY;
// 바디 중심 좌표
int posX;
int posY;
// 방향
int dirX = 0;
int dirY = -1;

POINT snake[90]{ {200, 200}, {200, 240}, {200, 280} };
POINT item{};
bool spawnItem = false;
bool getItem = false;
bool isDead = false;

TCHAR finish[20] = _T("Game Over");

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    headX = snake[0].x;
    headY = snake[0].y;
    switch (message)
    {
    case WM_CREATE:
    {
        SetTimer(hWnd, 1, 500, NULL); // 0.5초
        SetTimer(hWnd, 2, 2000, NULL);
        
    }break;
    
    case WM_TIMER:
    {
        if (wParam == 1)
        {
            if (headX == 0 || headY == 0 || headX == 400 || headY == 360)
            {
                isDead = true;
                InvalidateRgn(hWnd, NULL, true);
            }
            if (headX == item.x && headY == item.y)
            {
                snakeLen += 1;
                spawnItem = false;
                getItem = true;
                InvalidateRgn(hWnd, NULL, true);
            }
            if (!isDead)
            {   
                for (int i = snakeLen - 1; i > 0; --i)
                {
                    snake[i].x = snake[i - 1].x;
                    snake[i].y = snake[i - 1].y;
                    snake[1].x = headX;
                    snake[1].y = headY;
                }

                snake[0].x += dirX * 40;
                snake[0].y += dirY * 40;
                headX = snake[0].x;
                headY = snake[0].y;

                InvalidateRgn(hWnd, NULL, true);
            }
            
        }
        if (wParam == 2)
        {
            if (!spawnItem)
            {
                spawnItem = true;
                item.x = 40 + (rand() % 10) * 40;
                item.y = 40 + (rand() % 10) * 40;
            }
            
        }
    }break;
    
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_UP:
        {
            if (dirY != 1)
            {
                dirX = 0;
                dirY = -1;
            }
            
        }break;

        case VK_DOWN:
        {
            if (dirY != -1)
            {
                dirX = 0;
                dirY = 1;
            }
            
        }break;
           
        case VK_RIGHT:
        {
            if (dirX != -1)
            {
                dirX = 1;
                dirY = 0;
            }
            
        }break;

        case VK_LEFT:
        {
            if (dirX != 1)
            {
                dirX = -1;
                dirY = 0;
            }
            
        }break;
        }

    }break;
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            // 맵 테두리
            Rectangle(hdc, 0, 0, 400, 360);

            if (!isDead)
            {
                for (int i = 1; i < snakeLen; i++)
                {
                    posX = snake[i].x;
                    posY = snake[i].y;
                    Ellipse(hdc, posX - rad, posY - rad, posX + rad, posY + rad);
                }

                HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
                HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, redBrush);

                Ellipse(hdc, headX - rad, headY - rad, headX + rad, headY + rad);

                SelectObject(hdc, oldBrush);
                DeleteObject(redBrush);

                if (spawnItem)
                {
                    HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
                    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, greenBrush);

                    HPEN dot = CreatePen(PS_DOT, 1, NULL);
                    HPEN oldpen = (HPEN)SelectObject(hdc, dot);

                    Rectangle(hdc, item.x - 20, item.y - 20, item.x + 20, item.y + 20);

                    SelectObject(hdc, oldpen);
                    SelectObject(hdc, oldBrush);
                    DeleteObject(dot);
                    DeleteObject(greenBrush);
                }
            }
            else
            {
                TextOut(hdc, 200, 200, finish, _tcslen(finish));
            }
          
                

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
    {
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
    }break;
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
