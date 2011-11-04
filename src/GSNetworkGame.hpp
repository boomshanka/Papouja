#ifndef GSNETWORKGAME_HPP
#define GSNETWORKGAME_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"


class GSNetworkGame : public GameState
{
	public:
		GSNetworkGame(sf::RenderWindow& window, Settings& settings);
		~GSNetworkGame();
		
		void OnEnter();
		
		Status Update();
		void Render();
		
		GameState* OnLeave();
		
	private:
		
		
};


#endif // GSNETWORKGAME_HPP


