#include <iostream>

#include "../include/vortex.h"
#include "../include/settings.h"

Vortex::Vortex(Entity* target, float life, float speed, float time,float radius, Texture* texture, Color src_color)
{
	m_fx_type = FX_TELEPORTATION;
	m_texture = texture;

	m_average_life = life;
	m_average_speed = speed;

	m_is_occuring = true;

	m_timer = 0;
	m_timer_limit = time;

	m_radius = radius;

	m_global_color = src_color;

	m_target = target;
	m_start_pos = m_target->m_referential.o;
}

Vortex::~Vortex()
{

}

void Vortex::update(float deltaTime)
{
	spawnVortex(deltaTime);

	m_is_occuring = false;
	
	particleUpdate(deltaTime);
}

void Vortex::spawnVortex(float deltaTime)
{
	m_timer += deltaTime;

	m_start_pos = m_target->m_referential.o;

	if (m_timer < m_timer_limit)
	{
		Vector2f pos = { m_start_pos.x + randRange({ -m_radius,m_radius }),m_start_pos.y + randRange({ -m_radius,m_radius }) };

		Referential2 self_ref = {
			pos,(m_start_pos - pos).unit() ,(m_start_pos - pos).rotate90() ,0
		};

		float self_speed = randRange({ m_average_speed * .5f, m_average_speed });
		float self_life = randRange({ m_average_life * .5f, m_average_life + m_average_life * .5f });
		int size = GetRandomValue(16, 48);

		m_particle_list.push_back(Particle(self_ref, self_speed, self_life, size, m_texture, m_global_color));
	}
}

void Vortex::particleUpdate(float deltaTime)
{
	for (Particle& cur_particle : m_particle_list)
	{
		cur_particle.m_referential.j = (m_start_pos - cur_particle.m_referential.o);


		if (fabsf(cur_particle.m_referential.j.x) > (WINDOW_WIDTH - UI_PADDING) * .5f)
			cur_particle.m_referential.j.x *= -1;
		if (fabsf(cur_particle.m_referential.j.y) > (WINDOW_HEIGHT - UI_PADDING) * .5f)
			cur_particle.m_referential.j.y *= -1;

		cur_particle.m_referential.j = cur_particle.m_referential.j.unit();


		float squareLength = (cur_particle.m_referential.o - m_start_pos).squareLength();

		// if not in the radius, don't put a rotation
		if (squareLength  <= m_radius * m_radius)
		{
			cur_particle.m_referential.j.rotate(randRange({ PI / 6.f, PI / 2.f }));
			cur_particle.update(deltaTime);
		}
		else
		{
			float saved_speed = cur_particle.m_speed;
			cur_particle.m_speed *= 2.f;
			cur_particle.update(deltaTime);
			cur_particle.m_speed = saved_speed;
		}




		if (cur_particle.m_is_alive)
			m_is_occuring = true;
	}

}