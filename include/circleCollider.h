#pragma once

#include "collider.h"
#include "../toolBox/toolbox.h"
#include <vector>


class CircleCollider : public Collider
{
public:
	CircleCollider();
	~CircleCollider() {};
	Circle m_circle;

	void setCollisionToFalse() override;
	void setAABB(Referential2 local_ref) override;
	void setAABB() override;

	void draw() override;
};
