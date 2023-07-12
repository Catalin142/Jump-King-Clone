#include "input.h"

#include "window.h"

#include <iostream>
#include <GLFW/glfw3.h>

std::unordered_map<u32, bool> Input::buttons;

void Input::init(Window* window)
{
	glfwSetKeyCallback(window->get_native_window(), Input::callback);
}

void Input::callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Input::buttons[key] = (action != GLFW_RELEASE);
}
