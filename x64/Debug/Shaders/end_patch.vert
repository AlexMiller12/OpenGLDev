#version 430

//---------------------------------------------------------VARIABLES:

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

in vec3 in_position;
in float in_vertexID;

out vec3 v_position;

out vec4 v_color;

//-----------------------------------------------------------HELPERS:

vec3 pullNeighbor( int neighborIndex )
{
	return vec3( vbo[neighborIndex * 3], 
				 vbo[neighborIndex * 3 + 1], 
				 vbo[neighborIndex * 3 + 2] );
}

//--------------------------------------------------------------MAIN:

void main()
{
	v_position = in_position;	
	int vertexID = int( in_vertexID );
	// int valence = valence[1 + vertexID * 2];
	// float fn = float( valence );
	
	// vec3 resTangent1 = vec3( 0 );
	// vec3 resTangent2 = vec3( 0 );


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
		int id = vertexID + 5;
		vec3 pos = pullNeighbor( id );
		v_color = vec4( pos.x, pos.y, pos.z, 1 ) * 4;
	}
	
	gl_Position = vec4( in_position, 1.0 );	
};