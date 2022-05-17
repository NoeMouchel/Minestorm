#include <iostream>
#include <raylib.h>
#include "../include/windowManager.h"



WindowManager::WindowManager(int width, int height, const char* title, int fps)
{
	m_width = width;
	m_height = height;

	InitWindow(m_width, m_height, title);

	InitAudioDevice();

	SetTargetFPS(60);
}

WindowManager::~WindowManager()
{
	CloseAudioDevice();
	CloseWindow();        // Close window and OpenGL context
}

void WindowManager::close()
{
	CloseAudioDevice();
	CloseWindow();        // Close window and OpenGL context
}