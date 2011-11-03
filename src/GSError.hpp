#ifndef GSERROR_HPP
#define GSERROR_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"


class GSError : public GameState
{
	public:
		GSError(sf::RenderWindow& window);
		~GSError();
		
		void OnEnter();
		
		Status Update();
		void Render();
		
		GameState* OnLeave();
		
	private:
		
		
};


#endif // GSERROR_HPP


