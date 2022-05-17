#pragma once
#include "../toolBox/toolbox.h"

#include <raylib.h>

class GameObject
{
public:
	GameObject() = default;
	~GameObject() {};

	Referential2 m_referential;
	Rectangle m_rect; 

	Texture* m_texture;

	void setRectangle(float width, float height);
	void setRectangle(float size);

	void updateRectPos();
	virtual void draw(bool debug);
	void drawGuizmo(float scale);
	void drawGuizmo(float x_scale, float y_scale);


	float loopingClamp(float x, float min, float max);
	void clampReferential();

	virtual void update(float);
};