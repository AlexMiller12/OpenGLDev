#version 430

layout (std430) buffer valenceBuffer
{ 
  int valence[];
};

layout (std430) buffer neighborIndexBuffer
{ 
  int neighborIndices[];
};

//---------------------------------------------------------VARIABLES:

in vec3 in_position;
in float in_vertexID;

out vec3 v_position;

out vec4 v_color;

//--------------------------------------------------------------MAIN:

void main()
{
	v_position = in_position;	
	int vertexID = int( in_vertexID );
	int valence = valence[1 + vertexID * 2];

	int neighborX = neighborIndices[valence * 3];
	int neighborY = neighborIndices[valence * 3 + 1];
	int neighborZ = neighborIndices[valence * 3 + 2];
	v_color = vec4( neighborX, neighborY, neighborZ, 1 );

	// v_color = vec4(0);
	// if( vertexID == 5 )
	// {
	// 	v_color = vec4( 1 );
	// }
	
	gl_Position = vec4( in_position, 1.0 );	
};