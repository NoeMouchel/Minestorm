#pragma once

#include "entity.h"


class Bullet : public Entity
{
public:
	//CONSTRUCTORS - DESTRUCTORS
	Bullet(Vector2f pos, Vector2f direction, int type, Color src_color,Texture* texture_address);
	~Bullet();

	//VARIABLES
	float m_initial_life;
	float m_life;
	float m_size;
	float m_radius;

	bool m_collided;

	//FUNCTION
	void update(float) override;
	void setCollisionBox() override;
	void isDead() override;
	void draw(bool debug) override;
};