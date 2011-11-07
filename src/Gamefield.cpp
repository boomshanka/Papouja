#include "Gamefield.hpp"



Gamefield::Gamefield(Settings& settings) :
mySettings(settings), myStatus(gamefield::WAIT)
{

}


Gamefield::~Gamefield()
{

}



void Gamefield::LoadResource()
{

}



gamefield::Gamestatus Gamefield::Update()
{
	switch(myStatus)
	{
		case gamefield::WAIT:
			
			break;
		
		case gamefield::MOVE:
			
			break;
		
		case gamefield::EXPLODE:
			
			break;
		
		case gamefield::FALL:
			
			break;
	}
	
	return gamefield::CONTINUE;
}



void Gamefield::Move(gamefield::Direction direction)
{
	if(myStatus == gamefield::MOVE)
	{
		switch(direction)
		{
			case gamefield::LEFT:
				
			break;
			
			case gamefield::RIGHT:
				
			break;
			
			case gamefield::DOWN:
				
			break;
			
			case gamefield::ROTATE:
				
			break;
		}
	}
}


void Gamefield::StepDown()
{
	if(myStatus == gamefield::MOVE && myMoveStones[0] != NULL)
	{
		if(!myMoveStones[0]->HalfStep() && !myMoveStones[1]->HalfStep())
		{
		
		}
	}
}



void Gamefield::NextStones()
{

}



Color Gamefield::GetRandomColor(unsigned int max_colors)
{
	if(max_colors > 6)
		max_colors = 6;
	
	
}



