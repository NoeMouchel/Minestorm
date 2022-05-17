#include <iostream>
#include "../include/multiPolygonCollider.h"
#include "../include/settings.h"


MultiPolygonCollider::MultiPolygonCollider()
{
	m_type = C_MULTIPOLYGONE;
}
//Set the AABB of the multi polygon
void MultiPolygonCollider::setAABB(Referential2 local_ref)
{
	
	Range2 x_range(localToGlobalVector(local_ref,m_polygon_list[0].m_polygon.points[0]).x);
	Range2 y_range(localToGlobalVector(local_ref,m_polygon_list[0].m_polygon.points[0]).y);

	for (int i = 0 ; i < m_polygon_list.size() ; i++)
	{
		Range2 x_range_poly(localToGlobalVector(local_ref, m_polygon_list[i].m_polygon.points[0]).x);
		Range2 y_range_poly(localToGlobalVector(local_ref, m_polygon_list[i].m_polygon.points[0]).y);
		for (Vector2f current_point : m_polygon_list[i].m_polygon.points)
		{
			Vector2f vector_global = localToGlobalVector(local_ref, current_point);

			x_range_poly.change(vector_global.x);
			y_range_poly.change(vector_global.y);

			x_range.change(vector_global.x);
			y_range.change(vector_global.y);
		}

		//Set AABB for each polygon
		m_polygon_list[i].m_AABB.constructBox(x_range_poly, y_range_poly);
	}
	//Set AABB for the multi polygon
	m_AABB.constructBox(x_range, y_range);
}

void MultiPolygonCollider::setAABB()
{

	Range2 x_range(m_polygon_list[0].m_polygon.points[0].x);
	Range2 y_range(m_polygon_list[0].m_polygon.points[0].y);

	for (int i = 0; i < m_polygon_list.size(); i++)
	{
		Range2 x_range_poly(m_polygon_list[0].m_polygon.points[0].x);
		Range2 y_range_poly(m_polygon_list[0].m_polygon.points[0].y);

		for (Vector2f current_point : m_polygon_list[i].m_polygon.points)
		{
			Vector2f vector_global = current_point;

			x_range_poly.change(vector_global.x);
			y_range_poly.change(vector_global.y);

			x_range.change(vector_global.x);
			y_range.change(vector_global.y);
		}
		//Set AABB for each polygon
		m_polygon_list[i].m_AABB.constructBox(x_range_poly, y_range_poly);
	}
	//Set AABB for the multi polygon
	m_AABB.constructBox(x_range, y_range);
}

void MultiPolygonCollider::setCollisionToFalse()
{
	m_collided = false;
	m_AABB.m_collided = false;
	for (int i = 0; i < m_polygon_list.size(); i++)
	{
		m_polygon_list[i].setCollisionToFalse();
	}
}

void MultiPolygonCollider::collisionMulti(MultiPolygonCollider* other_multi_polygon)
{
	if (!intersectionBoxBox(other_multi_polygon->m_AABB.m_box, m_AABB.m_box))
	{
		return;
	}

	other_multi_polygon->m_AABB.m_collided = true;
	m_AABB.m_collided = true;

	m_AABB.m_collided = other_multi_polygon->m_AABB.m_collided = intersectionBoxBox(other_multi_polygon->m_AABB.m_box, m_AABB.m_box);

	for (PolygonCollider m_poly : m_polygon_list)
	{
		for (PolygonCollider o_poly : other_multi_polygon->m_polygon_list)
		{
			m_poly.collisionPolygon(&o_poly);
			if (m_poly.m_collided)
			{
				m_collided = true;
				other_multi_polygon->m_collided = true;
				return;
			}
		}
	}
}


void MultiPolygonCollider::collisionMulti(MultiPolygonCollider* other_multi_polygon, Referential2 m_ref, Referential2 o_ref)
{
	
	//	Reset all boolean to false if there the AABB do not collide
	if (!intersectionBoxBox(other_multi_polygon->m_AABB.m_box, m_AABB.m_box))
	{
		return;
	}

	//Else

	other_multi_polygon->m_AABB.m_collided = true ;
	m_AABB.m_collided = true;

	size_t m_size = m_polygon_list.size();
	size_t o_size = other_multi_polygon->m_polygon_list.size();
	
	//for each polygon
	for (size_t i = 0 ; i < m_size; i++)
	{
		//and for each polygon of the other multi polygon
		for (size_t j = 0 ; j < o_size; j++)
		{
			//detect if there is an intersection
			m_polygon_list[i].collisionPolygon(&other_multi_polygon->m_polygon_list[j], m_ref, o_ref);

			//if yes, set their collision boolean to true;
			if (m_polygon_list[i].m_collided)
			{
				m_collided = true;
				other_multi_polygon->m_collided = true;
				return;
			}
		}
	}
}


void MultiPolygonCollider::draw()
{
	m_AABB.draw();
	for (PolygonCollider poly : m_polygon_list)
	{
		poly.draw();
	}
}

void MultiPolygonCollider::draw(Referential2 ref)
{
	m_AABB.draw();
	for (PolygonCollider poly : m_polygon_list)
	{
		poly.draw(ref);
	}
}