#include "GSNetworkGame.hpp"

#include "GSMenu.hpp"
#include "GSError.hpp"

#include <iostream>


template<typename T>
T Squared(const T& base)
{
	return base * base;
}



GSNetworkGame::GSNetworkGame(sf::RenderWindow& window, Settings& settings, sf::TcpSocket* socket) :
GameState(window, settings), mySocket(socket), myReceiverThread(&GSNetworkGame::Receive, this), myNextStatus(CONTINUE), myNextState(NULL),
myGameStatus(network::GAME), myCurserPosition(0), isPingSended(false), isWaiting(true)
{

}


GSNetworkGame::~GSNetworkGame()
{
	myReceiverThread.Terminate();
	mySocket->Disconnect();
	
	delete mySocket;
}



void GSNetworkGame::OnEnter()
{
	
	myPingClock.Reset();
	myReceiverThread.Launch();
}



Status GSNetworkGame::Update()
{
	while(GameState::myWindow.PollEvent(myEvent))
	{
		if(myGameStatus == network::CHAT)
		{
			Edit();
		}
		else
		{
		
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
						sf::Packet packet; packet << DISCONNECT; Send(packet);
						myNextState = new GSMenu(myWindow, mySettings);
						myNextStatus = NEXTSTATE;
					}
					break;
					
					case network::CHAT:
						myGameStatus = network::GAME;
						myChatString.clear();
					break;
					
					case network::GAME:
						myGameStatus = network::QUIT;
						myEscapeClock.Reset();
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
					packet << MESSAGE;
					packet << myChatString;
					Send(packet);
					AddMessage("Me: " + myChatString);
					myChatString.clear();
					myGameStatus = network::GAME;
					myCurserPosition = 0;
				}
				else
				{
					myGameStatus = network::CHAT;
					myCurserPosition = 0;
				}
			}
		}
	}
	
	CheckConnection(); // Ping
	
	if(myGameStatus == network::QUIT && myEscapeClock.GetElapsedTime() > 500)
	{
		myGameStatus = network::GAME;
	}
	
	UpdateMessages();
	
	return myNextStatus;
}


void GSNetworkGame::Render()
{
	myMessageMutex.Lock();
	for(std::list<std::pair<sf::Text, sf::Clock> >::iterator it = myChatMessages.begin(); it != myChatMessages.end(); ++it)
	{
		myWindow.Draw((*it).first);
	}
	myMessageMutex.Unlock();
	
	if(myGameStatus == network::CHAT)
	{
		sf::Text text("Chat:  " + myChatString);
		text.SetCharacterSize(myWindow.GetWidth() / 50);
		text.SetPosition(static_cast<float>(myWindow.GetWidth()) / 50.f, static_cast<float>(myWindow.GetHeight()) * 0.6f
						+ static_cast<float>(myWindow.GetWidth() / 40));
		text.SetColor(sf::Color::Red);
		myWindow.Draw(text);
	}
}



GameState* GSNetworkGame::OnLeave()
{
	mySocket->SetBlocking(false);
	
	return myNextState;
}




void GSNetworkGame::UpdateMessages()
{
	myMessageMutex.Lock();
	for(std::list<std::pair<sf::Text, sf::Clock> >::reverse_iterator it = myChatMessages.rbegin(); it != myChatMessages.rend(); ++it)
	{
		if((*it).second.GetElapsedTime() < 15000)
			break;
		
		sf::Color color = (*it).first.GetColor();
		color.a = static_cast<unsigned char>(-0.1275f * (static_cast<float>((*it).second.GetElapsedTime()) - 17000.f));
		(*it).first.SetColor(color);
	}
	while(myChatMessages.size() > 0 && myChatMessages.back().second.GetElapsedTime() > 17000)
	{
		myChatMessages.pop_back();
	}
	
	if(myMessageClock.GetElapsedTime() < 1000)
	{
		std::size_t i = 1;
		for(std::list<std::pair<sf::Text, sf::Clock> >::iterator it = myChatMessages.begin(); it != myChatMessages.end(); ++it)
		{
			(*it).first.SetPosition(static_cast<float>(myWindow.GetWidth()) / 50.f,
									static_cast<float>(myWindow.GetHeight()) * 0.6f - static_cast<float>(i * myWindow.GetWidth() / 40) + 
									static_cast<float>(myWindow.GetWidth() / 40) *
									Squared(Squared(1.f - static_cast<float>(myMessageClock.GetElapsedTime())/1000.f)));
		
			++i;
		}
	}
	else if(isScrolling)
	{
		std::size_t i = 1;
		for(std::list<std::pair<sf::Text, sf::Clock> >::iterator it = myChatMessages.begin(); it != myChatMessages.end(); ++it)
		{
			(*it).first.SetPosition(static_cast<float>(myWindow.GetWidth()) / 50.f,
									static_cast<float>(myWindow.GetHeight()) * 0.6f - static_cast<float>(i * myWindow.GetWidth() / 40));
		
			++i;
		}
		
		isScrolling = false;
	}
	
	myMessageMutex.Unlock();
}



