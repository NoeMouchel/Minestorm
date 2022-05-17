#pragma once
#include "mine.h"

class MagneticMine : public Mine
{
	public:
		MagneticMine(Vector2f pos,  Vector2f dir, int size, Texture* texture_address);
		~MagneticMine() {};

		void setCollisionBox() override;
};