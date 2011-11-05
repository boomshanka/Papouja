#include "GSNetworkListener.hpp"

#include "GSNetworkGame.hpp"
#include "GSMenu.hpp"
#include "GSError.hpp"

#include <SFML/Window/Keyboard.hpp>



GSNetworkListener::GSNetworkListener(sf::RenderWindow& window, Settings& settings, Resourcemanager* resourcemanager) :
GameState(window, settings), myResourcemanager(resourcemanager), myMenupoint(networklistener::NAME), myMenustatus(networklistener::CHOOSE)
{

}


GSNetworkListener::~GSNetworkListener()
{

}



void GSNetworkListener::OnEnter()
{
	myNextStatus = CONTINUE;
}



Status GSNetworkListener::Update()
{
	while(myWindow.PollEvent(myEvent))
	{
		if(myEvent.Type == sf::Event::Closed)
		{
			return QUIT;
		}
		
		if(myMenustatus != networklistener::EDIT)
		{
			if(myEvent.Type == sf::Event::KeyPressed)
			{
				if(myEvent.Key.Code == sf::Keyboard::Escape)
				{
					myNextState = new GSMenu(myWindow, mySettings, myResourcemanager);
				
					myNextStatus = NEXTSTATE;
				}
				else if(myEvent.Key.Code == sf::Keyboard::Return)
				{
					Apply();
				}
				else if(myEvent.Key.Code == sf::Keyboard::Up)
				{
					switch(myMenupoint)
					{
						case networklistener::NAME:
							myMenupoint = networklistener::LISTEN;
						break;
						
						case networklistener::PORT:
							myMenupoint = networklistener::NAME;
						break;
						
						case networklistener::LISTEN:
							myMenupoint = networklistener::PORT;
						break;
					}
				}
				else if(myEvent.Key.Code == sf::Keyboard::Down)
				{
					switch(myMenupoint)
					{
						case networklistener::NAME:
							myMenupoint = networklistener::PORT;
						break;
						
						case networklistener::PORT:
							myMenupoint = networklistener::LISTEN;
						break;
						
						case networklistener::LISTEN:
							myMenupoint = networklistener::NAME;
						break;
					}
				}
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
			}
		}
	}
	
	return myNextStatus;
}


void GSNetworkListener::Render()
{

}



GameState* GSNetworkListener::OnLeave()
{
	return myNextState;
}



void GSNetworkListener::Apply()
{
	switch(myMenupoint)
	{
		case networklistener::NAME:
			if(myMenustatus == networklistener::CHOOSE)
			{
				myMenustatus = networklistener::EDIT;
				myCurserPosition = myNameString.length();
				editstr = &myNameString;
			}
		break;
		
		case networklistener::PORT:
			if(myMenustatus == networklistener::CHOOSE)
			{
				myMenustatus = networklistener::EDIT;
				myCurserPosition = myPortString.length();
				editstr = &myPortString;
			}
		break;
		
		case networklistener::LISTEN:
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
					myNextState = new GSNetworkGame(myWindow, mySettings);//, mySocket); FIXME
					myNextStatus = NEXTSTATE;
				break;
				
				default: break;
			}
		break;
	}
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




