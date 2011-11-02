#include "Musicmanager.hpp"

#include <iostream>


Musicmanager::Musicmanager(Resourcemanager& resourcemanager) :
myResourcemanager(resourcemanager)
{

}


Musicmanager::~Musicmanager()
{

}


bool Musicmanager::LoadMusic(const std::string& path)
{
	try
	{
		myResourcemanager.Get<sf::Music>(path);
	}
	catch(std::exception& ex)
	{
		std::cerr << "Error while loading a music file: " << ex.what() << "\n";
		return false;
	}
	return true;
}


bool Musicmanager::LoadSound(const std::string& path)
{
	try
	{
		myResourcemanager.Get<sf::SoundBuffer>(path);
	}
	catch(std::exception& ex)
	{
		std::cerr << "Error while loading a sound file: " << ex.what() << "\n";
		return false;
	}
	return true;
}


void Musicmanager::AddMusicToPlaylist(const std::string& path, const std::string& playlist)
{
	myPlaylists[playlist].push_back(path);
}


void Musicmanager::RemoveMusicFromPlaylist(const std::string& path, const std::string& playlist)
{
	myPlaylists[playlist].remove(path);
}

