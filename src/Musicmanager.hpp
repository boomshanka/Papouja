#ifndef MUSICMANAGER_HPP
#define MUSICMANAGER_HPP

#include "Resourcemanager.hpp"

#include <SFML/Audio.hpp>
#include <list>
#include <map>


class Musicmanager
{
public:
	Musicmanager(Resourcemanager& resourcemanager);
	~Musicmanager();
	
	bool LoadMusic(const std::string& path);
	bool LoadSound(const std::string& path);
	void PlaySound(const std::string& path);
	void AddMusicToPlaylist(const std::string& path, const std::string& playlist);
	void RemoveMusicFromPlaylist(const std::string& path, const std::string& playlist);
	void PlayPlaylist(const std::string& playlist);
	void StopPlaylist(const std::string& playlist);
private:
	Resourcemanager& myResourcemanager;
	
	std::map<std::string, std::list<std::string> > myPlaylists;
};


#endif


