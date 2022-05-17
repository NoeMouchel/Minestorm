#include <iostream>
#include "../include/circleCollider.h"
#include "../include/settings.h"


CircleCollider::CircleCollider() 
{
	m_type = C_CIRCLE;
}
void CircleCollider::setAABB(Referential2 local_ref)
{
	m_AABB.m_box.width = m_circle.radius*2.f;
	m_AABB.m_box.length = m_circle.radius*2.f;
	m_AABB.m_box.o = local_ref.o;
}

void CircleCollider::setAABB()
{
	m_AABB.m_box.width = m_circle.radius*2.f;
	m_AABB.m_box.length = m_circle.radius*2.f;

	m_AABB.m_box.o = m_circle.o;
}

void CircleCollider::setCollisionToFalse()
{
	m_collided = false;
	m_AABB.m_collided = false;
}

void CircleCollider::draw()
{
	m_AABB.draw();
	Color circle_color = GREEN;
	if (m_collided)
		circle_color = RED;

	DrawCircleLines((int)m_circle.o.x, (int)m_circle.o.y, m_circle.radius, circle_color);
}