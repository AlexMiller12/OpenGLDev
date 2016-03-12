#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <unordered_map>
#include <vector>
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
	const static GLint gl_Vertex			= 0;
	const static GLint gl_Normal			= 2;
	const static GLint gl_Color				= 3;
	const static GLint gl_SecondaryColor	= 4;
	const static GLint gl_FogCoord			= 5;
	const static GLint gl_MultiTexCoord0	= 8;
	const static GLint gl_MultiTexCoord1	= 9;
	const static GLint gl_MultiTexCoord2	= 10;
	const static GLint gl_MultiTexCoord3	= 11;
	const static GLint gl_MultiTexCoord4	= 12;
	const static GLint gl_MultiTexCoord5	= 13;
	const static GLint gl_MultiTexCoord6	= 14;
	const static GLint gl_MultiTexCoord7	= 15;

//---------------------------------------------------------------------------FIELDS:
public:

private:
	// Program handle
	GLuint handle;
	// Handle to the vao to which we will account any vbos
	GLuint vertexArrayObjectHandle;

	unordered_map<string, GLint> uniformLocations;
	unordered_map<string, GLint> attributeLocations;
	//unordered_map<string, GLint> attributeLocations;

	//vector<GLuint> shaders; 

	bool isVAOInitialized;
	//unordered_map<string, GLint> samplerTextureNumbers;

//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:

public:
	ShaderProgram();
	~ShaderProgram();

//--------------------------------------------------------------------------METHODS:

public:
	bool attatchShaders( const char* vertexSource, const char* fragmentSource );
	bool bindToVAO(); 
	bool createVBO( string attributeName );
	bool enableVec3Attribute( string attributeName, GLuint attributeindex );

	bool finalizeProgram();
	GLuint getAttributeLocation( string name );
	GLuint getHandle();
	GLuint getUniformLocation( string name );


	bool setVec3VBO( string attributeName, 
					 GLfloat data[], 
					 int dataLength, 
					 GLenum usage = GL_STATIC_DRAW );
	void use();

private:
};

#endif