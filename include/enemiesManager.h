#pragma once

#include <vector>


#include "floatingMine.h"
#include "magneticMine.h"
#include "fireballMine.h"
#include "magneticFireballMine.h"


#include "FXManager.h"

#include "spawnpoint.h"
#include "minelayer.h"
#include "bullet.h"
#include "player.h"
#include "spawner.h"

class EnemiesManager
{
public:
	EnemiesManager(Texture* texture_address, FXManager* fx_manager, int round);
	~EnemiesManager();

	

	FXManager* m_fx_manager;
	Minelayer* m_minelayer;

	std::vector<Mine*> m_mine_list;
	std::vector <Bullet*> m_fireball_list;

	std::vector<Vector2f> m_spawn_coor;
	std::vector<SpawnPoint> m_spawn_list;

	int m_current_round;

	float m_wave_timer = 0;
	float m_wave_timer_limit;
	float m_spawn_show_timer = 0;
	float m_minelayer_timer = 0;

	bool m_placing_mine;
	bool m_wave_launched;
	bool m_initial_wave_cleared;
	bool m_minelayer_spawn;
	bool m_spawn;

	Texture* m_texture;
	Spawner* m_spawner;
	//std::vector<Effect*> m_fx_list;

	void createSpawnPoint();
	void createEnemy(Vector2f pos, int mine_size, int type);

	void spawnPhase1();
	void spawnPhase1(int mine_size, int type);
	void spawnPhase2();

	
	void spawnManagment(float deltaTime);
	void update(float deltaTime, const std::vector<Player*> target);
	void spawnerUpdate(float deltaTime);
	void minesUpdate(float deltaTime, const std::vector<Player*> m_target);
	void minelayerUpdate(float deltaTime);

	void mineIsDead(Mine* cur_mine, Vector2f target);
	void shootFireball(Mine* cur_mine, Vector2f target);

	void checkEnemy(float deltaTime);

	void eraseFireball();
	void drawEnemies(bool debug);

	int getMineTypeFromRound(int i);

	bool roundCleared();

};

