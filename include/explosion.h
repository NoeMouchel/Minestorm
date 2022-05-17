#pragma once

#include "effect.h"


class Explosion : public Effect
{
public:
	//CONSTRUCTORS - DESTRUCTORS
	Explosion(Referential2 ref, float life, float speed, int density, Texture* texture,Color src_color, bool disperse);
	~Explosion();

	//VARIABLES

	//FUNCTION
	void update(float) override;
};