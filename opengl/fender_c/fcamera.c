#include "fcamera.h"

static void camera_update_view_matrix(void);

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

void camera_move(camera_t *camera, vector3_t *direction, vector3_t *amount)
{
	camera->eye.x += direction->x * amount->x;
	camera->eye.y += direction->y * amount->y;
	camera->eye.z += direction->z * amount->z;
	
	camera_update_view_matrix();
}

void camera_update_view_matrix()
{
	int x;
	
	x = 1;
}