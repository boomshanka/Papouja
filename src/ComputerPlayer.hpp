#ifndef COMPUTERPLAYER_HPP
#define COMPUTERPLAYER_HPP

#include "Gamefield.hpp"


class ComputerPlayer : public Gamefield
{
	public:
		ComputerPlayer(Settings& settings, Resourcemanager* resourcemanager);
		~ComputerPlayer();
		
	private:
		
};



#endif // COMPUTERPLAYER_HPP



