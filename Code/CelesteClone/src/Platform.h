#pragma once

namespace Platform
{
static bool isRunning = true;

bool InitializeWindow(int width, int height, char* title);
void UpdateWindow();
void* LoadGLFunction(char * funcName);
}