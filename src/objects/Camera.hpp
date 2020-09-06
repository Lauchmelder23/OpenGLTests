#pragma once

#include <glm/glm.hpp>

#include "Shader.hpp"

class Camera
{
public:
	Camera() = default;
	Camera(glm::vec3 position, glm::vec3 direction);
	Camera(glm::vec3 position, glm::vec2 pitchYaw);

	void SetPosition(glm::vec3 newPos);
	void Move(glm::vec3 movement);

	void SetRotation(glm::vec2 pitchYaw);
	void Rotate(glm::vec2 pitchYaw);

	void Use(const Shader& program);

public:
	glm::vec3 front, up, right;

private:
	void CalculateCamera();

	glm::vec3 position, direction;

	glm::mat4 viewMatrix;
};