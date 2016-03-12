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
#include "ShaderProgram.h"

//--------------------------------------------------------------------------GLOBALS:

float points[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};

const char* vertex_shader =
"#version 400\n"
"in vec3 vp;"
"void main () {"
"  gl_Position = vec4 (vp, 1.0);"
"}";

const char* fragment_shader =
"#version 400\n"
"out vec4 frag_colour;"
"void main () {"
"  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
"}";

//-----------------------------------------------------------------------PROTOTYPES:

void blarg();

//-----------------------------------------------------------------------------MAIN:

int main( int numArguments, char** arguments )
{
	Renderer renderer;
	renderer.createWindow();
	renderer.bind();

	ShaderProgram shaderProgram( vertex_shader, fragment_shader );

	//shaderProgram.use();
	shaderProgram.setVec3VBO( "vp", points, 9 );
	//GLuint vbo = 0;
	//glGenBuffers( 1, &vbo );
	//glBindBuffer( GL_ARRAY_BUFFER, vbo );
	//glBufferData( GL_ARRAY_BUFFER, 9 * sizeof( float ), points, GL_STATIC_DRAW );

	GLuint vao = 0;
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
	glEnableVertexAttribArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, shaderProgram.getLocation( "vp" ) );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );

	while( ! renderer.shouldClose() ) {
		// wipe the drawing surface clear
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		shaderProgram.use();
		glBindVertexArray( vao ); // shaderProgram.vertexArrayObjectHandle );
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays( GL_TRIANGLES, 0, 3 );
		// update other events like input handling 
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		renderer.swapBuffers();
	}

	// close GL context and any other GLFW resources
	renderer.unbind();
	renderer.closeWindow();
	return 0;
}

//------------------------------------------------------------------------FUNCTIONS:

void blarg()
{
	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable( GL_DEPTH_TEST ); // enable depth-testing
	glDepthFunc( GL_LESS ); // depth-testing interprets a smaller value as "closer"

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