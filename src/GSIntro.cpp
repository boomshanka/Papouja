#include "GSIntro.hpp"

#include "GSMenu.hpp"



GSIntro::GSIntro(sf::RenderWindow& window, Settings& settings) :
GameState(window, settings), myResourcemanager(new Resourcemanager())
{

}


GSIntro::~GSIntro()
{
	delete myResourcemanager;
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
	Resourcemanager* resourcemanager = myResourcemanager;
	myResourcemanager = NULL;
	
	return new GSMenu(myWindow, mySettings, resourcemanager);
}


