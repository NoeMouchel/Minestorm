#include <iostream>

#include "../include/backgroundParticles.h"
#include "../include/settings.h"

BackgroundParticle::BackgroundParticle(int density, Texture* texture, Color src_color)
{
	m_texture = texture;
	density = density / 4;
	m_color = src_color;
	for (int i = 0; i < density; i++)
	{
		createParticule(LIGHTGRAY);
		createParticule(m_color);
	}
}
void BackgroundParticle::createParticule(Color src_color)
{
	Referential2 self_ref =
	{
		{randRange({ 0,  WINDOW_WIDTH }),randRange({ 0,  WINDOW_HEIGHT }) },
		{1,0},
		{ 0,-1 },
		0
	};

	float self_angle = randRange({ -PI,  PI });
	float self_speed = randRange({ 1.f, 5.f });

	self_ref.setAngle(self_angle);

	m_particle_list.push_back(Particle(self_ref, self_speed, randRange({ 5.f,20.f }), GetRandomValue(8,36), m_texture, m_color));
}


void BackgroundParticle::update(float deltaTime)
{
	for (Particle& cur_particle : m_particle_list)
	{
		cur_particle.m_speed = ((cur_particle.m_life / cur_particle.m_initial_life) * .75f + .25f) * cur_particle.m_initial_speed;
		cur_particle.update(deltaTime);

		if (cur_particle.m_is_alive) continue;
		
		Referential2 self_ref =
		{
			{randRange({ 0,  WINDOW_WIDTH }),randRange({ 0,  WINDOW_HEIGHT }) },
			{1,0},
			{ 0,-1 },
			0
		};

		self_ref.setAngle(randRange({ -PI,  PI }));

		// pick randomly one of the two colors
		if (GetRandomValue(0, 10) % 2 == 0)
			cur_particle.m_color = m_color;
		else
			cur_particle.m_color = LIGHTGRAY;

		cur_particle.m_speed = randRange({ 1.f, 5.f });
		cur_particle.m_referential = self_ref;
		cur_particle.m_life = cur_particle.m_initial_life =  randRange({ 5.f,20.f });
		cur_particle.m_is_alive = true;
	}
}

void BackgroundParticle::draw()
{
	for (Particle& cur_particle : m_particle_list)
	{
		Color color_to_put = cur_particle.m_color;
		color_to_put.a = (unsigned char)(cur_particle.m_color.a * (1 - cur_particle.m_life / cur_particle.m_initial_life) * (cur_particle.m_life / cur_particle.m_initial_life));
		float width, height;
		height = width = cur_particle.m_size;
		DrawTexturePro((*cur_particle.m_texture), { 256 * 3 , 0 , 256 , 256 }, { cur_particle.m_rect.x,cur_particle.m_rect.y ,width,height }, { width * .5f,height * .5f }, 0, color_to_put);
	}
}