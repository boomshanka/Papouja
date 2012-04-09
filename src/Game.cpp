#include "Game.hpp"


sf::Vector2f scalefactor(const sf::Vector2i& windowsize)
{return sf::Vector2f(static_cast<float>(windowsize.x) / 1600.f, static_cast<float>(windowsize.y) / 1200.f);}



Game::Game(Gamefield& field1, Gamefield& field2, Settings& settings, Resourcemanager* resourcemanager) :
myFirstGamefield(field1), mySecondGamefield(field2), mySettings(settings), myResourcemanager(resourcemanager), isGameStarted(false)
{

}


Game::~Game()
{

}



void Game::LoadResources(const sf::Vector2i& windowsize)
{
	myBackgroundSprite.setTexture(myResourcemanager->Get<sf::Texture>(mySettings.GetSettings("Resource", "GameBackground")));
	
	myBackgroundSprite.setScale(scalefactor(windowsize));
	
	myFirstGamefield.LoadResource(sf::Vector2f(900 * scalefactor(windowsize).x, 200 * scalefactor(windowsize).y), sf::Vector2f(0, 0));
	mySecondGamefield.LoadResource(sf::Vector2f(100 * scalefactor(windowsize).x, 200 * scalefactor(windowsize).y), sf::Vector2f(0, 0));
}


void Game::Start()
{
	myFirstGamefield.StartGame();
	mySecondGamefield.StartGame();
	
	isGameStarted = true;
}



bool Game::Update()
{
	sf::Time time = myClock.getElapsedTime();
	myClock.restart();
	
	if(isGameStarted)
	{
		if(myStepClock.getElapsedTime().asMilliseconds() > 500)
		{
			myStepClock.restart();
			myFirstGamefield.StepDown();
			mySecondGamefield.StepDown();
		}
	
		if(!myFirstGamefield.Update())
		{
			return false;
		}
		else if(!mySecondGamefield.Update())
		{
			return false;
		}
	}
	
	return true;
}


void Game::Draw(sf::RenderWindow& window)
{
	window.draw(myBackgroundSprite);
	
	myFirstGamefield.Draw(window);
	mySecondGamefield.Draw(window);
}



