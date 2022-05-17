#pragma once
#include "entity.h"

class Mine : public Entity
{
public:
	Mine() = default;
	virtual ~Mine() {};

	
	int m_type;
	int m_size;
	int m_score;

	float m_rotation_speed;

	Vector2f m_direction;

	void displacement(float deltaTime);
	void updateDirection(Vector2f target);

	int newMineSize();
	void setRect();
	void setColor();

	void update(float deltaTime) override;
	void draw(bool debug) override;
};
