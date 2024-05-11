// Defines
#define APIENTRY

// Includes
#include <GL/glcorearb.h>

#include "Engine.h"
#include "Platform.h"
#include "PlatformWin32.h"
#include "Renderer.h"


int main()
{

    Platform::InitializeWindow(960, 540, L"Celeste");

    while (Platform::isRunning)
    {
        Platform::UpdateWindow();
    }

    return 0;
}