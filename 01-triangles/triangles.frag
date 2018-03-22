#version 450 core

layout (location = 0) out vec4 fColor;
uniform sampler2D myTextureSampler;
in vec2 pos;

void main()
{
	vec2 UV = pos;
	vec3 color = texture( myTextureSampler, UV ).rgb;
	fColor = vec4( color, 1.0 );
}
