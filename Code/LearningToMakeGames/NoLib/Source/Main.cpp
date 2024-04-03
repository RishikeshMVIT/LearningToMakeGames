#include "Theia.h"

TheiaAppEntryPoint
{
	// Game Init
	
	Theia::Game::SetGameUpdate([&](float delta)
	{

	}
	);

	Theia::Game::Start();
	// Game Update Logic

	// Game Shutdown

	return 0;
}
