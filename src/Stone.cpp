#include "Stone.hpp"



Stone::Stone(const sf::Vector2i& position, Color color) :
myPosition(position), myHalfstep(false), myColor(color)
{

}


Stone::~Stone()
{

}



void Stone::Move(const sf::Vector2i& movement)
{
	myPosition += movement;
}


bool Stone::HalfStep()
{
	if(myHalfstep)
	{
		myHalfstep = false;
		--myPosition.y;
	}
	else
	{
		myHalfstep = true;
	}
	
	return myHalfstep;
}



