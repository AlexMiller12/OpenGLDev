#include "EndPatchProgram.h"

//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:

//------------------------------------------------------------------------FUNCTIONS:

//--------------------------------------------------------------------------METHODS:

bool EndPatchProgram::init()
{
	if( ! ShaderProgram::init( true ) ||  ! loadShaders() )
	{
		return false;
	}

	createVBO( "in_position", ShaderProgram::gl_Vertex );

	if( ! finalizeProgram() )
	{
		return false;
	}
	return true;
}

void EndPatchProgram::updateControlPoints( vector<GLfloat> newControlPoints )
{
	use();
	numVertices = newControlPoints.size();
	setVBO( "in_position", newControlPoints );
}

//--------------------------------------------------------------------------HELPERS:

bool EndPatchProgram::loadShaders()
{
	string vertSource, contSource, evalSource, geomSource, fragSource;
	string directory = IOUtil::executionPath() + "\\Shaders\\";

	if( ! IOUtil::readWholeFile( directory + "end_patch.vert", vertSource ) ||
		! attachShader( vertSource, GL_VERTEX_SHADER ) )
	{
		return false;
	}
	if( ! IOUtil::readWholeFile( directory + "end_patch.frag", fragSource ) ||
		! attachShader( fragSource, GL_FRAGMENT_SHADER ) )
	{
		return false;
	}
	return true;
}