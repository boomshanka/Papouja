#ifndef GSINTRO_HPP
#define GSINTRO_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"


class GSIntro : public GameState
{
	public:
		GSIntro(sf::RenderWindow& window);
		~GSIntro();
		
		void OnEnter();
		
		Status Update();
		void Render();
		
		GameState* OnLeave();
		
	private:
		
		
};


#endif // GSINTRO_HPP


