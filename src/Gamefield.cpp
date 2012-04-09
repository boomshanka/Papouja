#include "Gamefield.hpp"

#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()


int random(int first, int second)
{
	return (std::rand() % (second - first + 1)) + first;
}



Gamefield::Gamefield(Settings& settings, Resourcemanager* resourcemanager) :
mySettings(settings), myResourcemanager(resourcemanager), myStatus(gamefield::WAIT)
{
	myStoneLists.resize(6, std::list<Stone>());
	std::srand(static_cast<unsigned int>(std::time(0) * std::time(0))); // set initial seed value to system clock
}


Gamefield::~Gamefield()
{

}


void Gamefield::LoadResource(sf::Vector2f pos1, sf::Vector2f pos2)
{
	myResourcemanager->Get<sf::Texture>(mySettings.GetSettings("Resource", "Bubbles"));
	
	myOrigin = pos1;
	myTextPosition = pos2;
	
	myMoveStones = NextStones();
	//myNextStones = NextStones();
}


void Gamefield::StartGame()
{
	myStatus = gamefield::MOVE;
}



bool Gamefield::Update()
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
	
	if(myStoneLists[2].size() > 12)
		return false;
	
	return true;
}


void Gamefield::Move(gamefield::Direction direction)
{
	if(myStatus == gamefield::MOVE)
	{
		switch(direction)
		{
			case gamefield::LEFT:
				if(CheckLeftCollision())
					myMoveStones.Move(sf::Vector2i(-1, 0));
			break;
			
			case gamefield::RIGHT:
				if(CheckRightCollision())
					myMoveStones.Move(sf::Vector2i(1, 0));
			break;
			
			case gamefield::DOWN:
				if(CheckBottomCollision())
					myMoveStones.Move(sf::Vector2i(0, 1));
				else if(CheckUpperPositionBottomCollision())
					myMoveStones.StepDown();
			break;
			
			case gamefield::ROTATE:
				if(CheckRotateCollision())
					myMoveStones.Rotate();
				else
				{
					switch(myMoveStones.GetRotation())
					{
						case 0:
							myMoveStones.Move(sf::Vector2i(1, 0));
							if(CheckRotateCollision())
								myMoveStones.Rotate();
							else
								myMoveStones.Move(sf::Vector2i(-1, 0));
						break;
						
						case 2:
							myMoveStones.Move(sf::Vector2i(-1, 0));
							if(CheckRotateCollision())
								myMoveStones.Rotate();
							else
								myMoveStones.Move(sf::Vector2i(1, 0));
						break;
						
						case 1:
							myMoveStones.Move(sf::Vector2i(0, -1));
							if(CheckRotateCollision())
								myMoveStones.Rotate();
							else
								myMoveStones.Move(sf::Vector2i(0, 1));
						break;
					}
				}
			break;
		}
	}
}


void Gamefield::StepDown()
{
	if(CheckUpperPositionBottomCollision())
	{
		myMoveStones.StepDown();
	}
	else
	{
		myStoneLists[myMoveStones.GetFirstStone().GetPosition().x].push_back(myMoveStones.GetFirstStone());
		myStoneLists[myMoveStones.GetSecondStone().GetPosition().x].push_back(myMoveStones.GetSecondStone());
		myMoveStones = NextStones();
	}
}


void Gamefield::Draw(sf::RenderWindow& window)
{
	for(std::size_t i = 0; i < 6; ++i)
	{
		for(std::list<Stone>::iterator it = myStoneLists[i].begin(); it != myStoneLists[i].end(); ++it)
		{
			it->Draw(window);
		}
	}
	
	myMoveStones.GetFirstStone().Draw(window);
	myMoveStones.GetSecondStone().Draw(window);
	
//	myNextStones.GetFirstStone().Draw(window);
//	myNextStones.GetSecondStone().Draw(window);
}



Color Gamefield::GetRandomColor(unsigned int max_colors)
{
	if(max_colors > 6)
		max_colors = 6;
	
	return Color(random(0, static_cast<int>(--max_colors)));
}


const Stonepair Gamefield::NextStones()
{
	sf::Sprite sprite(myResourcemanager->Get<sf::Texture>(mySettings.GetSettings("Resource", "Bubbles")));
	sprite.setScale(mySettings.GetScaleFactor());
	
	return Stonepair(Stone(sf::Vector2i(2, -1), myOrigin, GetRandomColor(), sprite),
					Stone(sf::Vector2i(2, -2), myOrigin, GetRandomColor(), sprite));
}



bool Gamefield::CheckLeftCollision()
{
	if(myMoveStones.GetFirstStone().GetPosition().x == 0 || myMoveStones.GetSecondStone().GetPosition().x == 0 )
			return false;
			
	if(myMoveStones.GetFirstStone().GetPosition().y +  static_cast<int>(myStoneLists[myMoveStones.GetFirstStone().GetPosition().x - 1].size()) > 11)
		return false;
	if(myMoveStones.GetSecondStone().GetPosition().y +  static_cast<int>(myStoneLists[myMoveStones.GetSecondStone().GetPosition().x - 1].size()) > 11)
		return false;
	
	return true;
}


bool Gamefield::CheckRightCollision()
{
	if(myMoveStones.GetFirstStone().GetPosition().x == 5 || myMoveStones.GetSecondStone().GetPosition().x == 5 )
			return false;
	
	if(myMoveStones.GetFirstStone().GetPosition().y +  static_cast<int>(myStoneLists[myMoveStones.GetFirstStone().GetPosition().x + 1].size()) > 11)
		return false;
	if(myMoveStones.GetSecondStone().GetPosition().y +  static_cast<int>(myStoneLists[myMoveStones.GetSecondStone().GetPosition().x + 1].size()) > 11)
		return false;
	
	return true;
}


bool Gamefield::CheckUpperPositionBottomCollision()
{
	if(myMoveStones.GetFirstStone().GetUpperPosition().y + static_cast<int>(myStoneLists[myMoveStones.GetFirstStone().GetPosition().x].size()) > 10)
		return false;
	if(myMoveStones.GetSecondStone().GetUpperPosition().y + static_cast<int>(myStoneLists[myMoveStones.GetSecondStone().GetPosition().x].size()) > 10)
		return false;
	
	return true;
}


bool Gamefield::CheckBottomCollision()
{
	if(myMoveStones.GetFirstStone().GetPosition().y + static_cast<int>(myStoneLists[myMoveStones.GetFirstStone().GetPosition().x].size()) > 10)
		return false;
	
	if(myMoveStones.GetSecondStone().GetPosition().y + static_cast<int>(myStoneLists[myMoveStones.GetSecondStone().GetPosition().x].size()) > 10)
		return false;
	
	return true;
}


bool Gamefield::CheckRotateCollision()
{
	myMoveStones.Rotate();
	
	if(myMoveStones.GetSecondStone().GetPosition().x == -1 || myMoveStones.GetSecondStone().GetPosition().x == 6 ||
		myMoveStones.GetFirstStone().GetPosition().x == -1 || myMoveStones.GetFirstStone().GetPosition().x == 6 ||
		myMoveStones.GetSecondStone().GetPosition().y +  static_cast<int>(myStoneLists[myMoveStones.GetSecondStone().GetPosition().x].size()) > 11)
	{
		myMoveStones.ReserveRotate();
		return false;
	}
	
	myMoveStones.ReserveRotate();
	return true;
}



