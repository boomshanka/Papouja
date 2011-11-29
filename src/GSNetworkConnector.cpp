#include "GSNetworkConnector.hpp"

#include "GSNetworkGame.hpp"
#include "GSMenu.hpp"
#include "GSError.hpp"



GSNetworkConnector::GSNetworkConnector(sf::RenderWindow& window, Settings& settings, Resourcemanager* resourcemanager) :
GameState(window, settings), Gui(window, settings, resourcemanager), myResourcemanager(resourcemanager)
{

}


GSNetworkConnector::~GSNetworkConnector()
{

}



void GSNetworkConnector::OnEnter()
{
	//try
	{
		Gui::LoadResources();
	}
	
	myNameString = GameState::mySettings.GetSettings("Game", "Name");
	myIpString = GameState::mySettings.GetSettings("Game", "Ip");
	myPortString = GameState::mySettings.GetSettings("Game", "Port");
	
	Gui::SetMenupointText(0, "Name: " + myNameString);
	Gui::SetMenupointText(1, "Ip: " + myIpString);
	Gui::SetMenupointText(2, "Port:" + myPortString);
	Gui::SetMenupointText(3, "Connect");
	Gui::SetMenupointText(4, "Main Menu");
	
	myNextStatus = CONTINUE;
	Gui::FadeIn();
}



Status GSNetworkConnector::Update()
{
	return myNextStatus;
}


void GSNetworkConnector::Render()
{
	Gui::Render();
}



GameState* GSNetworkConnector::OnLeave()
{
	return myNextState;
}



void GSNetworkConnector::Connect()
{
	std::stringstream sstr(myPortString);
	unsigned short port;
	sstr >> port;
	
	mySocket = new sf::TcpSocket();
	
	switch(mySocket->Connect(sf::IpAddress(myIpString), port, 3000))
	{
		case sf::Socket::Done:
			
		break;
		
		default:
			
		break;
	}
}



void GSNetworkConnector::Slot1()
{
	myMenustatus = networkconnector::EDIT;
	myCurserPosition = myNameString.length();
	editstr = &myNameString;
	myMenupoint = networkconnector::NAME;
}


void GSNetworkConnector::Slot2()
{
	myMenustatus = networkconnector::EDIT;
	myCurserPosition = myPortString.length();
	editstr = &myIpString;
	myMenupoint = networkconnector::IP;
}


void GSNetworkConnector::Slot3()
{
	myMenustatus = networkconnector::EDIT;
	myCurserPosition = myPortString.length();
	editstr = &myPortString;
	myMenupoint = networkconnector::PORT;
}


void GSNetworkConnector::Slot4()
{

}


void GSNetworkConnector::Slot5()
{
/*	switch(myMenustatus)
	{
		case networklistener::CHOOSE:
		myNextState = new GSMenu(GameState::myWindow, GameState::mySettings, myResourcemanager);	
		myNextStatus = NEXTSTATE;
		break;
		
		case networklistener::LISTENING:
			StopListening();
			Gui::SetMenupointText(2, "Start Listening");
			Gui::SetMenupointText(4, "Main Menu");
			Gui::ActivateMenupoint(0, true);
			Gui::ActivateMenupoint(1, true);
			myMenustatus = networklistener::CHOOSE;
		break;
		
		case networklistener::CONNECTED:
			myNextState = new GSMenu(GameState::myWindow, GameState::mySettings, myResourcemanager);
			myNextStatus = NEXTSTATE;
		break;
		
		default: break;
	}*/
}



