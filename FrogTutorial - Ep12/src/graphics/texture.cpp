#include "texture.h"

#include <iostream>

#include "GL/glew.h"
#include "std_image.h"

Texture::Texture(const std::string& filepath)
{
	i32 bbp;
	stbi_set_flip_vertically_on_load(true);

	stbi_uc* tex_data = nullptr;
	tex_data = stbi_load(filepath.c_str(), &width, &height, &bbp, 0);
	if (tex_data == nullptr)
		std::cerr << "Image doesn't exist\n";

	u32 internal_format = 0, format = 0;
	switch (bbp)
	{
	case 3:
		internal_format = GL_RGB8;
		format = GL_RGB;
		break;

	case 4:
		internal_format = GL_RGBA8;
		format = GL_RGBA;
		break;
	}

	glGenTextures(1, &m_handle);
	glBindTexture(GL_TEXTURE_2D, m_handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, tex_data);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(tex_data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_handle);
}

void Texture::bind(int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_handle);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
