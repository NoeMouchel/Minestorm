#include <iostream>

#include "../include/soundManager.h"
#include "../include/settings.h"
SoundManager::SoundManager()
{
	m_sounds.push_back(LoadSound("assets/Sounds/music.wav"));
	SetSoundVolume(m_sounds[S_MUSIC], .8f);

	m_sounds.push_back(LoadSound("assets/Sounds/ambient.wav"));
	SetSoundVolume(m_sounds[S_AMBIENT], .8f);

	m_sounds.push_back(LoadSound("assets/Sounds/shoot01.wav"));
	SetSoundVolume(m_sounds[S_SHOOT], .25f);

	m_sounds.push_back(LoadSound("assets/Sounds/propulsion.wav"));
	SetSoundVolume(m_sounds[S_PROPULSION], .1f);

	m_sounds.push_back(LoadSound("assets/Sounds/teleportation.wav"));
	SetSoundVolume(m_sounds[S_TELEPORTATION], .1f);

	m_sounds.push_back(LoadSound("assets/Sounds/explosion.wav"));
	SetSoundVolume(m_sounds[S_EXPLOSION], .15f);

	m_sounds.push_back(LoadSound("assets/Sounds/spawn.wav"));
	SetSoundVolume(m_sounds[S_SPAWN], .5f);

	m_sounds.push_back(LoadSound("assets/Sounds/minelayer_alive.wav"));
	SetSoundVolume(m_sounds[S_MINELAYER], .2f);
}

SoundManager::~SoundManager()
{
	StopSoundMulti();

	while (!m_sounds.empty())
	{
		UnloadSound(m_sounds.back());
		m_sounds.pop_back();
	}
}

void SoundManager::playShoot()
{
	PlaySoundMulti(m_sounds[S_SHOOT]);
}
void SoundManager::playPropulsion()
{
	PlaySoundMulti(m_sounds[S_PROPULSION]);
}
void SoundManager::playTeleportation()
{
	PlaySound(m_sounds[S_TELEPORTATION]);
}
void SoundManager::playExplosion()
{
	PlaySound(m_sounds[S_EXPLOSION]);
}
void SoundManager::playSpawn()
{
	PlaySound(m_sounds[S_SPAWN]);
}
void SoundManager::playMinelayer()
{
	if (!IsSoundPlaying(m_sounds[S_MINELAYER]))
	 PlaySound(m_sounds[S_MINELAYER]);
}



void SoundManager::playMusic()
{
	if(!IsSoundPlaying(m_sounds[S_MUSIC]))
		PlaySound(m_sounds[S_MUSIC]);
}
void SoundManager::stopMusic()
{
	StopSound(m_sounds[S_MUSIC]);
}

void SoundManager::playAmbient()
{
	if (!IsSoundPlaying(m_sounds[S_AMBIENT]))
		PlaySound(m_sounds[S_AMBIENT]);
}
void SoundManager::stopAmbient()
{
	StopSound(m_sounds[S_AMBIENT]);
}