#ifndef STONE_HPP
#define STONE_HPP

#include <SFML/System/Vector2.hpp>


enum Color
{
	RED = 0,
	BLUE = 1,
	YELLOW = 2,
	GREEN = 3,
	MAGENTA = 4,
	CYAN = 5
};



class Stone
{
	public:
		Stone(const sf::Vector2i& position, Color color);
		~Stone();
		
		const sf::Vector2i& GetPosition() {return myPosition;}
		Color GetColor() {return myColor;}
		
		void Move(const sf::Vector2i& movement);
		bool HalfStep();
		
	private:
		sf::Vector2i myPosition;
		bool myHalfstep;
		
		Color myColor;
		
};



#endif // STONE_HPP



