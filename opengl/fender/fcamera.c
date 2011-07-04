#include "fcamera.h"

camera_t camera_init(void)
{
	camera_t camera;
	camera.position.x = 0.0f;
	camera.position.y = 0.0f;
	camera.position.z = 0.0f;

	camera.rotation.x = 0.0f;
	camera.rotation.y = 0.0f;
	camera.rotation.z = 0.0f;

	camera.eye.x = 0.0f;
	camera.eye.y = 0.0f;
	camera.eye.z = 0.0f;		
	
	return camera;
}
