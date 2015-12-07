#version 330
layout( location = 0 ) in vec3 vert_modelSpace;
layout( location = 1 ) in vec3 vert_colour;
layout( location = 2 ) in vec3 normals;

uniform mat4 MVP;
uniform mat4 M;

out vec3 light_worldspace;
out vec3 normal_worldspace;
out vec3 eye_worldspace;
out vec3 colour;

void main()
{	
	//gl_Position = MVP * vec4( vert_ModelSpace, 1.0 );


	vec3 vert_worldspace = (M*(vec4(vert_modelSpace,1.0))).xyz;
	light_worldspace = vec3(3.0,1.0,10.0) - vert_worldspace;
	normal_worldspace = (M*vec4(normals,0.0)).xyz;
	
	colour = vert_colour;

	eye_worldspace = vec3(0.0,0.0,0.0) - vert_worldspace;
	eye_worldspace = normalize(eye_worldspace);

	gl_Position = MVP * vec4( vert_modelSpace, 1.0 );
	

}
