#version 460 core

out vec4 fragmentColor;

in vec2 textureCoords;
in vec3 vertexCoords;

uniform sampler2D lauch;

void main()
{
	fragmentColor = texture(lauch, textureCoords);
}