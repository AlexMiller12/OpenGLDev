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
	attributeLocations[attributeName] = newVBOHandle;

	// Assign it to "in vec3" variable in shader
	glBindAttribLocation( handle, newVBOHandle, attributeName.c_str() );

	return true;
}

// Compiles and links a shader program from given sources. Returns true on success
bool ShaderProgram::compileShaders( const char* vertexSource,
									const char* fragmentSource )
{

	handle = glCreateProgram();

	GLuint vertexShaderHandle = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShaderHandle, 1, &vertexSource, NULL );
	glCompileShader( vertexShaderHandle );

	int succeeded;
	glGetShaderiv( vertexShaderHandle, GL_COMPILE_STATUS, &succeeded );
	if( ! succeeded )   return false; //TODO delete shader
	
	GLuint fragmentShaderHandle = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShaderHandle, 1, &fragmentSource, NULL );
	glCompileShader( fragmentShaderHandle );

	glGetShaderiv( fragmentShaderHandle, GL_COMPILE_STATUS, &succeeded );
	if( ! succeeded )   return false; //TODO delete shader

	glAttachShader( handle, vertexShaderHandle );
	glAttachShader( handle, fragmentShaderHandle );

	return true;

}

bool ShaderProgram::enableVec3Attribute( string attributeName, 
										 GLuint attributeindex )
{
	GLuint bufferHandle = getAttributeLocation( attributeName );
	
	// Enable attribute
	glEnableVertexAttribArray( attributeindex );

	glBindBuffer( GL_ARRAY_BUFFER, bufferHandle );

	// Vec3 attributes have three floats per vertex
	int floatsPerVertex = 3;

	// Tell GL how to handle data in buffer
	glVertexAttribPointer( attributeindex,
						   floatsPerVertex, 
						   GL_FLOAT, 
						   GL_FALSE, 
						   0, 0 );

	//TODO falseonerror

	return true;
}

bool ShaderProgram::finalizeProgram()
{		
	glLinkProgram( handle );

	int succeeded;
	glGetProgramiv( handle, GL_LINK_STATUS, (int *)&succeeded );
	if( ! succeeded )   return false;
	return true;
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

bool ShaderProgram::setVec3VBO( string attributeName, 
								GLfloat data[], 
								int dataLength, 
								GLenum usage )
{
	if( ! attributeLocations[attributeName] )
	{
		createVBO( attributeName );
	}
	// Find handle to data buffer
	GLuint bufferHandle = getAttributeLocation( attributeName );
	// Bind to VAO so we assign new VBO to it
	glBindVertexArray( vertexArrayObjectHandle );
	// Bind to the VBO
	glBindBuffer( GL_ARRAY_BUFFER, bufferHandle );
	// Set the data of the buffer
	glBufferData( GL_ARRAY_BUFFER, 
				  dataLength * sizeof( GLfloat ), 
				  data, 
				  usage );


	//TODO return false on errors
	return true;
}	


void ShaderProgram::use()
{
	glUseProgram( handle );
	glBindVertexArray( vertexArrayObjectHandle );
}

//--------------------------------------------------------------------------HELPERS:





