#version 430

layout (std430) buffer vertexData
{ 
  float vbo[];
};

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

	if( vertexID == 6 )
	{
		int valence = valence[1 + vertexID * 2];
		int neighborX = neighborIndices[valence * 3];
		int neighborY = neighborIndices[valence * 3 + 1];
		int neighborZ = neighborIndices[valence * 3 + 2];
		v_color = vec4( neighborX, neighborY, neighborZ, 1 );
	}
	else
	{
		vec4 position = vec4( vbo[vertexID * 3],
							  vbo[vertexID * 3 + 1],
							  vbo[vertexID * 3 + 2],
							  1 );
		v_color = position;// + vec4( 2,2,2,1 );
		// v_color = v_color / 4;
		// v_color = vec4(1);
	}
	
	gl_Position = vec4( in_position, 1.0 );	
};