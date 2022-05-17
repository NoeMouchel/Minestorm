#pragma once

#include "../toolBox/toolbox.h"
#include <vector>

class AABB
{
public:
	AABB() { m_box = { 0, 0, 0 }; m_collided = false; };
	~AABB() {};

	Box		m_box;
	bool m_collided;
	void constructBox(Range2 x_range, Range2 y_range);
	void draw();

};


