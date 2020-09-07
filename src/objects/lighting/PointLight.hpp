#pragma once

#include <glm/glm.hpp>

#include "Shader.hpp"

class PointLight
{
public:
	static const float vertices[8 * 3];
	static const unsigned int indices[6 * 2 * 3];
public:
	PointLight(glm::vec3 position, glm::vec3 color, float intensity);
	~PointLight() = default;

	void Draw(const Shader& program);

private:
	static unsigned int VAO, VBO, EBO;

	glm::vec3 position, color;
	float intensity;

	glm::mat4 transformation;
};