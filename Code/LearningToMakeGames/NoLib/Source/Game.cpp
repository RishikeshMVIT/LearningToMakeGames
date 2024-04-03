#include "Game.h"

namespace Theia
{
	LRESULT WindowCallback(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT result = 0;

		switch (msg)
		{
		case WM_CLOSE:
		{
			Game::GetInstance().isRunning = false;
			PostQuitMessage(0);
			OutputDebugString(L"Window Closed\n");
		} break;

		case WM_DESTROY:
		{
			OutputDebugString(L"Window Destroyed");
		} break;

		case WM_PAINT:
		{
			PAINTSTRUCT paint;
			HDC deviceContext = BeginPaint(windowHandle, &paint);

			FillRect(deviceContext, &paint.rcPaint, (HBRUSH)(COLOR_WINDOW + 2));

			EndPaint(windowHandle, &paint);
		} break;

		default:
			result = DefWindowProc(windowHandle, msg, wParam, lParam);
		}

		return result;
	}

	Game::Game()
	{
		// Initialize Window Properties to default
		windowTitle = L"Theia App";
		windowWidth = 960;
		windowHeight = 540;
	}

	void Game::StartWindow()
	{
		const wchar_t* className = L"Theia Window";

		WNDCLASS windowClass = {};
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = WindowCallback;
		windowClass.hInstance = hInstance;
		windowClass.lpszClassName = className;

		if (!RegisterClass(&windowClass))
		{
			OutputDebugString(L"Failed to register window class");
			return;
		}

		windowHandle = CreateWindowEx(
			0,
			className,
			windowTitle.c_str(),
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT,
			windowWidth, windowHeight,
			0,
			0,
			hInstance,
			0
		);

		if (windowHandle)
		{
			isRunning = true;

			LARGE_INTEGER cpuFrequency;
			QueryPerformanceFrequency(&cpuFrequency);

			LARGE_INTEGER lastCounter;
			QueryPerformanceCounter(&lastCounter);

			while (isRunning)
			{
				LARGE_INTEGER currentCounter;
				QueryPerformanceCounter(&currentCounter);

				int64_t counterElapsed = currentCounter.QuadPart - lastCounter.QuadPart;

				float delta = (float)counterElapsed / (float)cpuFrequency.QuadPart;

				lastCounter = currentCounter;

				MSG msg;
				while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					if (msg.message == WM_QUIT)
						isRunning = false;

					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}

				GetInstance().Update(delta);
			}
		}
		else
		{
			OutputDebugString(L"Failed to create window");
			return;
		}
	}


}


