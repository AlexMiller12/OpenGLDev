// #version 400
// uniform mat4 Modelview;
// uniform mat3 NormalMatrix;
// layout(triangles) in;
// layout(triangle_strip, max_vertices = 3) out;
// in vec3 tePosition[3];
// in vec4 tePatchDistance[3];
// out vec3 gFacetNormal;
// out vec4 gPatchDistance;
// out vec3 gTriDistance;

// void main()
// {
// 	vec3 A = tePosition[2] - tePosition[0];
// 	vec3 B = tePosition[1] - tePosition[0];
// 	gFacetNormal = NormalMatrix * normalize(cross(A, B));

// 	gPatchDistance = tePatchDistance[0];
// 	gTriDistance = vec3(1, 0, 0);
// 	gl_Position = gl_in[0].gl_Position; EmitVertex();

// 	gPatchDistance = tePatchDistance[1];
// 	gTriDistance = vec3(0, 1, 0);
// 	gl_Position = gl_in[1].gl_Position; EmitVertex();

// 	gPatchDistance = tePatchDistance[2];
// 	gTriDistance = vec3(0, 0, 1);
// 	gl_Position = gl_in[2].gl_Position; EmitVertex();

// 	EndPrimitive();
// }

#version 450
layout( triangles ) in;
layout( triangle_strip, max_vertices = 3 ) out;

//---------------------------------------------------------CONSTANTS:

//---------------------------------------------------------VARIABLES:

in vec3 in_normal[3];
in vec3 in_position[3];

out vec3 out_triangleDistance;
out vec3 out_normal;

//uniform mat4 u_modelView;

//-----------------------------------------------------------HELPERS:

//--------------------------------------------------------------MAIN:

void main()
{
	vec3 edgeA = in_position[2] - in_position[0];
	vec3 edgeB = in_position[1] - in_position[0];
	
	out_normal = normalize( cross( edgeA, edgeB ) );

	out_triangleDistance = vec3(1, 0, 0);
	gl_Position = gl_in[0].gl_Position; 
	EmitVertex();

	out_triangleDistance = vec3(0, 1, 0);
	gl_Position = gl_in[1].gl_Position; 
	EmitVertex();

	out_triangleDistance = vec3(0, 0, 1);
	gl_Position = gl_in[2].gl_Position; 
	EmitVertex();

	EndPrimitive();
};