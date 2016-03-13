#include "Camera.h"

//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:

Camera::Camera()
{
}

Camera::Camera( float fieldOfView,
				uint screenWidth, 
				uint screenHeight,
				float nearClipPlane, 
				float farClipPlane )
{
	fov = fieldOfView;
	width = screenWidth;
	height = screenHeight;
	nearClip = nearClipPlane;
	farClip = farClipPlane;
	calcProjection();
}

Camera::~Camera()
{

}

//------------------------------------------------------------------------FUNCTIONS:

//--------------------------------------------------------------------------METHODS:

void Camera::lookAt( vec3 position, vec3 lookAt, vec3 cameraUp )
{
	pos = position;
	center = lookAt;
	up = cameraUp;
	view = glm::lookAt( pos, center, up );
}
mat4 Camera::viewProjectionMatrix()
{	
	return (projection * view);
}

//--------------------------------------------------------------------------HELPERS:

void Camera::calcProjection()
{
	float aspect = 1.0f * width / height;
	projection = glm::perspective( fov, aspect, nearClip, farClip );
}