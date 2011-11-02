#include "Settings.hpp"

#include <sstream>



Settings::Settings(int argc, char* argv[]) :
myArgc(argc), myArgv(argv)
{
	std::stringstream stringstream; stringstream << sf::Style::Close;
	WindowStyleClose = stringstream.str();
	stringstream.clear(); stringstream << sf::Style::Fullscreen;
	WindowStyleFullscreen = stringstream.str();
	WindowStyleEmulation = "0";
	
	LoadDefaults();
}


Settings::~Settings()
{
	iniManager::SaveConfigFile();
}



void Settings::LoadDefaults()
{
	iniManager::iniManager::mySettings["Window"]["Width"] = "800";
	iniManager::iniManager::mySettings["Window"]["Height"] = "600";
	iniManager::iniManager::mySettings["Window"]["Style"] = WindowStyleClose;
}



int Settings::ParseArguments()
{
	for(int i = 1; i < myArgc; ++i)
	{
		std::string argument = myArgv[i];
		
		if(argument == "--fullscreen" || argument == "-full")
		{
			iniManager::mySettings["Window"]["Style"] = WindowStyleFullscreen;
		}
		else if(argument == "--fullscreenemulation" || argument == "-fsemu")
		{
			iniManager::mySettings["Window"]["Style"] = WindowStyleEmulation;
			SetDesktopResolution();
		}
		else if(argument == "--window" || argument == "-win")
		{
			iniManager::mySettings["Window"]["Style"] = WindowStyleClose;
		}
		else if(argument == "--desktop-mode")
		{
			SetDesktopResolution();
		}
		else if(argument.substr(0,13) == "--resolution=" && argument.length() > 18)
		{
			std::string string(argument.substr(13));
			SetResolution(string);
		}
		else if(argument.substr(0,5) == "-res=" && argument.length() > 10)
		{
			std::string string(argument.substr(5));
			SetResolution(string);
		}
		else if(argument == "--help" || argument == "-h")
		{
			Help();
			return 1;
		}
		else
		{
			std::cout << myArgv[0] << ": invalid optin '" << argument << "'.\n";
			std::cout << "Try '" << myArgv[0] << " --help' to get more information." << std::endl;
			return -1;
		}
	}
	
	return 0;
}



void Settings::SetResolution(const std::string& string)
{
	iniManager::mySettings["Window"]["Width"] = string.substr(0, string.find(','));
	iniManager::mySettings["Window"]["Height"] = string.substr(string.find(',') + 1);
}


void Settings::SetDesktopResolution()
{
	std::stringstream sstr;
	sstr << sf::VideoMode::GetDesktopMode().Width;
	sstr >> iniManager::mySettings["Window"]["Width"];
	sstr.clear(); sstr << sf::VideoMode::GetDesktopMode().Height;
	sstr >> iniManager::mySettings["Window"]["Height"];
}


void Settings::Help() const
{
	std::cout << "    Medieval War - An isometric cross-platform real-time strategy game.\n\n";
	std::cout << "Arguments are:\n";
	std::cout << "\t-h\t  --help\t\t  Show this help text.\n";
	std::cout << "\t-win\t  --window\t\t  Play the game in window mode.\n";
	std::cout << "\t-full\t  --fullscreen\t\t  Play the game in fullscreen mode.\n";
	std::cout << "\t-fsemu\t  --fullscreenemulation\t  Emulate a fullscreen window.\n";
	std::cout << "\t-res=x,y  --resolution=x,y\t  Play with the resolution x * y.\n";
	std::cout << "\t\t  --desktop-mode\t  Play with the desktop resolution.\n";
	std::cout << std::endl;
}



sf::VideoMode Settings::GetVideoMode() const
{
	std::stringstream sstr;
	unsigned int x, y;
	sstr << (*(*iniManager::mySettings.find("Window")).second.find("Width")).second;
	sstr >> x; sstr.clear();
	sstr << (*(*iniManager::mySettings.find("Window")).second.find("Height")).second;
	sstr >> y;
	return sf::VideoMode(x, y);
}


unsigned long Settings::GetWindowStyle() const
{
	std::stringstream sstr;
	unsigned long style;
	sstr << (*(*iniManager::mySettings.find("Window")).second.find("Style")).second;
	sstr >> style;
	return style;
}


