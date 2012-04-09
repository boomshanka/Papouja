#ifndef GSSINGLEPLAYERGAME_HPP
#define GSSINGLEPLAYERGAME_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"

#include "HumanPlayer.hpp"
#include "ComputerPlayer.hpp"
#include "Game.hpp"


class GSSingleplayerGame : public GameState
{
	public:
		GSSingleplayerGame(sf::RenderWindow& window, Settings& settings);
		~GSSingleplayerGame();
		
		void OnEnter();
		
		Status Update();
		void Render();
		
		GameState* OnLeave();
		
	private:
		Resourcemanager* myResourcemanager;
		
		HumanPlayer myHumanPlayer;
		ComputerPlayer myComputerPlayer;
		
		Game myGame;
		
		Status myNextStatus;
		GameState* myNextState;
		
		sf::Event myEvent;
		
		sf::Clock myEscapeClock;
		bool isEscapePressed;
};


#endif // GSSINGLEPLAYERGAME_HPP


