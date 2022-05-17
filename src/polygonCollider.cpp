#include <iostream>
#include "../include/polygonCollider.h"
#include "../include/settings.h"


PolygonCollider::PolygonCollider()
{
	m_type = C_POLYGON; 
};

//Set the AABB of the polygon
void PolygonCollider::setAABB(Referential2 local_ref)
{
	ConvexPolygon polygon = localToGlobalConvex(m_polygon, local_ref);
	Range2 x_range(polygon.points[0].x);
	Range2 y_range(polygon.points[0].y);

	for (Vector2f current_point : polygon.points)
	{
		x_range.change(current_point.x);
		y_range.change(current_point.y);
	}
	m_AABB.constructBox(x_range, y_range);
}

void PolygonCollider::setAABB()
{
	Range2 x_range(m_polygon.points[0].x);
	Range2 y_range(m_polygon.points[0].y);

	for (Vector2f current_point : m_polygon.points)
	{
		x_range.change(current_point.x);
		y_range.change(current_point.y);
	}
	m_AABB.constructBox(x_range, y_range);
}


void PolygonCollider::setCollisionToFalse()
{
	m_collided = false;
	m_AABB.m_collided = false;
}

void PolygonCollider::collisionPolygon(PolygonCollider* other_polygon)
{
	if (intersectionBoxBox(m_AABB.m_box, other_polygon->m_AABB.m_box))
	{
		m_AABB.m_collided = other_polygon->m_AABB.m_collided = true;
		
		if (intersectionConvexConvex(m_polygon, other_polygon->m_polygon))
		{
			m_collided = other_polygon->m_collided = true;
		}
	}
}

void  PolygonCollider::collisionPolygon(PolygonCollider* other_polygon, Referential2 m_ref, Referential2 o_ref)
{
	if (intersectionBoxBox(m_AABB.m_box, other_polygon->m_AABB.m_box))
	{
		m_AABB.m_collided = other_polygon->m_AABB.m_collided = true;
		if (intersectionConvexConvex(localToGlobalConvex(m_polygon, m_ref), localToGlobalConvex(other_polygon->m_polygon, o_ref)))
		{
			m_collided = other_polygon->m_collided = true;
		}
	}
}

void PolygonCollider::draw(Referential2 ref)
{
	Color poly_color = GREEN;
	if (m_collided)
		poly_color = RED;

	m_AABB.draw();
	size_t size = m_polygon.points.size();
	for (size_t i = 0; i < size; i++)
	{
		Vector2f currentPoint = localToGlobalVector(ref, m_polygon.points[i]);
		Vector2f nextPoint = localToGlobalVector(ref, m_polygon.points[(i + 1) % size]);
		DrawLineEx({ currentPoint.x, currentPoint.y }, { nextPoint.x, nextPoint.y }, 1.50f, poly_color);
	}
}

void PolygonCollider::draw()
{
	Color poly_color = GREEN;
	if (m_collided)
		poly_color = RED;

	m_AABB.draw();
	size_t size = m_polygon.points.size();
	for (size_t i = 0; i < size; i++)
	{
		Vector2f currentPoint = m_polygon.points[i];
		Vector2f nextPoint = m_polygon.points[(i + 1) % size];
		DrawLineEx({ currentPoint.x, currentPoint.y }, { nextPoint.x, nextPoint.y }, 1.50f, poly_color);
	}
}