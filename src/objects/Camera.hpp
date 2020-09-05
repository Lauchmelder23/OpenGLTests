#pragma once

#include <glm/glm.hpp>

#include "Shader.hpp"

class Camera
{
public:
	Camera() = default;
	Camera(glm::vec3 position, glm::vec3 target);

	void SetPosition(glm::vec3 newPos);
	void SetTarget(glm::vec3 newTarget);

	void Move(glm::vec3 movement);

	void Use(const Shader& program);

private:
	void CalculateCamera();

	glm::vec3 position, target;
	glm::vec3 direction, up, right;

	glm::mat4 viewMatrix;
};