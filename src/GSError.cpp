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
			txtError.setString("Error while loading resources:");
			txtMessage.setString(myErrorMessage);
			txtSolution.setString("Please execute the program from the right destination.");
			
			std::cerr << "Error while loading media: " << myErrorMessage << "\n";
			std::cerr << "Please execute the program from the right destination.\n";
		break;
		
		case IMPORTANTRESOURCE:
			myNextStatus = ABORT;
			txtError.setString("Error while loading important resources:");
			txtMessage.setString(myErrorMessage);
			txtSolution.setString("Please execute the program from the right destination.");
			
			std::cerr << "Error while loading important media: " << myErrorMessage << "\n";
			std::cerr << "Please execute the program from the right destination.\n";
		break;
		
		case LOSTCONNECTION:
			myNextState = new GSMenu(myWindow, mySettings);
			
			txtError.setString("Error with the network connection:");
			txtMessage.setString(myErrorMessage);
			txtSolution.setString("Please check your network configuration and try again.");
			
			std::cerr << "Error with the network connection: " << myErrorMessage << "\n";
			std::cerr << "Please check your network configuration and try again.\n";
		break;
		
		case CANNOTCONNECT:
			myNextState = new GSMenu(myWindow, mySettings);
			
			txtError.setString("Error while connecting to a server:");
			txtMessage.setString(myErrorMessage);
			txtSolution.setString("Please check the address and the port of the server.");
			
			std::cerr << "Error while connecting to a server: " << myErrorMessage << "\n";
			std::cerr << "Please check the address and the port of the server.\n";
		break;
		
		case CANNOTLISTENT:
			myNextState = new GSMenu(myWindow, mySettings);
			
			txtError.setString("Error while listening to a connection:");
			txtMessage.setString(myErrorMessage);
			txtSolution.setString("Please use another port or check your network configuration.");
			
			std::cerr << "Error while listening to a connection: " << myErrorMessage << "\n";
			std::cerr << "Please use another port and check your network configuration.\n";
		break;
	}
	
	txtError.setColor(sf::Color::Red); txtMessage.setColor(sf::Color::Red); txtSolution.setColor(sf::Color::Red);
	
	txtError.setCharacterSize(myWindow.getSize().x / 25);
	txtMessage.setCharacterSize(myWindow.getSize().x / 25);
	txtSolution.setCharacterSize(myWindow.getSize().x / 30);
	
	txtError.setOrigin(txtError.getLocalBounds().width / 2.f, txtError.getLocalBounds().height / 2.f);
	txtMessage.setOrigin(txtMessage.getLocalBounds().width / 2.f, txtMessage.getLocalBounds().height / 2.f);
	txtSolution.setOrigin(txtSolution.getLocalBounds().width / 2.f, txtSolution.getLocalBounds().height / 2.f);
	
	txtError.setPosition(static_cast<float>(myWindow.getSize().x) / 2.f, static_cast<float>(myWindow.getSize().y) * 0.15f);
	txtMessage.setPosition(static_cast<float>(myWindow.getSize().x) / 2.f, static_cast<float>(myWindow.getSize().y) * 0.25f);
	txtSolution.setPosition(static_cast<float>(myWindow.getSize().x) / 2.f, static_cast<float>(myWindow.getSize().y) * 0.8f);
}



Status GSError::Update()
{
	if(myContinue)
	{
		while(myWindow.pollEvent(myEvent))
		{
			if(myEvent.type == sf::Event::KeyPressed)
				return myNextStatus;
		
			if(myEvent.type == sf::Event::Closed)
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
	myWindow.draw(txtError);
	myWindow.draw(txtMessage);
	myWindow.draw(txtSolution);
}



GameState* GSError::OnLeave()
{
	return myNextState;
}


