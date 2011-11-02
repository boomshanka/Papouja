#include "iniManager.hpp"

#include <iostream>
#include <fstream>
#include <sstream>



iniManager::iniManager()
{

}


iniManager::~iniManager()
{

}



void iniManager::LoadConfigFile(std::string path)
{
	std::ifstream file(path.c_str());
	
	if(!file.fail())
	{
		std::string section;
		
		while(!file.eof())
		{
			std::getline(file, section);
			if(section[0] == '[' && section.find(']') != std::string::npos)
			{
				section = section.substr(1, section.find(']') - 1);
				std::string name;
				
				while(!file.eof())
				{
					std::streamoff pos = file.tellg();
					std::getline(file, name);
					if(name[0] == '[')
					{
						file.seekg(pos);
						break;
					}
					if(name[0] != ';' && name[0] != '#' && name.size() > 0)
					{
						std::string value = name;
						name = name.substr(0, name.find('='));
						value = value.substr(value.find('=') + 1);
						
						mySettings[section][name] = value;
					}
				}
			}
		}
	}
	
	file.close();
}

void iniManager::SaveConfigFile(std::string path)
{
	std::ofstream file(path.c_str(), std::ios_base::trunc);
	
	if(!file.fail())
	{
		for(std::map<std::string, std::map<std::string, std::string> >::iterator it = mySettings.begin(); it != mySettings.end(); ++it)
		{
			file << '[' << (*it).first << "]\n";
			for(std::map<std::string, std::string>::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2)
			{
				file << (*it2).first << '=' << (*it2).second << "\n";
			}
		}
	}
	else
	{
		std::cerr << "Error: Cannot write the config file " << path << ".\n";
	}
	
	file.close();
}



const std::string& iniManager::GetSettings(const std::string& section, const std::string& name) const
{
	return (*(*mySettings.find(section)).second.find(name)).second;
}



