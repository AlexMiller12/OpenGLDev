#version 430

layout (std430, binding=2) buffer cameraData
{ 
  vec4 color;
};

//---------------------------------------------------------VARIABLES:

in vec3 v_position;
in float v_vertexID;

out vec4 out_fragColor;

//-----------------------------------------------------------HELPERS:

//--------------------------------------------------------------MAIN:

void main()
{
	out_fragColor = color + vec4( v_vertexID, 0, 0, 1 );
	// out_fragColor = vec4(1, 0, 0, 1);
}