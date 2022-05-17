#include <iostream>

#include "../include/explosion.h"
#include "../include/settings.h"

Explosion::Explosion(Referential2 ref, float life, float speed, int density, Texture* texture, Color src_color, bool disperse)
{
	m_fx_type = FX_EXPLOSION;

	m_average_life = life;
	m_average_speed = speed;

	m_is_occuring = true;

	for (int i = 0; i < density; i++)
	{
		Referential2 self_ref = ref;

		float self_angle;

		if(disperse)
			self_angle = randRange({ 0,  2*PI });
		else
			self_angle = randRange({ -PI/5.f,  PI /5.f });

		float self_speed = randRange({ 0, speed });
		float self_life = randRange({ life - 1.f, life + 1.f });

		int size = GetRandomValue(16, 48);

		self_ref.setAngle(self_angle);

		m_particle_list.push_back(Particle(self_ref, self_speed, self_life, size, texture, src_color));
	}
}

Explosion::~Explosion()
{

}

void Explosion::update(float deltaTime)
{
	updateEachParticule(deltaTime);
}
