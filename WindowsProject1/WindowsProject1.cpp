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
static int pn = 0;
static int pw = 0;
static int MAKS_GRENSE_X = 999999;
static int MAKS_GRENSE_Y = -999999;

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
            SetTimer(hWnd, 0, 100, 0);
        }
        break;

    case WM_TIMER:
    {
        lyskryssverdi = ++lyskryssverdi % 25;

        RECT client;
        GetClientRect(hWnd, &client);
        
        int* pointerX;
        int* pointerY;

        switch (pw) {
        case -1:
            {
            int tilfeldig = rand() % 25;
            if (tilfeldig == 1) {
                if (vestkoe.empty()) {
                    
                    Bil bil(client.left, client.bottom / 2 - 5, &MAKS_GRENSE_X, &MAKS_GRENSE_Y);
                    vestkoe.push_back(bil);
                }
                else {
                    pointerX = &vestkoe.back().xPos;
                    pointerY = &vestkoe.back().yPos;
                    Bil bil(client.left, client.bottom / 2 - 5, pointerX, pointerY);
                    vestkoe.push_back(bil);
                }
                
            }
            }
            break;

        case 0:
            {
            int tilfeldig = rand() % 15;
            if (tilfeldig == 1) {
                if (vestkoe.empty()) {

                    Bil bil(client.left, client.bottom / 2 - 5, &MAKS_GRENSE_X, &MAKS_GRENSE_Y);
                    vestkoe.push_back(bil);
                }
                else {
                    pointerX = &vestkoe.back().xPos;
                    pointerY = &vestkoe.back().yPos;
                    Bil bil(client.left, client.bottom / 2 - 5, pointerX, pointerY);
                    vestkoe.push_back(bil);
                }
            }
            }
            break;

        case 1:
            {
            int tilfeldig = rand() % 5;
            if (tilfeldig == 1) {
                if (vestkoe.empty()) {

                    Bil bil(client.left, client.bottom / 2 - 5, &MAKS_GRENSE_X, &MAKS_GRENSE_Y);
                    vestkoe.push_back(bil);
                }
                else {
                    pointerX = &vestkoe.back().xPos;
                    pointerY = &vestkoe.back().yPos;
                    Bil bil(client.left, client.bottom / 2 - 5, pointerX, pointerY);
                    vestkoe.push_back(bil);
                }
            }
            }
            break;
        }

        switch (pn) {
        case -1:
            {
            int tilfeldig = rand() % 25;
            if (tilfeldig == 1) {
                if (nordkoe.empty()) {

                    Bil bil2(client.right / 2 - 5, client.bottom - 20, &MAKS_GRENSE_X, &MAKS_GRENSE_Y);
                    nordkoe.push_back(bil2);
                }
                else {
                    pointerX = &nordkoe.back().xPos;
                    pointerY = &nordkoe.back().yPos;
                    Bil bil2(client.right / 2 - 5, client.bottom - 20, pointerX, pointerY);
                    nordkoe.push_back(bil2);
                }
            }
            }
            break;

        case 0:
            {
            //Standard-rate for bil-spawning
            int tilfeldig = rand() % 15;
            if (tilfeldig == 1) {

                
                
                //Sjekke om den nordg�ende-listen er tom.
                if (nordkoe.empty()) {

                    //Lager en nord-g�ende Bil med MAKSGRENSER langt utenfor vinduet s� sammenligning fremdeles er mulig.
                    Bil bil2(client.right / 2 - 5, client.bottom - 20, &MAKS_GRENSE_X, &MAKS_GRENSE_Y);
                    //Legger bilen BAKERST i listen.
                    nordkoe.push_back(bil2);
                }
                
                
                
                
                //Viss listen ikke er tom
                else {
                    //Henter lager til pointere ved � hente bakerste bil sine koordinater
                    pointerX = &nordkoe.back().xPos;
                    pointerY = &nordkoe.back().yPos;
                    
                    //Lager ny �st-g�ende Bil med pointere(KUN EN ER RELEVANT FOR S�R-NORD BEVEGELSE) til Bilen som kom f�r den i listen.
                    Bil bil2(client.right / 2 - 5, client.bottom - 20, pointerX, pointerY);
                    //Legger bilen BAKERST i listen.
                    nordkoe.push_back(bil2);
                }
            }

            }
            break;

        case 1:
            {
            int tilfeldig = rand() % 5;
            if (tilfeldig == 1) {
                if (nordkoe.empty()) {

                    Bil bil2(client.right / 2 - 5, client.bottom - 20, &MAKS_GRENSE_X, &MAKS_GRENSE_Y);
                    nordkoe.push_back(bil2);
                }
                else {
                    pointerX = &nordkoe.back().xPos;
                    pointerY = &nordkoe.back().yPos;
                    Bil bil2(client.right / 2 - 5, client.bottom - 20, pointerX, pointerY);
                    nordkoe.push_back(bil2);
                }
            }
            }
            break;
        }
        InvalidateRect(hWnd, &client, true);
    }
        break;
    
    case WM_MBUTTONDOWN:
        {
            lyskryssverdi = (lyskryssverdi + 10) % 25;
        }
        break;

    case WM_KEYDOWN:
    {
        switch (wParam) {
        case VK_UP:
            pn = 1;
            break;
        case VK_DOWN:
            pn = -1;
            break;
        case VK_LEFT:
            pw = -1;
            break;
        case VK_RIGHT:
            pw = 1;
            break;
        }
        
    }
    break;

    case WM_KEYUP:
    {
        switch (wParam) {
        case VK_UP:
            pn = 0; 
            break;
        case VK_DOWN:
            pn = 0; 
            break;
        case VK_LEFT:
            pw = 0;
            break;
        case VK_RIGHT:
            pw = 0;
            break;
        }
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
        KillTimer(hWnd, 0);
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
