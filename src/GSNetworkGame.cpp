#include "GSNetworkGame.hpp"

#include "GSMenu.hpp"
#include "GSError.hpp"

#include "NetworkProtocoll.hpp"



GSNetworkGame::GSNetworkGame(sf::RenderWindow& window, Settings& settings, sf::TcpSocket* socket) :
GameState(window, settings), myNextStatus(CONTINUE), myNextState(NULL), myGameStatus(network::GAME), myResourcemanager(new Resourcemanager()),
myNetworkThread(socket), myChat(sf::Vector2f(static_cast<float>(window.GetHeight()), static_cast<float>(window.GetWidth()))),
myHumanPlayer(mySettings, myResourcemanager), myNetworkPlayer(mySettings, myResourcemanager),
myGame(myHumanPlayer, myNetworkPlayer, mySettings, myResourcemanager)
{

}


GSNetworkGame::~GSNetworkGame()
{
	myNetworkThread.StopThread();
	delete myResourcemanager;
}



void GSNetworkGame::OnEnter()
{
	try
	{
		myGame.LoadResources(sf::Vector2i(myWindow.GetWidth(), myWindow.GetHeight()));
		
		myNetworkThread.StartThread();
	}
	catch(FileNotFoundException& ex)
	{
		myNextStatus = NEXTSTATE;
		myNextState = new GSError(GameState::myWindow, GameState::mySettings, IMPORTANTRESOURCE, ex.what());
	}
	
	//Test
	myGame.Start();
}



Status GSNetworkGame::Update()
{
	while(GameState::myWindow.PollEvent(myEvent))
	{
		if(myGameStatus == network::CHAT)
		{
			myChat.Edit(myEvent);
		}
		else
		{
			//myHumanPlayer.CheckInput(myEvent);
		}
		
		if(myEvent.Type == sf::Event::Closed)
		{
			myNextStatus = QUIT;
		}
		else if(myEvent.Type == sf::Event::KeyPressed)
		{
			if(myEvent.Key.Code == sf::Keyboard::Escape)
			{
				switch(myGameStatus)
				{
					case network::QUIT:
					{
						sf::Packet packet; packet << Protocoll::DISCONNECT; myNetworkThread.Send(packet);
						myNextState = new GSMenu(myWindow, mySettings);
						myNextStatus = NEXTSTATE;
					}
					break;
					
					case network::CHAT:
						myGameStatus = network::GAME;
						myChat.ClearEditedMessage();
					break;
					
					case network::GAME:
						myGameStatus = network::QUIT;
						myEscapeClock.Restart();
					break;
				}
			}
			else if(myGameStatus == network::QUIT)
			{
				myGameStatus = network::GAME;
			}
			
			if(myEvent.Key.Code == sf::Keyboard::Return)
			{
				if(myGameStatus == network::CHAT)
				{
					sf::Packet packet;
					packet << Protocoll::MESSAGE;
					packet << myChat.GetEditedMessage();
					myNetworkThread.Send(packet);
					myChat.AddEditedMessage("Me");
					myGameStatus = network::GAME;
				}
				else
				{
					myGameStatus = network::CHAT;
				}
			}
		}
	}
	
	if(!myGame.Update())
	{
		
	}
	
	ParseMessages();
	CheckNetworkStatus();
	
	
	if(myGameStatus == network::QUIT && myEscapeClock.GetElapsedTime().AsMilliseconds() > 500)
	{
		myGameStatus = network::GAME;
	}
	
	
	return myNextStatus;
}


void GSNetworkGame::Render()
{
	myGame.Draw(myWindow);
	myChat.Draw(myWindow);
}



GameState* GSNetworkGame::OnLeave()
{
	return myNextState;
}



void GSNetworkGame::ParseMessages()
{
	sf::Packet packet;
	int message;
	std::string contents;
	
	while(myNetworkThread.PollMessages(packet))
	{
		packet >> message;
		
		switch(message)
		{
			case Protocoll::READY:
				
				break;
			
			case Protocoll::NAME:
				
				break;
				
			case Protocoll::MESSAGE:
				packet >> contents;
				myChat.AddMessage(contents);
				packet.Clear();
				break;
				
			case Protocoll::NETWORKPLAYER:
				
				break;
			
			case Protocoll::GAMEFIELD:
			
				break;
			
			default:
				break;
		}
	}
}


void GSNetworkGame::CheckNetworkStatus()
{
	switch(myNetworkThread.CheckStatus())
	{
		case NetworkThread::CONNECTED:
			break;
		
		case NetworkThread::NOTREADY:
			break;
			
		case NetworkThread::DISSCONNECTED:
			delete myNextState; myNextState = new GSError(myWindow, mySettings, LOSTCONNECTION, "Client closed connection.");
			myNextStatus = NEXTSTATE;
			break;
			
		case NetworkThread::ERROR:
			delete myNextState; myNextState = new GSError(myWindow, mySettings, LOSTCONNECTION, "Error with the connection.");
			myNextStatus = NEXTSTATE;
			break;
			
		case NetworkThread::PINGTIMEOUT:
			delete myNextState; myNextState = new GSError(myWindow, mySettings, LOSTCONNECTION, "Ping timeout.");
			myNextStatus = NEXTSTATE;
			break;
			
		case NetworkThread::QUIT:
			//FIXME 
			break;
	}
}




