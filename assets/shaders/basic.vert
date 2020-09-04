#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 VertexColor;
out vec2 TexCoord;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	VertexColor = aCol;
	TexCoord = aTex;
}