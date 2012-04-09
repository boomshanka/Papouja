#ifndef NETWORKPLAYER_HPP
#define NETWORKPLAYER_HPP

#include "Gamefield.hpp"


class NetworkPlayer : public Gamefield
{
	public:
		NetworkPlayer(Settings& settings, Resourcemanager* resourcemanager);
		~NetworkPlayer();
		
	private:
		
};


#endif // NETWORKPLAYER_HPP



