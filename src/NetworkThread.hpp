#ifndef NETWORKTHREAD_HPP
#define NETWORKTHREAD_HPP

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <stack>



class NetworkThread
{
	public:
		enum Status
		{
			CONNECTED,
			NOTREADY,
			DISSCONNECTED,
			ERROR,
			PINGTIMEOUT,
			QUIT
		};
		
	private:
		sf::TcpSocket* mySocket;
		sf::Thread myThread;
		
		sf::Mutex mySocketMutex;
		sf::Mutex myMessageMutex;
		
		sf::Clock myClock;
		
		bool isPingSended;
		
		sf::Packet myPacket;
		std::stack<sf::Packet> myMessages;
		
		Status myStatus;
		
	public:
		NetworkThread(sf::TcpSocket* socket);
		~NetworkThread();
		
		void Run();
		
		void StartThread();
		void StopThread();
		
		bool PollMessages(sf::Packet& packet);
		Status CheckStatus();
		void Send(sf::Packet& packet);
		
	protected:
		bool ReceiveMessages();
		void ParseMessages();
		void CheckConnection();
};


#endif


