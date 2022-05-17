#pragma once

class WindowManager
{
public:
	//CONSTRUCTORS - DESTRUCTORS
	WindowManager(int width, int height, const char* title, int fps);

	~WindowManager();

	//FUNCITON

	void close();
	//VARIABLES

	int m_height;
	int m_width;
	char* m_title;
	int m_fps;

};