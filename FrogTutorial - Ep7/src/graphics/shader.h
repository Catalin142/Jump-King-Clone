#pragma once
#include "core/core.h"
#include <string>

class Shader
{
public:
	Shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath);
	~Shader();

	void bind();
	void unbind();

private:
	void create_program(const std::string& vertex_shader_code, const std::string& fragment_shader_code);
	std::string read_shader_code(const std::string& filepath);
	void check_for_compilation_errors(u32 shader_id);

private:
	u32 m_handle;

};