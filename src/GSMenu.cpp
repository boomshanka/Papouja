#include "GSMenu.hpp"

#include "GSIntro.hpp"
#include "GSSingleplayerGame.hpp"
#include "GSMultiplayerGame.hpp"
#include "GSNetworkListener.hpp"
#include "GSNetworkConnector.hpp"
#include "GSNetworkGame.hpp"
#include "GSSettings.hpp"
#include "GSError.hpp"



GSMenu::GSMenu(sf::RenderWindow& window, Settings& settings) :
GameState(window, settings), myResourcemanager(new Resourcemanager())
{

}


GSMenu::GSMenu(sf::RenderWindow& window, Settings& settings, Resourcemanager* resourcemanager) :
GameState(window, settings), myResourcemanager(resourcemanager)
{

}


GSMenu::~GSMenu()
{
	delete myResourcemanager;
}



void GSMenu::OnEnter()
{
	try
	{
		myBackground.SetTexture(myResourcemanager->Get<sf::Texture>(mySettings.GetSettings("Menu", "Background")));
		
		myNextStatus = CONTINUE;
	}
	catch(FileNotFoundException& ex)
	{
		myNextStatus = NEXTSTATE;
		myNextState = new GSError(myWindow, mySettings, IMPORTANTRESOURCE, ex.what());
	}
}



Status GSMenu::Update()
{
	return myNextStatus;
}


void GSMenu::Render()
{
	myWindow.Draw(myBackground);
}



GameState* GSMenu::OnLeave()
{
	return myNextState;
}



