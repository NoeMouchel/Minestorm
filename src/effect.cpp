#include <iostream>

#include "../include/effect.h"


void Effect::update(float deltaTime)
{
}

void Effect::updateEachParticule(float deltaTime)
{
	m_is_occuring = false;
	for (Particle& cur_particle : m_particle_list)
	{
		cur_particle.m_speed = ((cur_particle.m_life / cur_particle.m_initial_life) * .75f + .25f) * cur_particle.m_initial_speed;
		cur_particle.update(deltaTime);
		if (cur_particle.m_is_alive)
			m_is_occuring = true;
	}

	if (!m_is_occuring)
		m_particle_list.clear();
}

void Effect::draw(bool debug)
{
	for (Particle& cur_particle : m_particle_list)
		cur_particle.draw(debug);
}