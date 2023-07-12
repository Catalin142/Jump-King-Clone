#include "gl_objects.h"

#include <iostream>
#include <cassert>
#include <GL/glew.h>

VertexBuffer::VertexBuffer(u32 size, const void* data)
{
	glCreateBuffers(1, &m_handle);

	glBindBuffer(GL_ARRAY_BUFFER, m_handle);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_handle);
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_handle);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

IndexBuffer::IndexBuffer(u32 size, const void* data)
{
	glCreateBuffers(1, &m_handle);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_handle);
}

void IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
}

void IndexBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

VertexArray::VertexArray(VertexBuffer* vbo, IndexBuffer* ibo) :
	m_vbo(vbo), m_ibo(ibo)
{
	glCreateVertexArrays(1, &m_handle);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_handle);
	delete m_vbo;
	delete m_ibo;
}

void VertexArray::set_layout(u32 size, const std::vector<BatchAttribute>& atb)
{
	if (m_vbo == nullptr || m_ibo == nullptr)
	{
		std::cerr << "VAO has no index and vertex buffers\n";
		assert(false);
	}

	m_vbo->bind();
	glBindVertexArray(m_handle);

	for (int i = 0; i < atb.size(); i++)
	{
		const BatchAttribute& currAtr = atb.at(i);
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, currAtr.size, GL_FLOAT, GL_FALSE, size * sizeof(f32), (const void*)currAtr.offset);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexArray::bind()
{
	glBindVertexArray(m_handle);
	m_ibo->bind();
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
