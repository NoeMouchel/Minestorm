#pragma once

#include "entities.h"


class Bullet : public Entities
{
public:
	//CONSTRUCTORS - DESTRUCTORS
	Bullet(Vector2f pos, Vector2f direction);
	~Bullet();

	//VARIABLES
	float m_life;
	bool m_collided;

	//FUNCTION
	void update(float) override;
};