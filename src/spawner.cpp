#include <iostream>
#include "../include/spawner.h"
#include "../include/settings.h"


Spawner::Spawner(Texture* texture_address)
{
	m_texture = texture_address;
	m_referential = { {WINDOW_WIDTH * .5f,WINDOW_HEIGHT + 10.f}, {1,0},{0,-1},0 };
	setRectangle(SIZE_BIG);
}


void Spawner::update(float deltaTime)
{
	m_referential.o = m_referential.o + m_referential.j * SPAWNER_SPEED*deltaTime;
	updateRectPos();

	m_rect.width = SIZE_BIG * ((m_referential.o.y / WINDOW_HEIGHT *0.75f) + .25f);
	m_rect.height = SIZE_BIG * ((m_referential.o.y / WINDOW_HEIGHT * 0.75f) + .25f);

}

void Spawner::draw(bool debug)
{
	DrawTexturePro(*m_texture, { 256.f * 2.f , 0.f , 256.f , 256.f }, m_rect, { m_rect.width * .5f,m_rect.height * .5f }, 0, RED);
}