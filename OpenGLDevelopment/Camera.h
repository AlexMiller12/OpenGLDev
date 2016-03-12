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
	float aspect;
	float near;
	float far;

	vec3 pos;
	vec3 center;
	vec3 up;

	mat4 view;
	mat4 projection;


//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:
		
	Camera( float fieldOfView, float aspectRatio, float nearClip, float farClip );
	~Camera();

//------------------------------------------------------------------------FUNCTIONS:

//--------------------------------------------------------------------------METHODS:

public:
	void lookAt( vec3 position, vec3 lookAt, vec3 up );
private:
	void calcProjection();
};

#endif