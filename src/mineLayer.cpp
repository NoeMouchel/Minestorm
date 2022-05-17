#include <iostream>
#include "../include/mineLayer.h"
#include "../include/settings.h"

Minelayer::Minelayer(Texture* texture_address)
{
	m_texture = texture_address;


	m_color = RED;
	m_life = 10;
	m_referential.o = { randRange({ 0 + 75,WINDOW_WIDTH - 75 }), randRange({ 0 + 75,WINDOW_HEIGHT - 75 }) };
	m_referential.i = { 1,0 };
	m_referential.j = { 0,-1 };
	m_has_target = false;
	m_on_target = true;
	m_speed = MINELAYER_SPEED;
	setRectangle(SIZE_BIG, SIZE_BIG);
	setCollisionBox();
}



void Minelayer::setCollisionBox()
{
	float scale = m_rect.width / SIZE_BIG;
	m_collider = new MultiPolygonCollider();

	//CENTER PIC
	((MultiPolygonCollider*)m_collider)->m_polygon_list.push_back(PolygonCollider());
	{
		MultiPolygonCollider* multi_poly = ((MultiPolygonCollider*)m_collider);
		multi_poly->m_polygon_list[0].m_polygon.points.push_back(Vector2f(0.f, 30.f) * scale);
		multi_poly->m_polygon_list[0].m_polygon.points.push_back(Vector2f(-27.f, 7.5f) * scale);
		multi_poly->m_polygon_list[0].m_polygon.points.push_back(Vector2f(27.f, 7.5f) * scale);
		multi_poly->m_polygon_list[0].setAABB(m_referential);
	}

	//CENTER RECT
	((MultiPolygonCollider*)m_collider)->m_polygon_list.push_back(PolygonCollider());
	{
		MultiPolygonCollider* multi_poly = ((MultiPolygonCollider*)m_collider);
		multi_poly->m_polygon_list[1].m_polygon.points.push_back(Vector2f(-80.f, 7.5f) * scale);
		multi_poly->m_polygon_list[1].m_polygon.points.push_back(Vector2f(-80.f, -12.5f) * scale);
		multi_poly->m_polygon_list[1].m_polygon.points.push_back(Vector2f(80.f, -12.5f) * scale);
		multi_poly->m_polygon_list[1].m_polygon.points.push_back(Vector2f(80.f, 7.5f) * scale);
		multi_poly->m_polygon_list[1].setAABB(m_referential);
	}

	//LEFT PIC
	((MultiPolygonCollider*)m_collider)->m_polygon_list.push_back(PolygonCollider());
	{
		MultiPolygonCollider* multi_poly = ((MultiPolygonCollider*)m_collider);
		multi_poly->m_polygon_list[2].m_polygon.points.push_back(Vector2f(-80.f, 7.5f) * scale);
		multi_poly->m_polygon_list[2].m_polygon.points.push_back(Vector2f(-80.f, -12.5f) * scale);
		multi_poly->m_polygon_list[2].m_polygon.points.push_back(Vector2f(-95.f, -30.f) * scale);
		multi_poly->m_polygon_list[2].setAABB(m_referential);
	}

	//RIGHT PIC
	((MultiPolygonCollider*)m_collider)->m_polygon_list.push_back(PolygonCollider());
	{
		MultiPolygonCollider* multi_poly = ((MultiPolygonCollider*)m_collider);
		multi_poly->m_polygon_list[3].m_polygon.points.push_back(Vector2f(80.f, -12.5f) * scale);
		multi_poly->m_polygon_list[3].m_polygon.points.push_back(Vector2f(80.f, 7.5f) * scale);
		multi_poly->m_polygon_list[3].m_polygon.points.push_back(Vector2f(95.f, -30.f) * scale);
		multi_poly->m_polygon_list[3].setAABB(m_referential);
	}
	((MultiPolygonCollider*)m_collider)->setAABB(m_referential);
}



void Minelayer::generatRandomPoint()
{
	if (m_has_target) return;
	
	//if not, generate a target
	m_target = { randRange({ 0 + 75,WINDOW_WIDTH - 75 }), randRange({ 0 + 75,WINDOW_HEIGHT - 75 }) };
	m_has_target = true;
	m_on_target = false;
	
}

void Minelayer::update(float deltaTime)
{
	generatRandomPoint();

	//does it have a target?
	if (m_has_target)
	{
		Vector2f dir = getShortestDirection(m_target);
		
		float angle = (float)m_referential.j.angle(dir);
		
		if (angle > .05f)
		{
			float dotproduct = dir.dot(m_referential.i);

			if (dotproduct > 0)
				m_rotation = 2.f * deltaTime;
			else if (dotproduct < 0)
				m_rotation = -2.f * deltaTime;
			
			setDirectionRad();
		}
		else
		{
			m_targeting = true;
			
			onTarget();
			if (m_on_target)
				return;
			m_referential.o = m_referential.o + m_referential.j * m_speed * deltaTime;
			m_referential.o.x = loopingClamp(m_referential.o.x, UI_PADDING, WINDOW_WIDTH - UI_PADDING);
			m_referential.o.y = loopingClamp(m_referential.o.y, UI_PADDING, WINDOW_HEIGHT - UI_PADDING);
		}	
	}
	updateRectPos();
	((MultiPolygonCollider*)m_collider)->setAABB(m_referential);

	isDead();
}


void Minelayer::isDead()
{
	if (m_collider->m_collided == false) return;

	m_collider->m_collided = false;

	m_life--;

	if (m_life <= 0)
		m_is_alive = false;
}


void Minelayer::onTarget()
{
	((MultiPolygonCollider*)m_collider)->setCollisionToFalse();
	Vector2f pointModifier = m_referential.j *0;

	m_on_target = false;
	if (intersectionPointBox(m_target + pointModifier, ((MultiPolygonCollider*)m_collider)->m_AABB.m_box))
	{
		((MultiPolygonCollider*)m_collider)->m_AABB.m_collided = true;
		for (PolygonCollider poly : ((MultiPolygonCollider*)m_collider)->m_polygon_list)
		{
			if (intersectionPointBox(m_target + pointModifier, poly.m_AABB.m_box))
			{
				poly.m_AABB.m_collided = true;
				if (intersectionConvexPoint(localToGlobalConvex(poly.m_polygon, m_referential), m_target + pointModifier))
				{
					//	Raise Minelayer speed
					m_speed += 10.f;
					m_speed = (m_speed > 500) ? 500 : m_speed;

					poly.m_collided = true;
					m_on_target = true;
					m_has_target = false;
					return;
				}
			}
		}
	}
}


void Minelayer::draw(bool debug)
{
	Color color_to_put = m_color;
	if (debug)
	{
		((MultiPolygonCollider*)m_collider)->draw(m_referential);
		DrawTexturePro((*m_texture), { 256.f * 1 , 0.f , 256.f , 256.f }, {m_target.x,m_target.y,100,100}, { 100* .5f,100 * .5f }, 0, WHITE);
		drawGuizmo(50,200);
		color_to_put.a = 150;
	}
	DrawTexturePro(*m_texture, { 256.f * 2.f , 0.f , 256.f , 256.f }, m_rect, { m_rect.width * .5f,m_rect.height * .5f }, m_angle, color_to_put);
}