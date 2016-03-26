#ifndef FULL_PATCH_PROG
#define FULL_PATCH_PROG

#include "BasicShaders.h"
#include "ShaderProgram.h"

class FullPatchProgram : ShaderProgram
{
	
//----------------------------------------------------------------------------ENUMS:
	
//------------------------------------------------------------------------CONSTANTS:
	
//---------------------------------------------------------------------------FIELDS:

private:
	float innerTessellationLevel;
	float outerTessellationLevel;
	int numVertices;
	int controlPointsPerPatch;

//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:
		
//------------------------------------------------------------------------FUNCTIONS:

//--------------------------------------------------------------------------METHODS:

public:
	void draw( mat4 modelView, mat4 projection );
	bool init();
	void updateControlPoints( vector<GLfloat> controlPoints );

};

#endif