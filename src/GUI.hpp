#ifndef GUI_HPP
#define GUI_HPP

#include "Resourcemanager.hpp"
#include "Settings.hpp"

#include <SFML/Graphics.hpp>

#include <cstddef>
#include <string>


class MenuPoint
{
	public:
		MenuPoint();
		~MenuPoint();
		
		void SetText(const std::string& text, unsigned int size);
		void SetFont(const sf::Font& font);
		void SetPosition(const sf::Vector2f& position);
		void Activate(bool activate);
		bool IsActivated();
		
		sf::FloatRect GetRect();
		void Draw(sf::RenderWindow& window);
		
	private:
		sf::Text myText;
		bool isActive;
		
};


class Gui
{
	public:
		enum GuiStatus
		{
			DISABLED,
			FADEIN,
			ENABLED,
			FADEOUT
		};
		
	public:
		Gui(sf::RenderWindow& window, Settings& settings, Resourcemanager* resourcemanager);
		virtual ~Gui();
		
		void LoadResources();
		
		void ActivateMenupoint(std::size_t number, bool activate);
		
		void SetMenupointText(std::size_t number, const std::string& text);
		
		void CheckEvents(const sf::Event& event);
		void Render();
		
		void FadeIn();
		void FadeOut();
		
		GuiStatus GetGuiStatus();
		bool IsEnabled();
		
	private:
		sf::RenderWindow& myWindow;
		Settings& mySettings;
		Resourcemanager* myResourcemanager;
		
		std::size_t myMenuPosition;
		sf::Clock myClock;
		
		MenuPoint myMenuPoints[5];
		
		Gui::GuiStatus myGuiStatus;
		
	protected:
		virtual void Slot1() = 0;
		virtual void Slot2() = 0;
		virtual void Slot3() = 0;
		virtual void Slot4() = 0;
		
		virtual void Slot5() = 0; // Back/Quit
};


#endif // GUI_HPP



