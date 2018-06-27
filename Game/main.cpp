#include "engine.h"

int main(int argc, char* argv[])
{
	Engine engine;
	
	engine.Intialize();
	while (!engine.IsQuit())
	{
		engine.Update();
	}
	engine.Shutdown();

	return 0;
}