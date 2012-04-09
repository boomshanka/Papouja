#ifndef STONEPAIR_HPP
#define STONEPAIR_HPP

#include "Stone.hpp"


class Stonepair
{
	public:
		Stonepair() {}
		Stonepair(const Stone& stone1, const Stone& stone2) : myFirstStone(stone1), mySecondStone(stone2), myRotation(0) {}
		
		Stone& GetFirstStone() {return myFirstStone;}
		Stone& GetSecondStone() {return mySecondStone;}
		
		void Move(const sf::Vector2i& dir)
		{
			myFirstStone.Move(dir);
			mySecondStone.Move(dir);
		}
		
		void StepDown()
		{
			myFirstStone.StepDown();
			mySecondStone.StepDown();
		}
		
		void Rotate()
		{
			switch(myRotation)
			{
				case 0:
					++myRotation;
					mySecondStone.Move(sf::Vector2i(-1, 1));
				break;
				
				case 1:
					++myRotation;
					mySecondStone.Move(sf::Vector2i(1, 1));
				break;
				
				case 2:
					++myRotation;
					mySecondStone.Move(sf::Vector2i(1, -1));
				break;
				
				case 3:
					myRotation = 0;
					mySecondStone.Move(sf::Vector2i(-1, -1));
				break;
			}
		}
		
		void ReserveRotate()
		{
			switch(myRotation)
			{
				case 0:
					myRotation = 3;
					mySecondStone.Move(sf::Vector2i(1, 1));
				break;
				
				case 1:
					--myRotation;
					mySecondStone.Move(sf::Vector2i(1, -1));
				break;
				
				case 2:
					--myRotation;
					mySecondStone.Move(sf::Vector2i(-1, -1));
				break;
				
				case 3:
					--myRotation;
					mySecondStone.Move(sf::Vector2i(-1, 1));
				break;
			}
		}
		
		unsigned int GetRotation() {return myRotation;}
		
	private:
		Stone myFirstStone;
		Stone mySecondStone;
		
		unsigned int myRotation;
};


#endif


