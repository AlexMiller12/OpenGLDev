#version 450

//---------------------------------------------------------VARIABLES:

in vec3 g_normal;
in vec3 g_triangleDistance;
in vec3 g_patchDistance;

out vec4 out_fragColor;

// uniform vec3 ambient;
// uniform vec3 diffuse;
// uniform vec3 specular;
uniform vec3 u_objectColor;

//-----------------------------------------------------------HELPERS:

//--------------------------------------------------------------MAIN:

void main()
{
	vec3 normal = g_normal;
	normal.z = abs( normal.z );

	vec3 ambient = u_objectColor * 0.1;
	vec3 diffuse = u_objectColor * 0.9 * normal.z;

	vec3 specular = vec3( 1.0 ) * 0.9 * pow( normal.z, 64 );

	out_fragColor = vec4( ambient + diffuse + specular, 1.0 ) + vec4(4.0);	
}