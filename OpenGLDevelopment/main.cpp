//#include "FastCatRenderer.h"

#include <stdio.h>  
#include <stdlib.h>  

// For IO:
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "Dependencies\glew\glew.h"
#include "Dependencies\glfw\glfw3.h"

#include "Renderer.h"
#include "WireFrameProgram.h"
#include "QuadTessellatorProgram.h"
#include "FullPatchProgram.h"
#include "Camera.h"
//#include "Mesh_Gumbo.h"
#include "Mesh_SingleBSplinePatch.h"
#include "EndPatchProgram.h"
#include "IOUtil.h"

using namespace std;

//--------------------------------------------------------------------------GLOBALS:


Renderer renderer;
Camera camera;
WireFrameProgram wireFramProgram;
QuadTessellatorProgram quadProgram;
FullPatchProgram patchProgram;
EndPatchProgram endPatchProgram;
std::vector<GLfloat> vertices, colors;
std::vector<GLushort> indices;

//-----------------------------------------------------------------------PROTOTYPES:

vector<GLfloat> makeEnd();
vector<GLfloat> makeFSQ();
vector<GLfloat> makeGumbo();
void setupCamera();
void showCube();
void showGumbo();
void showGumboBSpline();
void showEndPatch();

//-----------------------------------------------------------------------------MAIN:

int main( int numArguments, char** arguments )
{
	//showCube();
	//showGumbo();
	//showGumboBSpline();
	showEndPatch();
	return 0;
}

//------------------------------------------------------------------------FUNCTIONS:


vector<GLfloat> makeEnd()
{
	GLfloat endVerts[33] =
	{
		  0,  0,  0,	// 0
		  0,  2,  0,
		  2,  0,  0,
		  2, -2,  0,
		 -2, -2,  0,
		 -2,  0,  0,
		  0,  2,  0,	// 6
		  4,  2,  0,
		  4, -4,  0,
		 -4, -4,  0,
		 -4,  2,  0
	};
	for( int i = 0; i < 33; i++ )
	{
		endVerts[i] *= 0.25f;
	}
	vector<GLfloat> vertices;
	vertices.assign( endVerts, endVerts + 18 );
	return vertices;
}

vector<GLuint> makeEndIndices()
{
	GLuint endIndices[15] =
	{
		0, 1, 2,	// triangle 1
		0, 2, 3,	// triangle 2
		0, 3, 4,
		0, 4, 5,
		0, 5, 1
	};
	vector<GLuint> indices;
	indices.assign( endIndices, endIndices + 15 );
	return indices;
}

vector<GLfloat> makeVertexIDs() {

	vector<GLfloat> ids;
	for( int i = 0; i < 6; i++ )
	{
		ids.push_back( i );
	}
	return ids;
}

vector<GLfloat> makeFSQ()
{
	GLfloat FSQVerts[12] =
	{
		 -1, -1, 0,
		 -1,  1, 0,
		  1,  1, 0 ,
		  1, -1, 0
	};

	int numVertices = 4;
	vector<GLfloat> controlPoints;

	controlPoints.assign( FSQVerts, FSQVerts + 12 );
	return controlPoints;
}

vector<GLushort> makeGumboIndices()
{
	int numVertices = sizeof( PatchData ) / ( sizeof( float ) * 3 );
	//int numIndices = numVertices * 3;
	vector<GLushort> indices;
	for( int i = 0; i < numVertices; i++ )
	{
		indices.push_back( i );
	}
	return indices;
}

vector<GLfloat> makeGumbo()
{
	int numVertices = sizeof( PatchData ) / ( sizeof( float ) * 3 );
	vector<GLfloat> controlPoints;
	for( int vert = 0; vert < numVertices; vert++ )
	{
		controlPoints.push_back( PatchData[vert][0] ); // x
		controlPoints.push_back( PatchData[vert][1] ); // y
		controlPoints.push_back( PatchData[vert][2] ); // z
	}
	return controlPoints;
}

void showCube()
{

	// 8 points, 24 elements
	GLfloat cube_vertices[] = 
	{
		// front
		-10.0, -10.0, 10.0,
		10.0, -10.0, 10.0,
		10.0, 10.0, 10.0,
		-10.0, 10.0, 10.0,
		// back
		-10.0, -10.0, -10.0,
		10.0, -10.0, -10.0,
		10.0, 10.0, -10.0,
		-10.0, 10.0, -10.0,
	};

	// Init GL
	renderer.createWindow();
	renderer.bind();

	// Set up camera so we can get our projection matrix
	setupCamera();

	if( !wireFramProgram.init() )
	{
		exit( 1 );
	}

	while( ! renderer.shouldClose() )
	{
		wireFramProgram.use();
		// Pretend that these are changing each frame
		wireFramProgram.updateVertexPositions( vertices );
		wireFramProgram.updateVertexColors( colors );
		wireFramProgram.setIndices( indices );
		// Run program
		wireFramProgram.draw( camera.viewProjectionMatrix() );
		// Display the framebuffer to which we just wrote
		renderer.swapBuffers();
	}
	renderer.unbind();
	renderer.closeWindow();
}

