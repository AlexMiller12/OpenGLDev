#version 430

layout (std430, binding=2) buffer valenceBuffer
{ 
  int valence[];
};

//---------------------------------------------------------VARIABLES:

in vec3 in_position;
in float in_vertexID;

out vec3 v_position;
// out float v_vertexID;
out vec4 v_color;
// out vec3 v_color;

//--------------------------------------------------------------MAIN:

void main()
{
	v_position = in_position;	
	int vertexID = int( in_vertexID );
	int valence = valence[1 + vertexID * 2];
	
	v_color = vec4( 0 );
	if( valence == 3 )
	{
		v_color = vec4( 1 );
	}
	if( valence == 4 )
	{
		v_color = vec4( 1, 0, 0, 1 );
	}
	gl_Position = vec4( in_position, 1.0 );	
};