#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 direction) :
	position(position), direction(direction)
{
	CalculateCamera();
}

Camera::Camera(glm::vec3 position, glm::vec2 pitchYaw) :
	position(position), direction(
		glm::vec3(
			cos(glm::radians(pitchYaw.y)) * cos(glm::radians(pitchYaw.x)),
			sin(glm::radians(pitchYaw.x)),
			sin(glm::radians(pitchYaw.y)) * cos(glm::radians(pitchYaw.x))
		)
	)
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
	direction = glm::vec3(
		cos(glm::radians(pitchYaw.y)) * cos(glm::radians(pitchYaw.x)),
		sin(glm::radians(pitchYaw.x)),
		sin(glm::radians(pitchYaw.y)) * cos(glm::radians(pitchYaw.x))
	);
	CalculateCamera();
}

void Camera::Rotate(glm::vec2 pitchYaw)
{
	direction += glm::vec3(
		cos(glm::radians(pitchYaw.y)) * cos(glm::radians(pitchYaw.x)),
		sin(glm::radians(pitchYaw.x)),
		sin(glm::radians(pitchYaw.y)) * cos(glm::radians(pitchYaw.x))
	);
	CalculateCamera();
}

void Camera::Use(const Shader& program)
{
	program.SetUniformMat4("view", &viewMatrix[0][0]);
}

void Camera::CalculateCamera()
{
	front = glm::normalize(direction);
	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	// right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), front));
	up = glm::cross(right, front);

	viewMatrix = glm::lookAt(position, position + front, up);
}
