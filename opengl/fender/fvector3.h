#ifndef FVECTOR3_H
#define FVECTOR3_H

#include "common.h"

typedef struct
{
	float x;
	float y;
	float z;
} vector3_t;

float vector3_length(vector3_t *v);
void vector3_normalize(vector3_t *v);

float vector3_dot(vector3_t *v1, vector3_t *v2);
void vector3_cross(vector3_t *v1, vector3_t *v2, vector3_t *dst);

void vector3_inverse(vector3_t *v1, vector3_t *result);
float vector3_magnitude(vector3_t *v1);
float vector3_distance(vector3_t *v1, vector3_t *v2);

void vector3_add(vector3_t *v1, vector3_t *v2, vector3_t *result);
void vector3_subtract(vector3_t *v1, vector3_t *v2, vector3_t *result);

void vector3_multiply_scalar(vector3_t *v, float scalar, vector3_t *result);

void vector3_divide_scalar(vector3_t *v, float scalar, vector3_t *result);

int vector3_equal(vector3_t *v1, vector3_t *v2);
int vector3_not_equal(vector3_t *v1, vector3_t *v2);

void vector3_zero(vector3_t *v);

#endif
