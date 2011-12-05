#include "GSError.hpp"

#include "GSMenu.hpp"

#include <SFML/Window/Event.hpp>

#include <iostream>



GSError::GSError(sf::RenderWindow& window, Settings& settings, ErrorCode code, const std::string& message) :
GameState(window, settings), myErrorCode(code), myErrorMessage(message), myContinue(true)
{

}


GSError::~GSError()
{

}



void GSError::OnEnter()
{
	myNextStatus = NEXTSTATE;
	
	switch(myErrorCode)
	{
		case WRONGWINDOWSETTINGS:
			myNextStatus = ABORT;
			myContinue = false;
			
			std::cerr << "Error while creating the window!" << "\n";
			std::cerr << "The window settings have been reseted.\n";
			
			mySettings.SetSettings("Window", "Width", "800");
			mySettings.SetSettings("Window", "Height", "600");
			mySettings.SetSettings("Window", "Style", "4");
		break;
		
		case RESOURCE:
			myNextState = new GSMenu(myWindow, mySettings);
			txtError.SetString("Error while loading resources:");
			txtMessage.SetString(myErrorMessage);
			txtSolution.SetString("Please execute the program from the right destination.");
			
			std::cerr << "Error while loading media: " << myErrorMessage << "\n";
			std::cerr << "Please execute the program from the right destination.\n";
		break;
		
		case IMPORTANTRESOURCE:
			myNextStatus = ABORT;
			txtError.SetString("Error while loading important resources:");
			txtMessage.SetString(myErrorMessage);
			txtSolution.SetString("Please execute the program from the right destination.");
			
			std::cerr << "Error while loading important media: " << myErrorMessage << "\n";
			std::cerr << "Please execute the program from the right destination.\n";
		break;
		
		case LOSTCONNECTION:
			myNextState = new GSMenu(myWindow, mySettings);
			
			txtError.SetString("Error with the network connection:");
			txtMessage.SetString(myErrorMessage);
			txtSolution.SetString("Please check your network configuration and try again.");
			
			std::cerr << "Error with the network connection: " << myErrorMessage << "\n";
			std::cerr << "Please check your network configuration and try again.\n";
		break;
		
		case CANNOTCONNECT:
			myNextState = new GSMenu(myWindow, mySettings);
			
			txtError.SetString("Error while connecting to a server:");
			txtMessage.SetString(myErrorMessage);
			txtSolution.SetString("Please check the address and the port of the server.");
			
			std::cerr << "Error while connecting to a server: " << myErrorMessage << "\n";
			std::cerr << "Please check the address and the port of the server.\n";
		break;
		
		case CANNOTLISTENT:
			myNextState = new GSMenu(myWindow, mySettings);
			
			txtError.SetString("Error while listening to a connection:");
			txtMessage.SetString(myErrorMessage);
			txtSolution.SetString("Please use another port or check your network configuration.");
			
			std::cerr << "Error while listening to a connection: " << myErrorMessage << "\n";
			std::cerr << "Please use another port and check your network configuration.\n";
		break;
	}
	
	txtError.SetColor(sf::Color::Red); txtMessage.SetColor(sf::Color::Red); txtSolution.SetColor(sf::Color::Red);
	
	txtError.SetCharacterSize(myWindow.GetWidth() / 25);
	txtMessage.SetCharacterSize(myWindow.GetWidth() / 25);
	txtSolution.SetCharacterSize(myWindow.GetWidth() / 30);
	
	txtError.SetOrigin(txtError.GetRect().Width / 2.f, txtError.GetRect().Height / 2.f);
	txtMessage.SetOrigin(txtMessage.GetRect().Width / 2.f, txtMessage.GetRect().Height / 2.f);
	txtSolution.SetOrigin(txtSolution.GetRect().Width / 2.f, txtSolution.GetRect().Height / 2.f);
	
	txtError.SetPosition(static_cast<float>(myWindow.GetWidth()) / 2.f, static_cast<float>(myWindow.GetHeight()) * 0.15f);
	txtMessage.SetPosition(static_cast<float>(myWindow.GetWidth()) / 2.f, static_cast<float>(myWindow.GetHeight()) * 0.25f);
	txtSolution.SetPosition(static_cast<float>(myWindow.GetWidth()) / 2.f, static_cast<float>(myWindow.GetHeight()) * 0.8f);
}



Status GSError::Update()
{
	if(myContinue)
	{
		while(myWindow.PollEvent(myEvent))
		{
			if(myEvent.Type == sf::Event::KeyPressed)
				return myNextStatus;
		
			if(myEvent.Type == sf::Event::Closed)
			{
				if(myNextStatus == ABORT)
					return myNextStatus;
			
				return QUIT;
			}
		}
	
		return CONTINUE;
	}
	
	return ABORT;
}


void GSError::Render()
{
	myWindow.Draw(txtError);
	myWindow.Draw(txtMessage);
	myWindow.Draw(txtSolution);
}



GameState* GSError::OnLeave()
{
	return myNextState;
}


