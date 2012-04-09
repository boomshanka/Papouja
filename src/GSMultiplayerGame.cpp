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
		myGame.LoadResources(sf::Vector2i(myWindow.getSize()));
		
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
	while(GameState::myWindow.pollEvent(myEvent))
	{
		//myHumanPlayer.CheckInput(myEvent);
		
		if(myEvent.type == sf::Event::Closed)
		{
			myNextStatus = QUIT;
		}
		else if(myEvent.type == sf::Event::KeyPressed)
		{
			if(myEvent.key.code == sf::Keyboard::Escape)
			{
				if(isEscapePressed)
				{
					myNextState = new GSMenu(myWindow, mySettings);
					myNextStatus = NEXTSTATE;
				}
				else
				{
					isEscapePressed = true;
					myEscapeClock.restart();
				}
			}
		}
	}
	
	if(!myGame.Update())
	{
		
	}
	
	
	if(isEscapePressed && myEscapeClock.getElapsedTime().asMilliseconds() > 500)
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


