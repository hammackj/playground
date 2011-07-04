#ifndef FCAMERA_H
#define FCAMERA_H

#include "fender.h"

typedef struct camera_t
{
	vector3_t position;
	vector3_t rotation;
	vector3_t eye;
} camera_t;

//Initialize the camera
camera_t camera_init(void);

//Called for each frame
void camera_update(camera_t *camera);

//Movement, negative values for backwards/down
void camera_move(vector3_t *direction, vector3_t *amount);

//void camera_move_forward(float speed);
//void camera_strafe(float speed);
//void camera_fly(float speed);

//Helper functions
void camera_set_position(float x, float y, float z);
void camera_set_rotation(float x, float y, float z);

void camera_get_position(float *x, float *y, float *z);
void camera_get_rotation(float *x, float *y, float *z);

#endif