struct camera_data_t
{
	float color[4];
} cameraData;

void showEndPatch()
{
	vector<GLfloat> vertices = makeEnd();
	vector<GLuint> indices = makeEndIndices();
	vector<GLfloat> ids = makeVertexIDs();
	// Init GL
	renderer.createWindow();
	renderer.bind();

	// Set up camera so we can get our projection matrix
	setupCamera();

	if( ! endPatchProgram.init() )
	{
		exit( 1 );
	}
	endPatchProgram.use();
	endPatchProgram.setVBO( "in_position", vertices ); 
	endPatchProgram.setVBO( "in_vertexID", ids );
	endPatchProgram.setIndices( indices );

	cameraData.color[1] = 1;
	cameraData.color[3] = 1;
	
	ShaderProgram::createSBO( "cameraData", sizeof( cameraData ), &cameraData );
	endPatchProgram.setSBOBindingPoint( 0, "cameraData" );

	while( ! renderer.shouldClose() )
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
		endPatchProgram.draw( camera.viewProjectionMatrix() );
		// Display the framebuffer to which we just wrote
		renderer.swapBuffers();
	}
	renderer.unbind();
	renderer.closeWindow();
}

void showGumbo()
{
	// Init GL
	renderer.createWindow();
	renderer.bind();

	// Set up camera so we can get our projection matrix
	setupCamera();
	
	if( ! quadProgram.init() )
	{
		exit( 1 );
	}
	
	// Load Gumbo model data
	vector<GLfloat> gumboControlPoints = makeGumbo();
	vector<GLushort> gumboIndices = makeGumboIndices();

	quadProgram.use();
	quadProgram.updateControlPoints( gumboControlPoints );
	quadProgram.setUniform( "AmbientMaterial", vec3( 0.04f ) );
	quadProgram.setUniform( "LightPosition", vec3( 0.25f, 0.25f, 1.0f ) );
	quadProgram.setUniform( "AmbientMaterial", vec3( 0.04f ) );
	quadProgram.setUniform( "SpecularMaterial", vec3( 0.5f ) );
	quadProgram.setUniform( "DiffuseMaterial", vec3( 0, 0.75f, 0.75f ) );
	quadProgram.setUniform( "Shininess", 50.0f );
	quadProgram.setUniform( "AmbientMaterial", vec3() );
	quadProgram.setUniform( "TessLevelInner", 6 );
	quadProgram.setUniform( "TessLevelOuter", 6 );
	
	while( ! renderer.shouldClose() )
	{
		// Pretend that these are changing each frame
		quadProgram.updateControlPoints( gumboControlPoints );
		quadProgram.setIndices( gumboIndices );
		// Run program
		quadProgram.draw( camera.viewMatrix(), camera.projectionMatrix() );
		// Display the framebuffer to which we just wrote
		renderer.swapBuffers();
	}
	renderer.unbind();
	renderer.closeWindow();
}

void showGumboBSpline()
{
	// Init GL
	renderer.createWindow();
	renderer.bind();

	// Set up camera so we can get our projection matrix
	setupCamera();

	if( ! patchProgram.init() )
	{
		exit( 1 );
	}

	vector<GLfloat> gumboControlPoints = makeGumbo();
	vector<GLushort> gumboIndices = makeGumboIndices();

	patchProgram.use();
	patchProgram.updateControlPoints( gumboControlPoints );
	patchProgram.setUniform( "u_objectColor", vec3( 1.0f, 0, 0 ) );
	patchProgram.setUniform( "u_tessLevelInner", 1 );
	patchProgram.setUniform( "u_tessLevelOuter", 1 );

	while( ! renderer.shouldClose() )
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		// Pretend that these are changing each frame
		patchProgram.updateControlPoints( gumboControlPoints );
		patchProgram.setIndices( gumboIndices );
		// Run program
		patchProgram.draw( camera.viewMatrix(), camera.projectionMatrix() );
		// Display the framebuffer to which we just wrote
		renderer.swapBuffers();
	}
	renderer.unbind();
	renderer.closeWindow();
}

void setupCamera()
{
	int screen_width = 640, screen_height = 480;
	camera = Camera( 45.0f, screen_width, screen_height, 1.0f, 200.0f );
	//vec3 camPos = vec3( -30, -10, 20 );
	//vec3 lookAt = vec3( 15, 19, 0 );

	vec3 camPos = vec3( 2, 2, 5 );
	vec3 lookAt = vec3( 0, 0, 0 );

	vec3 up = vec3( 0, 1, 0 );
	camera.lookAt( camPos, lookAt, up );
}
