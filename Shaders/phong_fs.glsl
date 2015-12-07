#version 330 core

in VertexData
{
    vec3 position_worldSpace;
    vec3 normal_cameraSpace;
    vec3 eyeDirection_cameraSpace;
    vec3 lightDirection_cameraSpace;
	vec3 color;
} inVertex;

out vec3 color;

void main()
{
	{
		vec3 diffuseColor = inVertex.color;
		const vec3 specularColor = vec3( 0.5, 0.5, 0.5 );
		const vec3 ambientColor = vec3( 0.1, 0.1, 0.1 );
		
		vec3 n = normalize( inVertex.normal_cameraSpace );
		vec3 l = normalize( inVertex.lightDirection_cameraSpace );
//		
//		if( !gl_FrontFacing )
//		{
//			n = -n;
//		}
		
		vec3 e = normalize( inVertex.eyeDirection_cameraSpace );
		vec3 r = reflect( -l, n);
		
		float cosAlpha = clamp( dot( e, r ), 0, 1 );
		float cosTheta = clamp( dot( n, l ), 0, 1 );
		
		
		color = ambientColor + diffuseColor * 0.25 +
		diffuseColor * cosTheta;// +
		//specularColor * pow( cosAlpha, 128);

	}
}
