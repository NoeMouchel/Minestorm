#include <iostream>
#include "../include/entities.h"
#include "../include/settings.h"

Entities::Entities()
{
	m_angle = 0;
	m_rotation = 0;
}

Entities::~Entities()
{
	delete m_collider;
}

void Entities::setDirection()
{
	//Set the direction vector of the entity
	//m_referential.j.rotate(m_rotation * PI_CONVERT);
	m_referential.setAngle(m_rotation * PI_CONVERT);
	m_angle += m_rotation;
	m_rotation = 0;
}

float Entities::loopingClamp(float x, float min, float max)
{
	//if the float reach a limit it goes to the opposite side
	if (x > max)
		return min;
	if (x < min)
		return max;
	return x;
}

void Entities::update(float deltatime)
{}


