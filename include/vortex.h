#pragma once

#include "effect.h"
#include "entity.h"

class Vortex : public Effect
{
public:
	//CONSTRUCTORS - DESTRUCTORS
	Vortex(Entity* target, float life, float speed,float time, float radius, Texture* texture,Color src_color);
	~Vortex();

	//VARIABLES
	float m_timer;
	float m_timer_limit;
	float m_radius;

	Entity* m_target;

	//FUNCTION
	void update(float) override;
	void spawnVortex(float);
	void particleUpdate(float);
};