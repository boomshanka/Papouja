#ifndef GAME_HPP
#define GAME_HPP

#include "Gamefield.hpp"

#include "Settings.hpp"
#include "Resourcemanager.hpp"



class Game
{
	public:
		Game(Gamefield& field1, Gamefield& field2, Settings& settings, Resourcemanager* resourcemanager);
		~Game();
		
		void LoadResources(const sf::Vector2i& windowsize);
		void Start();
		
		bool Update();
		void Draw(sf::RenderWindow& window);
		
	private:
		Gamefield& myFirstGamefield;
		Gamefield& mySecondGamefield;
		
		Settings& mySettings;
		Resourcemanager* myResourcemanager;
		
		sf::Sprite myBackgroundSprite;
		
		sf::Clock myClock;
		sf::Clock myStepClock;
		
		bool isGameStarted;
};



#endif // GAME_HPP



