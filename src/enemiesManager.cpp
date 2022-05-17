#include <iostream>

#include "../include/enemiesManager.h"
#include "../include/settings.h"


EnemiesManager::EnemiesManager(Texture* texture_address, FXManager* fx_manager, int round)
{
	m_minelayer = new Minelayer(texture_address);
	m_spawner = new Spawner(texture_address);
	m_placing_mine = true;

	m_fx_manager = fx_manager;

	m_initial_wave_cleared = false;
	m_wave_launched = false;
	m_minelayer_spawn = false;
	m_spawn = false;

	m_texture = texture_address;
	m_wave_timer_limit = WAVE_TIMER_LIMIT;
	m_current_round = round;
	createSpawnPoint();
}

EnemiesManager::~EnemiesManager()
{
	while (!m_mine_list.empty())
	{
		delete m_mine_list.back();
		m_mine_list.pop_back();
	}
		
	while (!m_fireball_list.empty())
	{
		delete m_fireball_list.back();
		m_fireball_list.pop_back();
	}

	delete m_minelayer;
	delete m_spawner;
}



void EnemiesManager::createSpawnPoint()
{
	int max_spawn = MIN_SPAWN + 7 * (int)((m_current_round-1)/10);

	//generating the spawn points randomly
	for (int i = 0; i < max_spawn; i++)
	{
		m_spawn_coor.push_back({ randRange({ 0 + 75,WINDOW_WIDTH - 75 }), randRange({ 0 + 75,WINDOW_HEIGHT - 75 }) });
	}
}

void EnemiesManager::createEnemy(Vector2f pos,int mine_size, int type)
{
	m_spawn = true;
	switch (type)
	{
	case M_FLOATING:
		m_mine_list.push_back(new FloatingMine(pos, Vector2f(0,-1).rotate(randRange({ 0,2 * PI })), mine_size, m_texture));
		break;
	case M_MAGNETIC:
		m_mine_list.push_back(new MagneticMine(pos, { -1, 0 }, mine_size, m_texture)); 
		break;
	case M_MAGNETIC_FIREBALL:
		m_mine_list.push_back(new MagneticFireballMine(pos, { -1, 0 }, mine_size, m_texture)); 
		break;
	case M_FIREBALL:
		m_mine_list.push_back(new FireballMine(pos, Vector2f(0, -1).rotate(randRange({ 0,2 * PI })), mine_size, m_texture));
		break;
	default:
		break;
	}
}

void EnemiesManager::spawnManagment(float deltaTime)
{	
	if (!m_spawn_list.empty())
	{
		m_wave_timer += deltaTime;
		
		//is used once
		if (!m_wave_launched)
		{
			if (m_wave_timer > WAVE_TIMER_LIMIT)
			{
				spawnPhase1();
				m_wave_timer = 0;
				m_wave_launched = true;
			}
		}
		else if (m_initial_wave_cleared)
		{
			if (m_wave_timer > m_wave_timer_limit)
			{
				spawnPhase2();
				m_wave_timer = 0;

				//	Raise the Spawning speed
				m_wave_timer_limit -= .25f;
				m_wave_timer_limit = (m_wave_timer_limit < 0) ? .5f : m_wave_timer_limit;
			}
		}
	}
}


bool EnemiesManager::roundCleared()
{
	// Check if the round is cleared
	return m_spawn_list.empty() && m_initial_wave_cleared && m_mine_list.empty() && !m_minelayer->m_is_alive;
}

int EnemiesManager::getMineTypeFromRound(int i)
{
	return round_data[(m_current_round-1)%10][i%4];
}

//Phase 1 spawn concern spawn point that are initially placed by the Spawner at the begining of the round

