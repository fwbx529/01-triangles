
#version 450 core

layout( location = 0 ) in vec2 vPosition;
out vec2 pos;

void
main()
{
	pos = vPosition;
    gl_Position = vec4( vPosition, 1, 1 );
}
