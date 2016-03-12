#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <unordered_map>
#include "Dependencies\glew\glew.h"
#include "Dependencies\glfw\glfw3.h"

using namespace std;

class ShaderProgram
{
	
//----------------------------------------------------------------------------ENUMS:
	
//------------------------------------------------------------------------CONSTANTS:

public:
	// https://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/attributes.php
	// These constants are reserved in opengl (at least for NVidia): 
	const GLint gl_Vertex			= 0;
	const GLint gl_Normal			= 2;
	const GLint gl_Color			= 3;
	const GLint gl_SecondaryColor	= 4;
	const GLint gl_FogCoord			= 5;
	const GLint gl_MultiTexCoord0	= 8;
	const GLint gl_MultiTexCoord1	= 9;
	const GLint gl_MultiTexCoord2	= 10;
	const GLint gl_MultiTexCoord3	= 11;
	const GLint gl_MultiTexCoord4	= 12;
	const GLint gl_MultiTexCoord5	= 13;
	const GLint gl_MultiTexCoord6	= 14;
	const GLint gl_MultiTexCoord7	= 15;

//---------------------------------------------------------------------------FIELDS:
public:
	// Handle to the vao to which we will account any vbos
	GLuint vertexArrayObjectHandle;

private:
	// Program handle
	GLuint handle;
	// Handle to the vao to which we will account any vbos
	//GLuint vertexArrayObjectHandle;

	unordered_map<string, GLint> uniformLocations;
	unordered_map<string, GLint> attributeLocations;

	bool isVAOInitialized;
	//unordered_map<string, GLint> samplerTextureNumbers;

//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:

public:
	ShaderProgram();
	ShaderProgram( const char* vertexSource, const char* fragmentSource );
	~ShaderProgram();

//--------------------------------------------------------------------------METHODS:

public:
	bool enableVec3Attribute( string attributeName, GLuint attributeindex );

	GLuint getAttributeLocation( string name );
	GLuint getHandle();
	GLuint getUniformLocation( string name );

	bool setVec3VBO( string attributeName, 
					 float data[], 
					 int dataLength, 
					 GLenum usage = GL_STATIC_DRAW );
	void use();

private:
	bool createVBO( string attributeName );
	GLuint shaderFromSource( const char* vertexSource, const char* fragmentSource );
};

#endif