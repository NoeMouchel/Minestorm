#pragma once
#include "entity.h"
#include "spawnPoint.h"

class Minelayer : public Entity
{
public:
//CONSTRUCTORS - DESTRUCTORS
	Minelayer(Texture* texture_address);
	~Minelayer() {};

//VARIABLES
	Vector2f m_target;

	bool m_targeting;
	bool m_on_target;
	bool m_has_target;

	int m_life;

//FUNCTIONS
	void generatRandomPoint();
	void onTarget();

	void update(float deltaTime) override;
	void setCollisionBox() override;
	void isDead() override;
	void draw(bool debug) override;
};

