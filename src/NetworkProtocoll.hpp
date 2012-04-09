#ifndef NETWORKPROTOCOLL_HPP
#define NETWORKPROTOCOLL_HPP


namespace Protocoll
{
	enum Message
	{
		PING = 0,
		PONG = 1,
		READY = 2,
		NAME = 3,
		MESSAGE = 4,
		DISCONNECT = 5,
		NETWORKPLAYER = 6,
		GAMEFIELD = 7
	};
}

#endif


