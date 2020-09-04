#version 460 core

in vec3 VertexColor;
in vec2 TexCoord;

out vec4 fragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float t;

void main()
{
	fragColor = mix(
		texture(texture1, TexCoord + vec2(t, 0)), 
		texture(texture2, TexCoord + vec2(0, t)), 0.5) * vec4(VertexColor, 
		1.0
	);
}