#include "Theia.h"

TheiaAppEntryPoint
{
	// Game Init
	
	Theia::Game::SetGameUpdate([&](float delta)
	{
			wchar_t charBuffer[256];
			swprintf(charBuffer, 256, L"delta: %f\n", delta);
			OutputDebugString(charBuffer);
	}
	);

	Theia::Game::Start();
	// Game Update Logic

	// Game Shutdown

	return 0;
}
