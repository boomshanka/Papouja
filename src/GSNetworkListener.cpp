#include "GSNetworkListener.hpp"

#include "GSNetworkGame.hpp"
#include "GSMenu.hpp"
#include "GSError.hpp"

#include <SFML/Window/Keyboard.hpp>

#include <sstream>



GSNetworkListener::GSNetworkListener(sf::RenderWindow& window, Settings& settings, Resourcemanager* resourcemanager) :
GameState(window, settings), Gui(window, settings, resourcemanager), myResourcemanager(resourcemanager), myMenupoint(networklistener::NAME), myMenustatus(networklistener::CHOOSE), myListenerThread(&GSNetworkListener::Listening, this), mySocket(NULL)
{

}


GSNetworkListener::~GSNetworkListener()
{
	StopListening();
	delete myResourcemanager;
}



void GSNetworkListener::OnEnter()
{
	//try
	{
		Gui::LoadResources();
	}
	
	myNameString = GameState::mySettings.GetSettings("Game", "Name");
	myPortString = GameState::mySettings.GetSettings("Game", "Port");
	
	Gui::SetMenupointText(0, "Name: " + myNameString);
	Gui::SetMenupointText(1, "Port: " + myPortString);
	Gui::SetMenupointText(2, "Start Listening");
	Gui::ActivateMenupoint(3, false);
	Gui::SetMenupointText(4, "Main Menu");
	
	myNextStatus = CONTINUE;
	Gui::FadeIn();
}



Status GSNetworkListener::Update()
{
	while(GameState::myWindow.pollEvent(myEvent))
	{
		if(myEvent.type == sf::Event::Closed)
		{
			return QUIT;
		}
		
		if(myMenustatus != networklistener::EDIT)
		{
			if(myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Escape)
			{
				myNextState = new GSMenu(GameState::myWindow, GameState::mySettings, myResourcemanager);
				
				myResourcemanager = NULL;
			
				myNextStatus = NEXTSTATE;
			}
			else
			{
				Gui::CheckEvents(myEvent);
			}
		}
		else
		{
			if(myEvent.type == sf::Event::KeyPressed && (myEvent.key.code == sf::Keyboard::Escape || myEvent.key.code == sf::Keyboard::Return))
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
	myGuiMutex.lock();
	Gui::Render();
	myGuiMutex.unlock();
}



GameState* GSNetworkListener::OnLeave()
{
	return myNextState;
}



void GSNetworkListener::Edit()
{
	if(myEvent.type == sf::Event::KeyPressed)
	{
		if(myEvent.key.code == sf::Keyboard::Back && myCurserPosition > 0)
		{
			editstr->erase(--myCurserPosition, 1);
		}
		else if(myEvent.key.code == sf::Keyboard::Left && myCurserPosition > 0)
		{
			--myCurserPosition;
		}
		else if(myEvent.key.code == sf::Keyboard::Right && editstr->length() > myCurserPosition)
		{
			++myCurserPosition;
		}
		else if(myEvent.key.code == sf::Keyboard::Up)
		{
			myCurserPosition = 0;
		}
		else if(myEvent.key.code == sf::Keyboard::Down)
		{
			myCurserPosition = editstr->length();
		}	
	}
	else if(myEvent.type == sf::Event::TextEntered && myEvent.text.unicode != 13 && myEvent.text.unicode != 8)
	{
		if(myMenupoint == networklistener::PORT)
		{
			switch(static_cast<char>(myEvent.text.unicode))
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
					myPortString.insert(myCurserPosition, std::size_t(1), static_cast<char>(myEvent.text.unicode));
					++myCurserPosition;
				break;
			}
		}
		else
		{
			editstr->insert(myCurserPosition, std::size_t(1), static_cast<char>(myEvent.text.unicode));
			++myCurserPosition;
		}
	}
}



void GSNetworkListener::StartListening()
{
	std::stringstream sstr(myPortString);
	unsigned short port;
	sstr >> port;
	
	if(myListener.listen(port) == sf::Socket::Done)
	{
		mySocket = new sf::TcpSocket();
		myListener.setBlocking(false);
		myListenerThread.launch();
	}
	else
	{
		myNextState = new GSError(GameState::myWindow, GameState::mySettings, CANNOTLISTENT, "Cannot listen on port " + myPortString + ".");
		myNextStatus = NEXTSTATE;
	}
}


void GSNetworkListener::StopListening()
{
	myListener.close();
	myMenustatus = networklistener::CHOOSE;
	myListenerThread.wait();
	delete mySocket;
	mySocket = NULL;
}



void GSNetworkListener::Listening()
{
	while(myMenustatus == networklistener::LISTENING)
	{
		switch(myListener.accept(*mySocket))
		{
			case sf::Socket::Done:
				Connected();
			break;
			
			default:
			
			break;
		}
		
		sf::sleep(sf::milliseconds(100));
	}
	while(myMenustatus == networklistener::CONNECTED)
	{
		sf::sleep(sf::milliseconds(100));
		
		if(mySocket->getRemoteAddress() == sf::IpAddress::None)
		{
			myGuiMutex.lock();
			myMenustatus = networklistener::CHOOSE;
			delete mySocket;
			mySocket = NULL;
			
			Gui::SetMenupointText(2, "Connection Lost - Start Listening again");
			Gui::SetMenupointText(4, "Main Menu");
			Gui::ActivateMenupoint(0, true);
			Gui::ActivateMenupoint(1, true);
			myGuiMutex.unlock();
		}
	}
}


void GSNetworkListener::Connected()
{
	myGuiMutex.lock();
	myMenustatus = networklistener::CONNECTED;
	myListener.close();
	
	Gui::SetMenupointText(2, "Connected! Start Game with " + mySocket->getRemoteAddress().toString());
	Gui::SetMenupointText(4, "Drop Connection");
	myGuiMutex.unlock();
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
			Gui::SetMenupointText(2, "Is Listening...");
			Gui::SetMenupointText(4, "Stop Listening");
			Gui::ActivateMenupoint(0, false);
			Gui::ActivateMenupoint(1, false);
		break;
		
		case networklistener::CONNECTED:
			myNextState = new GSNetworkGame(GameState::myWindow, GameState::mySettings, mySocket);
			myMenustatus = networklistener::CHOOSE;
			myListenerThread.wait();
			mySocket = NULL;
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
		myNextState = new GSMenu(GameState::myWindow, GameState::mySettings, myResourcemanager);
		myResourcemanager = NULL;
		myNextStatus = NEXTSTATE;
		break;
		
		case networklistener::LISTENING:
		case networklistener::CONNECTED:
			StopListening();
			Gui::SetMenupointText(2, "Start Listening");
			Gui::SetMenupointText(4, "Main Menu");
			Gui::ActivateMenupoint(0, true);
			Gui::ActivateMenupoint(1, true);
			myMenustatus = networklistener::CHOOSE;
		break;
	}
}




