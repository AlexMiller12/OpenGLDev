//#include "FastCatRenderer.h"

#include <stdio.h>  
#include <stdlib.h>  

// For IO:
#include <string.h>
#include <iostream>
#include <fstream>

#include "Dependencies\glew\glew.h"
#include "Dependencies\glfw\glfw3.h"

#include "Renderer.h"
#include "WireFrameProgram.h"
#include "Camera.h"

//--------------------------------------------------------------------------GLOBALS:

// 8 points, 24 elements
GLfloat cube_vertices[] = {
	// front
	-1.0, -1.0, 1.0,
	1.0, -1.0, 1.0,
	1.0, 1.0, 1.0,
	-1.0, 1.0, 1.0,
	// back
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0, 1.0, -1.0,
	-1.0, 1.0, -1.0,
};
// 8 points, 24 elements
GLfloat cube_colors[] = {
	// front colors
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 1.0,
	// back colors
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 1.0,
};
// 12 faces, 36 elements
GLushort cube_elements[] = {
	// front
	0, 1, 2,
	2, 3, 0,
	// top
	1, 5, 6,
	6, 2, 1,
	// back
	7, 6, 5,
	5, 4, 7,
	// bottom
	4, 0, 3,
	3, 7, 4,
	// left
	4, 5, 1,
	1, 0, 4,
	// right
	3, 2, 6,
	6, 7, 3,
};

Renderer renderer;
Camera camera;
WireFrameProgram program;
std::vector<GLfloat> vertices, colors;
std::vector<GLushort> indices;

//-----------------------------------------------------------------------PROTOTYPES:

void setupCamera();
void showCube();

//-----------------------------------------------------------------------------MAIN:

int main( int numArguments, char** arguments )
{
	showCube();
	return 0;
}

//------------------------------------------------------------------------FUNCTIONS:

void showCube()
{
	// We will get our data in vectors probably
	vertices.assign( cube_vertices, cube_vertices + 24 );
	colors.assign( cube_colors, cube_colors + 24 );
	indices.assign( cube_elements, cube_elements + 36 );

	// Init GL
	renderer.createWindow();
	renderer.bind();

	// Set up camera so we can get our projection matrix
	setupCamera();

	program.init();

	while( !renderer.shouldClose() )
	{
		// Pretend that these are changing each frame
		program.updateVertexPositions( vertices );
		program.updateVertexColors( colors );
		program.updateIndices( indices );

		program.draw( camera.viewProjectionMatrix() );

		// put the stuff we've been drawing onto the display
		renderer.swapBuffers();
	}
	renderer.unbind();
	renderer.closeWindow();
}

void setupCamera()
{
	int screen_width = 640, screen_height = 480;
	camera = Camera( 45.0f, screen_width, screen_height, 0.1f, 100.0f );
	camera.lookAt( vec3( 5, 0, -5 ), vec3( 0, 0, 0 ), vec3( 0, 1, 0 ) );

}

bool readWholeFile( const char *fileName, std::string &ret_content )
{
	bool success = true;
	std::ifstream ifs( fileName, std::ifstream::in | std::ifstream::binary );

	if( ifs )
	{
		ifs.seekg( 0, std::ifstream::end );
		int length = ifs.tellg();
		ifs.seekg( 0, std::ifstream::beg );

		ret_content.resize( length );
		ifs.read( &ret_content[0], length );

		ifs.close();
	}
	else
	{
		std::cout << "Cannot open shader file: " << fileName << '\n';
		return !success;
	}

	return success;
}
