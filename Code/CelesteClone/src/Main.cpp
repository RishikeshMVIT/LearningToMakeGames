
#include "EngineLib.h"

#pragma region Globals
static bool isRunning = true;
#pragma endregion

#pragma region Platform
bool PlatformCreateWindow(unsigned int width, unsigned int height, const char* title);
void PlatformUpdateWindow();
#pragma endregion

#pragma region Windows Platform
#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define UNICODE

#include <Windows.h>

static HWND window = NULL;

static LRESULT CALLBACK OnWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = NULL;

    switch (uMsg)
    {
    case WM_CREATE:
    {
        break;
    }

    case WM_CLOSE:
    {
        if (MessageBox(hWnd, L"Really quit?", L"Celeste Clone", MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(hWnd);
        }

        return 0;
    }

    case WM_DESTROY:
    {
        PostQuitMessage(0);
        isRunning = false;

        return 0;
    }

    default:
    {
        result = DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    }

    return result;
}

bool PlatformCreateWindow(unsigned int width, unsigned int height, LPCWSTR title)
{
    HINSTANCE instance = GetModuleHandle(0);
    WNDCLASS wc = {};
    //wc.style            = ;
    wc.lpfnWndProc      = OnWindowMessage;
    wc.cbClsExtra       = NULL;
    wc.cbWndExtra       = NULL;
    wc.hInstance        = instance;
    wc.hIcon            = LoadIcon(instance, IDI_APPLICATION);
    wc.hCursor          = LoadCursor(instance, IDC_ARROW);
    //wc.hbrBackground    = ;
    //wc.lpszMenuName     = ;
    wc.lpszClassName    = L"BaseWindowClass";

    if (!RegisterClass(&wc))
    {
        return false;
    }

    DWORD dwStyle = WS_OVERLAPPEDWINDOW; 

    window = CreateWindow(
        L"BaseWindowClass",
        title,
        dwStyle,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        NULL,
        NULL,
        instance,
        NULL
    );

    if (window == NULL)
    {
        return false;
    }

    ShowWindow(window, SW_SHOW);

    return true;

}

void PlatformUpdateWindow()
{
    MSG msg;
    while(PeekMessage(&msg, window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

#endif
#pragma endregion

int main()
{
    PlatformCreateWindow(960, 540, L"Celeste Clone");

    while (isRunning)
    {
        PlatformUpdateWindow();

    }

    return 0;
}