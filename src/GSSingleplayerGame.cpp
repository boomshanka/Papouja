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
	while(myWindow.PollEvent(myEvent))
	{
		if(myEvent.Type == sf::Event::Closed)
		{
			myNextStatus = QUIT;
		}
		else if(myEvent.Type == sf::Event::KeyPressed)
		{
			if(myEvent.Key.Code == sf::Keyboard::Escape)
			{
				if(myEscapeClock.GetElapsedTime() < 500)
				{
					myNextStatus = NEXTSTATE;
					myNextState = new GSMenu(myWindow, mySettings);
				}
				else
				{
					myEscapeClock.Reset();
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


