#ifndef GSSETTINGS_HPP
#define GSSETTINGS_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"
#include "GUI.hpp"

#include "Resourcemanager.hpp"


class GSSettings : public GameState
{
	public:
		GSSettings(sf::RenderWindow& window, Settings& settings, Resourcemanager* resourcemanager);
		~GSSettings();
		
		void OnEnter();
		
		Status Update();
		void Render();
		
		GameState* OnLeave();
		
	private:
		
		
};


#endif // GSSETTINGS_HPP


