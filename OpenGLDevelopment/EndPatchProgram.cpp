#include "EndPatchProgram.h"

//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:

//------------------------------------------------------------------------FUNCTIONS:

//--------------------------------------------------------------------------METHODS:

void EndPatchProgram::draw( mat4 mvp )
{
	use();

	enableVec3Attribute( "in_position" );

	glDrawElements( GL_TRIANGLES,
					numIndices * sizeof( GLuint ),
					GL_UNSIGNED_INT,
					0 );

	GLUtil::printErrors();
}

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

	use();

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable( GL_DEPTH_TEST ); // enable depth-testing
	glDepthFunc( GL_LESS ); // depth-testing interprets a smaller value as "closer"

	return true;
}

void EndPatchProgram::updateControlPoints( vector<GLfloat> newControlPoints )
{
	use();
	numVertices = newControlPoints.size() / 3;
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