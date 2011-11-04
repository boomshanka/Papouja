#ifndef GSNETWORKLISTENER_HPP
#define GSNETWORKLISTENER_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"


class GSNetworkListener : public GameState
{
	public:
		GSNetworkListener(sf::RenderWindow& window, Settings& settings);
		~GSNetworkListener();
		
		void OnEnter();
		
		Status Update();
		void Render();
		
		GameState* OnLeave();
		
	private:
		
		
};


#endif // GSNETWORKLISTENER_HPP


