#include "GUI.hpp"


MenuPoint::MenuPoint() :
isActive(true)
{

}


MenuPoint::~MenuPoint()
{

}



void MenuPoint::SetText(const std::string& text, unsigned int size)
{
	myText.SetString(text);
	myText.SetCharacterSize(size);
	myText.SetOrigin(myText.GetRect().Width / 2.f, myText.GetRect().Height / 2.f);
}


void MenuPoint::SetFont(const sf::Font& font)
{
	myText.SetFont(font);
	myText.SetOrigin(myText.GetRect().Width / 2.f, myText.GetRect().Height / 2.f);
}


void MenuPoint::SetPosition(const sf::Vector2f& position)
{
	myText.SetPosition(position);
}


void MenuPoint::Activate(bool activate)
{
	isActive = activate;
}


bool MenuPoint::IsActivated()
{
	return isActive;
}



sf::FloatRect MenuPoint::GetRect()
{
	return myText.GetRect();
}


void MenuPoint::Draw(sf::RenderWindow& window)
{
	window.Draw(myText);
}



void MenuPoint::Select()
{
	myText.SetColor(sf::Color::Red);
}


void MenuPoint::Deselect()
{
	myText.SetColor(sf::Color::White);
}


//  --  //


Gui::Gui(sf::RenderWindow& window, Settings& settings, Resourcemanager* resourcemanager) :
myWindow(window), mySettings(settings), myResourcemanager(resourcemanager), myMenuPosition(0), myGuiStatus(Gui::DISABLED)
{

}


Gui::~Gui()
{

}


void Gui::LoadResources()
{
	
	myMenuPoints[myMenuPosition].Select();
}



void Gui::ActivateMenupoint(std::size_t number, bool activate)
{
	myMenuPoints[number].Activate(activate);
}



void Gui::SetMenupointText(std::size_t number, const std::string& text)
{
	myMenuPoints[number].SetText(text, myWindow.GetWidth() / 25);
	
	float factor = static_cast<float>(number) * 0.15f + 0.1f;
	if(number == 4) factor = 0.8f;
	
	myMenuPoints[number].SetPosition(sf::Vector2f(
									static_cast<float>(myWindow.GetWidth()) / 2.f, factor * static_cast<float>(myWindow.GetHeight())));
}



void Gui::CheckEvents(const sf::Event& event)
{
	if(myGuiStatus != Gui::DISABLED && event.Type == sf::Event::KeyPressed)
	{
		switch(event.Key.Code)
		{
			case sf::Keyboard::Up:
			myMenuPoints[myMenuPosition].Deselect();
			while(true)
			{
				if(myMenuPosition == 0)
				{
					myMenuPosition = 4;
				}
				else
				{
					--myMenuPosition;
				}
				if(myMenuPoints[myMenuPosition].IsActivated()) break;
			}
			myMenuPoints[myMenuPosition].Select();
			break;
			
			case sf::Keyboard::Down:
			myMenuPoints[myMenuPosition].Deselect();
			while(true)
			{
				if(myMenuPosition == 4)
				{
					myMenuPosition = 0;
				}
				else
				{
					++myMenuPosition;
				}
				if(myMenuPoints[myMenuPosition].IsActivated()) break;
			}
			myMenuPoints[myMenuPosition].Select();
			break;
			
			case sf::Keyboard::Return:
			switch(myMenuPosition)
			{
				case 0:
					if(myMenuPoints[0].IsActivated()) Slot1();
				break;
				
				case 1:
					if(myMenuPoints[1].IsActivated()) Slot2();
				break;
				
				case 2:
					if(myMenuPoints[2].IsActivated()) Slot3();
				break;
				
				case 3:
					if(myMenuPoints[3].IsActivated()) Slot4();
				break;
				
				case 4:
					if(myMenuPoints[4].IsActivated()) Slot5();
				break;
			}
			break;
			
			default: break;
		}
	}
}


void Gui::Render()
{
	if(myGuiStatus != Gui::DISABLED)
	{
		for(std::size_t i = 0; i < 5; ++i)
		{
			myMenuPoints[i].Draw(myWindow);
		}
	}
}



void Gui::FadeIn()
{
	myGuiStatus = Gui::FADEIN;
	myClock.Reset();
	myMenuPosition = 0;
}


void Gui::FadeOut()
{
	myGuiStatus = Gui::FADEOUT;
	myClock.Reset();
}



Gui::GuiStatus Gui::GetGuiStatus()
{
	return myGuiStatus;
}


bool Gui::IsEnabled()
{
	return (myGuiStatus == Gui::FADEIN || myGuiStatus == Gui::ENABLED);
}



