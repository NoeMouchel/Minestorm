#pragma once
#include "windowManager.h"
#include "settings.h"
#include "renderer.h"
#include "entitiesManager.h"
#include "soundManager.h"
#include "backgroundParticles.h"

class Game
{
public:
	//CONSTRUCTORS / DESTRUCTORS
	Game();
	~Game();

	//VARIABLES
	WindowManager*	m_window;
	Renderer*		m_renderer;
	EntitiesManager* m_entities;
	SoundManager*	m_sound_manager;

	int m_display;
	int m_saved_display;

	float deltaTime;
	float m_round_timer = 0;

	/*debug*/
	bool collide_test1 = false;
	bool m_debug;
	
	BackgroundParticle	m_background_fx;

	//FUNCTIONS

	void gameLoop();

	void gameEvent();
	void mainMenuEvent();
	void inGameEvent();
	void pauseEvent();
	void gameOverEvent();
	void interRoundEvent();

	void gameUpdate();
	void inGameUpdate();

	void gameRender();
	void mainMenuRender();
	void inGameRender();
	void pauseRender();
	void gameOverRender();
	void interRoundRender();

	void gamePlayer();
	void mainMenuPlayer();
	void inGamePlayer();
	void pausePlayer();
	void gameOverPlayer();
};

