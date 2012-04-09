#include "HumanPlayer.hpp"

#include "UnicodeToKey.hpp"



HumanPlayer::HumanPlayer(Settings& settings, Resourcemanager* resourcemanager, bool firstplayer) :
Gamefield(settings, resourcemanager)
{
	if(firstplayer)
	{
		myLeftKey = sf::Keyboard::Key(UnicodeToKey(settings.GetSettings("Player1", "Left")[0]));
		myRightKey = sf::Keyboard::Key(UnicodeToKey(settings.GetSettings("Player1", "Right")[0]));
		myDownKey = sf::Keyboard::Key(UnicodeToKey(settings.GetSettings("Player1", "Down")[0]));
		myRotateKey = sf::Keyboard::Key(UnicodeToKey(settings.GetSettings("Player1", "Rotate")[0]));
	}
	else
	{
		myLeftKey = sf::Keyboard::Key(UnicodeToKey(settings.GetSettings("Player2", "Left")[0]));
		myRightKey = sf::Keyboard::Key(UnicodeToKey(settings.GetSettings("Player2", "Right")[0]));
		myDownKey = sf::Keyboard::Key(UnicodeToKey(settings.GetSettings("Player2", "Down")[0]));
		myRotateKey = sf::Keyboard::Key(UnicodeToKey(settings.GetSettings("Player2", "Rotate")[0]));
	}
}


HumanPlayer::~HumanPlayer()
{

}



bool HumanPlayer::Update()
{
	CheckInput();
	
	return Gamefield::Update();
}



void HumanPlayer::CheckInput()
{
	if(sf::Keyboard::IsKeyPressed(myRotateKey))
	{
		if(myRotateClock.GetElapsedTime().AsMilliseconds() > 250 || myRotateReleased) // Rotate
		{
			myRotateClock.Restart();
			Gamefield::Move(gamefield::ROTATE);
		}
		myRotateReleased = false;
	}
	else
	{
		myRotateReleased = true;
	}
	
	if(sf::Keyboard::IsKeyPressed(myDownKey))
	{
		if(myDownClock.GetElapsedTime().AsMilliseconds() > 50 || myDownReleased) // Down
		{
			myDownClock.Restart();
			Gamefield::Move(gamefield::DOWN);
		}
		myDownReleased = false;
	}
	else
	{
		myDownReleased = true;
	}
	
	if(sf::Keyboard::IsKeyPressed(myLeftKey))
	{
		if(mySideClock.GetElapsedTime().AsMilliseconds() > 200 || mySideReleased) // Left
		{
			mySideClock.Restart();
			Gamefield::Move(gamefield::LEFT);
		}
		mySideReleased = false;
	}
	else if(sf::Keyboard::IsKeyPressed(myRightKey))
	{
		if(mySideClock.GetElapsedTime().AsMilliseconds() > 200 || mySideReleased) // Right
		{
			mySideClock.Restart();
			Gamefield::Move(gamefield::RIGHT);
		}
		mySideReleased = false;
	}
	else
	{
		mySideReleased = true;
	}
}



