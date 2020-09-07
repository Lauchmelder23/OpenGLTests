#version 460 core

in vec2 vertexUV;

out vec4 fragmentColor;

uniform sampler2D modelTexture;

void main()
{
	fragmentColor = texture(modelTexture, vertexUV);
}