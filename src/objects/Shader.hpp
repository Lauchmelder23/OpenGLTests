#pragma once

#define SHADER_DIR "assets/shaders/"

class Shader
{
public:
	static void LoadShaderSource(const char* filepath, char** buffer);

public:
	Shader(const char* vertShader, const char* fragShader);
	~Shader();

	void Use();

	void SetUniformInt(const char* uniform, int value);
	void SetUniformFloat(const char* uniform, float value);
	void SetUniformMat4(const char* uniform, const float* ptrToMatrix);

private:
	unsigned int program;
};