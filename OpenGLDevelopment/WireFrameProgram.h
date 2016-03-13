#ifndef WIRE_FRAME_PROG
#define WIRE_FRAME_PROG

#include "ShaderProgram.h"

class WireFrameProgram
{

//------------------------------------------------------------------------CONSTANTS:

private:
	const char* vertex_shader =
		"#version 450\n"
		"uniform mat4 mvp;"
		"in vec3 in_position;"
		"in vec3 in_color;"

		"out vec3 ex_color;"

		"void main () {"
		"  ex_color = in_color;"
		//"  ex_color =  (mvp * vec4(in_color, 1.0)).xyz;"
		"  gl_Position = mvp * vec4 (in_position, 1.0);"
		//"  gl_Position = vec4(in_position, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 450\n"
		"in vec3 ex_color;"
		"out vec4 gl_FragColor;"
		"void main () {"
		"  gl_FragColor = vec4(ex_color, 1.0);"
		"}";

//---------------------------------------------------------------------------FIELDS:

private:
	ShaderProgram shaderProgram;
	GLfloat* positions;
	GLfloat* colors;
	GLushort* indices;

//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:

//------------------------------------------------------------------------FUNCTIONS:

public:
	void draw( mat4 mvp );
	bool init();
	void updateIndices( vector<GLushort> indices );
	void updateVertexPositions( vector<GLfloat> vertexPositions );
	void updateVertexColors( vector<GLfloat> vertexColors );

//--------------------------------------------------------------------------METHODS:
	
};

#endif