#pragma once

#include "collider.h"
#include "../toolBox/toolbox.h"
#include <vector>

class PolygonCollider : public Collider
{
public:
	PolygonCollider();
	~PolygonCollider() {};

	ConvexPolygon m_polygon;

	void setAABB(Referential2 local_ref) override;
	void setAABB() override;
	
	void setCollisionToFalse() override;
	void collisionPolygon(PolygonCollider* other_polygon);
	void collisionPolygon(PolygonCollider* other_polygon,Referential2 m_ref , Referential2 o_ref);

	void draw(Referential2 ref);
	void draw() override;
};
