#include "Chat.hpp"

#include <iostream>


template<typename T>
T Squared(const T& base)
{
	return base * base;
}



Chat::Chat(const sf::Vector2f& windowsize) :
myCurserPosition(0), myWindowSize(windowsize), isScrolling(false)
{

}


Chat::~Chat()
{

}



void Chat::Update(const sf::Time& time)
{
	for(std::list<std::pair<sf::Text, sf::Clock> >::reverse_iterator it = myChatMessages.rbegin(); it != myChatMessages.rend(); ++it)
	{
		if((*it).second.getElapsedTime().asMilliseconds() < 25000)
			break;
		
		sf::Color color = (*it).first.getColor();
		color.a = static_cast<unsigned char>(-0.1275f * (static_cast<float>((*it).second.getElapsedTime().asMilliseconds()) - 27000.f));
		(*it).first.setColor(color);
	}
	while(myChatMessages.size() > 0 && myChatMessages.back().second.getElapsedTime().asMilliseconds() > 27000)
	{
		myChatMessages.pop_back();
	}
	
	if(myMessageClock.getElapsedTime().asMilliseconds() < 1000)
	{
		std::size_t i = 1;
		for(std::list<std::pair<sf::Text, sf::Clock> >::iterator it = myChatMessages.begin(); it != myChatMessages.end(); ++it)
		{
			(*it).first.setPosition(myWindowSize.x / 50.f, myWindowSize.y * 0.6f - static_cast<float>(i) * myWindowSize.x / 40 +
									 myWindowSize.x / 40 * Squared(Squared(1.f - myMessageClock.getElapsedTime().asSeconds())));
		
			++i;
		}
	}
	else if(isScrolling)
	{
		std::size_t i = 1;
		for(std::list<std::pair<sf::Text, sf::Clock> >::iterator it = myChatMessages.begin(); it != myChatMessages.end(); ++it)
		{
			(*it).first.setPosition(myWindowSize.x / 50.f, myWindowSize.y * 0.6f - static_cast<float>(i) * myWindowSize.x / 40);
		
			++i;
		}
		
		isScrolling = false;
	}
}



void Chat::Edit(const sf::Event& event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::Back && myCurserPosition > 0)
		{
			myChatString.erase(--myCurserPosition, 1);
		}
		else if(event.key.code == sf::Keyboard::Left && myCurserPosition > 0)
		{
			--myCurserPosition;
		}
		else if(event.key.code == sf::Keyboard::Right && myChatString.length() > myCurserPosition)
		{
			++myCurserPosition;
		}
		else if(event.key.code == sf::Keyboard::Up)
		{
			myCurserPosition = 0;
		}
		else if(event.key.code == sf::Keyboard::Down)
		{
			myCurserPosition = myChatString.length();
		}	
	}
	else if(event.type == sf::Event::TextEntered && event.text.unicode != 13 && event.text.unicode != 8)
	{
		myChatString.insert(myCurserPosition, std::size_t(1), static_cast<char>(event.text.unicode));
		++myCurserPosition;
	}
}


void Chat::AddEditedMessage(const std::string& nickname)
{
	myChatMessages.push_front(std::make_pair(sf::Text(nickname + ": " + myChatString), sf::Clock()));
	myChatMessages.front().first.setCharacterSize(static_cast<unsigned int>(myWindowSize.x / 50));
	myChatMessages.front().first.setPosition(myWindowSize.x / 50.f, myWindowSize.y * 0.6f);
	myChatMessages.front().first.setColor(sf::Color::White);
	myChatMessages.front().second.restart();
	myMessageClock.restart();
	isScrolling = true;
	
	std::cout << nickname << ": " << myChatString << std::endl;
	
	myChatString.clear();
	myCurserPosition = 0;
}


void Chat::ClearEditedMessage()
{
	myChatString.clear();
	myCurserPosition = 0;
}


void Chat::AddMessage(const std::string& message, const sf::Color& color)
{
	myChatMessages.push_front(std::make_pair(sf::Text(message), sf::Clock()));
	myChatMessages.front().first.setCharacterSize(static_cast<unsigned int>(myWindowSize.x / 50));
	myChatMessages.front().first.setPosition(myWindowSize.x / 50.f, myWindowSize.y * 0.6f);
	myChatMessages.front().first.setColor(color);
	myChatMessages.front().second.restart();
	myMessageClock.restart();
	
	isScrolling = true;
	
	std::cout << message << std::endl;
}



void Chat::Draw(sf::RenderWindow& window)
{
	for(std::list<std::pair<sf::Text, sf::Clock> >::iterator it = myChatMessages.begin(); it != myChatMessages.end(); ++it)
	{
		window.draw((*it).first);
	}
	
	if(!myChatString.empty())
	{
		sf::Text text("Chat:  " + myChatString);
		text.setCharacterSize(static_cast<unsigned int>(myWindowSize.x / 50));
		text.setPosition(myWindowSize.x / 50.f, myWindowSize.y * 0.6f + myWindowSize.x / 40);
		text.setColor(sf::Color::Red);
		window.draw(text);
	}
}



