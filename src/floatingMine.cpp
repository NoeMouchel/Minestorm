#include <iostream>
#include "../include/floatingMine.h"
#include "../include/settings.h"

FloatingMine::FloatingMine(Vector2f pos, Vector2f dir, int size, Texture* texture_address)
{
	m_referential = { pos,{1,0},{0,-1},0 };
	m_type = M_FLOATING;
	m_texture = texture_address;
	m_rotation_speed = randRange({ 0.5f,3.f });

	m_is_alive = true;
	m_size = size;
	m_direction = dir;
	setRect();

	if (m_size == SI_BIG)
	{
		m_speed = SLOW_SPEED;
		m_score = BIG_FLOATING_MINE_SCORE;
	}
	else if (m_size == SI_MEDIUM)
	{
		m_speed = MEDIUM_SPEED;
		m_score = MEDIUM_FLOATING_MINE_SCORE;
	}
	if (m_size == SI_SMALL)
	{
		m_speed = GREAT_SPEED;
		m_score = SMALL_FLOATING_MINE_SCORE;
	}

	setCollisionBox();
	setColor();
}


void FloatingMine::setCollisionBox()
{
	float scale = m_rect.width / SIZE_BIG;
	m_collider = new MultiPolygonCollider();
	((MultiPolygonCollider*)m_collider)->m_polygon_list.push_back(PolygonCollider());
	{
		MultiPolygonCollider* multi_poly = ((MultiPolygonCollider*)m_collider);
		multi_poly->m_polygon_list[0].m_polygon.points.push_back(Vector2f(0.f, 0.f) * scale);
		multi_poly->m_polygon_list[0].m_polygon.points.push_back(Vector2f(-15.f, 10.f) * scale);
		multi_poly->m_polygon_list[0].m_polygon.points.push_back(Vector2f(0.f, 55.f) * scale);
		multi_poly->m_polygon_list[0].m_polygon.points.push_back(Vector2f(15.f, 10.f) * scale);
		multi_poly->m_polygon_list[0].setAABB(m_referential);
	}
	
	((MultiPolygonCollider*)m_collider)->m_polygon_list.push_back(PolygonCollider());
	{
		MultiPolygonCollider* multi_poly = ((MultiPolygonCollider*)m_collider);
		multi_poly->m_polygon_list[1].m_polygon.points.push_back(Vector2f(0.f,0.f) * scale);
		multi_poly->m_polygon_list[1].m_polygon.points.push_back(Vector2f(-15.f, 10.f) * scale);
		multi_poly->m_polygon_list[1].m_polygon.points.push_back(Vector2f(-45.f, -27.5f) * scale);
		multi_poly->m_polygon_list[1].m_polygon.points.push_back(Vector2f(0, -17.5f) * scale);
		multi_poly->m_polygon_list[1].setAABB(m_referential);
	}
	
	((MultiPolygonCollider*)m_collider)->m_polygon_list.push_back(PolygonCollider());
	{
		MultiPolygonCollider* multi_poly = ((MultiPolygonCollider*)m_collider);
		multi_poly->m_polygon_list[2].m_polygon.points.push_back(Vector2f(0.f,0.f) * scale);
		multi_poly->m_polygon_list[2].m_polygon.points.push_back(Vector2f(15.f, 10.f) * scale);
		multi_poly->m_polygon_list[2].m_polygon.points.push_back(Vector2f(45.f, -27.5f) * scale);
		multi_poly->m_polygon_list[2].m_polygon.points.push_back(Vector2f(0, -17.5f) * scale);
		multi_poly->m_polygon_list[2].setAABB(m_referential);
	}
	((MultiPolygonCollider*)m_collider)->setAABB(m_referential);
}
