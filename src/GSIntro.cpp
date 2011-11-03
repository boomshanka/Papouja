#include "GSIntro.hpp"

#include "GSMenu.hpp"



GSIntro::GSIntro(sf::RenderWindow& window) :
GameState(window)
{

}


GSIntro::~GSIntro()
{

}



void GSIntro::OnEnter()
{

}



Status GSIntro::Update()
{
	return NEXTSTATE;
}


void GSIntro::Render()
{

}



GameState* GSIntro::OnLeave()
{
	return new GSMenu(myWindow);
}


