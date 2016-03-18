#ifndef GL_UTIL
#define GL_UTIL

#include "Dependencies\glew\glew.h"
#include "Dependencies\glfw\glfw3.h"

#include <string>

using namespace std;

class GLUtil
{
	
//----------------------------------------------------------------------------ENUMS:
	
//------------------------------------------------------------------------CONSTANTS:
	
//---------------------------------------------------------------------------FIELDS:
	
//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:
		
//------------------------------------------------------------------------FUNCTIONS:


//--------------------------------------------------------------------------METHODS:

public:
	static bool isError();
	static int maxNumPatches();
	static bool printErrors();

};

#endif