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
"in vec3 vp;"
"in vec3 pop;"

"out vec3 color;"

"void main () {"
"  f_col = vp;"
"  gl_Position = vec4 (vp, 1.0);"
"}";

const char* fragment_shader =
"#version 400\n"
"in vec3 color;"
"out vec4 frag_colour;"
"void main () {"
"  frag_colour = vec4 (color, 1.0);"
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

	shaderProgram.use();
	shaderProgram.setVec3VBO( "vp", points, 9 );
	shaderProgram.enableVec3Attribute( "vp", ShaderProgram::gl_Vertex );

	shaderProgram.setVec3VBO( "pop", colors, 9 );
	shaderProgram.enableVec3Attribute( "pop", ShaderProgram::gl_Color );

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