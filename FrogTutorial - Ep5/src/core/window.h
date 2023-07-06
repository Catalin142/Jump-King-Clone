#pragma once
#include "core.h"
#include <string>

struct GLFWwindow;

class Window
{
public:
	Window(u32 width, u32 height, const std::string& title);
	~Window();

	void pool_events();
	
public:
	bool opened;

private:
	GLFWwindow* m_native_window;
	
	u32 m_width, m_height;
	std::string m_title;

};