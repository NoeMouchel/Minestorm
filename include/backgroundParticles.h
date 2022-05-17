#pragma once

#include "particle.h"


class BackgroundParticle
{
public:
	//CONSTRUCTORS - DESTRUCTORS
	BackgroundParticle() = default;
	BackgroundParticle(int density, Texture* texture, Color src_color);
	~BackgroundParticle() {};

	//VARIABLES

	std::vector<Particle> m_particle_list;
	Texture* m_texture;
	Color m_color;

	//FUNCTION
	void createParticule(Color src_color);
	void update(float);
	void draw();
};