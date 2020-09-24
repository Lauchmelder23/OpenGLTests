#version 410 core

in vec2 vertexUV;

out vec4 fragmentColor;

uniform sampler2D modelTexture;
uniform vec3 lightColor;

void main()
{
	fragmentColor = texture(modelTexture, vertexUV) * vec4(lightColor, 1.0f);
}