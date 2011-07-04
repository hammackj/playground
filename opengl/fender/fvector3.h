#ifndef FVECTOR3_H
#define FVECTOR3_H

#include "fender.h"

typedef struct
{
	float x;
	float y;
	float z;
} vector3_t;


float vector3_length(vector3_t *v);
void vector3_normalize(vector3_t *v);

float vector3_dot(vector3_t *v1, vector3_t *v2);
vector3_t vector3_cross(vector3_t *v1, vector3_t *v2);

vector3_t vector3_inverse(vector3_t *v1);
float vector3_magnitude(vector3_t *v1);

vector3_t vector3_add(vector3_t *v1, vector3_t *v2);
vector3_t vector3_subtract(vector3_t *v1, vector3_t *v2);
vector3_t vector3_multiply(vector3_t *v1, vector3_t *v2);
vector3_t vector3_divide(vector3_t *v1, vector3_t *v2);

#endif