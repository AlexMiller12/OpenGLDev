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
	
//---------------------------------------------------------------------------FIELDS:
public:
	// Handle to the vao to which we will account any vbos
	GLuint vertexArrayObjectHandle;

private:
	// Program handle
	GLuint handle;
	// Handle to the vao to which we will account any vbos
	//GLuint vertexArrayObjectHandle;
	// Uniform and attribute locations
	unordered_map<string, GLint> locations;

	bool isVAOInitialized;
	//unordered_map<string, GLint> samplerTextureNumbers;

//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:

public:
	ShaderProgram();
	ShaderProgram( const char* vertexSource, const char* fragmentSource );
	~ShaderProgram();

//--------------------------------------------------------------------------METHODS:

public:
	GLuint getHandle();
	GLuint getLocation( string name );

	bool setVec3VBO( string attributeName, 
					 float data[], 
					 int numPoints, 
					 GLenum usage = GL_STATIC_DRAW );
	void use();

private:
	bool createVBO( string attributeName );
	GLuint shaderFromSource( const char* vertexSource, const char* fragmentSource );
};

#endif