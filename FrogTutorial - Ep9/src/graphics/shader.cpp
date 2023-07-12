#include "shader.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <cassert>

#include <GL/glew.h>

Shader::Shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath)
{
	std::string vertexSource = read_shader_code(vertex_shader_filepath);
	std::string fragmentSource = read_shader_code(fragment_shader_filepath);
	create_program(vertexSource, fragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(m_handle);
}

void Shader::bind()
{
	glUseProgram(m_handle);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::set_uniform_float(const std::string& name, f32 f)
{
	bind();
	u32 uniform_location = get_uniform_location(name);
	glUniform1f(uniform_location, f);
}

void Shader::create_program(const std::string& vertex_shader_code, const std::string& fragment_shader_code)
{
	u32 vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);

	const char* vertex_shader_char = vertex_shader_code.c_str();
	glShaderSource(vertex_shader, 1, &vertex_shader_char, NULL);
	glCompileShader(vertex_shader);
	check_for_compilation_errors(vertex_shader);

	u32 fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* fragment_shader_char = fragment_shader_code.c_str();
	glShaderSource(fragment_shader, 1, &fragment_shader_char, NULL);
	glCompileShader(fragment_shader);
	check_for_compilation_errors(fragment_shader);

	m_handle = glCreateProgram();

	glAttachShader(m_handle, vertex_shader);
	glAttachShader(m_handle, fragment_shader);
	glLinkProgram(m_handle);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

std::string Shader::read_shader_code(const std::string& filepath)
{
	std::ifstream t(filepath);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}

void Shader::check_for_compilation_errors(u32 shader_id)
{
	i32 result;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		int lenght;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &lenght);

		char* message = (char*)_malloca(lenght * sizeof(char));
		glGetShaderInfoLog(shader_id, lenght, &lenght, message);
		std::cerr << message;

		_freea(message);
		glDeleteShader(shader_id);
		assert(false);
	}
}

u32 Shader::get_uniform_location(const std::string& uniform_name)
{
	return glGetUniformLocation(m_handle, uniform_name.c_str());
}
