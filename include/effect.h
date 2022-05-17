#pragma once

#include "particle.h"

class Effect
{
public:
	//CONSTRUCTORS - DESTRUCTORS
	Effect() = default;

	virtual ~Effect() { m_particle_list.clear(); };

	//VARIABLES
	int m_fx_type;

	float m_average_life;
	float m_average_speed;

	bool m_is_occuring;

	Vector2f m_start_pos;
	Vector2f m_average_dir;

	Texture* m_texture;
	Color m_global_color;

	std::vector<Particle> m_particle_list;

	//FUNCTION
	virtual void update(float deltaTime);

	void updateEachParticule(float);
	void draw(bool debug);
};