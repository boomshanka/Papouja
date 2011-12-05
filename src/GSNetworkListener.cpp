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
	myGuiMutex.Lock();
	Gui::Render();
	myGuiMutex.Unlock();
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
	std::stringstream sstr(myPortString);
	unsigned short port;
	sstr >> port;
	
	if(myListener.Listen(port) == sf::Socket::Done)
	{
		mySocket = new sf::TcpSocket();
		myListener.SetBlocking(false);
		myListenerThread.Launch();
	}
	else
	{
		myNextState = new GSError(GameState::myWindow, GameState::mySettings, CANNOTLISTENT, "Cannot listen on port " + myPortString + ".");
		myNextStatus = NEXTSTATE;
	}
}


void GSNetworkListener::StopListening()
{
	myListener.Close();
	myMenustatus = networklistener::CHOOSE;
	myListenerThread.Wait();
	delete mySocket;
	mySocket = NULL;
}



void GSNetworkListener::Listening()
{
	while(myMenustatus == networklistener::LISTENING)
	{
		switch(myListener.Accept(*mySocket))
		{
			case sf::Socket::Done:
				Connected();
			break;
			
			default:
			
			break;
		}
		
		sf::Sleep(100);
	}
	while(myMenustatus == networklistener::CONNECTED)
	{
		sf::Sleep(100);
		
		if(mySocket->GetRemoteAddress() == sf::IpAddress::None)
		{
			myGuiMutex.Lock();
			myMenustatus = networklistener::CHOOSE;
			delete mySocket;
			mySocket = NULL;
			
			Gui::SetMenupointText(2, "Connection Lost - Start Listening again");
			Gui::SetMenupointText(4, "Main Menu");
			Gui::ActivateMenupoint(0, true);
			Gui::ActivateMenupoint(1, true);
			myGuiMutex.Unlock();
		}
	}
}


void GSNetworkListener::Connected()
{
	myGuiMutex.Lock();
	myMenustatus = networklistener::CONNECTED;
	myListener.Close();
	
	Gui::SetMenupointText(2, "Connected! Start Game with " + mySocket->GetRemoteAddress().ToString());
	Gui::SetMenupointText(4, "Drop Connection");
	myGuiMutex.Unlock();
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
			myListenerThread.Wait();
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




