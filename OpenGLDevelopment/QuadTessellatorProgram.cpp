#include "QuadTessellatorProgram.h"

//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:

//--------------------------------------------------------------------------METHODS:

bool QuadTessellatorProgram::init()
{
	// Initialize program with index buffer
	program.init( true );

	program.attachShader( BasicShaders::noMVP_v, GL_VERTEX_SHADER );
	program.attachShader( BasicShaders::simple_tc, GL_TESS_CONTROL_SHADER );
	program.attachShader( BasicShaders::simple_te, GL_TESS_EVALUATION_SHADER  );
	program.attachShader( BasicShaders::simple_g, GL_GEOMETRY_SHADER );
	program.attachShader( BasicShaders::lambert_f, GL_FRAGMENT_SHADER );

	program.createVBO( "Position", ShaderProgram::gl_Vertex );

	program.finalizeProgram();

	return true;
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
