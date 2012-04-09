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



Status GSSingleplayerGame::Update()
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


void GSSingleplayerGame::Render()
{
	myGame.Draw(myWindow);
}



GameState* GSSingleplayerGame::OnLeave()
{
	return myNextState;
}


