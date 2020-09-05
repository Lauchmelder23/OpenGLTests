#pragma once

#include "Shader.hpp"

#include <glm/glm.hpp>

class Cube
{
public:
	static const float VERTICES[36 * (3 + 2)]; 
public:
	Cube(glm::vec3 position, glm::vec3 sidelengths);
	~Cube();

	void Draw(const Shader& program);

	// These should probably all go in a base class
	void ResetTransformation();
	void Move(glm::vec3 movement);
	void Rotate(float angleInRad, glm::vec3 axis);
	void Scale(glm::vec3 scaling);

	const float* GetMatrix() const;

private:
	static unsigned int VAO, VBO;

	glm::mat4 transformation;
};