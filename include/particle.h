#pragma once

#include "gameObject.h"


class Particle : public GameObject
{
public:
	//CONSTRUCTORS - DESTRUCTORS
	Particle(Referential2 ref, float speed, float life, int size, Texture* texture ,Color src_color);
	~Particle();

	//VARIABLES
	float m_initial_life;
	float m_life;

	float m_initial_speed;
	float m_speed;

	float m_size;

	bool m_is_alive;

	Color m_color;

	//FUNCTION
	void update(float);
	void draw(bool debug) override;
};