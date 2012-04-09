#include "NetworkThread.hpp"

#include "NetworkProtocoll.hpp"



NetworkThread::NetworkThread(sf::TcpSocket* socket) :
mySocket(socket), myThread(&NetworkThread::Run, this), isPingSended(false), myStatus(CONNECTED)
{
	mySocket->setBlocking(false);
}



NetworkThread::~NetworkThread()
{
	myStatus = QUIT;
	myThread.wait();
	
	mySocket->disconnect();
	delete mySocket;
}



void NetworkThread::Run()
{
	while(ReceiveMessages())
	{
		if(myPacket && !myPacket.endOfPacket())
		{
			ParseMessages();
			myPacket.clear();
		}
		
		CheckConnection();
		
		sf::sleep(sf::milliseconds(100));
	}
}


void NetworkThread::StartThread()
{
	myThread.launch();
}


void NetworkThread::StopThread()
{
	myStatus = QUIT;
}



bool NetworkThread::PollMessages(sf::Packet& packet)
{
	myMessageMutex.lock();
	
	if(myMessages.size() != 0)
	{
		packet = myMessages.top();
		myMessages.pop();
		
		myMessageMutex.unlock();
		
		return true;
	}
	
	myMessageMutex.unlock();
	
	return false;
}



NetworkThread::Status NetworkThread::CheckStatus()
{
	return myStatus;
}



void NetworkThread::Send(sf::Packet& packet)
{
	if(myStatus == CONNECTED || myStatus == NOTREADY)
	{
		mySocketMutex.lock();
	
		switch(mySocket->send(packet))
		{
			case sf::Socket::Done:
				myStatus = CONNECTED;
				break;
		
			case sf::Socket::NotReady:
				myStatus = NOTREADY; //FIXME konnte NICHT gesendet werden, senden wiederholen!
				break;
		
			case sf::Socket::Disconnected:
				myStatus = DISSCONNECTED;
				break;
		
			case sf::Socket::Error:
				myStatus = ERROR;
				break;
		}
	
		mySocketMutex.unlock();
	}
}




bool NetworkThread::ReceiveMessages()
{
	if(!(myStatus == CONNECTED || myStatus == NOTREADY))
	{
		return false;
	}
	
	mySocketMutex.lock();
	
	switch(mySocket->receive(myPacket))
	{
		case sf::Socket::Done:
			myStatus = CONNECTED;
			mySocketMutex.unlock();
			return true;
		
		case sf::Socket::NotReady:
			myStatus = NOTREADY;
			mySocketMutex.unlock();
			return true;
		
		case sf::Socket::Disconnected:
			myStatus = DISSCONNECTED;
			break;
		
		case sf::Socket::Error:
			myStatus = ERROR;
			break;
	}
	
	mySocketMutex.unlock();
	
	return false;
}



void NetworkThread::ParseMessages()
{
	int message;
	std::string temp;
	
	myPacket >> message;
	
	switch(message)
	{
		case Protocoll::PING:
			myPacket.clear();
			myPacket << static_cast<int>(Protocoll::PONG);
			Send(myPacket);
		break;
		
		case Protocoll::PONG:
			//myPing = myPingClock.GetElapsedTime().AsMilliseconds();
			isPingSended = false;
			myClock.restart();
		break;
		
		case Protocoll::DISCONNECT:
			myStatus = QUIT;
		break;
		
		default:
			myMessageMutex.lock();
			
			myMessages.push(sf::Packet());
			myMessages.top().append(myPacket.getData(), myPacket.getDataSize());
			
			myMessageMutex.unlock();
		break;
	}
}




void NetworkThread::CheckConnection()
{
	if(isPingSended)
	{
		if(myClock.getElapsedTime().asSeconds() > 10)
		{
			myStatus = PINGTIMEOUT;
		}
	}
	else
	{
		if(myClock.getElapsedTime().asSeconds() > 30)
		{
			sf::Packet packet;
			packet << static_cast<int>(Protocoll::PING);
			Send(packet);
			isPingSended = true;
			myClock.restart();
		}
	}
}




