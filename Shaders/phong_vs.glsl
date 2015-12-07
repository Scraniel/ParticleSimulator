#version 330
layout( location = 0 ) in vec3 vert_modelSpace;
layout( location = 1 ) in vec3 vert_color;

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;

out VertexData
{
	vec3 position_worldSpace;
	vec3 eyeDirection_cameraSpace;
	vec3 lightDirection_cameraSpace;
	vec3 color;
} outVertex;

void main()
{
	const vec3 light_worldSpace = vec3(10, 50, 50);
	
	gl_Position = MVP * vec4( vert_modelSpace, 1.0 );
	
	outVertex.position_worldSpace = (M * vec4(vert_modelSpace,1)).xyz;

	vec3 vert_cameraSpace = (V * M * vec4( vert_modelSpace, 1.0 )).xyz;
	outVertex.eyeDirection_cameraSpace = -vert_cameraSpace;

	// TODO chane light to vec4 as it never changes.

	vec3 light_cameraSpace = (V * vec4( light_worldSpace, 1 )).xyz;
	outVertex.lightDirection_cameraSpace =
		light_cameraSpace + outVertex.eyeDirection_cameraSpace;
	
	outVertex.color = vert_color;
}
