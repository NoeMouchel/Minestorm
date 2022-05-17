#include <iostream>
#include "../include/player.h"
#include "../include/settings.h"
#include "../toolBox/toolbox.h"


Player::Player(float x, float y, Color playercolor, Texture* texture_address)
{
	m_texture = texture_address;

	m_life = 3;
	m_speed = 0;

	m_is_alive = true;
	m_can_propulse = false;
	m_can_shoot = false;
	m_can_teleport = false;

	m_propulse = false;
	m_teleport = false;
	m_shoot = false;

	m_color = playercolor;
	m_referential = { { x, y }, { 1, 0 }, { 0, -1 }, 0 };
	m_spawn_pos = { x,y };
	m_velocity = { 0.f, 0.f };
	setRectangle(PLAYER_WIDTH, PLAYER_HEIGHT);
	setCollisionBox();
};

Player::~Player()
{
	while (!m_bullet_list.empty())
	{
		delete m_bullet_list.back();
		m_bullet_list.pop_back();
	}
};



void Player::reset()
{
	if (!m_bullet_list.empty())
	{
		for (int i = 0; i < m_bullet_list.size(); i++)
		{
			delete m_bullet_list[i];
		}
		m_bullet_list.clear();
	}

	m_referential.o = m_spawn_pos;

	updateRectPos();
	m_velocity = { 0.f, 0.f };
	m_speed = 0;
	m_is_alive = true;
}



void Player::setCollisionBox()
{
	m_collider = new MultiPolygonCollider();
	((MultiPolygonCollider*)m_collider)->m_polygon_list.push_back(PolygonCollider());
	{
		MultiPolygonCollider* multi_poly = ((MultiPolygonCollider*)m_collider);
		multi_poly->m_polygon_list[0].m_polygon.points.push_back(Vector2f(0.f, -22.f));
		multi_poly->m_polygon_list[0].m_polygon.points.push_back(Vector2f(-10.f, -25.f));
		multi_poly->m_polygon_list[0].m_polygon.points.push_back(Vector2f(-17.f, -18.f));
		multi_poly->m_polygon_list[0].m_polygon.points.push_back(Vector2f(0.f, 30.f));
		multi_poly->m_polygon_list[0].setAABB(m_referential);
	}

	((MultiPolygonCollider*)m_collider)->m_polygon_list.push_back(PolygonCollider());
	{
		MultiPolygonCollider* multi_poly = ((MultiPolygonCollider*)m_collider);
		multi_poly->m_polygon_list[1].m_polygon.points.push_back(Vector2f(0.f, -22.f));
		multi_poly->m_polygon_list[1].m_polygon.points.push_back(Vector2f(10.f, -25.f));
		multi_poly->m_polygon_list[1].m_polygon.points.push_back(Vector2f(17.f, -18.f));
		multi_poly->m_polygon_list[1].m_polygon.points.push_back(Vector2f(0.f, 30.f));
		multi_poly->m_polygon_list[1].setAABB(m_referential);
	}
	((MultiPolygonCollider*)m_collider)->setAABB(m_referential);
}



void Player::update(float deltaTime)
{
	m_teleport = false;
	m_shoot = false;

	if (m_is_alive)
	{
		displacement(deltaTime);
		shoot(deltaTime);
		teleport(deltaTime);
		isDead();
	}
	updateBullets(deltaTime);
}



void Player::displacement(float deltaTime)
{
	//	If the player is impulsed, speed isn't null
	if (m_can_propulse)
		m_speed = PLAYER_DIPLACEMENT_SPEED;

	m_velocity = m_velocity + m_referential.j * deltaTime * m_speed - m_velocity * PLAYER_DRAG;

	if (m_can_propulse)
		m_velocity = (m_velocity + m_referential.j * DRIFT).unit() * m_velocity.magnitude();
	m_speed = 0.f;

	//	Update player position
	m_referential.o = m_referential.o + m_velocity;

	//	If the player reach the border teleport to the other size
	clampReferential();

	//	Update rectangle position for the rendering
	updateRectPos();

	//	Update AABB which is isn't in the local ref
	m_collider->setAABB(m_referential);
}

void Player::updateBullets(float deltaTime)
{
	//Update all bullets
	for (int i = 0; i < m_bullet_list.size(); i++)
	{
		if (m_bullet_list[i]->m_is_alive)
			m_bullet_list[i]->update(deltaTime);
	}

	eraseBullet();
}

void Player::rotateLeft(float deltaTime)
{
	m_rotation -= 1.f * PLAYER_ROTATION_SPEED * deltaTime;
	setDirectionDeg();
}

void Player::rotateRight(float deltaTime)
{
	m_rotation += 1.f * PLAYER_ROTATION_SPEED * deltaTime;
	setDirectionDeg();
}

void Player::teleport(float deltaTime)
{
	if (m_can_teleport)
		m_teleport_timer += deltaTime;

	if (m_teleport_timer <= .5f) return;
	
	m_can_teleport = false;
	m_teleport_timer = 0;

	//Teleportation
	{
		m_referential.o = 
		{ 
			randRange({0 + 75,WINDOW_WIDTH - 75}),
			randRange({0 + 75,WINDOW_HEIGHT - 75}) 
		};

		m_velocity = { 0,0 };
	}
	m_teleport = true;
	
}

void Player::shoot(float deltaTime)
{
	m_shoot_timer += deltaTime;
	if (!m_can_shoot) return;
	
	m_can_shoot = false;
	m_shoot_timer = 0;
	
	//	Create bullet
	m_bullet_list.push_back(new Bullet(m_referential.o, m_referential.j, B_PLAYER_BULLET, m_color, m_texture));

	m_shoot = true;
	
}

void Player::isDead()
{
	if (m_collider->m_collided == false) return;
	
	//  Remove one life to the player and set the player as dead so he can respawn and restart the round
	m_life--;
	m_is_alive = false;
	
}

void Player::eraseBullet()
{
	if (m_bullet_list.empty())
		return;

	int size = (int)m_bullet_list.size();
	for (int i = 0; i < size; i++)
	{
		if (!m_bullet_list[i]->m_is_alive)
		{
			delete m_bullet_list[i];
			m_bullet_list.erase(m_bullet_list.begin() + i);
			i--;
			size--;
		}
	}
}



void Player::draw(bool debug)
{
	if (m_is_alive == true)
	{
		Color color_to_put = m_color;
		if (debug)
		{
			((MultiPolygonCollider*)m_collider)->draw(m_referential);
			drawGuizmo(50);
			color_to_put.a = 150;
		}
		DrawTexturePro((*m_texture), { 0 , 0 , 256 , 256 }, m_rect, { m_rect.width * .5f, m_rect.height * .5f }, m_angle, color_to_put);
	}

	for (Bullet* cur_bullet : m_bullet_list)
	{
		cur_bullet->draw(debug);
	}
}
