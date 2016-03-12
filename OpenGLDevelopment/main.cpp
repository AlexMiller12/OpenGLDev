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

const GLfloat cube[] =
{
	-1.0f, -1.0f, -1.0f, // triangle 1 : begin
	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f, -1.0f, // triangle 2 : begin
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f, // triangle 2 : end
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};
// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] =
{
	0.583f, 0.771f, 0.014f,
	0.609f, 0.115f, 0.436f,
	0.327f, 0.483f, 0.844f,
	0.822f, 0.569f, 0.201f,
	0.435f, 0.602f, 0.223f,
	0.310f, 0.747f, 0.185f,
	0.597f, 0.770f, 0.761f,
	0.559f, 0.436f, 0.730f,
	0.359f, 0.583f, 0.152f,
	0.483f, 0.596f, 0.789f,
	0.559f, 0.861f, 0.639f,
	0.195f, 0.548f, 0.859f,
	0.014f, 0.184f, 0.576f,
	0.771f, 0.328f, 0.970f,
	0.406f, 0.615f, 0.116f,
	0.676f, 0.977f, 0.133f,
	0.971f, 0.572f, 0.833f,
	0.140f, 0.616f, 0.489f,
	0.997f, 0.513f, 0.064f,
	0.945f, 0.719f, 0.592f,
	0.543f, 0.021f, 0.978f,
	0.279f, 0.317f, 0.505f,
	0.167f, 0.620f, 0.077f,
	0.347f, 0.857f, 0.137f,
	0.055f, 0.953f, 0.042f,
	0.714f, 0.505f, 0.345f,
	0.783f, 0.290f, 0.734f,
	0.722f, 0.645f, 0.174f,
	0.302f, 0.455f, 0.848f,
	0.225f, 0.587f, 0.040f,
	0.517f, 0.713f, 0.338f,
	0.053f, 0.959f, 0.120f,
	0.393f, 0.621f, 0.362f,
	0.673f, 0.211f, 0.457f,
	0.820f, 0.883f, 0.371f,
	0.982f, 0.099f, 0.879f
};

/*float colors[] =
{
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
};*/
/* We're going to create a simple diamond made from lines */
const GLfloat diamond[12] = 
{
	 0.0, 1.0, 1.0, /* Top point */
	 1.0, 0.0, 1.0, /* Right point */
	 0.0, -1.0, 1.0, /* Bottom point */
	 -1.0, 0.0, 1.0 }; /* Left point */

const GLfloat colors[12] = 
{
	 1.0, 0.0, 0.0, /* Red */
	 0.0, 1.0, 0.0, /* Green */
	 0.0, 0.0, 1.0, /* Blue */
	 1.0, 1.0, 1.0 }; /* White */

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
"  gl_FragColor = vec4(1.0);"
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
	//shaderProgram.use();
	shaderProgram.createVBO( "in_position" );
	shaderProgram.setVec3VBO( "in_position", (GLfloat*)diamond, 12 );
	//shaderProgram.enableVec3Attribute( "in_position", ShaderProgram::gl_Vertex );

	shaderProgram.createVBO( "in_color" );
	shaderProgram.setVec3VBO( "in_color", (GLfloat*)colors, 12 );
	//shaderProgram.enableVec3Attribute( "in_color", ShaderProgram::gl_FogCoord );

	shaderProgram.finalizeProgram();
	shaderProgram.enableVec3Attribute( "in_position", ShaderProgram::gl_Vertex );
	shaderProgram.enableVec3Attribute( "in_color", ShaderProgram::gl_FogCoord );

	while( ! renderer.shouldClose() ) 
	{
		/* Make our background black */
		glClearColor( 0.0, 0.0, 0.0, 1.0 );
		glClear( GL_COLOR_BUFFER_BIT );

		/* Invoke glDrawArrays telling that our data is a line loop and we want to draw 4 vertices */
		glDrawArrays( GL_LINE_LOOP, 0, 4 );

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