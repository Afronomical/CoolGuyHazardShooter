#include "Game/Game.h"

#include <ctime>

#include "MemoryLeakDetector/MemoryLeakDetector.h"

int main(int argc, char* argv[])
{
	// INFO: Memory Leak Detection Flags
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// INFO: Setting seed for random number generation
	srand(unsigned int(time(NULL)));

	Game game("Game", Vector2(800, 600));

    return 0;
}

