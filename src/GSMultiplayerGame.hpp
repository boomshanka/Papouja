#ifndef GSMULTIPLAYERGAME_HPP
#define GSMULTIPLAYERGAME_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"


class GSMultiplayerGame : public GameState
{
	public:
		GSMultiplayerGame(sf::RenderWindow& window, Settings& settings);
		~GSMultiplayerGame();
		
		void OnEnter();
		
		Status Update();
		void Render();
		
		GameState* OnLeave();
		
	private:
		
		
};


#endif // GSMULTIPLAYERGAME_HPP


