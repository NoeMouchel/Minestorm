#pragma once

#include "polygonCollider.h"
#include "../toolBox/toolbox.h"
#include <vector>



class MultiPolygonCollider : public Collider
{
public:
	MultiPolygonCollider();
	~MultiPolygonCollider() { m_polygon_list.clear(); };

	std::vector<PolygonCollider> m_polygon_list;

	void setAABB(Referential2 local_ref) override;
	void setAABB() override;

	void setCollisionToFalse() override;
	void collisionMulti(MultiPolygonCollider* other_multi_polygon);
	void collisionMulti(MultiPolygonCollider* other_multi_polygon, Referential2 m_ref, Referential2 o_ref);
	
	void draw() override;
	void draw(Referential2 ref) override;
	;
};