void GSNetworkGame::CheckConnection()
{
	if(isPingSended)
	{
		if(myPingClock.GetElapsedTime() > 10000)
		{
			myNextStatus = NEXTSTATE;
			myNextState = new GSError(myWindow, mySettings, LOSTCONNECTION, "Ping timeout.");
		}
	}
	else
	{
		if(myPingClock.GetElapsedTime() > 30000)
		{
			sf::Packet packet;
			packet << static_cast<int>(PING);
			Send(packet);
			isPingSended = true;
			myPingClock.Reset();
		}
	}
}



void GSNetworkGame::Edit()
{
	if(myEvent.Type == sf::Event::KeyPressed)
	{
		if(myEvent.Key.Code == sf::Keyboard::Back && myCurserPosition > 0)
		{
			myChatString.erase(--myCurserPosition, 1);
		}
		else if(myEvent.Key.Code == sf::Keyboard::Left && myCurserPosition > 0)
		{
			--myCurserPosition;
		}
		else if(myEvent.Key.Code == sf::Keyboard::Right && myChatString.length() > myCurserPosition)
		{
			++myCurserPosition;
		}
		else if(myEvent.Key.Code == sf::Keyboard::Up)
		{
			myCurserPosition = 0;
		}
		else if(myEvent.Key.Code == sf::Keyboard::Down)
		{
			myCurserPosition = myChatString.length();
		}	
	}
	else if(myEvent.Type == sf::Event::TextEntered && myEvent.Text.Unicode != 13 && myEvent.Text.Unicode != 8)
	{
		myChatString.insert(myCurserPosition, std::size_t(1), static_cast<char>(myEvent.Text.Unicode));
		++myCurserPosition;
	}
}



void GSNetworkGame::Receive()
{
	sf::Packet packet;
	
	while(myNextStatus == CONTINUE)
	{
		switch(mySocket->Receive(packet))
		{
			case sf::Socket::Done:
			break;
			
			case sf::Socket::NotReady:
				myNextStatus = NEXTSTATE;
				myNextState = new GSError(myWindow, mySettings, LOSTCONNECTION, "Connection not ready.");
			break;
			
			case sf::Socket::Disconnected:
				myNextStatus = NEXTSTATE;
				myNextState = new GSError(myWindow, mySettings, LOSTCONNECTION, "Client closed connection.");
			break;
			
			case sf::Socket::Error:
				myNextStatus = NEXTSTATE;
				myNextState = new GSError(myWindow, mySettings, LOSTCONNECTION, "Lost connection.");
			break;
		}
		
		int message;
		std::string temp;
		
		packet >> message;
		
		switch(message)
		{
			case PING:
				packet.Clear();
				packet << static_cast<int>(PONG);
				Send(packet);
			break;
			
			case PONG:
				//myPing = myPingClock.GetElapsedTime();
				isPingSended = false;
				myPingClock.Reset();
			break;
			
			case MESSAGE:
				packet >> temp;
				AddMessage(temp);
			break;
			
			case DISCONNECT:
				AddMessage("Player disconnected!", sf::Color::Red);
				sf::Sleep(3000);
				myNextStatus = NEXTSTATE;
				if(myNextState == NULL)
					myNextState = new GSMenu(myWindow, mySettings);
			break;
			
			default: break;
		}
	}
}



void GSNetworkGame::Send(sf::Packet& packet)
{
	mySenderMutex.Lock();
	
	mySocket->Send(packet);
	
	mySenderMutex.Unlock();
}



void GSNetworkGame::AddMessage(const std::string& message, const sf::Color& color)
{
	myMessageMutex.Lock();
	myChatMessages.push_front(std::make_pair(sf::Text(message), sf::Clock()));
	myChatMessages.front().first.SetCharacterSize(myWindow.GetWidth() / 50);
	myChatMessages.front().first.SetPosition(static_cast<float>(myWindow.GetWidth()) / 50.f, static_cast<float>(myWindow.GetHeight()) * 0.6f);
	myChatMessages.front().first.SetColor(color);
	myChatMessages.front().second.Reset();
	myMessageClock.Reset();
	isScrolling = true;
	myMessageMutex.Unlock();
	
	std::cout << message << "\n";
}



