#ifndef GSMULTIPLAYERGAME_HPP
#define GSMULTIPLAYERGAME_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"

#include "HumanPlayer.hpp"
#include "Game.hpp"


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
		Resourcemanager* myResourcemanager;
		
		HumanPlayer myFirstPlayer;
		HumanPlayer mySecondPlayer;
		
		Game myGame;
		
		Status myNextStatus;
		GameState* myNextState;
		
		sf::Event myEvent;
		
		sf::Clock myEscapeClock;
		bool isEscapePressed;
		
};


#endif // GSMULTIPLAYERGAME_HPP


