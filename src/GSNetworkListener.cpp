#include "GSNetworkListener.hpp"

#include "GSNetworkGame.hpp"
#include "GSMenu.hpp"
#include "GSError.hpp"

#include <SFML/Window/Keyboard.hpp>



GSNetworkListener::GSNetworkListener(sf::RenderWindow& window, Settings& settings, Resourcemanager* resourcemanager) :
GameState(window, settings), myResourcemanager(resourcemanager), myMenupoint(networklistener::NAME), myMenustatus(networklistener::CHOOSE),
Gui(window, settings, resourcemanager)
{

}


GSNetworkListener::~GSNetworkListener()
{

}



void GSNetworkListener::OnEnter()
{
	Gui::SetMenupointText(0, "Name: " + myNameString);
	Gui::SetMenupointText(1, "Port: " + myPortString);
	Gui::SetMenupointText(2, "Start Listening");
	Gui::SetMenupointText(4, "Main Menu");
	
	myNextStatus = CONTINUE;
	Gui::FadeIn();
}



Status GSNetworkListener::Update()
{
	while(GameState::myWindow.PollEvent(myEvent))
	{
		if(myEvent.Type == sf::Event::Closed)
		{
			return QUIT;
		}
		
		if(myMenustatus != networklistener::EDIT)
		{
			if(myEvent.Type == sf::Event::KeyPressed && myEvent.Key.Code == sf::Keyboard::Escape)
			{
				myNextState = new GSMenu(GameState::myWindow, GameState::mySettings, myResourcemanager);
			
				myNextStatus = NEXTSTATE;
			}
			else
			{
				Gui::CheckEvents(myEvent);
			}
		}
		else
		{
			if(myEvent.Type == sf::Event::KeyPressed && (myEvent.Key.Code == sf::Keyboard::Escape || myEvent.Key.Code == sf::Keyboard::Return))
			{
				myMenustatus = networklistener::CHOOSE;
			}
			else
			{
				Edit();
				
				if(myMenupoint == networklistener::NAME)
				{
					Gui::SetMenupointText(0, "Name: " + *editstr);
				}
				else if(myMenupoint == networklistener::PORT)
				{
					Gui::SetMenupointText(1, "Port: " + *editstr);
				}
			}
		}
	}
	
	return myNextStatus;
}


void GSNetworkListener::Render()
{
	Gui::Render();
}



GameState* GSNetworkListener::OnLeave()
{
	return myNextState;
}



void GSNetworkListener::Edit()
{
	if(myEvent.Type == sf::Event::KeyPressed)
	{
		if(myEvent.Key.Code == sf::Keyboard::Back && myCurserPosition > 0)
		{
			editstr->erase(--myCurserPosition, 1);
		}
		else if(myEvent.Key.Code == sf::Keyboard::Left && myCurserPosition > 0)
		{
			--myCurserPosition;
		}
		else if(myEvent.Key.Code == sf::Keyboard::Right && editstr->length() > myCurserPosition)
		{
			++myCurserPosition;
		}
		else if(myEvent.Key.Code == sf::Keyboard::Up)
		{
			myCurserPosition = 0;
		}
		else if(myEvent.Key.Code == sf::Keyboard::Down)
		{
			myCurserPosition = editstr->length();
		}	
	}
	else if(myEvent.Type == sf::Event::TextEntered && myEvent.Text.Unicode != 13 && myEvent.Text.Unicode != 8)
	{
		if(myMenupoint == networklistener::PORT)
		{
			switch(static_cast<char>(myEvent.Text.Unicode))
			{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					myPortString.insert(myCurserPosition, std::size_t(1), static_cast<char>(myEvent.Text.Unicode));
					++myCurserPosition;
				break;
			}
		}
		else
		{
			editstr->insert(myCurserPosition, std::size_t(1), static_cast<char>(myEvent.Text.Unicode));
			++myCurserPosition;
		}
	}
}



void GSNetworkListener::StartListening()
{

}


void GSNetworkListener::StopListening()
{
	
}



void GSNetworkListener::Listening()
{
	
}



void GSNetworkListener::Slot1()
{
	myMenustatus = networklistener::EDIT;
	myCurserPosition = myNameString.length();
	editstr = &myNameString;
	myMenupoint = networklistener::NAME;
}


void GSNetworkListener::Slot2()
{
	myMenustatus = networklistener::EDIT;
	myCurserPosition = myPortString.length();
	editstr = &myPortString;
	myMenupoint = networklistener::PORT;
}


void GSNetworkListener::Slot3()
{
	switch(myMenustatus)
	{
		case networklistener::CHOOSE:
			StartListening();
			myMenustatus = networklistener::LISTENING;
		break;
		
		case networklistener::LISTENING:
			StopListening();
			myMenustatus = networklistener::CHOOSE;
		break;
		
		case networklistener::CONNECTED:
			myNextState = new GSNetworkGame(GameState::myWindow, GameState::mySettings);//, mySocket); FIXME
			myNextStatus = NEXTSTATE;
		break;
		
		default: break;
	}
}


void GSNetworkListener::Slot4()
{

}


void GSNetworkListener::Slot5()
{
	switch(myMenustatus)
	{
		case networklistener::CHOOSE:
	//		StartListening();
	//		myMenustatus = networklistener::LISTENING;
		break;
		
		case networklistener::LISTENING:
	//		StopListening();
	//		myMenustatus = networklistener::CHOOSE;
		break;
		
		case networklistener::CONNECTED:
	//		myNextState = new GSNetworkGame(GameState::myWindow, GameState::mySettings);//, mySocket); FIXME
	//		myNextStatus = NEXTSTATE;
		break;
		
		default: break;
	}
}