void EnemiesManager::spawnPhase1()
{	
	int end_list = (int)m_spawn_list.size() - 1;
	int mine_number = 2 + (int)((m_current_round - 1) / 10);

	//only two mine spawn
	for (int i = end_list; i > end_list - mine_number; i--)
	{
		createEnemy(m_spawn_list[i].m_referential.o, SI_BIG, getMineTypeFromRound(end_list-i));

		m_spawn_list.erase(m_spawn_list.begin() + i);
		if (i == 0)
		{
			m_minelayer_spawn = true;
			m_initial_wave_cleared = true;
			m_spawn_list.clear();
		}
	}
	
}

void EnemiesManager::spawnPhase1(int mine_size,int type)
{
	//if the size is a valable one, spawn two new mines
	if (mine_size != -1)
	{
		int end_list = (int)m_spawn_list.size() -1;

		//only two mine spawn
		for (int i = end_list; i > end_list - 2; i--)
		{
			createEnemy(m_spawn_list[i].m_referential.o, mine_size, type);

			m_spawn_list.erase(m_spawn_list.begin() + i);
			if (i == 0)
			{
				m_minelayer_spawn = true;
				m_initial_wave_cleared = true;
				m_spawn_list.clear();
			}
		}
	}
}


//Phase 2 spawn concern spawn point that are placed by the mineLayer after the initial wave is cleared

void EnemiesManager::spawnPhase2()
{
	//	Spawn at the points placed by the mine layer
	int mine_list_size = (int)m_spawn_list.size();
	int index = GetRandomValue(0, mine_list_size-1);
	
	//	The type and the size are choosed randomly
	int mine_type = GetRandomValue(M_FLOATING, M_MAGNETIC_FIREBALL);
	int mine_size = GetRandomValue(SI_BIG,SI_SMALL);

	//	Create new Mine
	createEnemy(m_spawn_list[index].m_referential.o, mine_size, mine_type);

	m_spawn_list.erase(m_spawn_list.begin()+ index);
}

//Vector2f nearestTarget(Vector2f pos, std::vector<Vector2f> target_pos)
Vector2f nearestTarget(Vector2f pos ,const std::vector<Player*> target)
{
	float min = FLT_MAX;
	Vector2f to_return;
	for (Player* cur_target : target)
	{
		if (!cur_target->m_is_alive) continue;

		float distance = (cur_target->m_referential.o - pos).squareLength();
		if (distance < min)
		{
			min = distance;
			to_return = cur_target->m_referential.o;
		}
	}
	return to_return;
}

//void EnemiesManager::update(float deltaTime, std::vector<Vector2f> target_pos)
void EnemiesManager::update(float deltaTime, const std::vector<Player*> m_target)
{
	m_spawn = false;
	if (m_placing_mine)
	{
		spawnerUpdate(deltaTime);
		return;
	}
	spawnManagment(deltaTime);

	minesUpdate(deltaTime, m_target);

	//Update all bullets
	for (int i = 0; i < m_fireball_list.size(); i++)
	{
		if (m_fireball_list[i]->m_is_alive)
		{
			m_fireball_list[i]->update(deltaTime);
		}
	}

	//	Manage mines death
	checkEnemy(deltaTime);

	minelayerUpdate(deltaTime);

	eraseFireball();
}

void EnemiesManager::spawnerUpdate(float deltaTime)
{
	int size = (int)m_spawn_coor.size();

	if (size == 0)
		m_placing_mine = false;

	m_spawner->update(deltaTime);

	for (int i = 0; i < size; i++)
	{
		if (m_spawner->m_referential.o.y < m_spawn_coor[i].y)
		{
			m_spawn_list.push_back(SpawnPoint(m_spawner->m_referential.o, m_spawn_coor[i], m_texture));
			m_spawn_coor.erase(m_spawn_coor.begin() + i);
			i--;
			size--;
		}

	}

	for (SpawnPoint& current_point : m_spawn_list)
	{
		current_point.update(deltaTime);
		if (current_point.m_placed == false)
			m_placing_mine = true;
	}


}

