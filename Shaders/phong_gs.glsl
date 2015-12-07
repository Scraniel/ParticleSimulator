#version 330 core

layout( triangles ) in;
layout( triangle_strip, max_vertices = 3 ) out;

uniform mat4 V;
uniform mat4 M;

in VertexData
{
    vec3 position_worldSpace;
    vec3 eyeDirection_cameraSpace;
    vec3 lightDirection_cameraSpace;
	vec3 color;
} inVertex[];

out VertexData
{
    vec3 position_worldSpace;
    vec3 normal_cameraSpace;
    vec3 eyeDirection_cameraSpace;
    vec3 lightDirection_cameraSpace;
	vec3 color;
} outVertex;

void main()
{
	vec3 norm_modelSpace = cross(
	(inVertex[1].position_worldSpace - inVertex[0].position_worldSpace),
		(inVertex[2].position_worldSpace - inVertex[0].position_worldSpace)
		);
	
	norm_modelSpace = normalize(norm_modelSpace);
	
	// No scaling so OK, but use inverse-transpose of MV otherwise
	// Careful of the 0 for vector transform
	vec3 normal_cameraSpace = (V * M * vec4( norm_modelSpace, 0.0 )).xyz;
	
	
//vertex 0
	outVertex.normal_cameraSpace = normal_cameraSpace;
	outVertex.position_worldSpace = inVertex[0].position_worldSpace;
	outVertex.eyeDirection_cameraSpace = inVertex[0].eyeDirection_cameraSpace;
	outVertex.lightDirection_cameraSpace = inVertex[0].lightDirection_cameraSpace;
	outVertex.color = inVertex[0].color;
	gl_Position	= gl_in[0].gl_Position;
	EmitVertex();
	
//vertex 1
	outVertex.normal_cameraSpace = normal_cameraSpace;
	outVertex.position_worldSpace = inVertex[1].position_worldSpace;
	outVertex.eyeDirection_cameraSpace = inVertex[1].eyeDirection_cameraSpace;
	outVertex.lightDirection_cameraSpace = inVertex[1].lightDirection_cameraSpace;
	outVertex.color = inVertex[1].color;
	gl_Position	= gl_in[1].gl_Position;
	EmitVertex();
	
//vertex 2
	outVertex.normal_cameraSpace = normal_cameraSpace;
	outVertex.position_worldSpace = inVertex[2].position_worldSpace;
	outVertex.eyeDirection_cameraSpace = inVertex[2].eyeDirection_cameraSpace;
	outVertex.lightDirection_cameraSpace = inVertex[2].lightDirection_cameraSpace;
	outVertex.color = inVertex[2].color;
	gl_Position	= gl_in[2].gl_Position;
	EmitVertex();
	
	EndPrimitive();
}