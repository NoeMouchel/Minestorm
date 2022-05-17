#pragma once
#include "mine.h"

class FloatingMine : public Mine
{
public:
	FloatingMine(Vector2f pos,  Vector2f dir, int size, Texture* texture_address);
	~FloatingMine() {};

	void setCollisionBox() override;
};