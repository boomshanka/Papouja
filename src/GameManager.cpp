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
	myWindow.ShowMouseCursor(false);
}


GameManager::~GameManager()
{
	myWindow.Close();
	delete myState;
}



int GameManager::Run()
{
	int returnValue = EXIT_SUCCESS;
	GameState* temp;
	
	if(myWindow.IsOpen() && mySettings.GetVideoMode().IsValid())
		myState = new GSMenu(myWindow, mySettings);
	else
		myState = new GSError(myWindow, mySettings, WRONGWINDOWSETTINGS);
	
	myState->OnEnter();
	
	while(myWindow.IsOpen())
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
				delete myState;
				myState = NULL;
				returnValue = EXIT_SUCCESS;
				myWindow.Close();
			break;
				
			case ABORT:
				myState->OnLeave();
				delete myState;
				myState = NULL;
				returnValue = EXIT_FAILURE;
				myWindow.Close();
			break;
			
		}
	}
	
	return returnValue;
}



