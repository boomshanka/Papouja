#include "GameState.hpp"

#include "GSIntro.hpp"
#include "GSMenu.hpp"
#include "GSSingleplayerGame.hpp"
#include "GSMultiplayerGame.hpp"
#include "GSSettings.hpp"
#include "GSError.hpp"

#include "GameManager.hpp"


GameManager::GameManager(Settings& settings) :
mySettings(settings)
{
	myWindow.Create(mySettings.GetVideoMode(), "Medieval War", mySettings.GetWindowStyle());
	myWindow.EnableVerticalSync(true);
}


GameManager::~GameManager()
{
	myWindow.Close();
}



int GameManager::Run()
{
/*	boost::scoped_ptr<GameState> state(new GSIntro(myWindow));
	
	while(state)
	{
		state.reset(state->Run());
	}
	
	return GameState::GetReturnValue();*/
}



