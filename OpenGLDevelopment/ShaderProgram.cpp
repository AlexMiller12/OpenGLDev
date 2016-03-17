#include "ShaderProgram.h"

//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram() 
{
	// TODO, clean up!
}

//------------------------------------------------------------------------FUNCTIONS:

//--------------------------------------------------------------------------METHODS:

bool ShaderProgram::attachShader( const char* source, GLenum type )
{
	bindToVAO();
	GLuint shaderHandle = glCreateShader( type );
	glShaderSource( shaderHandle, 1, &source, NULL );
	glCompileShader( shaderHandle );

	// Save the handle to the shader so we can delete after linking 
	// (Or for printing errors)
	shaders.push_back( shaderHandle );
	//TODO: only on debug mode
	int succeeded;
	glGetShaderiv( shaderHandle, GL_COMPILE_STATUS, &succeeded );
	if( ! succeeded )   return false; 

	glAttachShader( handle, shaderHandle );


	return true; //TODO return false on error
}

//bool ShaderProgram::bindToIndexBuffer()
//{
//	
//}

bool ShaderProgram::bindToVAO()
{
	glBindVertexArray( vertexArrayObjectHandle );
	return true;
}

// Initializes a vertex buffer and assigns given attribute index (for when we want
// to create a pointer to buffer)
bool ShaderProgram::createVBO( string attributeName, GLuint attributeindex )
{
	// Bind to VAO so we assign new VBO to it
	bindToVAO();

	// Generate new buffer
	GLuint newVBOHandle;
	glGenBuffers( 1, &newVBOHandle );

	//TODO return false on error

	// Store handle for quick lookup later
	attributeLocations[attributeName] = newVBOHandle;

	attributeIndices[attributeName] = attributeindex;

	// Assign it to "in vec3" variable in shader
	glBindAttribLocation( handle, attributeindex, attributeName.c_str() );

	return true;
}

// Enables an attribute pointer to buffer with given name
bool ShaderProgram::enableVec3Attribute( string attributeName )
{
	GLuint bufferHandle = getAttributeLocation( attributeName );
	
	GLuint attributeIndex = attributeIndices[attributeName]; //TODO check if there
	// Enable attribute
	glEnableVertexAttribArray( attributeIndex );

	glBindBuffer( GL_ARRAY_BUFFER, bufferHandle );

	// Vec3 attributes have three floats per vertex
	int floatsPerVertex = 3;

	// Tell GL how to handle data in buffer
	glVertexAttribPointer( attributeIndex,
						   floatsPerVertex, 
						   GL_FLOAT, 
						   GL_FALSE, // normalized?
						   0,		 // stride 
						   (void*)0 );      // array buffer offset

	//TODO falseonerror
	return true;
}

bool ShaderProgram::finalizeProgram()
{		
	glLinkProgram( handle );

	int succeeded;
	glGetProgramiv( handle, GL_LINK_STATUS, (int *)&succeeded );

	// TODO go through shaders and detach and delete them
	/*glDetachShader( geomFragProgram, fragShader );
	glDeleteShader( geomShader );*/
	return succeeded;
}

// Returns the handle of the unifrom or attribute associated with given name
GLuint ShaderProgram::getAttributeLocation( string name )
{
	// Look up the stored uniform location
	GLuint attributeLocation = attributeLocations[name];

	// If it has not yet been stored, we must query GL for location.  We don't 
	// simply query every time because it is much more expensive than a simple 
	// hash map lookup
	if( ! attributeLocation )
	{
		// Query location
		attributeLocation = glGetAttribLocation( handle, name.c_str() );

		// Store for later use
		attributeLocations[name] = attributeLocation;
	}
	return attributeLocation;
}

GLuint ShaderProgram::getHandle()
{
	return handle;
}

// Returns the handle of the unifrom or attribute associated with given name
GLuint ShaderProgram::getUniformLocation( string name )
{
	// Look up the stored uniform location
	GLuint uniformLocation = uniformLocations[name];
	
	// If it has not yet been stored, we must query GL for location.  We don't 
	// simply query every time because it is much more expensive than a simple 
	// hash map lookup
	if( ! uniformLocation )
	{
		// Query location
		uniformLocation = glGetUniformLocation( handle, name.c_str() );

		// Store for later use
		uniformLocations[name] = uniformLocation;
	}
	return uniformLocation;
}

