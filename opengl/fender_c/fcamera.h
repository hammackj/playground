#ifndef FCAMERA_H
#define FCAMERA_H

#include "fender.h"

typedef struct
{
	vector3_t position;
	vector3_t rotation;
	vector3_t eye;
	
	float fovx;
	float znear;
	float aspect_ratio;
	float accum_pitch_degrees;
	
	vector3_t x_axis;
	vector3_t y_axis;
	vector3_t z_axis;
	vector3_t view_dir;
} camera_t;

/*
float m_fovx;
float m_znear;
float m_zfar;
float m_aspectRatio;
float m_accumPitchDegrees;
Vector3 m_eye;
Vector3 m_xAxis;
Vector3 m_yAxis;
Vector3 m_zAxis;
Vector3 m_viewDir;
Vector3 m_acceleration;
Vector3 m_currentVelocity;
Vector3 m_velocity;
Quaternion m_orientation;
Matrix4 m_viewMatrix;
Matrix4 m_projMatrix;
*/
//Initialize the camera
camera_t camera_init(void);

void camera_lookat(vector3_t *eye, vector3_t *target, vector3_t *up);

void camera_perspective(float fovx, float aspect, float znear, float zfar);
void camera_rotate(float heading_degrees, float pitch_degrees, float roll_degrees);
void camera_update_poisition(vector3_t *direction, float elapsed_time_sec);

//Called for each frame
//void camera_update(camera_t *camera);

//Movement, negative values for backwards/down
//void camera_move(camera_t *camera, vector3_t *direction, vector3_t *amount);


//void camera_rotate_first_person(float heading_degrees, float pitch_degrees);

//void camera_move_forward(float speed);
//void camera_strafe(float speed);
//void camera_fly(float speed);

//Helper functions
void camera_set_position(float x, float y, float z);
void camera_set_rotation(float x, float y, float z);

void camera_get_position(float *x, float *y, float *z);
void camera_get_rotation(float *x, float *y, float *z);

#endif