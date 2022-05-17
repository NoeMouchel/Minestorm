#pragma once

#include "gameObject.h"
#include "collider.h"

class Entities : public GameObject
{
public:
	//CONSTRUCTORS - DESTRUCTORS
	Entities();
	~Entities();

	//VARIABLES
	bool	m_is_alive;
	int		m_speed;

	float	m_angle;
	float	m_rotation;

	Collider* m_collider;
	
	//FUNCTIONS
	virtual void update(float);
	float loopingClamp(float x, float min, float max);
	void setDirection();
};