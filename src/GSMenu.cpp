#include "GSMenu.hpp"

#include "GSIntro.hpp"
#include "GSSingleplayerGame.hpp"
#include "GSMultiplayerGame.hpp"
#include "GSNetworkListener.hpp"
#include "GSNetworkConnector.hpp"
#include "GSNetworkGame.hpp"
#include "GSSettings.hpp"
#include "GSError.hpp"



GSMenu::GSMenu(sf::RenderWindow& window, Settings& settings) :
GameState(window, settings), Gui(window, settings, new Resourcemanager()), myResourcemanager(Gui::myResourcemanager), isNetworkChoosed(false)
{

}


GSMenu::GSMenu(sf::RenderWindow& window, Settings& settings, Resourcemanager* resourcemanager) :
GameState(window, settings), Gui(window, settings, resourcemanager), myResourcemanager(resourcemanager), isNetworkChoosed(false)
{

}


GSMenu::~GSMenu()
{
	delete myResourcemanager;
}



void GSMenu::OnEnter()
{
	try
	{
	//	myBackground.SetTexture(myResourcemanager->Get<sf::Texture>(mySettings.GetSettings("Resource", "MenuBackground")));
		Gui::LoadResources();
		
		Gui::SetMenupointText(0, "Singleplayer Game");
		Gui::SetMenupointText(1, "Multiplayer Game");
		Gui::SetMenupointText(2, "Network Game");
		Gui::SetMenupointText(3, "Settings");
		Gui::SetMenupointText(4, "Quit");
		
		Gui::FadeIn();
		
		myNextStatus = CONTINUE;
	}
	catch(FileNotFoundException& ex)
	{
		myNextStatus = NEXTSTATE;
		myNextState = new GSError(GameState::myWindow, GameState::mySettings, IMPORTANTRESOURCE, ex.what());
	}
}



Status GSMenu::Update()
{
	while(GameState::myWindow.PollEvent(myEvent))
	{
		if(myEvent.Type == sf::Event::Closed)
		{
			return QUIT;
		}
		
		if(myEvent.Type == sf::Event::KeyPressed && myEvent.Key.Code == sf::Keyboard::Escape)
		{
			if(isNetworkChoosed)
			{
				isNetworkChoosed = false;
				
				Gui::SetMenupointText(0, "Singleplayer Game");
				Gui::SetMenupointText(1, "Multiplayer Game");
				Gui::SetMenupointText(2, "Network Game");
				Gui::SetMenupointText(3, "Settings");
				Gui::SetMenupointText(4, "Quit");
		
				Gui::ActivateMenupoint(0, true);
				Gui::ActivateMenupoint(3, true);
			}
			else
			{
				return QUIT;
			}
		}
		
		Gui::CheckEvents(myEvent);
		
	}
	
	return myNextStatus;
}


void GSMenu::Render()
{
	GameState::myWindow.Draw(myBackground);
	Gui::Render();
}



GameState* GSMenu::OnLeave()
{
	return myNextState;
}



void GSMenu::Slot1()
{
	myNextStatus = NEXTSTATE;
	myNextState = new GSSingleplayerGame(GameState::myWindow, GameState::mySettings);
}


void GSMenu::Slot2()
{
	if(!isNetworkChoosed)
	{
		myNextStatus = NEXTSTATE;
		myNextState = new GSMultiplayerGame(GameState::myWindow, GameState::mySettings);
	}
	else
	{
		myNextStatus = NEXTSTATE;
		myNextState = new GSNetworkConnector(GameState::myWindow, GameState::mySettings, myResourcemanager);
		myResourcemanager = NULL;
	}
}


void GSMenu::Slot3()
{
	if(!isNetworkChoosed)
	{
		isNetworkChoosed = true;
		
		Gui::SetMenupointText(0, "");
		Gui::SetMenupointText(1, "Connect to Server");
		Gui::SetMenupointText(2, "Create Server");
		Gui::SetMenupointText(3, "");
		Gui::SetMenupointText(4, "Back");
		
		Gui::ActivateMenupoint(0, false);
		Gui::ActivateMenupoint(3, false);
	}
	else
	{
		myNextStatus = NEXTSTATE;
		myNextState = new GSNetworkListener(GameState::myWindow, GameState::mySettings, myResourcemanager);
		myResourcemanager = NULL;
	}
}


void GSMenu::Slot4()
{
	myNextStatus = NEXTSTATE;
	myNextState = new GSSettings(GameState::myWindow, GameState::mySettings, myResourcemanager);
	myResourcemanager = NULL;
}


void GSMenu::Slot5()
{
	if(isNetworkChoosed)
	{
		isNetworkChoosed = false;
		
		Gui::SetMenupointText(0, "Singleplayer Game");
		Gui::SetMenupointText(1, "Multiplayer Game");
		Gui::SetMenupointText(2, "Network Game");
		Gui::SetMenupointText(3, "Settings");
		Gui::SetMenupointText(4, "Quit");
		
		Gui::ActivateMenupoint(0, true);
		Gui::ActivateMenupoint(3, true);
	}
	else
	{
		myNextStatus = QUIT;
	}
}



