#define WIN32_MEAN_AND_LEAN

#include <vulkan\vulkan.h>
#include <Windows.h>

void OnResize(HWND hWnd, UINT flag, int width, int height)
{

}

static LRESULT OnWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_SIZE:
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);

			OnResize(hWnd, (UINT)wParam, int width, int height);
		} break;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(hWnd, &ps);
		} break;

		case WM_CLOSE:
		{
			
		} break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		} break;

		case WM_QUIT:
		{

		} break;

		default:
		{
			return DefWindowProcW(hWnd, msg, wParam, lParam);
		}
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	bool isRunning = true;

	WNDCLASSEXW wcex = {};
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = OnWindowMessage;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIconW(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursorW(hInstance, IDC_ARROW);
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"Theia Window";
	wcex.hIconSm = LoadIconW(hInstance, IDI_APPLICATION);

	ATOM windowClass = RegisterClassExW(&wcex);

	if (!windowClass)
	{
		OutputDebugStringW(L"Failed to register window");
		return -1;
	}

	HWND windowHandle = CreateWindowExW(
		WS_EX_APPWINDOW,
		(LPCWSTR)windowClass,
		L"CoreWindow",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		960, 540,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	if (!windowHandle)
	{
		OutputDebugStringW(L"Failed to create window");
		return -1;
	}

	ShowWindow(windowHandle, nCmdShow);

	while(isRunning)
	{
		MSG msg = {};
		while (PeekMessageW(&msg, windowHandle, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

	}

	DestroyWindow(windowHandle);
	UnregisterClassW((LPCWSTR)windowClass, hInstance);

	return 0;
}
