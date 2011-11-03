#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <SFML/Graphics.hpp>

#include "Settings.hpp"
#include "GameState.hpp"


class GameManager
{
	public:
		GameManager(Settings& settings);
		~GameManager();

		int Run();
		
	private:
		sf::RenderWindow myWindow;
		Settings& mySettings;
		
		GameState* myState;
};


#endif // GAMEMANAGER_HPP


