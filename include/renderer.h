#pragma once
#include <raylib.h>
#include <vector>
#include "../toolBox/toolbox.h"

class Renderer
{
public:
	//CONSTRUCTOR - DESTRUCTOR
	Renderer();
	~Renderer();

	//FUNCTIONS

	void drawBackground();
	void drawForeground();

	void drawPlayerLife(float x, float y, Color color_to_put);

	//VARIABLES
	std::vector<Texture2D> m_textures;

};