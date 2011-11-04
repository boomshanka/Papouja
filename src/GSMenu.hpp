#ifndef GSMENU_HPP
#define GSMENU_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"

#include "Resourcemanager.hpp"


class GSMenu : public GameState
{
	public:
		GSMenu(sf::RenderWindow& window, Settings& settings);
		GSMenu(sf::RenderWindow& window, Settings& settings, Resourcemanager* resourcemanager);
		~GSMenu();
		
		void OnEnter();
		
		Status Update();
		void Render();
		
		GameState* OnLeave();
		
	private:
		Resourcemanager* myResourcemanager;
		
		sf::Sprite myBackground;
		
		
		Status myNextStatus;
		GameState* myNextState;
		
};


#endif // GSMENU_HPP


