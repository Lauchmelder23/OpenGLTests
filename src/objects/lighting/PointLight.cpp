#include "PointLight.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

unsigned int PointLight::VAO = 0;
unsigned int PointLight::VBO = 0;
unsigned int PointLight::EBO = 0;

const float PointLight::vertices[8 * 3] = {
		-1.0f, 1.0f, 1.0f,			// Front Top Left
		1.0f, 1.0f, 1.0f,			// Front Top Right
		1.0f, -1.0f, 1.0f,			// Front Bottom Right
		-1.0f, -1.0f, 1.0f,			// Front Bottom Left
		-1.0f, 1.0f, -1.0f,			// Back Top Left
		1.0f, 1.0f, -1.0f,			// Back Top Right
		1.0f, -1.0f, -1.0f,			// Back Bottom Right
		-1.0f, -1.0f, -1.0f,		// Back Bottom Left
};

const unsigned int PointLight::indices[6 * 2 * 3] = {
		0, 1, 3,	// Front
		1, 2, 3,
		4, 5, 7,	// Back
		5, 6, 7,
		4, 5, 0,	// Top
		5, 1, 0,
		7, 6, 3,	// Bottom
		6, 2, 3,
		4, 0, 7,	// Left
		0, 3, 7,
		1, 5, 2,
		5, 6, 2
};

PointLight::PointLight(glm::vec3 position, glm::vec3 color, float intensity) :
	position(position), color(color), intensity(intensity),
	transformation(1.0f)
{
	if (VAO == 0)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	transformation = glm::translate(transformation, position);
	transformation = glm::scale(transformation, glm::vec3(0.05f));
}

void PointLight::Draw(const Shader& program)
{
	program.SetUniformFloat3("color", &color[0]);
	program.SetUniformMat4("model", &transformation[0][0]);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glDrawElements(GL_TRIANGLES, 3 * 6 * 2, GL_UNSIGNED_INT, 0);
}
