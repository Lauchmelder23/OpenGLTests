#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec2 pitchYaw) :
	position(position), rotation(pitchYaw)
{
	CalculateCamera();
}

void Camera::SetPosition(glm::vec3 newPos)
{
	position = newPos;
	CalculateCamera();
}

void Camera::Move(glm::vec3 movement)
{
	position += movement;
	CalculateCamera();
}

void Camera::SetRotation(glm::vec2 pitchYaw)
{
	rotation = pitchYaw;
	CalculateCamera();
}

void Camera::Rotate(glm::vec2 pitchYaw)
{
	rotation += pitchYaw;
	if (rotation.x > 89.0f)
		rotation.x = 89.0f;
	else if (rotation.x < -89.0f)
		rotation.x = -89.0f;
	CalculateCamera();
}

void Camera::Constrain(glm::vec4 constraints)
{
	rotationConstraints = constraints;
}

void Camera::Use(const Shader& program)
{
	program.SetUniformMat4("view", &viewMatrix[0][0]);
}

void Camera::CalculateCamera()
{
	front = glm::normalize(glm::vec3(
		cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x)),
		sin(glm::radians(rotation.x)),
		sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x))
	));
	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::cross(right, front);

	viewMatrix = glm::lookAt(position, position + front, up);
}
