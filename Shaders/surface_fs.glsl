#version 330 core

in vec3 light_worldspace;
in vec3 normal_worldspace;
in vec3 eye_worldspace;
in vec3 reflect_worldspace;
in vec3 colour;

out vec3 color;

void main()
{

	vec3 n = normalize(normal_worldspace);
	vec3 l = normalize(light_worldspace);

	vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1);

	vec3 reflect = (n * (2*(dot(n,l)))) - l;
	reflect = normalize(reflect);
				
	float specular = max(dot(eye_worldspace, reflect), 0);
	specular = pow(specular, 75);

	
	color = MaterialAmbientColor + clamp(dot(n, l),0.0,1.0) * colour + specular*vec3(0.4, 0.4, 0.4);
}
