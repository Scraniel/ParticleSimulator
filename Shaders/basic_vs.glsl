#version 330
layout( location = 0 ) in vec3 vert_modelSpace;
layout( location = 1 ) in vec3 vert_color;

uniform mat4 MVP;

out vec3 interpolateColor;

void main()
{
	gl_Position = MVP * vec4( vert_modelSpace, 1.0 );
	interpolateColor = vert_color;
}
