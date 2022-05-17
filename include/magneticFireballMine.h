#pragma once
#include "mine.h"

class MagneticFireballMine : public Mine
{
public:
	MagneticFireballMine(Vector2f pos, Vector2f dir, int size, Texture* texture_address);
	~MagneticFireballMine() {};
	void setCollisionBox() override;
};