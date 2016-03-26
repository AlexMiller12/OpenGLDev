#version 450
layout( triangles ) in;
layout( triangle_strip, max_vertices = 3 ) out;

//---------------------------------------------------------CONSTANTS:

//---------------------------------------------------------VARIABLES:

// in vec3 te_normal[3];
in vec3 te_PatchDistance[3];
in vec3 te_position[3];

out vec3 g_triangleDistance;
out vec3 g_patchDistance;
out vec3 g_normal;

//uniform mat4 u_modelView;

//-----------------------------------------------------------HELPERS:

//--------------------------------------------------------------MAIN:

void main()
{
	vec3 edgeA = te_position[2] - te_position[0];
	vec3 edgeB = te_position[1] - te_position[0];
	g_normal = normalize( cross( edgeA, edgeB ) );

	g_patchDistance = te_PatchDistance[0];
	g_triangleDistance = vec3(1, 0, 0);
	gl_Position = gl_in[0].gl_Position; 
	EmitVertex();

	g_patchDistance = te_PatchDistance[1];
	g_triangleDistance = vec3(0, 1, 0);
	gl_Position = gl_in[1].gl_Position; 
	EmitVertex();

	g_patchDistance = te_PatchDistance[2];
	g_triangleDistance = vec3(0, 0, 1);
	gl_Position = gl_in[2].gl_Position; 
	EmitVertex();

	EndPrimitive();
};