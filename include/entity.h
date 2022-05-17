#pragma once

#include "gameObject.h"
#include "boxCollider.h"
#include "polygonCollider.h"
#include "multiPolygonCollider.h"
#include "circleCollider.h"

class Entity : public GameObject
{
public:
	//CONSTRUCTORS - DESTRUCTORS
	Entity() = default;
	 ~Entity();

	//VARIABLES
	bool	m_is_alive;

	float	m_speed;
	float	m_angle;
	float	m_rotation;

	Collider* m_collider;
	Color m_color;
	
	//FUNCTIONS
	void setDirectionRad(); 
	void setDirectionDeg();
	Vector2f getShortestDirection(Vector2f target);

	virtual void isDead();
	virtual void setCollisionBox();
};