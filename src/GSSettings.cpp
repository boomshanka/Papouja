#include "GSSettings.hpp"

#include "GSMenu.hpp"
#include "GSError.hpp"



GSSettings::GSSettings(sf::RenderWindow& window, Settings& settings, Resourcemanager* resourcemanager) :
GameState(window, settings), Gui(window, settings, resourcemanager), myResourcemanager(resourcemanager),
myNextStatus(CONTINUE), myNextState(NULL), myMenupoint(settings::MAIN), isChoosed(false)
{

}


GSSettings::~GSSettings()
{
	delete myResourcemanager;
}



void GSSettings::OnEnter()
{
	try
	{
	//	myBackground.SetTexture(myResourcemanager->Get<sf::Texture>(mySettings.GetSettings("Menu", "Background")));
		Gui::LoadResources();
		
		Gui::SetMenupointText(0, "Game Settings");
		Gui::SetMenupointText(1, "Window Settings");
		Gui::SetMenupointText(2, "Controls Player 1");
		Gui::SetMenupointText(3, "Controls Player 2");
		Gui::SetMenupointText(4, "Main Menu");
		
		Gui::FadeIn();
		
		myNextStatus = CONTINUE;
	}
	catch(FileNotFoundException& ex)
	{
		myNextStatus = NEXTSTATE;
		myNextState = new GSError(GameState::myWindow, GameState::mySettings, IMPORTANTRESOURCE, ex.what());
	}
}



Status GSSettings::Update()
{
	while(GameState::myWindow.pollEvent(myEvent))
	{
		if(myEvent.type == sf::Event::Closed)
		{
			myNextStatus = QUIT;
		}
		
		if(myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Escape)
		{
			if(myMenupoint != settings::MAIN)
			{
				if(!isChoosed)
				{
					Gui::SetMenupointText(0, "Game Settings");
					Gui::SetMenupointText(1, "Window Settings");
					Gui::SetMenupointText(2, "Controls Player 1");
					Gui::SetMenupointText(3, "Controls Player 2");
					Gui::SetMenupointText(4, "Main Menu");
				
					myMenupoint = settings::MAIN;
				}
				else
				{
					isChoosed = false;
				}
			}
			else
			{
				myNextStatus = NEXTSTATE;
				myNextState = new GSMenu(GameState::myWindow, GameState::mySettings, myResourcemanager);
				myResourcemanager = NULL;
			}
		}
		else if(isChoosed)
		{
			
		}
		else if(myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Left)
		{
			if(myMenupoint == settings::GAME)
			{
				switch(Gui::GetMenuPosition())
				{
					case 0:
						
					break;
					
					case 1:
						
					break;
					
					case 2:
						
					break;
					
					case 3:
						
					break;
				}
			}
		}
		else if(myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Right)
		{
			if(myMenupoint == settings::GAME)
			{
				switch(Gui::GetMenuPosition())
				{
					case 0:
						
					break;
					
					case 1:
						
					break;
					
					case 2:
						
					break;
					
					case 3:
						
					break;
				}
			}
		}
		else
		{
			Gui::CheckEvents(myEvent);
		}
	}
	
	return myNextStatus;
}


void GSSettings::Render()
{
	Gui::Render();
}



GameState* GSSettings::OnLeave()
{
	return myNextState;
}




void GSSettings::Slot1()
{
	switch(myMenupoint)
	{
		case settings::MAIN:
			Gui::SetMenupointText(0, "Music Volume: " + GameState::mySettings.GetSettings("Game", "MusicVolume"));
			Gui::SetMenupointText(1, "Sound Volume: " + GameState::mySettings.GetSettings("Game", "SoundVolume"));
			Gui::SetMenupointText(2, "Key Sensitivity: " + GameState::mySettings.GetSettings("Game", "Sensitivity"));
			Gui::SetMenupointText(3, "AI Level: " + GameState::mySettings.GetSettings("Game", "AiLevel"));
			Gui::SetMenupointText(4, "Back");
		
			myMenupoint = settings::GAME;
		break;
		
		case settings::GAME:
			
		break;
		
		case settings::WINDOW:
			
		break;
		
		case settings::CONTROLS1:
			
		break;
		
		case settings::CONTROLS2:
			
		break;
	}
}


void GSSettings::Slot2()
{
	switch(myMenupoint)
	{
		case settings::MAIN:
			Gui::SetMenupointText(0, "Window Resolution: ");
			Gui::SetMenupointText(1, "Window Mode: ");
			Gui::SetMenupointText(2, "");
			Gui::SetMenupointText(3, "Apply");
			Gui::SetMenupointText(4, "Back");
		
			myMenupoint = settings::WINDOW;
			Gui::ActivateMenupoint(2, false);
		break;
		
		case settings::GAME:
			
		break;
		
		case settings::WINDOW:
			
		break;
		
		case settings::CONTROLS1:
			
		break;
		
		case settings::CONTROLS2:
			
		break;
	}
}


void GSSettings::Slot3()
{
	switch(myMenupoint)
	{
		case settings::MAIN:
			Gui::SetMenupointText(0, "Left: ");
			Gui::SetMenupointText(1, "Right: ");
			Gui::SetMenupointText(2, "Down: ");
			Gui::SetMenupointText(3, "Rotate: ");
			Gui::SetMenupointText(4, "Back");
			
			myMenupoint = settings::CONTROLS1;
		break;
		
		case settings::GAME:
			
		break;
		
		case settings::WINDOW:
			
		break;
		
		case settings::CONTROLS1:
			
		break;
		
		case settings::CONTROLS2:
			
		break;
	}
}


void GSSettings::Slot4()
{
	switch(myMenupoint)
	{
		case settings::MAIN:
			Gui::SetMenupointText(0, "Left: ");
			Gui::SetMenupointText(1, "Right: ");
			Gui::SetMenupointText(2, "Down: ");
			Gui::SetMenupointText(3, "Rotate: ");
			Gui::SetMenupointText(4, "Back");
			
			myMenupoint = settings::CONTROLS2;
		break;
		
		case settings::GAME:
			
		break;
		
		case settings::WINDOW:
			
		break;
		
		case settings::CONTROLS1:
			
		break;
		
		case settings::CONTROLS2:
			
		break;
	}
}


void GSSettings::Slot5()
{
	if(myMenupoint == settings::MAIN)
	{
		myNextStatus = NEXTSTATE;
		myNextState = new GSMenu(GameState::myWindow, GameState::mySettings, myResourcemanager);
		myResourcemanager = NULL;
	}
	else
	{
		Gui::SetMenupointText(0, "Game Settings");
		Gui::SetMenupointText(1, "Window Settings");
		Gui::SetMenupointText(2, "Controls Player 1");
		Gui::SetMenupointText(3, "Controls Player 2");
		Gui::SetMenupointText(4, "Main Menu");
		Gui::ActivateMenupoint(2, true);
		
		myMenupoint = settings::MAIN;
	}
}



