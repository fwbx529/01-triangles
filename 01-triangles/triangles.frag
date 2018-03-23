#version 450 core

uniform sampler2D myTextureSampler;
in vec2 pos;
out vec4 fcolor;

void main()
{
	vec2 UV = pos;
	fcolor = texture( myTextureSampler, gl_PointCoord );
	if ( fcolor.x > 0.9 && fcolor.y > 0.9 && fcolor.z > 0.9 ) fcolor.w = 0;
}
