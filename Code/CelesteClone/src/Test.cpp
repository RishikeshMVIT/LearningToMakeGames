#define UNICODE
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

static bool isRunning = true;

static LRESULT CALLBACK OnWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0; 

    switch (uMsg)
    {
        case WM_CLOSE:
        {
            isRunning = false;
            break;
        }

        default:
        {
            result = DefWindowProcW(hWnd, uMsg, wParam, lParam);
        }
    }

    return result;
}

int main()
{
    HINSTANCE hInstance = GetModuleHandle(nullptr);
    HWND window;
    ATOM windowClass;

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

    window = CreateWindowExW(
        0,
        L"Window",
        L"Celeste",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        960, 540,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (!window)
        return -1;

    ShowWindow(window, SW_SHOW);

    while (isRunning)
    {
        MSG msg = {};
        while (GetMessageW(&msg, window, 0, 0) > 0)
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }
}

