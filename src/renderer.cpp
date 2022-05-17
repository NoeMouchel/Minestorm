#include <iostream>
#include "../include/renderer.h"
#include "../include/settings.h"

Renderer::Renderer()
{
	//Texture loading
	m_textures.push_back(LoadTexture("assets/Images/minestorm_darkbackground.png"));
	m_textures.push_back(LoadTexture("assets/Images/minestorm_lightforground.png"));
	m_textures.push_back(LoadTexture("assets/Images/minestorm_sprite_atlas_mine_storm.png"));
}

Renderer::~Renderer()
{
	std::cout << "unloading textures" << std::endl;
	//unload textures
	for (int i = 0; i < T_COUNT; i++)
	{
		UnloadTexture(m_textures[i]);
	}
	m_textures.clear();
}

void Renderer::drawBackground()
{
	DrawTexture(m_textures[T_BACKGROUND], 0, 0, WHITE);
}

void Renderer::drawForeground()
{
	DrawTexture(m_textures[T_FOREGROUND], 0, 0, WHITE);
}

void  Renderer::drawPlayerLife(float x, float y, Color color_to_put)
{
	DrawTexturePro(m_textures[T_SPRITE], { 0 , 0 , 256 , 256 }, { x , y , 48 , 48}, { 48* .5f, 48* .5f }, 0 , color_to_put);
}


