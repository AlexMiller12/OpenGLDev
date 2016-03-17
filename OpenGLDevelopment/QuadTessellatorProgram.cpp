#include "QuadTessellatorProgram.h"

//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:

//--------------------------------------------------------------------------METHODS:

void QuadTessellatorProgram::draw( mat4 mvp )
{
	program.use();
}

bool QuadTessellatorProgram::init()
{
	// Initialize program without index buffer
	program.init( false );

	bool succeeded;
	succeeded = program.attachShader( BasicShaders::noMVP_v, GL_VERTEX_SHADER );
	if( ! succeeded )   program.printErrors();
	succeeded = program.attachShader( BasicShaders::simple_tc, GL_TESS_CONTROL_SHADER );
	if( ! succeeded ) 	program.printErrors();
	succeeded = program.attachShader( BasicShaders::simple_te, GL_TESS_EVALUATION_SHADER );
	if( ! succeeded ) 	program.printErrors();
	succeeded = program.attachShader( BasicShaders::simple_g, GL_GEOMETRY_SHADER );
	if( ! succeeded ) 	program.printErrors();
	succeeded = program.attachShader( BasicShaders::lambert_f, GL_FRAGMENT_SHADER );
	if( ! succeeded ) 	program.printErrors();
	
	program.createVBO( "Position", ShaderProgram::gl_Vertex );
	succeeded = program.finalizeProgram();
	if( ! succeeded ) 	program.printErrors();
	return succeeded;
}

void QuadTessellatorProgram::updateIndices( vector<GLushort> indices )
{

}

void QuadTessellatorProgram::updateControlPoints( vector<GLfloat> newControlPoints )
{
	int len = newControlPoints.size();
	controlPoints = &newControlPoints[0];
	program.setVec3VBO( "Position", controlPoints, len );
}

//--------------------------------------------------------------------------HELPERS:
