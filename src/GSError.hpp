#ifndef GSERROR_HPP
#define GSERROR_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"


enum ErrorCode
{
	WRONGWINDOWSETTINGS,
	RESOURCE,
	IMPORTANTRESOURCE,
	LOSTCONNECTION,
	CANNOTCONNECT,
	CANNOTLISTENT
};


class GSError : public GameState
{
	public:
		GSError(sf::RenderWindow& window, Settings& settings, ErrorCode code, const std::string& message = "");
		~GSError();
		
		void OnEnter();
		
		Status Update();
		void Render();
		
		GameState* OnLeave();
		
	private:
		ErrorCode myErrorCode;
		std::string myErrorMessage;
		
		Status myNextStatus;
		GameState* myNextState;
		
		sf::Event myEvent;
		
		sf::Text txtError;
		sf::Text txtMessage;
		sf::Text txtSolution;
		
		bool myContinue;
};


#endif // GSERROR_HPP


