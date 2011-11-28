#ifndef GSNETWORKLISTENER_HPP
#define GSNETWORKLISTENER_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"
#include "GUI.hpp"

#include "Resourcemanager.hpp"

#include <cstddef>
#include <string>


namespace networklistener
{
	enum Menupoint
	{
		NAME,
		PORT,
		LISTEN
	};
	
	enum Status
	{
		CHOOSE,
		EDIT,
		LISTENING,
		CONNECTED
	};
}


class GSNetworkListener : public GameState, public Gui
{
	public:
		GSNetworkListener(sf::RenderWindow& window, Settings& settings, Resourcemanager* resourcemanager);
		~GSNetworkListener();
		
		void OnEnter();
		
		Status Update();
		void Render();
		
		GameState* OnLeave();
		
	private:
		void Apply();
		void Edit();
		
		void StartListening();
		void StopListening();
		
		void Listening();
		
		std::size_t myCurserPosition;
		
		Resourcemanager* myResourcemanager;
		
		Status myNextStatus;
		GameState* myNextState;
		
		sf::Event myEvent;
		
		networklistener::Menupoint myMenupoint;
		networklistener::Status myMenustatus;
		
		std::string myNameString;
		std::string myPortString;
		std::string* editstr;
		
		void Slot1();
		void Slot2();
		void Slot3();
		void Slot4();
		void Slot5();
};


#endif // GSNETWORKLISTENER_HPP


