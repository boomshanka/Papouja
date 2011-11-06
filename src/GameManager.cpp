#include "GameManager.hpp"

#include "GSIntro.hpp"
#include "GSMenu.hpp"
#include "GSSingleplayerGame.hpp"
#include "GSMultiplayerGame.hpp"
#include "GSNetworkGame.hpp"
#include "GSSettings.hpp"
#include "GSError.hpp"



GameManager::GameManager(Settings& settings) :
mySettings(settings)
{
	myWindow.Create(mySettings.GetVideoMode(), "Papouja", mySettings.GetWindowStyle());
	myWindow.EnableVerticalSync(true);
}


GameManager::~GameManager()
{
	myWindow.Close();
}



int GameManager::Run()
{
	int returnValue = EXIT_SUCCESS;
	GameState* temp;
	
	if(myWindow.IsOpened() && mySettings.GetVideoMode().IsValid())
		myState = new GSSingleplayerGame(myWindow, mySettings);//new GSIntro(myWindow, mySettings);
	else
		myState = new GSError(myWindow, mySettings, WRONGWINDOWSETTINGS);
	
	myState->OnEnter();
	
	while(myWindow.IsOpened())
	{
		switch(myState->Update())
		{
			case CONTINUE:
				myWindow.Clear();
				myState->Render();
				myWindow.Display();
			break;
			
			case NEXTSTATE:
				temp = myState->OnLeave();
				delete myState;
				myState = temp;
				temp = NULL;
				myState->OnEnter();
			break;
				
			case QUIT:
				myState->OnLeave();
				myState = NULL;
				returnValue = EXIT_SUCCESS;
				myWindow.Close();
			break;
				
			case ABORT:
				myState->OnLeave();
				myState = NULL;
				returnValue = EXIT_FAILURE;
				myWindow.Close();
			break;
			
		}
	}
	
	return returnValue;
}



