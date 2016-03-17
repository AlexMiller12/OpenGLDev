#ifndef QUAD_TESS_PROG
#define QUAD_TESS_PROG

#include "BasicShaders.h"
#include "ShaderProgram.h"

class QuadTessellatorProgram
{
	
//----------------------------------------------------------------------------ENUMS:
	
//------------------------------------------------------------------------CONSTANTS:
	
//---------------------------------------------------------------------------FIELDS:
	
private:
	float innerTessellationLevel;
	float outerTessellationLevel;

	GLfloat* controlPoints;
	GLushort* indices;

	ShaderProgram program;

//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:
		
//--------------------------------------------------------------------------METHODS:

public:
	void draw( mat4 mvp );
	bool init();
	void updateIndices( vector<GLushort> indices );
	void updateControlPoints( vector<GLfloat> controlPoints );

};

#endif