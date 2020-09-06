#pragma once

#include <glm/glm.hpp>

#include "Shader.hpp"

// TODO: reimplement, make it better
class Camera
{
public:
	Camera() = default;
	Camera(glm::vec3 position, glm::vec2 pitchYaw);

	void SetPosition(glm::vec3 newPos);
	void Move(glm::vec3 movement);

	void SetRotation(glm::vec2 pitchYaw);
	void Rotate(glm::vec2 pitchYaw);

	void Constrain(glm::vec4 constraints);

	void Use(const Shader& program);

public:
	glm::vec3 front, up, right;

private:
	void CalculateCamera();

	glm::vec3 position;
	glm::vec2 rotation;
	glm::vec4 rotationConstraints;

	glm::mat4 viewMatrix;
};