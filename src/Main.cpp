#include "Settings.hpp"
#include "GameManager.hpp"


int main(int argc, char* argv[])
{
	Settings settings(argc, argv);
	settings.LoadConfigFile();
	
	switch(settings.ParseArguments())
	{
		case 1:
			return EXIT_SUCCESS;
		case -1:
			return EXIT_FAILURE;
	}
	
	GameManager* game = new GameManager(settings);
	int returnValue = game->Run();
	delete game;

	return returnValue;
}


