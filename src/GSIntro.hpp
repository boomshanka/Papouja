#ifndef GSINTRO_HPP
#define GSINTRO_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"

#include "Resourcemanager.hpp"


class GSIntro : public GameState
{
	public:
		GSIntro(sf::RenderWindow& window, Settings& settings);
		~GSIntro();
		
		void OnEnter();
		
		Status Update();
		void Render();
		
		GameState* OnLeave();
		
	private:
		Resourcemanager* myResourcemanager;
		
};


#endif // GSINTRO_HPP


