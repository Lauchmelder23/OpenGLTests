#include "Texture.hpp"

#include <string>
#include <iostream>

#include <glad/glad.h>
#include <stb_image.h>

Texture::Texture(const char* name) :
	width(0), height(0), nrChannels(0), ID(0)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load((TEXTURE_DIR + std::string(name)).c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture: " << name << std::endl;
	}
	

	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &ID);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}
