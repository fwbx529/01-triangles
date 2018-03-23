
#version 450 core

layout( location = 0 ) in vec2 vPosition;
out vec2 pos;
uniform float time;

void
main()
{
	pos = vPosition;
    gl_Position = vec4( vPosition, 1, 1 );
	gl_Position.y = gl_Position.y - time/500;
	if ( gl_Position.y < -1 ) gl_Position.y += 2;
}
