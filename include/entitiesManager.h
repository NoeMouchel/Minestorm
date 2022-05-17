#pragma once

#include "player.h"
#include "enemiesManager.h"

#include "settings.h"



class EntitiesManager
{
private:
	PlayersInput m_inputs;
	Texture* m_spriteSheet;
public:
	EntitiesManager(bool duo,Texture* texture_address);
	~EntitiesManager();


//VARIABLES
	EnemiesManager* m_enemy_manager;
	FXManager* m_fx_manager;
	//	Booleans
	bool	m_duo;
	bool	m_game_over;
	bool	m_next_round;
	bool	m_explosion;
	bool	m_check_collision;
	bool	minelayer_telport_done;
	
	//	Datas
	int m_player_score = 0;
	int m_round = START_ROUND;

	//	Timers
	float m_gameover_timer = 0.f;
	float m_respawn_timer = 0.f;
	float m_endround_timer = 0.f;

	// Lists
	std::vector<Player*> m_player;
	std::vector<Effect*> m_fx_list;
	;
//FUNCTIONS
	void EventPlayers(float deltaTime);
	void update(float deltaTime);
	void playersUpdate(float deltaTime);
	void fxUpdate(float deltaTime);

	void entityBulletCollision(Entity* m_target, std::vector<Bullet*> bullets);
	void multipolyCircleCollision(Entity* m_target, std::vector<Bullet*> bullets);
	void circleCircleCollision(Entity* m_target, std::vector<Bullet*> bullets);

	void checkCollision();
	void checkPlayerPlayerCollision(Player* cur_player);
	void checkMineCollision(Player* cur_player);
	void checkMinelayerCollision(Player* cur_player);

	void playerCollided(Player* cur_player);

	void checkRound(float deltaTime);
	void checkPlayer(float deltaTime);
	void reset();
	void drawEntity(bool debug);

	void checkEffects();
};