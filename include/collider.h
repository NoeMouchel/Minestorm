#pragma once

#include "../toolBox/toolbox.h"
#include "boxCollider.h"
#include <vector>

class Collider
{
public:
	Collider() { m_AABB = AABB(); m_type = 0; };
	virtual ~Collider() {};

	AABB	m_AABB;
	int		m_type;
	bool	m_collided = false;

	virtual void setCollisionToFalse();
	virtual void setAABB(Referential2 local_ref);
	virtual void setAABB();

	virtual void draw() {};
	virtual void draw(Referential2) {};
};