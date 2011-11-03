#ifndef GSSINGLEPLAYERGAME_HPP
#define GSSINGLEPLAYERGAME_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"


class GSSingleplayerGame : public GameState
{
	public:
		GSSingleplayerGame(sf::RenderWindow& window);
		~GSSingleplayerGame();
		
		void OnEnter();
		
		Status Update();
		void Render();
		
		GameState* OnLeave();
		
	private:
		
		
};


#endif // GSSINGLEPLAYERGAME_HPP


