#include "Game/Game.h"

#include "MemoryLeakDetector/MemoryLeakDetector.h"

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game("Game");

    return 0;
}

