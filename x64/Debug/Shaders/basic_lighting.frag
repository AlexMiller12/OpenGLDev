#version 400

// This function comes right out of the author's implementation
// It's a B-spline basis evaluation via deBoor pyramid

//---------------------------------------------------------CONSTANTS:

//---------------------------------------------------------VARIABLES:

in vec3 in_position;
in vec3 in_normal;

out vec4 out_fragColor;

// uniform vec3 ambient;
// uniform vec3 diffuse;
// uniform vec3 specular;
uniform vec3 u_objectColor;

//-----------------------------------------------------------HELPERS:

//--------------------------------------------------------------MAIN:

void main()
{
	vec3 normal = in_normal;
	normal.z = abs( normal.z );

	vec3 ambient = u_objectColor * 0.1;
	vec3 diffuse = u_objectColor * 0.9 * in_normal.z;

	vec3 specular = vec3( 1.0 ) * 0.9 * pow( normal.z, 64 );

	out_fragColor = vec4( ambient + diffuse + specular, 1.0 ) + vec4(1.0);	
}