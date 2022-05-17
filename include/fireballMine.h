#pragma once
#include "mine.h"

class FireballMine : public Mine
{
public:
	FireballMine(Vector2f pos, Vector2f dir, int size, Texture* texture_address);
	~FireballMine() {};

	void setCollisionBox() override;
};