#pragma once
#include "gameObject.h"

class Spawner : public GameObject
{
public:
//CONSTRUCTORS - DESTRUCTORS
	Spawner(Texture* texture_address);
	~Spawner() {};

//FUNCTIONS
	void update(float deltaTime) override;
	void draw(bool debug) override;
};

