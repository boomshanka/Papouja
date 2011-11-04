#ifndef INIMANAGER_HPP
#define INIMANAGER_HPP

#include <string>
#include <map>


class iniManager
{
	public:
		iniManager();
		~iniManager();
		
		void LoadConfigFile(std::string path = "settings.ini");
		void SaveConfigFile(std::string path = "settings.ini");
		
		const std::string& GetSettings(const std::string& section, const std::string& name) const;
		void SetSettings(const std::string& section, const std::string& name, const std::string& setting);
			
	protected:
		std::map<std::string, std::map<std::string, std::string> > mySettings;
		
};


#endif // INIMANAGER_HPP


