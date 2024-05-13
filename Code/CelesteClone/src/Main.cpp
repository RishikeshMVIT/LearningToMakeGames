// Defines
#define APIENTRY
#define GL_GLEXT_PROTOTYPES

// Includes
#include "Input.h"

#include "Engine.h"
#include "Platform.h"
#include "PlatformWin32.h"
#include "Renderer.cpp"

int main()
{

    Platform::InitializeWindow(960, 540, L"Celeste");
    input.screensizeX = 960;
    input.screensizeY = 540;

    BumpAllocator transientStorage = MakeAllocator(MB(64));

    glInitialize(&transientStorage);

    while (Platform::isRunning)
    {
        Platform::UpdateWindow();
        glRender();

        Platform::SwapWindowBuffers();
    }

    Platform::Shutdown();

    return 0;
}