#include "window.h"

#include <iostream>
#include <cassert>
#include <GLFW/glfw3.h>
#include <GL/glew.h>

void GLAPIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei lenght,
	const GLchar* message, const void* data)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:   std::cout << message << std::endl; assert(false);  return;
	case GL_DEBUG_SEVERITY_MEDIUM: std::cout << message << std::endl; assert(false);  return;
	default:														  return;
	}
}

Window::Window(u32 width, u32 height, const std::string& title) : 
	m_width(width), m_height(height), m_title(title)
{
	if (!glfwInit())
		std::cerr << "Glfw can not initalize\n";

	glfwWindowHint(GLFW_RESIZABLE, false);
	m_native_window = glfwCreateWindow(m_width, m_height, title.c_str(), NULL, NULL);
	glfwMakeContextCurrent(m_native_window);

	if (glewInit() != GLEW_OK)
		std::cerr << "Glew can not initalize\n";

#if DEBUG == 1
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(GLDebugMessageCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_TRUE);
#endif 

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
