#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 vertexUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);

	vertexUV = aTex;
}