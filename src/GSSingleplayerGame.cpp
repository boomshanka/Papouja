#include "GSSingleplayerGame.hpp"

#include "GSMenu.hpp"
#include "GSError.hpp"



GSSingleplayerGame::GSSingleplayerGame(sf::RenderWindow& window, Settings& settings) :
GameState(window, settings), myHumanPlayer(settings), myComputerPlayer(settings), myGame(myHumanPlayer, myComputerPlayer)
{

}


GSSingleplayerGame::~GSSingleplayerGame()
{

}



void GSSingleplayerGame::OnEnter()
{

}



Status GSSingleplayerGame::Update()
{

}


void GSSingleplayerGame::Render()
{

}



GameState* GSSingleplayerGame::OnLeave()
{

}


