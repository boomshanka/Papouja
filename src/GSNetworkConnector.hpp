#ifndef GSNETWORKCONNECTOR_HPP
#define GSNETWORKCONNECTOR_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "GameState.hpp"
#include "GUI.hpp"

#include "Resourcemanager.hpp"


namespace networkconnector
{
	enum Menupoint
	{
		NAME,
		IP,
		PORT,
		CONNECT
	};
	
	enum Status
	{
		CHOOSE,
		EDIT,
		CONNECTED
	};
}


class GSNetworkConnector : public GameState, public Gui
{
	public:
		GSNetworkConnector(sf::RenderWindow& window, Settings& settings, Resourcemanager* resourcemanager);
		~GSNetworkConnector();
		
		void OnEnter();
		
		Status Update();
		void Render();
		
		GameState* OnLeave();
		
	private:
		Resourcemanager* myResourcemanager;
		
		std::string myNameString;
		std::string myIpString;
		std::string myPortString;
		
		std::string* editstr;
		
		Status myNextStatus;
		GameState* myNextState;
		
		std::size_t myCurserPosition;
		
		networkconnector::Menupoint myMenupoint;
		networkconnector::Status myMenustatus;
		
		sf::TcpSocket* mySocket;
		
		sf::Event myEvent;
		
		void Edit();
		void Connect();
		
		void Slot1();
		void Slot2();
		void Slot3();
		void Slot4();
		void Slot5();
};


#endif // GSNETWORKCONNECTOR_HPP


