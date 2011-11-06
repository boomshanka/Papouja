#ifndef GAMEFIELD_HPP
#define GAMEFIELD_HPP

#include <SFML/Graphics.hpp>

#include "Stone.hpp"
#include "Settings.hpp"
#include "Resourcemanager.hpp"


namespace gamefield
{
	enum Status
	{
		WAIT,
		MOVE,
		EXPLODE,
		FALL
	};
	
	enum Direction
	{
		LEFT,
		RIGHT,
		DOWN,
		ROTATE
	};
	
	enum Gamestatus
	{
		CONTINUE,
		PLAYER1WIN,
		PLAYER2WIN
	};
}


class Gamefield
{
	public:
		Gamefield(Settings& settings);
		~Gamefield();
		
		void LoadResource();
		
		void Move(gamefield::Direction direction);
		
		bool Update();
		void Draw(sf::RenderWindow& window);
	private:
		Stone* myStones[8][16];
		
		Settings& mySettings;
};


#endif // GAMEFIELD_HPP


