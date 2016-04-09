#version 450

layout (std430, binding=2) buffer cameraData
{ 
  vec4 color
};

//---------------------------------------------------------VARIABLES:

in vec3 v_position;

out vec4 out_fragColor;

//-----------------------------------------------------------HELPERS:

//--------------------------------------------------------------MAIN:

void main()
{
	out_fragColor = vec4(1, 0, 0, 1);
}