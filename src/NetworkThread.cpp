#include "NetworkThread.hpp"

#include "NetworkProtocoll.hpp"



NetworkThread::NetworkThread(sf::TcpSocket* socket) :
mySocket(socket), myThread(&NetworkThread::Run, this), isPingSended(false), myStatus(CONNECTED)
{
	mySocket->SetBlocking(false);
}



NetworkThread::~NetworkThread()
{
	myStatus = QUIT;
	myThread.Wait();
	
	mySocket->Disconnect();
	delete mySocket;
}



void NetworkThread::Run()
{
	while(ReceiveMessages())
	{
		if(myPacket && !myPacket.EndOfPacket())
		{
			ParseMessages();
			myPacket.Clear();
		}
		
		CheckConnection();
		
		sf::Sleep(sf::Milliseconds(100));
	}
}


void NetworkThread::StartThread()
{
	myThread.Launch();
}


void NetworkThread::StopThread()
{
	myStatus = QUIT;
}



bool NetworkThread::PollMessages(sf::Packet& packet)
{
	myMessageMutex.Lock();
	
	if(myMessages.size() != 0)
	{
		packet = myMessages.top();
		myMessages.pop();
		
		myMessageMutex.Unlock();
		
		return true;
	}
	
	myMessageMutex.Unlock();
	
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
		mySocketMutex.Lock();
	
		switch(mySocket->Send(packet))
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
	
		mySocketMutex.Unlock();
	}
}




bool NetworkThread::ReceiveMessages()
{
	if(!(myStatus == CONNECTED || myStatus == NOTREADY))
	{
		return false;
	}
	
	mySocketMutex.Lock();
	
	switch(mySocket->Receive(myPacket))
	{
		case sf::Socket::Done:
			myStatus = CONNECTED;
			mySocketMutex.Unlock();
			return true;
		
		case sf::Socket::NotReady:
			myStatus = NOTREADY;
			mySocketMutex.Unlock();
			return true;
		
		case sf::Socket::Disconnected:
			myStatus = DISSCONNECTED;
			break;
		
		case sf::Socket::Error:
			myStatus = ERROR;
			break;
	}
	
	mySocketMutex.Unlock();
	
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
			myPacket.Clear();
			myPacket << static_cast<int>(Protocoll::PONG);
			Send(myPacket);
		break;
		
		case Protocoll::PONG:
			//myPing = myPingClock.GetElapsedTime().AsMilliseconds();
			isPingSended = false;
			myClock.Restart();
		break;
		
		case Protocoll::DISCONNECT:
			myStatus = QUIT;
		break;
		
		default:
			myMessageMutex.Lock();
			
			myMessages.push(sf::Packet());
			myMessages.top().Append(myPacket.GetData(), myPacket.GetDataSize());
			
			myMessageMutex.Unlock();
		break;
	}
}




void NetworkThread::CheckConnection()
{
	if(isPingSended)
	{
		if(myClock.GetElapsedTime().AsSeconds() > 10)
		{
			myStatus = PINGTIMEOUT;
		}
	}
	else
	{
		if(myClock.GetElapsedTime().AsSeconds() > 30)
		{
			sf::Packet packet;
			packet << static_cast<int>(Protocoll::PING);
			Send(packet);
			isPingSended = true;
			myClock.Restart();
		}
	}
}




