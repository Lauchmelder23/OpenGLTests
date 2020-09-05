#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 target) :
	position(position), target(target)
{
	CalculateCamera();
}

void Camera::SetPosition(glm::vec3 newPos)
{
	position = newPos;
	CalculateCamera();
}

void Camera::SetTarget(glm::vec3 newTarget)
{
	target = newTarget;
	CalculateCamera();
}

void Camera::Move(glm::vec3 movement)
{
	position += movement;
	CalculateCamera();
}

void Camera::Use(const Shader& program)
{
	program.SetUniformMat4("view", &viewMatrix[0][0]);
}

void Camera::CalculateCamera()
{
	direction = glm::normalize(target - position);
	right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), direction));
	up = glm::cross(direction, right);

	viewMatrix = glm::lookAt(position, target, up);
}
