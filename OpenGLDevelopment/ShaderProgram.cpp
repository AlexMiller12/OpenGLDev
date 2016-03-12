#include "ShaderProgram.h"

//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::ShaderProgram( const char* vertexSource,
							  const char* fragmentSource )
{
}

ShaderProgram::~ShaderProgram() 
{
	// TODO, clean up!
}

//------------------------------------------------------------------------FUNCTIONS:

//--------------------------------------------------------------------------METHODS:


GLuint ShaderProgram::getHandle()
{
	return handle;
}

// Returns the handle of the unifrom or attribute associated with given name
GLuint ShaderProgram::getLocation( string name )
{
	// Look up the stored uniform location
	GLuint uniformLocation = locations[name];

	// If it has not yet been stored, we must query GL for location.  We don't 
	// simply query every time because it is much more expensive than a simple 
	// hash map lookup
	if( ! uniformLocation )
	{
		// Query location
		uniformLocation = glGetUniformLocation( handle, name.c_str() );

		// Store for later use
		locations[name] = uniformLocation;
	}
	return uniformLocation;
}


bool ShaderProgram::setVec3VBO( string attributeName, 
								GLfloat data[], 
								int dataLength, 
								GLenum usage )
{
	if( ! locations[attributeName] )
	{
		createVBO( attributeName );
	}

	GLuint bufferHandle = getLocation( attributeName );

	glBindBuffer( GL_ARRAY_BUFFER, bufferHandle );

	glBufferData( GL_ARRAY_BUFFER, 
				  dataLength * sizeof( GLfloat ), 
				  data, 
				  usage );  

	// Vec3 attributes have three floats per vertex
	int floatsPerVertex = 3;
	
	glVertexAttribPointer( bufferHandle,
						   floatsPerVertex, 
						   GL_FLOAT, 
						   GL_FALSE, 
						   0, 0 );

	glEnableVertexAttribArray( bufferHandle );

	//TODO return false on errors

	return true;
}	

void ShaderProgram::use()
{
	glUseProgram( handle );
	glBindVertexArray( vertexArrayObjectHandle );
}

//--------------------------------------------------------------------------HELPERS:

bool ShaderProgram::createVBO( string attributeName )
{
	// Check that our vertex array object has been created
	if( ! isVAOInitialized )
	{
		// If not, create it
		glGenVertexArrays( 1, &vertexArrayObjectHandle );

		//TODO return false on error

		isVAOInitialized = true;
	}
	// Bind to VAO so we assign new VBO to it
	glBindVertexArray( vertexArrayObjectHandle );

	// Generate new buffer
	GLuint newVBOHandle;
	glGenBuffers( 1, &newVBOHandle );

	//TODO return false on error

	// Store handle for quick lookup later
	locations[attributeName] = newVBOHandle;

	return true;
}


// Compiles and links a shader program from given sources and returns handle on
// success, -1 on failure.
GLuint ShaderProgram::shaderFromSource( const char* vertexSource,
									    const char* fragmentSource )
{
	GLuint vertexShaderHandle = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShaderHandle, 1, &vertexSource, NULL );
	glCompileShader( vertexShaderHandle );
	
	// TODO: return on error
	
	GLuint fragmentShaderHandle = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShaderHandle, 1, &fragmentSource, NULL );
	glCompileShader( fragmentShaderHandle );

	// TODO: return on error

	GLuint programHandle = glCreateProgram();
	glAttachShader( programHandle, vertexShaderHandle );
	glAttachShader( programHandle, fragmentShaderHandle );
	glLinkProgram( programHandle );

	// TODO: delete shaders

	return programHandle;
}


