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
	myWindow.create(mySettings.GetVideoMode(), "Papouja", mySettings.GetWindowStyle());
	myWindow.setVerticalSyncEnabled(true);
	myWindow.setMouseCursorVisible(false);
}


GameManager::~GameManager()
{
	myWindow.close();
}



int GameManager::Run()
{
	int returnValue = EXIT_SUCCESS;
	GameState* temp;
	
	if(myWindow.isOpen() && mySettings.GetVideoMode().isValid())
		myState = new GSMenu(myWindow, mySettings);
	else
		myState = new GSError(myWindow, mySettings, WRONGWINDOWSETTINGS);
	
	myState->OnEnter();
	
	while(myWindow.isOpen())
	{
		switch(myState->Update())
		{
			case CONTINUE:
				myWindow.clear();
				myState->Render();
				myWindow.display();
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
				myWindow.close();
			break;
				
			case ABORT:
				myState->OnLeave();
				myState = NULL;
				returnValue = EXIT_FAILURE;
				myWindow.close();
			break;
			
		}
	}
	
	return returnValue;
}



