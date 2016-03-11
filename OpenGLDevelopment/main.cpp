//#include "FastCatRenderer.h"

#include <stdio.h>  
#include <stdlib.h>  

#include "Dependencies\glew\glew.h"
#include "Dependencies\glfw\glfw3.h"

#include "Renderer.h"

//-----------------------------------------------------------------------PROTOTYPES:

void blarg();

//-----------------------------------------------------------------------------MAIN:

int main( int numArguments, char** arguments )
{
	Renderer renderer; 
	

	// start GL context and O/S window using the GLFW helper library
	if( ! renderer.createWindow() ) {
		fprintf( stderr, "ERROR: could not start GLFW3\n" );
		return 1;
	}
	renderer.bind();
	
	// get version info
	const GLubyte* rendererString = glGetString( GL_RENDERER ); // get renderer string
	const GLubyte* version = glGetString( GL_VERSION ); // version as a string
	printf( "Renderer: %s\n", rendererString );
	printf( "OpenGL version supported %s\n", version );


	/* OTHER STUFF GOES HERE NEXT */

	// close GL context and any other GLFW resources
	glfwTerminate();
	return 0;
}

//------------------------------------------------------------------------FUNCTIONS:

void blarg()
{
	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable( GL_DEPTH_TEST ); // enable depth-testing
	glDepthFunc( GL_LESS ); // depth-testing interprets a smaller value as "closer"

}