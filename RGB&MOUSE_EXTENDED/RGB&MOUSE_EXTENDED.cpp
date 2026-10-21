
#include "framework.h"
#include "RGB&MOUSE_EXTENDED.h"
#include "Resource.h"

#define MAX_LOADSTRING 100
HINSTANCE hInst;                                
char szTitle[MAX_LOADSTRING];                   
char szWindowClass[MAX_LOADSTRING];             

HBRUSH g_hbrBackground = NULL;

std::vector<unsigned int> PRGB;
DWORD dw;
POINT cursor;
bool paused = false;
std::vector<unsigned int> frozenPRGB;
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

    

    
    
    strcpy_s(szTitle, MAX_LOADSTRING, "RGB+MOUSE");
    
    strcpy_s(szWindowClass, MAX_LOADSTRING, "RGB+MOUSE");
    MyRegisterClass(hInstance);

    
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RGBMOUSEEXTENDED));

    MSG msg;
    
    
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
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RGBMOUSEEXTENDED));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    
    if (g_hbrBackground == NULL) {
        g_hbrBackground = CreateSolidBrush(RGB(40,40,40));
    }
    wcex.hbrBackground  = g_hbrBackground;
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_RGBMOUSEEXTENDED);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RGBMOUSEEXTENDED));

    return RegisterClassEx(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

   HWND hWnd = CreateWindowA(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 450, 280, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   
   
   SetTimer(hWnd, 1, 10, NULL);

   return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            
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

            
            DrawSampleInfo(hWnd, hdc);

            EndPaint(hWnd, &ps);

        }
        break;
    case WM_TIMER:
        {
            
            DrawSampleInfo(hWnd, NULL);

            if (!paused) {
                
                HDC hdcScreen = GetDC(HWND_DESKTOP);
                PRGB = RGB_POS(hWnd, hdcScreen);
                ReleaseDC(HWND_DESKTOP, hdcScreen);

                
                InvalidateRect(hWnd, NULL, TRUE);
            }
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
