#include <cstdlib>
#include <iostream>

#include "ruru/Game.h"
#include "ruru/Config.h"

#include "example/GamePlayScene.h"

int main(int argc, char* argv[])
{
	RuRu::Config config;
	config.setResolutionWidth(600);
	config.setResolutionHeight(960);
	config.setFrameSpeed(40);

	RuRu::Game game(&config);

	try
	{
		game.initialise();
		game.pushScene(new GamePlayScene());
		game.run();
	}
	catch(std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
