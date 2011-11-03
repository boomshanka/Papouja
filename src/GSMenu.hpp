#ifndef GSMENU_HPP
#define GSMENU_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"


class GSMenu : public GameState
{
	public:
		GSMenu(sf::RenderWindow& window);
		~GSMenu();
		
		void OnEnter();
		
		Status Update();
		void Render();
		
		GameState* OnLeave();
		
	private:
		
		
};


#endif // GSMENU_HPP


