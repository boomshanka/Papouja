#include "GSSingleplayerGame.hpp"

#include "GSMenu.hpp"
#include "GSError.hpp"



GSSingleplayerGame::GSSingleplayerGame(sf::RenderWindow& window, Settings& settings) :
GameState(window, settings), myHumanPlayer(settings), myComputerPlayer(settings), myGame(myHumanPlayer, myComputerPlayer)
{

}


GSSingleplayerGame::~GSSingleplayerGame()
{

}



void GSSingleplayerGame::OnEnter()
{

}



Status GSSingleplayerGame::Update()
{
	while(myWindow.pollEvent(myEvent))
	{
		if(myEvent.type == sf::Event::Closed)
		{
			myNextStatus = QUIT;
		}
		else if(myEvent.type == sf::Event::KeyPressed)
		{
			if(myEvent.key.code == sf::Keyboard::Escape)
			{
				if(myEscapeClock.getElapsedTime().asMilliseconds() < 500)
				{
					myNextStatus = NEXTSTATE;
					myNextState = new GSMenu(myWindow, mySettings);
				}
				else
				{
					myEscapeClock.restart();
				}
			}
		}
	}
	
	return myNextStatus;
}


void GSSingleplayerGame::Render()
{
	myGame.Draw(myWindow);
}



GameState* GSSingleplayerGame::OnLeave()
{
	return myNextState;
}


