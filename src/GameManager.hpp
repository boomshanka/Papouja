#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include "Settings.hpp"


class GameManager
{
	public:
		GameManager(Settings& settings);
		~GameManager();

		int Run();
		
	private:
		sf::RenderWindow myWindow;
		Settings& mySettings;
};


#endif // GAMEMANAGER_HPP



