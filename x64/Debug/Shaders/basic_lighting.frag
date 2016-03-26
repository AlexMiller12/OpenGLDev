#version 400
layout( quads ) in;

// This function comes right out of the author's implementation
// It's a B-spline basis evaluation via deBoor pyramid

//---------------------------------------------------------CONSTANTS:

//---------------------------------------------------------VARIABLES:

in vec3 in_position;
in vec3 in_normal;

out vec4 FragColor;

// uniform vec3 ambient;
// uniform vec3 diffuse;
// uniform vec3 specular;
uniform vec3 objectColor;

//-----------------------------------------------------------HELPERS:

//--------------------------------------------------------------MAIN:

void main()
{
	in_normal.z = abs( in_normal.z );

	vec3 ambient = objectColor * 0.1;
	vec3 diffuse = objectColor * 0.9 * in_normal.z;

	vec3 specular = vec3( 1.0 ) * 0.9 * pow( in_normal.z, 64 );

	FragColor = vec4( ambient + diffuse + specular, 1.0 );	
}