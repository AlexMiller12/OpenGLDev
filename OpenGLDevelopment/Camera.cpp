#include "Camera.h"

//---------------------------------------------------------CONSTRUCTORS/DESTRUCTORS:

Camera::Camera( float fieldOfView,
				float aspectRatio, 
				float nearClip, 
				float farClip )
{
	fov = fieldOfView;
	aspect = aspectRatio;
	near = nearClip;
	far = farClip;	
	calcProjection();
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

//--------------------------------------------------------------------------HELPERS:

void Camera::calcProjection()
{
	projection = glm::perspective( fov, aspect, near, far );
}