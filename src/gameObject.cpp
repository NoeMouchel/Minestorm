
#include "../include/gameObject.h"
#include "../include/settings.h"


void GameObject::setRectangle(float width, float height)
{
	m_rect = { m_referential.o.x,m_referential.o.y,width,height };
}

void GameObject::setRectangle(float size)
{
	m_rect = { m_referential.o.x,m_referential.o.y,size,size };
}

void  GameObject::updateRectPos()
{
	m_rect.x = m_referential.o.x;
	m_rect.y = m_referential.o.y;
}

void GameObject::draw(bool debug)
{

}

void GameObject::drawGuizmo(float scale)
{
	//Draw Guizmo of the object referential

	Vector2 start = { m_referential.o.x , m_referential.o.y };
	Vector2 stop_i = { m_referential.i.x * scale + start.x, m_referential.i.y * scale + start.y };
	Vector2 stop_j = { m_referential.j.x * scale + start.x, m_referential.j.y * scale + start.y };

	DrawLineV(start, stop_i, RED);
	DrawLineV(start, stop_j, GREEN);
}

void GameObject::drawGuizmo(float x_scale, float y_scale)
{
	//Draw Guizmo of the object referential

	Vector2 start = { m_referential.o.x , m_referential.o.y };
	Vector2 stop_i = { m_referential.i.x * x_scale + start.x, m_referential.i.y * x_scale + start.y };
	Vector2 stop_j = { m_referential.j.x * y_scale + start.x, m_referential.j.y * y_scale + start.y };

	DrawLineV(start, stop_i, RED);
	DrawLineV(start, stop_j, GREEN);
}

float GameObject::loopingClamp(float x, float min, float max)
{
	//if the float reach a limit it goes to the opposite side
	if (x > max)
		return min;
	if (x < min)
		return max;
	return x;
}

void GameObject::clampReferential()
{
	m_referential.o.x = loopingClamp(m_referential.o.x, UI_PADDING, WINDOW_WIDTH - UI_PADDING);
	m_referential.o.y = loopingClamp(m_referential.o.y, UI_PADDING, WINDOW_HEIGHT - UI_PADDING);
}


void GameObject::update(float deltatime)
{}