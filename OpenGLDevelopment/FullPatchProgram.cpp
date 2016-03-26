#include "FullPatchProgram.h"

//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:

//--------------------------------------------------------------------------METHODS:

void FullPatchProgram::draw( mat4 modelView, mat4 projection )
{
	
}

bool FullPatchProgram::init()
{
	// Initialize program without index buffer
	if( ! ShaderProgram::init( true ) )
	{
		return false;
	}

	loadShaders();

	if( ! finalizeProgram() )
	{
		return false;
	}

	glEnable( GL_DEPTH_TEST );
	glClearColor( 0.7f, 0.6f, 0.5f, 1.0f );

	return true;
}

void FullPatchProgram::updateControlPoints( vector<GLfloat> newControlPoints )
{
	numVertices = newControlPoints.size();
	setVec3VBO( "Position", newControlPoints );
}

//--------------------------------------------------------------------------HELPERS:

bool FullPatchProgram::loadShaders()
{

	string vertSource, contSource, evalSource, geomSource, fragSource;
	string directory = IOUtil::executionPath() + "\\Shaders\\";

	if( ! IOUtil::readWholeFile( directory + "no_mvp.vert", vertSource ) ||
		! attachShader( vertSource, GL_VERTEX_SHADER ) )
	{
		return false;
	}

	if( ! IOUtil::readWholeFile( directory + "bspline.cont", contSource ) ||
		! attachShader( contSource, GL_TESS_CONTROL_SHADER ) )
	{
		return false;
	}
	if( ! IOUtil::readWholeFile( directory + "bspline.eval", evalSource ) ||
		! attachShader( evalSource, GL_TESS_EVALUATION_SHADER ) )
	{
		return false;
	}
	if( ! IOUtil::readWholeFile( directory + "basic.geom", geomSource ) ||
		! attachShader( geomSource, GL_GEOMETRY_SHADER ) )
	{
		return false;
	}
	if( ! IOUtil::readWholeFile( directory + "basic_lighting.frag", fragSource ) ||
		! attachShader( BasicShaders::lambert_f, GL_FRAGMENT_SHADER ) )
	{
		return false;
	}
	return true;
}