#include <iostream>

#include "../include/mine.h"
#include "../include/settings.h"

void Mine::setRect()
{
	if (m_size == SI_BIG)
		setRectangle(SIZE_BIG);
	else if(m_size == SI_MEDIUM)
		setRectangle(SIZE_MEDIUM);
	else
		setRectangle(SIZE_SMALL);
}

void Mine::update(float deltaTime)
{
	m_rotation += m_rotation_speed;
	setDirectionDeg();
	displacement(deltaTime);
	m_collider->setAABB(m_referential);
}

void Mine::displacement(float deltaTime)
{
	m_referential.o = m_referential.o + m_direction * m_speed * deltaTime;
	
	m_referential.o.x = loopingClamp(m_referential.o.x, UI_PADDING, WINDOW_WIDTH - UI_PADDING);
	m_referential.o.y = loopingClamp(m_referential.o.y, UI_PADDING, WINDOW_HEIGHT - UI_PADDING);

	updateRectPos();
}

int Mine::newMineSize()
{
	if (m_size == SI_BIG)
		return SI_MEDIUM;
	else if (m_size == SI_MEDIUM)
		return SI_SMALL;
	else
		return -1;
}

void Mine::updateDirection(Vector2f target)
{
	m_direction = getShortestDirection(target);
}


void Mine::draw(bool debug)
{
	Color color_to_put = m_color;
	if (debug)
	{
		((MultiPolygonCollider*)m_collider)->draw(m_referential);
		drawGuizmo(50);
		color_to_put.a = 150;
	}
	DrawTexturePro((*m_texture), { 256.f * m_type , 256.f , 256.f , 256.f }, m_rect, { m_rect.width * .5f,m_rect.height * .5f }, m_angle, color_to_put);
}

void Mine::setColor()
{
	switch (m_type)
	{
	case M_FLOATING:
		m_color = PURPLE; break;
	case M_MAGNETIC:
		m_color = DARKBLUE; break;
	case M_MAGNETIC_FIREBALL:
		m_color = ORANGE;  break;
	case  M_FIREBALL:
		m_color = YELLOW;  break;
	}
}