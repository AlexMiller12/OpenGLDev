#include "WireFrameProgram.h"

//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:

//------------------------------------------------------------------------FUNCTIONS:

//--------------------------------------------------------------------------METHODS:

void WireFrameProgram::draw( mat4 mvp )
{
	shaderProgram.use();

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Enable pointers so we can access attribute in shader
	shaderProgram.enableVec3Attribute( "in_position" );
	shaderProgram.enableVec3Attribute( "in_color" );

	// Pass in uniform mvp (setting it each frame prettending it changes)
	shaderProgram.setUniform( "mvp", mvp );

	// Draw wireframe
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	// Draw call
	glDrawElements( GL_TRIANGLES, numIndices * sizeof( GLushort ), GL_UNSIGNED_SHORT, 0 );
}

bool WireFrameProgram::init()
{
	// Initialize program with index buffer
	shaderProgram.init( true );

	if( ! shaderProgram.attachShader( vertex_shader, GL_VERTEX_SHADER )  ||
		! shaderProgram.attachShader( fragment_shader, GL_FRAGMENT_SHADER ) )
	{
		return false;
	}

	shaderProgram.createVBO( "in_position", ShaderProgram::gl_Vertex );
	shaderProgram.createVBO( "in_color", ShaderProgram::gl_Color );

	shaderProgram.finalizeProgram();

	// Set some GL state stuff that will be saved to our program's vao
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LESS );

	return true;
}


void WireFrameProgram::updateIndices( vector<GLushort> elements )
{
	numIndices = elements.size();
	
	indices = &elements[0];
	shaderProgram.setIndices( indices, numIndices );
}

void WireFrameProgram::updateVertexPositions( vector<GLfloat> vertexPositions )
{
	int len = vertexPositions.size();
	positions = &vertexPositions[0];
	shaderProgram.setVec3VBO( "in_position", positions, len );
}

void WireFrameProgram::updateVertexColors( vector<GLfloat> vertexColors )
{
	int len = vertexColors.size();
	colors = &vertexColors[0];
	shaderProgram.setVec3VBO( "in_color", colors, len );
}

//--------------------------------------------------------------------------HELPERS:
