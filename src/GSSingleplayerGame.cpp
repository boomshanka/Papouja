#include "GSSingleplayerGame.hpp"

#include "GSMenu.hpp"
#include "GSError.hpp"



GSSingleplayerGame::GSSingleplayerGame(sf::RenderWindow& window, Settings& settings) :
GameState(window, settings), myResourcemanager(new Resourcemanager),
myHumanPlayer(settings, myResourcemanager), myComputerPlayer(settings, myResourcemanager),
myGame(myHumanPlayer, myComputerPlayer, mySettings, myResourcemanager)
{

}


GSSingleplayerGame::~GSSingleplayerGame()
{
	delete myResourcemanager;
}



void GSSingleplayerGame::OnEnter()
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



Status GSSingleplayerGame::Update()
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


void GSSingleplayerGame::Render()
{
	myGame.Draw(myWindow);
}



GameState* GSSingleplayerGame::OnLeave()
{
	return myNextState;
}


