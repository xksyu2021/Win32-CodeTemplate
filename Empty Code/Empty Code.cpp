#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

//New UI
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

//Basic info
static TCHAR szWindowClass[] = _T("classNAME");         //
static TCHAR szTitle[] = _T("NAME");            //
HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    // Window config
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            szTitle, MB_ICONERROR);
        return 1;
    }


    //Create window
    hInst = hInstance;
    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass, szTitle,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        530, 560, NULL, NULL,
        hInstance, NULL
    );
    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            szTitle,NULL);
        return 1;
    }

    //Create controls
    HWND hLabel = CreateWindow(
        L"STATIC", L"XKSYU2021",
        WS_VISIBLE | WS_CHILD,
        30, 55, 200, 40,
        hWnd, NULL,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL
    );

    if (NULL) {     //
        MessageBox(NULL,        //
            _T("Control creating failed!"),
            szTitle, MB_ICONERROR);
        return 1;
    }

    //Font
    HFONT hFont = CreateFont(
        24,
        0, 0, 0,
        FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY,
        FF_ROMAN,
        L"Arial"
    );
    SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, TRUE);

    //Visibility & Loop
    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

//Behavior of controls
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("by xksyu2021");

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        TextOut(hdc,
            5, 5,
            greeting, _tcslen(greeting));
        EndPaint(hWnd, &ps);
        break;

    case WM_COMMAND:
    {
        WORD wmId = LOWORD(wParam);
        switch (wmId)
        {
        //
        }
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}