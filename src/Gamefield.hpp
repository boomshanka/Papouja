#ifndef GAMEFIELD_HPP
#define GAMEFIELD_HPP

#include <vector>
#include <list>


#include <SFML/Graphics.hpp>

#include "Stone.hpp"
#include "StonePair.hpp"
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
}


class Gamefield
{
	public:
		Gamefield(Settings& settings, Resourcemanager* resourcemanager);
		~Gamefield();
		
		void LoadResource(sf::Vector2f pos1, sf::Vector2f pos2);
		void StartGame();
		
		virtual bool Update();
		
		void Move(gamefield::Direction direction);
		void StepDown();
		
		const Stonepair NextStones();
		
		void Draw(sf::RenderWindow& window);
		
	private:
		Settings& mySettings;
		Resourcemanager* myResourcemanager;
		
		gamefield::Status myStatus;
		
		std::vector<std::list<Stone> > myStoneLists;
		
		sf::Vector2f myOrigin;
		sf::Vector2f myTextPosition;
		
		Stonepair myMoveStones;
		Stonepair myNextStones;
		
		Color GetRandomColor(unsigned int max_colors = 5);
		
		bool CheckBottomCollision();
		bool CheckUpperPositionBottomCollision();
		
		bool CheckRightCollision();
		bool CheckLeftCollision();
		
		bool CheckRotateCollision();
};


#endif // GAMEFIELD_HPP


