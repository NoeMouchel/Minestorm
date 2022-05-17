#pragma once
#include "gameObject.h"

class SpawnPoint : public GameObject
{
public:
	SpawnPoint(Vector2f pos, Texture* texture_address);
	SpawnPoint(Vector2f pos, Vector2f target, Texture* texture_address);
	~SpawnPoint() {};

	bool m_placed;
	Vector2f m_target;

	void update(float deltaTime) override;
	void draw(bool debug) override;
};