// Initializes index buffer
bool ShaderProgram::init( bool createIndexBuffer )
{
	handle = glCreateProgram();
	glGenVertexArrays( 1, &vertexArrayObjectHandle );
	// TODO: return false on error
	if( createIndexBuffer )
	{
		glGenBuffers( 1, &indexBufferHandle );
		// TODO: return false on error
	}
	return true;
}

void ShaderProgram::printErrors()
{
	for( int i = 0; i < shaders.size(); i++ )
	{
		GLuint shaderHandle = shaders.at( i );
		int status;
		glGetShaderiv( shaderHandle, GL_COMPILE_STATUS, &status );
		if( ! status )
		{
			GLint expectedLength = 0;
			glGetShaderiv( shaderHandle, GL_INFO_LOG_LENGTH, &expectedLength );
			vector<GLchar> errorLog( expectedLength );
			GLsizei actualLength;
			glGetShaderInfoLog( shaderHandle, expectedLength, &actualLength, &errorLog[0] );
			printf( "Log:\n%s", &errorLog[0] );
		}
	}
	int linkStatus;
	glGetProgramiv( handle, GL_LINK_STATUS, (int *)&linkStatus );
	if( ! linkStatus )
	{
		GLint expectedLength = 0;
		glGetProgramiv( handle, GL_INFO_LOG_LENGTH, &expectedLength );
		vector<GLchar> errorLog( expectedLength );
		GLsizei actualLength;
		glGetProgramInfoLog( handle, expectedLength, &actualLength, &errorLog[0] );
		printf( "Log:\n%s", &errorLog[0] );
	}

	
}

bool ShaderProgram::setIndices( GLushort indices[], int numFaces, GLenum usage )
{
	GLushort bufferSize = numFaces * 3 * sizeof( GLushort );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, bufferSize, indices, usage );
	return true;
}



bool ShaderProgram::setUniform( string uniformName, float value )
{
	use();
	GLuint uniformLocation = getUniformLocation( uniformName );
	glUniform1f( uniformLocation, value );
	// TODO if debug mode return false on error
	return true;
}

bool ShaderProgram::setUniform( string uniformName, mat4 value )
{
	use();
	GLuint uniformLocation = getUniformLocation( uniformName );
	glUniformMatrix4fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	// TODO if debug mode return false on error
	return true;
}

bool ShaderProgram::setUniform( string uniformName, vec3 value )
{
	use();
	GLuint uniformLocation = getUniformLocation( uniformName );
	glUniform3f( uniformLocation, value.x, value.y, value.z );
	// TODO if debug mode return false on error
	return true;
}

bool ShaderProgram::setUniform( string uniformName, vec4 value )
{
	use();
	GLuint uniformLocation = getUniformLocation( uniformName );
	glUniform4f( uniformLocation, value.x, value.y, value.z, value.w );
	// TODO if debug mode return false on error
	return true;
}

bool ShaderProgram::setVec3VBO( string attributeName, 
								GLfloat data[], 
								int dataLength, 
								GLenum usage )
{
	// If the VBO has not been created, return false
	if( ! attributeLocations[attributeName] )   return false;

	// Bind to VAO so we assign new VBO to it
	bindToVAO();
	
	// Find handle to data buffer
	GLuint bufferHandle = getAttributeLocation( attributeName );

	// Bind to the VBO
	glBindBuffer( GL_ARRAY_BUFFER, bufferHandle );

	// Set the data of the buffer
	glBufferData( GL_ARRAY_BUFFER, 
				  dataLength * sizeof( GLfloat ), 
				  data, 
				  usage );
	//TODO return false on errors if debug mode
	return true;
}	


void ShaderProgram::use()
{
	glUseProgram( handle );
}

//--------------------------------------------------------------------------HELPERS:





