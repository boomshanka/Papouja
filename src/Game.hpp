#ifndef GAME_HPP
#define GAME_HPP

#include "Gamefield.hpp"



class Game
{
	public:
		Game(Gamefield& field1, Gamefield& field2);
		~Game();
		
	private:
		Gamefield& myFirstGamefield;
		Gamefield& mySecondGamefield;
		
};



#endif // GAME_HPP



