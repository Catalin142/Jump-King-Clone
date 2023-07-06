#include "window.h"

#include <iostream>
#include <GLFW/glfw3.h>
#include "GL/glew.h"

Window::Window(u32 width, u32 height, const std::string& title) : 
	m_width(width), m_height(height), m_title(title)
{
	if (!glfwInit())
		std::cerr << "Glfw can not initalize\n";

	glfwWindowHint(GLFW_RESIZABLE, false);
	m_native_window = glfwCreateWindow(m_width, m_height, "FrogTutorial", NULL, NULL);
	glfwMakeContextCurrent(m_native_window);

	if (glewInit() != GLEW_OK)
		std::cerr << "Glew can not initalize\n";

	glfwSwapInterval(true);
	glViewport(0, 0, m_width, m_height);

	glfwSetFramebufferSizeCallback(m_native_window, [](GLFWwindow* window, int Width, int Height) -> void
		{
			glViewport(0, 0, Width, Height);
		});

	glfwSetWindowSizeCallback(m_native_window, [](GLFWwindow* window, int Width, int Height) -> void
		{
			glViewport(0, 0, Width, Height);
		});
}

Window::~Window()
{
	glfwDestroyWindow(m_native_window);
	glfwTerminate();
}

void Window::pool_events()
{
	opened = !glfwWindowShouldClose(m_native_window);
	glfwSwapBuffers(m_native_window);
	glfwPollEvents();
}
