#include <iostream>
#include "../include/entity.h"
#include "../include/settings.h"


Entity::~Entity()
{
	if (m_collider->m_type == C_CIRCLE)
		delete (CircleCollider*)m_collider;
	else if (m_collider->m_type == C_POLYGON)
		delete (PolygonCollider*)m_collider;
	else if (m_collider->m_type == C_MULTIPOLYGONE)
		delete (MultiPolygonCollider*)m_collider;
	else
		delete m_collider;
}

void Entity::setDirectionDeg()
{
	//convert the angle in radiant so we can rotate our director
	m_referential.setAngle(m_rotation * (float)PI_CONVERT);

	m_angle += m_rotation;
	m_rotation = 0;
}

void Entity::setDirectionRad()
{
	//convert the angle in radiant so we can rotate our director
	m_referential.setAngle(m_rotation);

	m_angle += m_rotation/ (float)PI_CONVERT;
	m_rotation = 0;
}



//Virtual functions


void Entity::isDead()
{
	if(m_collider->m_collided)
		m_is_alive = false;
}

void Entity::setCollisionBox()
{}


Vector2f Entity::getShortestDirection(Vector2f target)
{
	Vector2f dir = target - m_referential.o;

	float width = (WINDOW_WIDTH - UI_PADDING);
	float height = (WINDOW_HEIGHT - UI_PADDING);

	if (fabsf(dir.x) > width * .5f)
	{
		dir.x *= -1;
		if (dir.x < 0)
			dir.x =-( width + dir.x);
		else
			dir.x = width - dir.x;
	}
	if (fabsf(dir.y) > height * .5f)
	{
		dir.y *= -1;
		if(dir.y<0)
			dir.y =- (height + dir.y);
		else
			dir.y = (height - dir.y);
	}

	return dir.unit();
}
