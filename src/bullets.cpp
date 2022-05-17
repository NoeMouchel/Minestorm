#include <iostream>
#include "../include/bullets.h"
#include "../include/settings.h"

Bullet::Bullet(Vector2f pos, Vector2f direction)
{
	m_referential.o = pos;
	m_referential.j = direction;
	m_referential.i = direction.rotate(-PI/2);

	m_collider = new CircleCollider();
	((CircleCollider*)m_collider)->m_circle = Circle(pos, 7.5f);
	m_life = 1.f;

	m_collided = false;
	m_is_alive = true;
}

Bullet::~Bullet()
{
}

void Bullet::update(float deltaTime)
{
	m_referential.o = m_referential.o + m_referential.j * BULLET_SPEED * deltaTime;

	m_referential.o.x = loopingClamp(m_referential.o.x, UI_PADDING, WINDOW_WIDTH - UI_PADDING);
	m_referential.o.y = loopingClamp(m_referential.o.y, UI_PADDING, WINDOW_HEIGHT - UI_PADDING);

	((CircleCollider*)m_collider)->m_circle.o = m_referential.o;

	m_life -= deltaTime;
	if (m_life <= 0 || m_collided)
	{
		m_life = 0;
		m_is_alive = false;
	}
}