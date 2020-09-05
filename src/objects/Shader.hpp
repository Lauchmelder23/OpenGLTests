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

	void SetUniformInt(const char* uniform, int value) const;
	void SetUniformFloat(const char* uniform, float value) const;
	void SetUniformMat4(const char* uniform, const float* ptrToMatrix) const;

private:
	unsigned int program;
};