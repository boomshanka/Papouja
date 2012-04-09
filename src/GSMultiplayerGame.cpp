#include "GSMultiplayerGame.hpp"

#include "GSError.hpp"
#include "GSMenu.hpp"



GSMultiplayerGame::GSMultiplayerGame(sf::RenderWindow& window, Settings& settings) :
GameState(window, settings), myResourcemanager(new Resourcemanager),
myFirstPlayer(settings, myResourcemanager, true), mySecondPlayer(settings, myResourcemanager, false),
myGame(myFirstPlayer, mySecondPlayer, mySettings, myResourcemanager)
{

}


GSMultiplayerGame::~GSMultiplayerGame()
{
	delete myResourcemanager;
}



void GSMultiplayerGame::OnEnter()
{
	try
	{
		myGame.LoadResources(sf::Vector2i(myWindow.GetWidth(), myWindow.GetHeight()));
		
		myNextStatus = CONTINUE;
		myGame.Start();
	}
	catch(FileNotFoundException& ex)
	{
		myNextStatus = NEXTSTATE;
		myNextState = new GSError(GameState::myWindow, GameState::mySettings, RESOURCE, ex.what());
	}
}



Status GSMultiplayerGame::Update()
{
	while(GameState::myWindow.PollEvent(myEvent))
	{
		//myHumanPlayer.CheckInput(myEvent);
		
		if(myEvent.Type == sf::Event::Closed)
		{
			myNextStatus = QUIT;
		}
		else if(myEvent.Type == sf::Event::KeyPressed)
		{
			if(myEvent.Key.Code == sf::Keyboard::Escape)
			{
				if(isEscapePressed)
				{
					myNextState = new GSMenu(myWindow, mySettings);
					myNextStatus = NEXTSTATE;
				}
				else
				{
					isEscapePressed = true;
					myEscapeClock.Restart();
				}
			}
		}
	}
	
	if(!myGame.Update())
	{
		
	}
	
	
	if(isEscapePressed && myEscapeClock.GetElapsedTime().AsMilliseconds() > 500)
	{
		isEscapePressed = false;
	}
	
	
	return myNextStatus;
}


void GSMultiplayerGame::Render()
{
	myGame.Draw(myWindow);
}



GameState* GSMultiplayerGame::OnLeave()
{
	return myNextState;
}


