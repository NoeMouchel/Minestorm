#pragma once

#include "explosion.h"
#include "vortex.h"
#include "propulsion.h"
#include "entity.h"

class FXManager
{
public:
	//CONSTRUCTORS
	FXManager(Texture* spriteSheet);
	~FXManager();

	//VARIABLES
	std::vector<Effect*> m_fx_list;
	Texture* m_spriteSheet;

	//FUNCTIONS
	void update(float deltaTime);
	void checkEffects();
	void draw(bool debug);
	void clearFX();

	void bulletExplode(Entity* m_entity);

	void mineExplode(Entity* m_entity);

	void minelayerSpawn(Entity* m_entity);
	void minelayerExplode(Entity* m_entity);

	void playerExplode(Entity* m_entity);
	void playerPropulse(Entity* m_entity);
	void playerTeleport(Entity* m_entity);

};