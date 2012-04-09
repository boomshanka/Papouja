#ifndef HUMANPLAYER_HPP
#define HUMANPLAYER_HPP

#include "Gamefield.hpp"


class HumanPlayer : public Gamefield
{
	public:
		HumanPlayer(Settings& settings, Resourcemanager* resourcemanager, bool firstplayer = true);
		~HumanPlayer();
		
		bool Update();
		
		void CheckInput();
		
		
	private:
		sf::Clock mySideClock;
		sf::Clock myDownClock;
		sf::Clock myRotateClock;
		
		bool mySideReleased;
		bool myDownReleased;
		bool myRotateReleased;
		
		sf::Keyboard::Key myLeftKey;
		sf::Keyboard::Key myRightKey;
		sf::Keyboard::Key myDownKey;
		sf::Keyboard::Key myRotateKey;
};


#endif // HUMANPLAYER_HPP


