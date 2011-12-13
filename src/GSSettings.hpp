#ifndef GSSETTINGS_HPP
#define GSSETTINGS_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"
#include "GUI.hpp"

#include "Resourcemanager.hpp"



namespace settings
{
	enum Menupoint
	{
		MAIN,
		GAME,
		WINDOW,
		CONTROLS1,
		CONTROLS2
	};
}


class GSSettings : public GameState, public Gui
{
	public:
		GSSettings(sf::RenderWindow& window, Settings& settings, Resourcemanager* resourcemanager);
		~GSSettings();
		
		void OnEnter();
		
		Status Update();
		void Render();
		
		GameState* OnLeave();
		
	private:
		Resourcemanager* myResourcemanager;
		
		sf::Sprite myBackground;
		sf::Event myEvent;
		
		Status myNextStatus;
		GameState* myNextState;
		
		settings::Menupoint myMenupoint;
		bool isChoosed;
		
		void Slot1();
		void Slot2();
		void Slot3();
		void Slot4();
		void Slot5();
};


#endif // GSSETTINGS_HPP