void EnemiesManager::minelayerUpdate(float deltaTime)
{
	//Minelayer spawn
	if (m_minelayer_spawn)
	{
		//	Wait a little bit before the mine layer spawn
		m_minelayer_timer += deltaTime;
		if (m_minelayer_timer > 3.f)
		{
			m_minelayer->m_is_alive = true;
			m_minelayer_timer = 0;
			m_minelayer_spawn = false;
		}
	}

	//Minelayer update
	if (m_minelayer->m_is_alive)
	{
		m_minelayer->update(deltaTime);
		if (m_minelayer->m_on_target)
		{
			m_spawn_list.push_back({ m_minelayer->m_target,m_texture });
			m_minelayer->m_on_target = false;
		}
	}
}

void EnemiesManager::minesUpdate(float deltaTime, const std::vector<Player*> m_target)
{
	int size_mine = (int)m_mine_list.size();
	for (int i = 0; i < size_mine; i++)
	{
		
		Vector2f target = nearestTarget(m_mine_list[i]->m_referential.o, m_target);

		//	Update the direction of the magnetics mines
		if (m_mine_list[i]->m_type == M_MAGNETIC || m_mine_list[i]->m_type == M_MAGNETIC_FIREBALL)
			m_mine_list[i]->updateDirection(target);
		
		m_mine_list[i]->update(deltaTime);

		//	Manage what happen if a mine dies
		mineIsDead(m_mine_list[i], target);
	}
}

void EnemiesManager::mineIsDead(Mine* cur_mine, Vector2f target)
{
	//	Is it dead
	cur_mine->isDead();
	if (cur_mine->m_is_alive) return;
	
	//	If yes, shoot fire ball if the dead mine was a fireball type
	shootFireball(cur_mine, target);

	if (m_initial_wave_cleared) return;
	
	//	If the initial wave isn't cleared, the mine death brings the birth of two new mine
	m_wave_timer = 0;	
	spawnPhase1(cur_mine->newMineSize(), cur_mine->m_type);
}

void EnemiesManager::shootFireball(Mine* cur_mine, Vector2f target)
{
	if (cur_mine->m_type != M_FIREBALL && cur_mine->m_type != M_MAGNETIC_FIREBALL) return;
	
	Vector2f pos = cur_mine->m_referential.o;

	//	For more difficulty, the fireball takes the fastes path to reach its target
	Vector2f dir = cur_mine->getShortestDirection(target);
	m_fireball_list.push_back(new Bullet(pos, dir.unit(), B_FIREBALL, ORANGE, m_texture));
	
}

void EnemiesManager::checkEnemy(float deltaTime)
{

	int size_mine = (int)m_mine_list.size();
	for (int i = 0; i < size_mine; i++)
	{
		if (!m_mine_list[i]->m_is_alive)
		{
			delete m_mine_list[i];
			m_mine_list.erase(m_mine_list.begin() + i);
			size_mine -= 1;
			i--;
		}
	}
}

void EnemiesManager::eraseFireball()
{
	if (m_fireball_list.empty())
		return;

	int size = (int)m_fireball_list.size();
	for (int i = 0; i < size; i++)
	{
		if (!m_fireball_list[i]->m_is_alive)
		{
			delete m_fireball_list[i];
			m_fireball_list.erase(m_fireball_list.begin() + i);
			i--;
			size--;
		}
	}
}


void EnemiesManager::drawEnemies(bool debug)
{

	for (SpawnPoint cur_spawn : m_spawn_list)
		cur_spawn.draw(debug);

	for (Mine* cur_mine : m_mine_list)
		cur_mine->draw(debug);

	for (Bullet* cur_bullet : m_fireball_list)
		cur_bullet->draw(debug);

	if (m_minelayer->m_is_alive)
	{
		m_minelayer->draw(debug);
	}

	if (m_placing_mine)
	{
		m_spawner->draw(debug);
	}
}