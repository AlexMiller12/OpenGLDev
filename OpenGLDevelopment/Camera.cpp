#include "Camera.h"

//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:

Camera::Camera()
{
}

Camera::Camera( float fieldOfView,
				float aspectRatio, 
				float nearClipPlane, 
				float farClipPlane )
{
	fov = fieldOfView;
	aspect = aspectRatio;
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
	projection = glm::perspective( fov, aspect, nearClip, farClip );
}