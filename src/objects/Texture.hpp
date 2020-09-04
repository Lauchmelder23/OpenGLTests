#pragma once

#define TEXTURE_DIR "assets/textures/"

class Texture
{
public:
	Texture(const char* name);
	~Texture();

	void Bind();

private:
	int width, height, nrChannels;

public:
	unsigned int ID;
};