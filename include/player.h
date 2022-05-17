#pragma once

#include "entity.h"
#include "bullet.h"



class Player : public Entity
{
public:
	//CONSTRUCTORS - DESTRUCTORS
	Player(float x, float y, Color playercolor, Texture* texture_address);
	~Player();

	//VARIABLES
	Vector2f m_spawn_pos;
	Vector2f m_impulsion_direction;
	Vector2f m_velocity;
	Vector2f m_force;

	bool m_can_propulse;
	bool m_can_shoot;
	bool m_can_teleport;

	bool m_propulse;
	bool m_teleport;
	bool m_shoot;

	float m_drag = .05f;
	float m_impulsion_force;
	float m_shoot_timer = 0;
	float m_teleport_timer = 0;

	int m_life;
	std::vector<Bullet*> m_bullet_list;

	//FUNCTIONS
	void setCollisionBox() override;
	void update(float) override;
	void updateBullets(float deltaTime);

	void displacement(float);
	void rotateLeft(float deltaTime);
	void rotateRight(float deltaTime);

	void shoot(float deltaTime);
	void teleport(float deltaTime);

	void reset();
	void eraseBullet();

	void draw(bool debug) override;
	void isDead() override;
};