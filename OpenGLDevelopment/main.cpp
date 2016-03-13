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
#include "Camera.h"

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
static const GLfloat cubeColor[] =
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

const char* vert2 =
"#version 450\n"
"uniform mat4 mvp;"
"in vec3 inPos;"
"void main(){"
"vec4 position = vec4( inPos, 1.0 );"
"gl_Position = mvp * position;"
//"gl_Position = position;"
"}";

const char* frag2 =
"#version 450\n"
"out vec4 color;"
"void main(){"
"color = vec4(1.0, 0.0, 0.0, 1.0);"
"}";



const char* vertex_shader =
"#version 450\n"
"uniform mat4 mvp;"
"in vec3 in_position;"
"in vec3 in_color;"

"out vec3 ex_color;"

"void main () {"
"  ex_color = in_color;"
//"  ex_color =  (mvp * vec4(in_color, 1.0)).xyz;"
"  gl_Position = mvp * vec4 (in_position, 1.0);"
//"  gl_Position = vec4(in_position, 1.0);"
"}";

const char* fragment_shader =
"#version 450\n"
"in vec3 ex_color;"
"out vec4 gl_FragColor;"
"void main () {"
"  gl_FragColor = vec4(ex_color, 1.0);"
"}";


//-----------------------------------------------------------------------PROTOTYPES:

void blarg();

//-----------------------------------------------------------------------------MAIN:

int main( int numArguments, char** arguments )
{
	blarg();

	return 0;
}

//------------------------------------------------------------------------FUNCTIONS:

void blarg()
{
	Renderer renderer;
	renderer.createWindow();
	renderer.bind();

	int screen_width = 640, screen_height = 480;
	Camera camera( 45.0f, screen_width, screen_height, 0.1f, 100.0f );
	camera.lookAt( vec3( 0, 5, -5 ), vec3( 0, 0, 0 ), vec3( 0, 0, 1 ) );
	glm::mat4 mvp = camera.viewProjectionMatrix();

	ShaderProgram shaderProgram;
	shaderProgram.init( true );
	//	if( ! shaderProgram.attatchShaders( vertex_shader, fragment_shader ) )
	if( !shaderProgram.attatchShaders( vertex_shader, fragment_shader ) )
	{
		exit( 1 );
	}
	int numFaces = 12;
	shaderProgram.setIndices( cube_elements, numFaces );

	shaderProgram.createVBO( "in_position", ShaderProgram::gl_Vertex );
	shaderProgram.setVec3VBO( "in_position", (GLfloat*)cube_vertices, 24 );
	
	shaderProgram.createVBO( "in_color", ShaderProgram::gl_Color );
	shaderProgram.setVec3VBO( "in_color", (GLfloat*)cube_colors, 24 );


	//shaderProgram.setUniform( "mvp", camera.viewProjectionMatrix() );

	/*glm::mat4 model = glm::translate( glm::mat4( 1.0f ), glm::vec3( 0.0, 0.0, -4.0 ) );
	glm::mat4 view = glm::lookAt( glm::vec3( 0.0, 2.0, 0.0 ), glm::vec3( 0.0, 0.0, -4.0 ), glm::vec3( 0.0, 1.0, 0.0 ) );
	glm::mat4 projection = glm::perspective( 45.0f, 1.0f*screen_width / screen_height, 0.1f, 10.0f );
	glm::mat4 mvp = projection * view * model;
	mvp = mat4( 1.0 );*/
	shaderProgram.finalizeProgram();

	shaderProgram.enableVec3Attribute( "in_position" );
	shaderProgram.enableVec3Attribute( "in_color" );
	shaderProgram.setUniform( "mvp", mvp );
	
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LESS );
	while( ! renderer.shouldClose() )
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		shaderProgram.use();

		/* Invoke glDrawArrays telling that our data is a line loop and we want to draw 4 vertices */
		glDrawElements( GL_TRIANGLES, 36 * sizeof(GLushort), GL_UNSIGNED_SHORT, 0 );

		// update other events like input handling 
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		renderer.swapBuffers();
	}
	renderer.unbind();
	renderer.closeWindow();
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
