#ifndef MY_CAMERA
#define MY_CAMERA

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"

using namespace glm;

class Camera
{
	
//----------------------------------------------------------------------------ENUMS:
	
//------------------------------------------------------------------------CONSTANTS:
	
//---------------------------------------------------------------------------FIELDS:
	
private:
	float fov;
	float nearClip;
	float farClip;

	uint width, height;

	vec3 pos;
	vec3 center;
	vec3 up;

	mat4 view;
	mat4 projection;


//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:
		
public:
	Camera();
	Camera( float fieldOfView, 
			uint screenWidth, 
			uint screenHeight, 
			float nearClipPlane, 
			float farClipPlane );
	~Camera();

//------------------------------------------------------------------------FUNCTIONS:

//--------------------------------------------------------------------------METHODS:

public:
	void lookAt( vec3 position, vec3 lookAt, vec3 up );
	mat4 viewProjectionMatrix();
private:
	void calcProjection();
};

#endif