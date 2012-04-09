#ifndef CHAT_HPP
#define CHAT_HPP


#include <SFML/Graphics.hpp>

#include <list>
#include <string>
#include <utility>


class Chat
{
	private:
		std::list<std::pair<sf::Text, sf::Clock> > myChatMessages;
		
		std::string myChatString;
		std::size_t myCurserPosition;
		
		sf::Clock myMessageClock;
		sf::Vector2f myWindowSize;
		
		bool isScrolling;
		
	public:
		Chat(const sf::Vector2f& windowsize);
		~Chat();
		
		void Update(const sf::Time& time);
		void Edit(const sf::Event& event);
		void AddEditedMessage(const std::string& nickname);
		void ClearEditedMessage();
		void AddMessage(const std::string& message, const sf::Color& color = sf::Color::White);
		
		const std::string& GetEditedMessage() {return myChatString;}
		
		void Draw(sf::RenderWindow& window);
};


#endif


