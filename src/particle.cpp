#include <iostream>

#include "../include/particle.h"
#include "../include/settings.h"


Particle::Particle(Referential2 ref, float speed, float life, int size, Texture* texture,  Color src_color)
{
	m_referential = ref;
	m_life = m_initial_life = life;
	m_speed = m_initial_speed = speed;
	m_size = (float)size;

	m_texture = texture;
	m_color = src_color;

	m_is_alive = true;

	setRectangle(m_size);
}

Particle::~Particle()
{

}

void Particle::update(float deltaTime)
{
	m_life -= deltaTime * PARTICLE_AGING;
	m_referential.o = m_referential.o + m_referential.j * (m_speed * deltaTime);
	
	clampReferential();

	updateRectPos();

	if (m_life <= 0)
	{
		m_life = 0;
		m_is_alive = false;
	}
}
void Particle::draw(bool debug)
{
	Color color_to_put = m_color;
	color_to_put.a = (unsigned char)(255*(m_life/m_initial_life));
	float width, height;
	height = width = m_size;
	DrawTexturePro((*m_texture), { 256 * 3 , 0 , 256 , 256 }, { m_rect.x,m_rect.y ,width,height }, { width * .5f,height * .5f }, 0, color_to_put);
}