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
		if((*it).second.GetElapsedTime().AsMilliseconds() < 25000)
			break;
		
		sf::Color color = (*it).first.GetColor();
		color.a = static_cast<unsigned char>(-0.1275f * (static_cast<float>((*it).second.GetElapsedTime().AsMilliseconds()) - 27000.f));
		(*it).first.SetColor(color);
	}
	while(myChatMessages.size() > 0 && myChatMessages.back().second.GetElapsedTime().AsMilliseconds() > 27000)
	{
		myChatMessages.pop_back();
	}
	
	if(myMessageClock.GetElapsedTime().AsMilliseconds() < 1000)
	{
		std::size_t i = 1;
		for(std::list<std::pair<sf::Text, sf::Clock> >::iterator it = myChatMessages.begin(); it != myChatMessages.end(); ++it)
		{
			(*it).first.SetPosition(myWindowSize.x / 50.f, myWindowSize.y * 0.6f - static_cast<float>(i) * myWindowSize.x / 40 +
									 myWindowSize.x / 40 * Squared(Squared(1.f - myMessageClock.GetElapsedTime().AsSeconds())));
		
			++i;
		}
	}
	else if(isScrolling)
	{
		std::size_t i = 1;
		for(std::list<std::pair<sf::Text, sf::Clock> >::iterator it = myChatMessages.begin(); it != myChatMessages.end(); ++it)
		{
			(*it).first.SetPosition(myWindowSize.x / 50.f, myWindowSize.y * 0.6f - static_cast<float>(i) * myWindowSize.x / 40);
		
			++i;
		}
		
		isScrolling = false;
	}
}



void Chat::Edit(const sf::Event& event)
{
	if(event.Type == sf::Event::KeyPressed)
	{
		if(event.Key.Code == sf::Keyboard::Back && myCurserPosition > 0)
		{
			myChatString.erase(--myCurserPosition, 1);
		}
		else if(event.Key.Code == sf::Keyboard::Left && myCurserPosition > 0)
		{
			--myCurserPosition;
		}
		else if(event.Key.Code == sf::Keyboard::Right && myChatString.length() > myCurserPosition)
		{
			++myCurserPosition;
		}
		else if(event.Key.Code == sf::Keyboard::Up)
		{
			myCurserPosition = 0;
		}
		else if(event.Key.Code == sf::Keyboard::Down)
		{
			myCurserPosition = myChatString.length();
		}	
	}
	else if(event.Type == sf::Event::TextEntered && event.Text.Unicode != 13 && event.Text.Unicode != 8)
	{
		myChatString.insert(myCurserPosition, std::size_t(1), static_cast<char>(event.Text.Unicode));
		++myCurserPosition;
	}
}


void Chat::AddEditedMessage(const std::string& nickname)
{
	myChatMessages.push_front(std::make_pair(sf::Text(nickname + ": " + myChatString), sf::Clock()));
	myChatMessages.front().first.SetCharacterSize(static_cast<unsigned int>(myWindowSize.x / 50));
	myChatMessages.front().first.SetPosition(myWindowSize.x / 50.f, myWindowSize.y * 0.6f);
	myChatMessages.front().first.SetColor(sf::Color::White);
	myChatMessages.front().second.Restart();
	myMessageClock.Restart();
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
	myChatMessages.front().first.SetCharacterSize(static_cast<unsigned int>(myWindowSize.x / 50));
	myChatMessages.front().first.SetPosition(myWindowSize.x / 50.f, myWindowSize.y * 0.6f);
	myChatMessages.front().first.SetColor(color);
	myChatMessages.front().second.Restart();
	myMessageClock.Restart();
	
	isScrolling = true;
	
	std::cout << message << std::endl;
}



void Chat::Draw(sf::RenderWindow& window)
{
	for(std::list<std::pair<sf::Text, sf::Clock> >::iterator it = myChatMessages.begin(); it != myChatMessages.end(); ++it)
	{
		window.Draw((*it).first);
	}
	
	if(!myChatString.empty())
	{
		sf::Text text("Chat:  " + myChatString);
		text.SetCharacterSize(static_cast<unsigned int>(myWindowSize.x / 50));
		text.SetPosition(myWindowSize.x / 50.f, myWindowSize.y * 0.6f + myWindowSize.x / 40);
		text.SetColor(sf::Color::Red);
		window.Draw(text);
	}
}



