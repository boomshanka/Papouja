#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <SFML/Window.hpp>
#include <iostream>

#include "iniManager.hpp"


class Settings : public iniManager
{
	public:
		Settings(int argc, char* argv[]);
		~Settings();
		
		void LoadDefaults();
		int ParseArguments();
	
		sf::VideoMode GetVideoMode() const;
		unsigned long GetWindowStyle() const;
		
	private:
		void Help() const;
		void SetResolution(const std::string&);
		void SetDesktopResolution();
	
		int myArgc;
		char** myArgv;
	
	
		std::string WindowStyleClose;
		std::string WindowStyleFullscreen;
		std::string WindowStyleEmulation;
};


#endif // SETTINGS_HPP


