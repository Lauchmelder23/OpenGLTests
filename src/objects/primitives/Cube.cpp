#include "Cube.hpp"

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>

const float Cube::VERTICES[36 * (3 + 2)] = {
	-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f, -1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
	 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
	-1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,

	-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
	 1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
	-1.0f,  1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,

	-1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
	-1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
	-1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

	 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
	 1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
	 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

	-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f, -1.0f,  1.0f, 1.0f,
	 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
	 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
	-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
	-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,

	-1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
	 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
	 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
	-1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
	-1.0f,  1.0f, -1.0f,  0.0f, 1.0f
};

unsigned int Cube::VAO = 0;
unsigned int Cube::VBO = 0;

Cube::Cube(glm::vec3 position, glm::vec3 sidelengths)
{
	if (VAO == 0)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}

	ResetTransformation();
	Move(position);
	Scale(sidelengths);
}

Cube::~Cube()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void Cube::Draw(const Shader& program)
{
	program.SetUniformMat4("model", &transformation[0][0]);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::ResetTransformation()
{
	transformation = glm::mat4(1.0f);
}

void Cube::Move(glm::vec3 movement)
{
	transformation = glm::translate(transformation, movement);
}

void Cube::Rotate(float angleInRad, glm::vec3 axis)
{
	transformation = glm::rotate(transformation, angleInRad, axis);
}

void Cube::Scale(glm::vec3 scaling)
{
	transformation = glm::scale(transformation, scaling);
}

const float* Cube::GetMatrix() const
{
	return &transformation[0][0];
}
