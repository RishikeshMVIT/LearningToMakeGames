#pragma once

// Defines
#define UNICODE
#define NOMINMAX

// Includes
#include <Windows.h>
#include <GL/glcorearb.h>
#include <GL/wglext.h>

#include "Engine.h"
#include "Platform.h"

namespace Platform
{
    static HINSTANCE hInstance;
    static HWND window;
    static ATOM windowClass = 0;
    static HDC dc;

    static LRESULT CALLBACK OnWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT result = TRUE;

        switch (uMsg)
        {
            case WM_CLOSE:
            {
                if (MessageBox(window, L"Quit?", L"Celeste", MB_OKCANCEL))
                {
                    DestroyWindow(window);
                    isRunning = false;
                }
                return 0;
            }

            case WM_SIZE:
            {
                RECT rect = {};
                GetClientRect(window, &rect);
                input.screensizeX = rect.right - rect.left;
                input.screensizeY = rect.bottom - rect.top;
            }
            
            default:
                result = DefWindowProcW(hWnd, uMsg, wParam, lParam);
                break;
        }

        return result;
    }

    bool InitializeWindow(int width, int height, LPCWSTR title)
    {
        hInstance = GetModuleHandle(nullptr);
        
        WNDCLASSEXW wcex = {};
        wcex.cbSize         = sizeof(wcex);
        //wcex.style          = CS_OWNDC;
        wcex.lpfnWndProc    = OnWindowMessage;
        wcex.cbClsExtra     = 0;
        wcex.cbWndExtra     = 0;
        wcex.hInstance      = hInstance;
        wcex.hIcon          = LoadIconW(hInstance, (LPCWSTR)IDI_APPLICATION);
        wcex.hCursor        = LoadCursorW(hInstance, (LPCWSTR)IDC_ARROW);
        wcex.hbrBackground  = nullptr;
        wcex.lpszMenuName   = nullptr;
        wcex.lpszClassName  = L"Window";
        wcex.hIconSm        = LoadIconW(hInstance, (LPCWSTR)IDI_APPLICATION);

        windowClass = RegisterClassExW(&wcex);

        CE_ASSERT(windowClass, "Faield to create window class");

        PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;

        DWORD dwStyle = WS_OVERLAPPEDWINDOW;

        //Initialize OpenGL
        {
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

            if (window == NULL)
            {
                CE_ASSERT(false, "Failed to create window");
                return false;
            }

            HDC tempDC = GetDC(window);

            if(!tempDC)
            {
                CE_ASSERT(false, "Failed to get HDC");
                return false;
            }

            PIXELFORMATDESCRIPTOR pfd = {};
            pfd.nSize           = sizeof(pfd);
            pfd.nVersion        = 1;
            pfd.dwFlags         = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
            pfd.iPixelType      = PFD_TYPE_RGBA;
            pfd.cColorBits      = 32;
            pfd.cAlphaBits      = 8;
            pfd.cDepthBits      = 24;

            int pixelFormat = ChoosePixelFormat(tempDC, &pfd);
            if(!pixelFormat)
            {
                CE_ASSERT(false, "Failed to get pixel format");
                return false;
            }

            if(!SetPixelFormat(tempDC, pixelFormat, &pfd))
            {
                CE_ASSERT(false, "Failed to set pixel format");
                return false;
            }

            HGLRC tempRC = wglCreateContext(tempDC);

            if(!tempRC)
            {
                CE_ASSERT(false, "Failed to create render context");
                return false;
            }

            if (!wglMakeCurrent(tempDC, tempRC))
            {
                CE_ASSERT(false, "Failed to set current context");
                return false;
            }

            wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC) Platform::LoadGLFunction("wglChoosePixelFormatARB");
            wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) Platform::LoadGLFunction("wglCreateContextAttribsARB");

            if (!wglChoosePixelFormatARB || !wglCreateContextAttribsARB)
            {
                CE_ASSERT(false, "Failed to get WGL functions");
                return false;
            }

            wglMakeCurrent(tempDC, 0);
            wglDeleteContext(tempRC);
            ReleaseDC(window, tempDC);
            DestroyWindow(window);

            CE_TRACE("Initialized OpenGL");
        }

        //Create Window
        {
            {
                RECT borderRect = {};
                AdjustWindowRectEx(&borderRect, dwStyle, 0, 0);
                width += borderRect.right - borderRect.left;
                height += borderRect.top - borderRect.bottom;
            }

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

            if (window == NULL)
            {
                CE_ASSERT(false, "Failed to create window");
                return false;
            }

            dc = GetDC(window);
            if (!dc)
            {
                CE_ASSERT(false, "Failed to get DC");
                return false;
            }

            const int pixelAttribs[] = 
            {
                WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
                WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
                WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
                WGL_SWAP_METHOD_ARB,    WGL_SWAP_COPY_ARB,
                WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
                WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
                WGL_COLOR_BITS_ARB,     32,
                WGL_ALPHA_BITS_ARB,     8,
                WGL_DEPTH_BITS_ARB,     24,
                0
            };

            UINT pixelFormatCount = 0;
            int pixelFormat = 0;

            if (!wglChoosePixelFormatARB(dc, pixelAttribs, 0, 1, &pixelFormat, &pixelFormatCount))
            {
                CE_ASSERT(false, "failed to choos epixel format");
                return false;
            }

            PIXELFORMATDESCRIPTOR pfd = {};
            DescribePixelFormat(dc, pixelFormat, sizeof(pfd), &pfd);

            if (!SetPixelFormat(dc, pixelFormat, &pfd))
            {
                CE_ASSERT(false, "Failed to set pixel format");
                return false;
            }

            const int contextAttribs[] = 
            {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 3,
            WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            WGL_CONTEXT_FLAGS_ARB,         WGL_CONTEXT_DEBUG_BIT_ARB,
            0  
            };

            HGLRC rc = wglCreateContextAttribsARB(dc, 0, contextAttribs);
            if (!rc)
            {
                CE_ASSERT(false, "Failed to get rendering context");
                return false;
            }

            if (!wglMakeCurrent(dc, rc))
            {
                CE_ASSERT(false, "Failed to set context");
                return false;
            }

        }

        CE_TRACE("Initialized Window");

        ShowWindow(window, SW_SHOW);

        return true;
    }

    void UpdateWindow()
    {
        MSG msg = {};
        while (PeekMessageW(&msg, window, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    void* LoadGLFunction(char* funcName)
    {
        PROC proc = wglGetProcAddress(funcName);
        if(!proc)
        {
            static HMODULE openglDLL = LoadLibraryW(L"opengl32.dll");
            proc = GetProcAddress(openglDLL, funcName);
            
            if (!proc)
            {
                CE_ASSERT(false, "Failed to Load OpenGL");
                return nullptr;
            }
        }

        return (void*)proc;
    }

    void SwapWindowBuffers()
    {
        SwapBuffers(dc);
    }

    void Shutdown()
    {
        DestroyWindow(window);
        UnregisterClassW((LPCWSTR)windowClass, hInstance);
    }

}