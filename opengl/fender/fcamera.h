#ifndef FCAMERA_H
#define FCAMERA_H

#include "fmath.h"

typedef struct
{
	float x, y, z;
} position_t;

typedef struct
{
	float x, y, z;
} rotation_t;

typedef struct 
{
	position_t position;
	rotation_t rotation;
} camera_t;

//Initialize the camera
void camera_init(void);

//Called for each frame
void camera_update(void);

//Movement, negative values for backwards/down
void camera_move_forward(float speed);
void camera_strafe(float speed);
void camera_fly(float speed);

//Helper functions
void camera_set_position(float x, float y, float z);
void camera_set_rotation(float x, float y, float z);

void camera_get_position(float *x, float *y, float *z);
void camera_get_rotation(float *x, float *y, float *z);

#endif