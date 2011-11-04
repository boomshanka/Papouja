#ifndef GSNETWORKCONNECTOR_HPP
#define GSNETWORKCONNECTOR_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"


class GSNetworkConnector : public GameState
{
	public:
		GSNetworkConnector(sf::RenderWindow& window, Settings& settings);
		~GSNetworkConnector();
		
		void OnEnter();
		
		Status Update();
		void Render();
		
		GameState* OnLeave();
		
	private:
		
		
};


#endif // GSNETWORKCONNECTOR_HPP


