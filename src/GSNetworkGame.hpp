#ifndef GSNETWORKGAME_HPP
#define GSNETWORKGAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "GameState.hpp"
#include "Game.hpp"
#include "HumanPlayer.hpp"
#include "NetworkPlayer.hpp"

#include "Chat.hpp"
#include "NetworkThread.hpp"
#include "Resourcemanager.hpp"



namespace network
{
	enum Status
	{
		GAME,
		CHAT,
		QUIT
	};
}


class GSNetworkGame : public GameState
{
	public:
		GSNetworkGame(sf::RenderWindow& window, Settings& settings, sf::TcpSocket* socket);
		~GSNetworkGame();
		
		void OnEnter();
		
		Status Update();
		void Render();
		
		GameState* OnLeave();
		
	protected:
		void ParseMessages();
		void CheckNetworkStatus();
		
	private:
		Status myNextStatus;
		GameState* myNextState;
		network::Status myGameStatus; //FIXME
		
		Resourcemanager* myResourcemanager;
		
		NetworkThread myNetworkThread;
		Chat myChat;
		
		sf::Event myEvent;
		sf::Clock myEscapeClock;
		
		HumanPlayer myHumanPlayer;
		NetworkPlayer myNetworkPlayer;
		
		Game myGame;
};


#endif // GSNETWORKGAME_HPP


