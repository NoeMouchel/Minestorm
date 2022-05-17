#include <iostream>
#include "../include/bullet.h"
#include "../include/settings.h"


Bullet::Bullet(Vector2f pos, Vector2f direction, int type, Color src_color,  Texture* texture_address)
{
	m_texture = texture_address;
	m_referential.o = pos;
	m_referential.j = direction;
	m_referential.i = direction.rotate(-PI / 2);
	m_color = src_color;
	

	if (type == B_PLAYER_BULLET)
	{
		m_speed = PLAYER_BULLET_SPEED;
		m_life = m_initial_life =PLAYER_BULLET_AGE;
		m_size = PLAYER_BULLET_SIZE;
		m_radius = m_size * (1.f / 16.f);
	}
	else if (type == B_FIREBALL)
	{
		m_speed = FIREBALL_SPEED;
		m_life = m_initial_life = FIREBALL_AGE;
		m_size = FIREBALL_SIZE;
		m_radius = m_size * (1.f / 16.f);
	}

	setCollisionBox();

	m_collided = false;
	m_is_alive = true;
}

void Bullet::setCollisionBox()
{
	m_collider = new CircleCollider();
	((CircleCollider*)m_collider)->m_circle = Circle(m_referential.o, m_radius);
	m_collider->setAABB();
}

Bullet::~Bullet()
{
}


void Bullet::update(float deltaTime)
{
	m_life -= BULLET_AGING * deltaTime;

	//	Update position
	m_referential.o = m_referential.o + m_referential.j * m_speed * deltaTime;

	clampReferential();

	//	Update collider
	((CircleCollider*)m_collider)->m_circle.o = m_referential.o;
	m_collider->setAABB();

	//	Update rectangle for renedering
	updateRectPos();

	isDead();
}


void Bullet::isDead()
{
	if (m_life <= 0 || m_collider->m_collided)
	{
		m_life = 0;
		m_is_alive = false;
	}
}

void Bullet::draw(bool debug)
{
	if (debug)
	{
		drawGuizmo(25);
		m_collider->draw();
	}

	Color color_to_put = m_color;
	color_to_put.a = (unsigned char)((.25f + (m_life/m_initial_life * .75f)) * 255);

	float width, height;
	height = width = m_size;
	DrawTexturePro((*m_texture), { 256 * 3 , 0 , 256 , 256 }, { m_rect.x,m_rect.y ,width,height }, { width * .5f,height * .5f }, 0, color_to_put);
}
