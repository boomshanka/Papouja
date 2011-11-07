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
		LOOSE
	};
}


class Gamefield
{
	public:
		Gamefield(Settings& settings);
		~Gamefield();
		
		void LoadResource();
		
		gamefield::Gamestatus Update();
		
		void Move(gamefield::Direction direction);
		void StepDown();
		
		void NextStones();
		
		void Draw(sf::RenderWindow& window);
		
	private:
		Settings& mySettings;
		
		gamefield::Status myStatus;
		
		Stone* myStones[8][16];
		
		Stone* myMoveStones[2];
		Stone* myNextStones[2];
		
		
		Color GetRandomColor(unsigned int max_colors = 5);
};


#endif // GAMEFIELD_HPP


