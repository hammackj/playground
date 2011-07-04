#include "fvector3.h"

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
vector3_t vector3_cross(vector3_t *v1, vector3_t *v2)
{
	vector3_t cross = {
		(v1->y * v2->z) - (v1->z * v2->y),
		(v1->z * v2->x) - (v1->x * v2->z),
		(v1->x * v2->y) - (v1->y * v2->x),
	};
	
	return cross;
}


