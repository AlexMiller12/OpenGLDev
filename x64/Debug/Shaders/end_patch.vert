#version 430

//---------------------------------------------------------VARIABLES:

in vec3 in_position;
in float in_vertexID;

out vec3 v_position;
out float v_vertexID;
// out vec3 v_color;

//--------------------------------------------------------------MAIN:

void main()
{
	v_position = in_position;	
	if( in_vertexID > 1 )
	{
		v_vertexID = 1;
	}
	else
	{
		v_vertexID = 0;
	}
	gl_Position = vec4( in_position, 1.0 );	
};