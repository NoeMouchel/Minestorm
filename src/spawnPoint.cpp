#include <iostream>
#include "../include/spawnPoint.h"
#include "../include/settings.h"

SpawnPoint::SpawnPoint(Vector2f pos, Texture* texture_address)
{
	m_referential = { pos, {1,0}, {0,-1},0 };
	setRectangle(SPAWN_SIZE);

	m_placed = true;
	m_texture = texture_address;
}

SpawnPoint::SpawnPoint(Vector2f pos, Vector2f target, Texture* texture_address)
{
	m_referential = { pos, {1,0}, {0,-1},0 };
	setRectangle(SPAWN_SIZE);

	m_target = target;

	m_placed = false;
	m_texture = texture_address;
}

void SpawnPoint::update(float deltaTime)
{
	if (m_placed) return;
	
	Vector2f dir = m_target - m_referential.o;

	if (dir.squareLength() <= SPAWN_ACCEPTANCE_RADIUS)
	{
		m_placed = true;
		return;
	}
	m_referential.o = m_referential.o + dir.unit() * SPAWN_POINT_SPEED * deltaTime;

	updateRectPos();
}


void SpawnPoint::draw(bool debug)
{
	DrawTexturePro((*m_texture), { 256.f * 1 , 0.f , 256.f , 256.f }, m_rect, { m_rect.width * .5f,m_rect.height * .5f }, 0, WHITE);
}