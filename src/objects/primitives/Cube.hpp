#pragma once

#include "Shader.hpp"

class Cube
{
public:
	Cube(float x, float y, float z, float a);
	~Cube();

	void Draw(const Shader& program);

private:
	unsigned int VAO, VBO, EBO;
};