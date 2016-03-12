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

float colors[] =
{
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
};

const char* vertex_shader =
"#version 400\n"
"in vec3 in_position;"
"in vec3 in_color;"

"out vec3 ex_color;"

"void main () {"
"  ex_color = in_color + in_color;"
"  gl_Position = vec4 (in_position, 1.0);"
"}";

const char* fragment_shader =
"#version 400\n"
"in vec3 ex_color;"
"out vec4 gl_FragColor;"
"void main () {"
"  gl_FragColor = vec4(ex_color,1.0);;"
"}";

//-----------------------------------------------------------------------PROTOTYPES:

void blarg();

//-----------------------------------------------------------------------------MAIN:

int main( int numArguments, char** arguments )
{
	Renderer renderer;
	renderer.createWindow();
	renderer.bind();

	ShaderProgram shaderProgram;

	if( ! shaderProgram.compileShaders( vertex_shader, fragment_shader ) )
	{
		printf( " oh now! " );
	}
	shaderProgram.use();
	shaderProgram.createVBO( "pop" );

	shaderProgram.setVec3VBO( "gl_Vertex", colors, 9 );
	shaderProgram.enableVec3Attribute( "gl_Vertex", ShaderProgram::gl_Vertex );

	shaderProgram.setVec3VBO( "pop", colors, 9 );
	shaderProgram.enableVec3Attribute( "pop", ShaderProgram::gl_FogCoord );

	shaderProgram.finalizeProgram();
	while( ! renderer.shouldClose() ) {
		// wipe the drawing surface clear
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		// Bind to shaderProgram's vao and use its Program
		shaderProgram.use();
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