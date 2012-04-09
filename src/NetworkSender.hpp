#ifndef NETWORKSENDER_HPP
#define NETWORKSENDER_HPP

#include "HumanPlayer.hpp"


class NetworkSender : public HumanPlayer
{
	public:
		NetworkSender(Settings& settings, Resourcemanager* resourcemanager);
		~NetworkSender();
		
	private:
		
};


#endif // NETWORKSENDER_HPP


