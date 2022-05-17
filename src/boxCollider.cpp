#include <iostream>
#include "../include/boxCollider.h"
#include <raylib.h>


//Constrcut box from the two ranges
void AABB::constructBox(Range2 x_range, Range2 y_range)
{
	float width = x_range.max - x_range.min;
	float height = y_range.max - y_range.min;

	m_box.o = { x_range.min + width * .5f, y_range.min + height * .5f };
	m_box.length = height;
	m_box.width = width;
}

void AABB::draw()
{
	Color poly_color = GREEN;
	if (m_collided)
		poly_color = RED;
	poly_color.a = 150;

	DrawLineEx({ m_box.o.x - m_box.width * .5f, m_box.o.y + m_box.length * .5f }, { m_box.o.x + m_box.width * .5f, m_box.o.y + m_box.length * .5f }, 1.25f, poly_color);
	DrawLineEx({ m_box.o.x + m_box.width * .5f, m_box.o.y + m_box.length * .5f }, { m_box.o.x + m_box.width * .5f, m_box.o.y - m_box.length * .5f }, 1.25f, poly_color);
	DrawLineEx({ m_box.o.x + m_box.width * .5f, m_box.o.y - m_box.length * .5f }, { m_box.o.x - m_box.width * .5f, m_box.o.y - m_box.length * .5f }, 1.25f, poly_color);
	DrawLineEx({ m_box.o.x - m_box.width * .5f, m_box.o.y - m_box.length * .5f }, { m_box.o.x - m_box.width * .5f, m_box.o.y + m_box.length * .5f }, 1.25f, poly_color);
}
