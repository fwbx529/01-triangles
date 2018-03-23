#version 450 core

uniform sampler2D myTextureSampler;
in vec2 pos;

void main()
{
	vec2 UV = pos;
	gl_FragColor = texture( myTextureSampler, gl_PointCoord );
	if ( gl_FragColor.x > 0.9 && gl_FragColor.y > 0.9 && gl_FragColor.z > 0.9 ) gl_FragColor.w = 0;
}
