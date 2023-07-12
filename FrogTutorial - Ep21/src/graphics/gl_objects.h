#pragma once
#include "core/core.h"

#include <vector>

class VertexBuffer
{
public:
	VertexBuffer(u32 size, const void* data);
	~VertexBuffer();

	void set_data(u32 size, const void* data);

	void bind();
	void unbind();

private:
	u32 m_handle;
};

class IndexBuffer
{
public:
	IndexBuffer(u32 size, const void* data);
	~IndexBuffer();

	void bind();
	void unbind();

private:
	u32 m_handle;
};

struct BatchAttribute {
	BatchAttribute(u32 s, u32 o) : size(s), offset(o) { }
	u32 size, offset;
};

// takes ownership
class VertexArray
{
public:
	VertexArray() = default;
	~VertexArray();

	void init(VertexBuffer* vbo, IndexBuffer* ibo);
	void set_layout(u32 size, const std::vector<BatchAttribute>& atb);

	void bind();
	void unbind();

private:
	u32 m_handle = 0;
	VertexBuffer* m_vbo = nullptr;
	IndexBuffer* m_ibo = nullptr;
};