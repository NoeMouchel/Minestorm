#include <iostream>
#include "../include/magneticFireballMine.h"
#include "../include/settings.h"

MagneticFireballMine::MagneticFireballMine(Vector2f pos, Vector2f dir, int size, Texture* texture_address)
{
	m_referential = { pos,{1,0},{0,-1},0 };
	m_type = M_MAGNETIC_FIREBALL;
	m_texture = texture_address;
	m_rotation_speed = randRange({ 0.5f,3.f });

	m_is_alive = true;
	m_size = size;
	m_direction = dir;
	setRect();

	if (m_size == SI_BIG)
	{
		m_speed = SLOW_SPEED;
		m_score = BIG_MAGNETIC_FIREBALL_MINE_SCORE;
	}
	else if (m_size == SI_MEDIUM)
	{
		m_speed = MEDIUM_SPEED;
		m_score = MEDIUM_MAGNETIC_FIREBALL_MINE_SCORE;
	}
	if (m_size == SI_SMALL)
	{
		m_speed = GREAT_SPEED;
		m_score = SMALL_MAGNETIC_FIREBALL_MINE_SCORE;
	}
	setCollisionBox();
	setColor();
}



void MagneticFireballMine::setCollisionBox()
{
	float scale = m_rect.width / SIZE_BIG;
	m_collider = new MultiPolygonCollider();
	((MultiPolygonCollider*)m_collider)->m_polygon_list.push_back(PolygonCollider());
	{
		MultiPolygonCollider* multi_poly = ((MultiPolygonCollider*)m_collider);
		multi_poly->m_polygon_list[0].m_polygon.points.push_back(Vector2f(0.f, 0.f) * scale);
		multi_poly->m_polygon_list[0].m_polygon.points.push_back(Vector2f(-33.5f, 57.5f) * scale);
		multi_poly->m_polygon_list[0].m_polygon.points.push_back(Vector2f(-33.5f, -20.f) * scale);
		multi_poly->m_polygon_list[0].setAABB(m_referential);
	}

	((MultiPolygonCollider*)m_collider)->m_polygon_list.push_back(PolygonCollider());
	{
		MultiPolygonCollider* multi_poly = ((MultiPolygonCollider*)m_collider);
		multi_poly->m_polygon_list[1].m_polygon.points.push_back(Vector2f(0.f, 0.f) * scale);
		multi_poly->m_polygon_list[1].m_polygon.points.push_back(Vector2f(-57.5f, -33.5f) * scale);
		multi_poly->m_polygon_list[1].m_polygon.points.push_back(Vector2f(20.f, -33.5f) * scale);
		multi_poly->m_polygon_list[1].setAABB(m_referential);
	}

	((MultiPolygonCollider*)m_collider)->m_polygon_list.push_back(PolygonCollider());
	{
		MultiPolygonCollider* multi_poly = ((MultiPolygonCollider*)m_collider);
		multi_poly->m_polygon_list[2].m_polygon.points.push_back(Vector2f(0.f, 0.f) * scale);
		multi_poly->m_polygon_list[2].m_polygon.points.push_back(Vector2f(33.5f, -57.5f) * scale);
		multi_poly->m_polygon_list[2].m_polygon.points.push_back(Vector2f(33.5f, 20.f) * scale);
		multi_poly->m_polygon_list[2].setAABB(m_referential);
	}

	((MultiPolygonCollider*)m_collider)->m_polygon_list.push_back(PolygonCollider());
	{
		MultiPolygonCollider* multi_poly = ((MultiPolygonCollider*)m_collider);
		multi_poly->m_polygon_list[3].m_polygon.points.push_back(Vector2f(0.f, 0.f) * scale);
		multi_poly->m_polygon_list[3].m_polygon.points.push_back(Vector2f(57.5f, 33.5f) * scale);
		multi_poly->m_polygon_list[3].m_polygon.points.push_back(Vector2f(-20.f, 33.5f) * scale);
		multi_poly->m_polygon_list[3].setAABB(m_referential);
	}
	((MultiPolygonCollider*)m_collider)->setAABB(m_referential);
}


