#include "fvector3.h"

vector3_t zero_vector = { 0.0f, 0.0f, 0.0f };

/**
 *
 */
float vector3_length(vector3_t *v)
{	
	 return (sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z)));	
}

/**
 *
 */
void vector3_normalize(vector3_t *v)
{
	float len = vector3_length(v);
	
	v->x /= len;
	v->y /= len;
	v->z /= len;
}

/**
 *
 */
float vector3_dot(vector3_t *v1, vector3_t *v2)
{
	return ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
}

/**
 *
 */
void vector3_cross(vector3_t *v1, vector3_t *v2, vector3_t *dst)
{
	dst->x = (v1->y * v2->z) - (v1->z * v2->y);
	dst->y = (v1->z * v2->x) - (v1->x * v2->z);
	dst->z = (v1->x * v2->y) - (v1->y * v2->x);
}

//check this function for accuracy
void vector3_inverse(vector3_t *v1, vector3_t *result)
{
	result->x = -v1->x;
	result->y = -v1->y;
	result->z = -v1->z;
}

/**
 *
 */
float vector3_magnitude(vector3_t *v1)
{
	return sqrt((v1->x * v1->x) + (v1->y * v1->y) + (v1->y * v1->y));
}

/**
 *
 */
float vector3_distance(vector3_t *v1, vector3_t *v2)
{
	return sqrt(((v1->x - v2->x) * (v1->x - v2->x)) + ((v1->y - v2->y) * (v1->x - v2->y)) + ((v1->z - v2->z) * (v1->z - v2->z)));
}

/**
 *
 */
void vector3_add(vector3_t *v1, vector3_t *v2, vector3_t *result)
{
	result->x = v1->x + v2->x;
	result->y = v1->y + v2->y;
	result->z = v1->z + v2->z;		
}

/**
 *
 */
void vector3_subtract(vector3_t *v1, vector3_t *v2, vector3_t *result)
{
	result->x = v1->x - v2->x;
	result->y = v1->y - v2->y;
	result->z = v1->z - v2->z;	
}

/**
 *
 */
void vector3_multiply_scalar(vector3_t *v, float scalar, vector3_t *result)
{
	result->x = v->x * scalar;
	result->y = v->y * scalar;
	result->z = v->z * scalar;		
}

/**
 *
 */
void vector3_divide_scalar(vector3_t *v, float scalar, vector3_t *result)
{
	result->x = v->x * (1.0f /scalar);
	result->y = v->y * (1.0f /scalar);
	result->z = v->z * (1.0f /scalar);
}

/**
 *
 */
int vector3_equal(vector3_t *v1, vector3_t *v2)
{
	return ((v1->x == v2->x) && (v1->y == v2->y) && (v1->z == v2->z));
}

/**
 *
 */
int vector3_not_equal(vector3_t *v1, vector3_t *v2)
{
	return ((v1->x != v2->x) || (v1->y != v2->y) || (v1->z != v2->z));
}

/**
 *
 */
void vector3_zero(vector3_t *v)
{
	v->x = 0.0f;
	v->y = 0.0f;
	v->z = 0.0f;
}
