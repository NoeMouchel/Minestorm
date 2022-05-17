#pragma once

#include <raylib.h>
#include <vector>

class SoundManager
{
private:
	//VARIABLES
	std::vector<Sound> m_sounds;
public:
	//CONSTRUCTORS
	SoundManager();
	~SoundManager();

	//FUNCTIONS
	void playShoot();
	void playPropulsion();
	void playTeleportation();
	void playExplosion();
	void playSpawn();
	void playMinelayer();

	void playMusic();
	void stopMusic();

	void playAmbient();
	void stopAmbient();


};