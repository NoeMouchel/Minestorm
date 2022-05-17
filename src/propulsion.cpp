#include <iostream>

#include "../include/propulsion.h"
#include "../include/settings.h"

Propulsion::Propulsion(Referential2 ref, float life, float speed, int density, Texture* texture, Color src_color)
{
	m_fx_type = FX_PROPULSION;
	m_average_life = life;
	m_average_speed = speed;

	m_is_occuring = true;

	Referential2 self_ref = ref;
	self_ref.o = ref.o - ref.j*25.f;

	for (int i = 0; i < density; i++)
	{
		
		self_ref.setAngle(PI);

		float self_angle;

		self_angle = randRange({ -2*PI/3.f,  2*PI /3.f });

		float self_speed = randRange({ 0, speed });
		float self_life = randRange({ life - 1.f, life + 1.f });
		
		int size = GetRandomValue(16, 48);

		self_ref.setAngle(self_angle);

		m_particle_list.push_back(Particle(self_ref, self_speed, self_life, size, texture, src_color));
	}
}

Propulsion::~Propulsion()
{

}

void Propulsion::update(float deltaTime)
{
	updateEachParticule(deltaTime);
}