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

	void set_uniform_float(const std::string& name, f32 f);
	void set_uniform_int(const std::string& name, i32 i);

private:
	void create_program(const std::string& vertex_shader_code, const std::string& fragment_shader_code);
	std::string read_shader_code(const std::string& filepath);
	void check_for_compilation_errors(u32 shader_id);

	u32 get_uniform_location(const std::string& uniform_name);

private:
	u32 m_handle;

};