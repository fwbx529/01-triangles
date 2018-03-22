#version 450 core

uniform sampler2D myTextureSampler;
in vec2 pos;

void main()
{
	vec2 UV = pos;
	gl_FragColor = texture( myTextureSampler, gl_PointCoord );
}
