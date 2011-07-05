#ifndef FMATRIX4
#define FMATRIX4

#include "fmath.h"

typedef struct
{
	float matrix[4][4];
} matrix4_t;

float matrix4_determinant();

void matrix4_from_axes(vector3_t *x, vector3_t *y, vector3_t *z);

void matrix4_identity();
void matrix4_inverse();
void matrix4_transpose();



#endif