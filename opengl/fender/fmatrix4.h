#ifndef FMATRIX4
#define FMATRIX4

#include "common.h"
#include "fmath.h"
#include "fvector3.h"

typedef struct
{
	float matrix[4][4];
} matrix4_t;

void matrix4_from_head_pitch_roll(matrix4_t *m, float head_degrees, float pitch_degrees, float roll_degrees);
void matrix4_to_head_pitch_roll(matrix4_t *m, float *head_degrees, float *pitch_degrees, float *roll_degrees);
void matrix4_rotate(matrix4_t *m, vector3_t *axis, float degrees);
void matrix4_identity(matrix4_t *m);

void matrix4_add(matrix4_t *m1, matrix4_t *m2);
void matrix4_subtract(matrix4_t *m1, matrix4_t *m2);
void matrix4_multiply(matrix4_t *m1, matrix4_t *m2, matrix4_t *m3);
void matrix4_divide(matrix4_t *m1, matrix4_t *m2);

bool matrix4_equal(matrix4_t *m1, matrix4_t *m2);
bool matrix4_not_equal(matrix4_t *m1, matrix4_t *m2);

//float matrix4_determinant(matrix4_t *m);
//void matrix4_from_axes(matrix4_t *m, vector3_t *x, vector3_t *y, vector3_t *z);
//void matrix4_from_axes_transposed(matrix4_t *m, vector3_t *x, vector3_t *y, vector3_t *z);
//void matrix4_orient(matrix4_t *m, vector3_t *from, vector3_t *to);
//void matrix4_scale(matrix4_t *m, float sx, float sy, float sz);
//void matrix4_to_axes(matrix4_t *m, vector3_t *x, vector3_t *y, vector3_t *z);
//void matrix4_to_axes_transposed(matrix4_t *m, vector3_t *x, vector3_t *y, vector3_t *z);
//void matrix4_inverse(matrix4_t *m, matrix4_t *dst);
//void matrix4_transpose(matrix4_t *m, matrix4_t *result);
//void matrix4_translate(matrix4_t *m);

#endif