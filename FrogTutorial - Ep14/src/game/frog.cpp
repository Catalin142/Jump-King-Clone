#include "frog.h"

#include "GLFW/glfw3.h"

Frog::Frog()
{
	texture = new Texture("res/textures/frog.png");
}

Frog::~Frog()
{
	delete texture;
}

void Frog::update(f32 delta_time, GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position.x += 100.0f * delta_time;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position.x -= 100.0f * delta_time;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position.y += 100.0f * delta_time;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position.y -= 100.0f * delta_time;
}
