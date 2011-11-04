#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>

#include "Settings.hpp"


enum Status
{
	CONTINUE,
	NEXTSTATE,
	QUIT,
	ABORT
};
	

class GameState
{
	public:
		GameState(sf::RenderWindow& window, Settings& settings) : myWindow(window), mySettings(settings) {}
		virtual ~GameState() {}
		
		virtual void OnEnter() = 0;
		
		virtual Status Update() = 0;
		virtual void Render() = 0;
		
		virtual GameState* OnLeave() = 0;
		
	protected:
		sf::RenderWindow& myWindow;
		Settings& mySettings;
		
	private:
		
		
};


#endif // GAMESTATE_HPP


