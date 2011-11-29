#ifndef GSMENU_HPP
#define GSMENU_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"
#include "GUI.hpp"

#include "Resourcemanager.hpp"


class GSMenu : public GameState, public Gui
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
		
		sf::Event myEvent;
		
		bool isNetworkChoosed;
		
		Status myNextStatus;
		GameState* myNextState;
		
		void Slot1();
		void Slot2();
		void Slot3();
		void Slot4();
		void Slot5();
};


#endif // GSMENU_HPP


