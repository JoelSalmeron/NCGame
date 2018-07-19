#include "game.h"
#include "engine.h"

int main(int argc, char* argv[])
{
	Engine engine;
	GAME game(&engine);

	game.Intialize();
	while (game.Run()) game.Update();
	game.Shutdown();

	return 0;
}