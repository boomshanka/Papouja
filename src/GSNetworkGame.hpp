#ifndef GSNETWORKGAME_HPP
#define GSNETWORKGAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "GameState.hpp"

#include <list>
#include <string>
#include <utility>
#include <string>


namespace network
{
	enum Status
	{
		GAME,
		CHAT,
		QUIT
	};
}


class GSNetworkGame : public GameState
{
	public:
		enum Message
		{
			PING = 0,
			PONG = 1,
			READY = 2,
			NAME = 3,
			MESSAGE = 4,
			DISCONNECT = 5
		};
	
	public:
		GSNetworkGame(sf::RenderWindow& window, Settings& settings, sf::TcpSocket* socket);
		~GSNetworkGame();
		
		void OnEnter();
		
		Status Update();
		void Render();
		
		GameState* OnLeave();
		
	private:
		sf::TcpSocket* mySocket;
		
		sf::Thread myReceiverThread;
		
		sf::Event myEvent;
		sf::Mutex mySenderMutex;
		sf::Mutex myMessageMutex;
		sf::Clock myPingClock;
		sf::Clock myMessageClock;
		sf::Clock myEscapeClock;
		
		Status myNextStatus;
		GameState* myNextState;
		
		network::Status myGameStatus;
		
		std::list<std::pair<sf::Text, sf::Clock> > myChatMessages;
		
		std::string myChatString;
		std::size_t myCurserPosition;
		
		bool isPingSended;
		bool isWaiting;
		bool isScrolling;
		
		void UpdateMessages();
		void CheckConnection();
		void Edit();
		
		void Receive();
		void Send(sf::Packet& packet);
		
		void AddMessage(const std::string& message, const sf::Color& color = sf::Color::White);
};


#endif // GSNETWORKGAME_HPP


