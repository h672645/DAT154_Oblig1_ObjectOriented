// WindowsProject1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WindowsProject1.h"
#include "Lyskryss.cpp"
#include "TrafikklysNord.cpp"
#include "TrafikklysVest.cpp"
#include "Bil.cpp"
#include <list>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
static int lyskryssverdi = 0;

static bool nordLysRodt = false;
static bool vestLysRodt = false;
static list<Bil> nordkoe;
static list<Bil> vestkoe;
static const int TIMER_LIGHTS = 1;
static const int TIMER_BILVEST = 2;
static const int TIMER_BILNORD = 3;

// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

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
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int pn = 1;
    static int pw = 1;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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

    case WM_CREATE:
        {
            SetTimer(hWnd, TIMER_LIGHTS, 500, 0);
            SetTimer(hWnd, TIMER_BILVEST, 1000, 0);
            SetTimer(hWnd, TIMER_BILNORD, 1000, 0);
        }
        break;

    case WM_TIMER:
        {
        
        switch (wParam) {

        case TIMER_LIGHTS:
        {
            RECT client;
            GetClientRect(hWnd, &client);
            lyskryssverdi = (lyskryssverdi + 1) % 25;
            InvalidateRect(hWnd, &client, true);
        }
            break;

        case TIMER_BILVEST:
        {
            RECT client;
            GetClientRect(hWnd, &client);
            int tilfeldig;
            if (pw == 1 || pw == 2 ? tilfeldig = rand() % 10 : tilfeldig = 1);
            
            if (tilfeldig == 1) {
                Bil bil(client.left, client.bottom / 2 - 5);
                vestkoe.push_back(bil);
            }
        }
            break;

        case TIMER_BILNORD:
        {
            RECT client;
            GetClientRect(hWnd, &client);
            int tilfeldig;
            if (pn == 1 || pn == 2 ? tilfeldig = rand() % 10 : tilfeldig = 1);

            if (tilfeldig == 1) {
                Bil bil2(client.right / 2 - 5, client.bottom - 20);
                nordkoe.push_back(bil2);
            }
        }
            break;
        }
        }
        break;
    
    case WM_MBUTTONDOWN:
        {
            RECT rect;
            GetClientRect(hWnd, &rect);

            lyskryssverdi = (lyskryssverdi + 10) % 25;

            InvalidateRect(hWnd, &rect, true);
        }
        break;

    case WM_LBUTTONDOWN:
    {
        RECT rect;
        GetClientRect(hWnd, &rect);
        pw = 2;
        InvalidateRect(hWnd, &rect, true);
    }
    break;

    case WM_LBUTTONUP:
    {
        RECT rect;
        GetClientRect(hWnd, &rect);
        pw = 1;
        InvalidateRect(hWnd, &rect, true);
    }
    break;

    case WM_RBUTTONDOWN:
    {
        RECT rect;
        GetClientRect(hWnd, &rect);
        pn = 2;
        InvalidateRect(hWnd, &rect, true);
    }
    break;

    case WM_RBUTTONUP:
    {
        RECT rect;
        GetClientRect(hWnd, &rect);
        pn = 1;
        InvalidateRect(hWnd, &rect, true);
    }
    break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...

            Lyskryss lyskryss(1, 1);
            lyskryss.draw(hWnd, hdc);
            TrafikklysNord trafikklysnord(lyskryssverdi);
            TrafikklysVest trafikklysvest(lyskryssverdi);
            bool* lyspointervest = &vestLysRodt;
            bool* lyspointernord = &nordLysRodt;
            trafikklysnord.draw(hWnd, hdc, lyspointernord);
            trafikklysvest.draw(hWnd, hdc, lyspointervest);

            POINT point = { 10,10 };

            for (auto& bil : vestkoe) {
                bil.drawBilVest(hWnd, hdc, point, vestLysRodt);
            }
            
            for (auto& bil : nordkoe) {
                bil.drawBilNord(hWnd, hdc, point, nordLysRodt);
            }
            

            EndPaint(hWnd, &ps);
        }
        break;

    case WM_DESTROY:
        KillTimer(hWnd, TIMER_LIGHTS);
        KillTimer(hWnd, TIMER_BILNORD);
        KillTimer(hWnd, TIMER_BILVEST);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
