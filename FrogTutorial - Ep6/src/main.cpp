#include <iostream>

#include <cinttypes>

#include "core/window.h"

#include "graphics/shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main()
{
	Window* window = new Window(1600, 900, "FrogTutorial");

	float vertices[] = {
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	uint32_t VBO;
	glCreateBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	uint32_t indices[] = { 
		0, 1, 3,
		1, 2, 3 
	};

	uint32_t IBO;
	glCreateBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	uint32_t VAO;
	glCreateVertexArrays(1, &VAO);
	
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Shader shader("res/shaders/quad_vertex.glsl", "res/shaders/quad_fragment.glsl");

	while (window->opened)
	{
		glClearColor(0.2f, 0.8f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.bind();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		window->pool_events();
	}

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	
	delete window;

	return 0;
}