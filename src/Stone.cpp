#include "Stone.hpp"



Stone::Stone(const sf::Vector2i& position, const sf::Vector2f& origin, Color color, const sf::Sprite& sprite) :
mySprite(sprite), myPosition(position), myOrigin(origin), myColor(color)
{
	myPosition.y *= 10;
	mySpriteSize = sf::Vector2f(mySprite.getGlobalBounds().width, mySprite.getGlobalBounds().height);
	
	switch(myColor)
	{
		case RED:
			mySprite.setColor(sf::Color::Red);
		break;
		
		case BLUE:
			mySprite.setColor(sf::Color::Blue);
		break;
		
		case YELLOW:
			mySprite.setColor(sf::Color::Yellow);
		break;
		
		case GREEN:
			mySprite.setColor(sf::Color::Green);
		break;
		
		case CYAN:
			mySprite.setColor(sf::Color::Cyan);
		break;
		
		case MAGENTA:
			mySprite.setColor(sf::Color::Magenta);
		break;
	}
	
	UpdateSpritePosition();
}


Stone::~Stone()
{

}



void Stone::Move(const sf::Vector2i& movement)
{
	myPosition.x += movement.x;
	myPosition.y += movement.y * 10;
	
	UpdateSpritePosition();
}


sf::Vector2i Stone::GetPosition()
{
	sf::Vector2i vec = myPosition;
	if(vec.y > 0) vec.y += 5;
	vec.y /= 10;
	
	return vec;
}


sf::Vector2i Stone::GetUpperPosition()
{
	sf::Vector2i vec = myPosition;
	if(vec.y < 0) vec.y -= 5;
	vec.y /= 10;
	
	return vec;
}


void Stone::StepDown()
{
	myPosition.y += 5;
	
	UpdateSpritePosition();
}


void Stone::Draw(sf::RenderWindow& window)
{
	window.draw(mySprite);
}



void Stone::UpdateSpritePosition()
{
	sf::Vector2f vec = mySpriteSize;
	
	vec.x *= static_cast<float>(myPosition.x);
	vec.y *= 0.1f * static_cast<float>(myPosition.y);
	vec += sf::Vector2f(1, 1);
	
	mySprite.setPosition(myOrigin + vec);
}



