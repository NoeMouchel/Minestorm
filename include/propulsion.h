#pragma once

#include "effect.h"


class Propulsion : public Effect
{
public:
	//CONSTRUCTORS - DESTRUCTORS
	Propulsion(Referential2 ref, float life, float speed, int density, Texture* texture,Color src_colore);
	~Propulsion();

	//VARIABLES

	//FUNCTION
	void update(float) override;
};