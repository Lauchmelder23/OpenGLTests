#include "Shader.hpp"

#include <iostream>
#include <fstream>

#include <glad/glad.h>

void Shader::LoadShaderSource(const char* filepath, char** buffer)
{
	std::string t = std::string(SHADER_DIR) + std::string(filepath);
	std::ifstream file(std::string(SHADER_DIR) + std::string(filepath));
	if (!file.good())
	{
		std::cerr << "Could not open file: " << filepath << std::endl;
		*buffer = nullptr;
		return;
	}

	std::string source(
		(std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>()
	);
	size_t size = source.size();
	*buffer = (char*)malloc(size + sizeof(char));
	if (*buffer == nullptr)
	{
		std::cerr << "Failed to allocate memory for shader source code" << std::endl;
		return;
	}

	memcpy_s(*buffer, size, source.c_str(), size);
	(*buffer)[size] = '\0';
}

Shader::Shader(const char* vertShader, const char* fragShader) :
	program(0)
{
	int success;
	char error[512];

	// Load Vertex Shader
	unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
	char* buffer;
	LoadShaderSource(vertShader, &buffer);
	if (buffer == nullptr)
		buffer = "";
	glShaderSource(vert, 1, &buffer, NULL);
	glCompileShader(vert);
	glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vert, 512, NULL, error);
		std::cerr << error << std::endl;
		return;
	}

	// Load Fragment Shader
	unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
	LoadShaderSource(fragShader, &buffer);
	if (buffer == nullptr)
		buffer = "";
	glShaderSource(frag, 1, &buffer, NULL);
	glCompileShader(frag);
	glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(frag, 512, NULL, error);
		std::cerr << error << std::endl;
		return;
	}

	// Link Shaders
	program = glCreateProgram();
	glAttachShader(program, vert);
	glAttachShader(program, frag);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, error);
		std::cerr << error << std::endl;
		return;
	}

	glDeleteShader(frag);
	glDeleteShader(vert);
}

Shader::~Shader()
{
	glDeleteProgram(program);
}

void Shader::Use()
{
	glUseProgram(program);
}

void Shader::SetUniformInt(const char* uniform, int value) const
{
	glUniform1i(glGetUniformLocation(program, uniform), value);
}

void Shader::SetUniformFloat(const char* uniform, float value) const
{
	glUniform1f(glGetUniformLocation(program, uniform), value);
}

void Shader::SetUniformMat4(const char* uniform, const float* ptrToMatrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(program, uniform), 1, GL_FALSE, ptrToMatrix);
}
