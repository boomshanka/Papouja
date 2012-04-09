#ifndef STONE_HPP
#define STONE_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>


enum Color
{
	RED = 0,
	BLUE = 1,
	YELLOW = 2,
	GREEN = 3,
	CYAN = 4,
	MAGENTA = 5,
	BLACK = 6
};



class Stone
{
	public:
		Stone() {}
		Stone(const sf::Vector2i& position, const sf::Vector2f& origin, Color color, const sf::Sprite& sprite);
		~Stone();
		
		sf::Vector2i GetPosition();
		sf::Vector2i GetUpperPosition();
		Color GetColor() {return myColor;}
		
		void Move(const sf::Vector2i& movement);
		void StepDown();
		
		void Draw(sf::RenderWindow& window);
		
	private:
		sf::Sprite mySprite;
		
		sf::Vector2i myPosition;
		sf::Vector2f myOrigin;
		
		sf::Vector2f mySpriteSize;
		Color myColor;
		
		void UpdateSpritePosition();
};



#endif // STONE_HPP



