#define UNICODE
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "Engine.h"

static bool isRunning = true;
static HWND window;
static ATOM windowClass = 0;

static LRESULT CALLBACK OnWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = TRUE;

    switch (uMsg)
    {
    case WM_CLOSE:
    {
        DestroyWindow(window);
        break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }
    case WM_QUIT:
    {
        isRunning = false;
    }
    
    default:
        result = DefWindowProcW(hWnd, uMsg, wParam, lParam);
    }

    return result;
}

bool InitializeWindow(int width, int height, LPCWSTR title)
{
        HINSTANCE hInstance = GetModuleHandle(nullptr);
    
    WNDCLASSEXW wcex = {};
    wcex.cbSize         = sizeof(wcex);
    wcex.style          = CS_OWNDC;
    wcex.lpfnWndProc    = OnWindowMessage;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIconW(hInstance, IDI_APPLICATION);
    wcex.hCursor        = LoadCursorW(hInstance, IDC_ARROW);
    wcex.hbrBackground  = nullptr;
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = L"Window";
    wcex.hIconSm        = LoadIconW(hInstance, IDI_APPLICATION);

    windowClass = RegisterClassExW(&wcex);

    CE_ASSERT(windowClass, "Faield to create window class");

    window = CreateWindowExW(
        0,
        L"Window",
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    CE_ASSERT(window, "Failed to create window");

    ShowWindow(window, SW_SHOW);

    return true;
}

void UpdateWindow()
{
    MSG msg = {};
    while (GetMessageW(&msg, window, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

int main()
{

    InitializeWindow(960, 540, L"Celeste");

    while (isRunning)
    {
        UpdateWindow();
    }

    return 0;
}