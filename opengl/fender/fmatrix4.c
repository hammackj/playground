#include "fmatrix4.h"

/**
 *
 *
 */
void matrix4_from_head_pitch_roll(matrix4_t *m, float head_degrees, float pitch_degrees, float roll_degrees)
{
	float cosH = 0.0f, cosP = 0.0f, cosR = 0.0f;
	float sinH = 0.0f, sinP = 0.0f, sinR = 0.0f;
	
	head_degrees = DEGREES_TO_RADIANS(head_degrees);
	pitch_degrees = DEGREES_TO_RADIANS(pitch_degrees);
	roll_degrees = DEGREES_TO_RADIANS(roll_degrees);
	
	cosH = cosf(head_degrees);
	cosP = cosf(pitch_degrees);
	cosR = cosf(roll_degrees);

	sinH = sinf(head_degrees);
	sinP = sinf(pitch_degrees);
	sinR = sinf(roll_degrees);
	
	m->matrix[0][0] = cosR * cosH - sinR * sinP * sinH;
	m->matrix[0][1] = sinR * cosH + cosR * cosP * sinH;
	m->matrix[0][2] = -cosP * sinH;
	m->matrix[0][3] = 0.0f;
	
	m->matrix[1][0] = -sinR * cosP;
	m->matrix[1][1] = cosR * cosP;
	m->matrix[1][2] = sinP;
	m->matrix[1][3] = 0.0f;
	
	m->matrix[2][0] = cosR * sinH + sinR * sinP * cosH;
	m->matrix[2][1] = sinR * sinH - cosR * sinP * cosH;
	m->matrix[2][2] = cosP * cosH;
	m->matrix[2][3] = 0.0f;

	m->matrix[3][0] = 0.0f;
	m->matrix[3][1] = 0.0f;
	m->matrix[3][2] = 0.0f;
	m->matrix[3][3] = 0.0f;
}

/**
 *
 *
 */
void matrix4_to_head_pitch_roll(matrix4_t *m, float *head_degrees, float *pitch_degrees, float *roll_degrees)
{
	float thetaX = asinf(m->matrix[1][2]);
	float thetaY = 0.0f;
	float thetaZ = 0.0f;
	
	if (thetaX < HALF_PI)
	{
		if (thetaX > -HALF_PI)
		{
			thetaZ = atan2f(-m->matrix[1][0], m->matrix[1][1]);
			thetaY = atan2f(-m->matrix[0][2], m->matrix[2][2]);
		}
		else
		{
			thetaZ = -atan2f(m->matrix[2][0], m->matrix[0][0]);
			thetaY = 0.0f;
		}
	}
	else
	{
		thetaZ = atan2f(m->matrix[2][0], m->matrix[0][0]);
		thetaY = 0.0f;
	}
	
	*head_degrees = RADIANS_TO_DEGREES(thetaY);
	*pitch_degrees = RADIANS_TO_DEGREES(thetaX);
	*roll_degrees = RADIANS_TO_DEGREES(thetaZ);
}

/**
 *
 *
 */
void matrix4_rotate(matrix4_t *m, vector3_t *axis, float degrees)
{
	float x = 0.0f, y = 0.0f, z = 0.0f;
	float c = 0.0f, s = 0.0f;
	
	degrees = DEGREES_TO_RADIANS(degrees);
	
	x = axis->x;
	y = axis->y;
	z = axis->z;
	c = cosf(degrees);
	z = sinf(degrees);
	
	m->matrix[0][0] = (x * x) * (1.0f - c) + c;
	m->matrix[0][1] = (x * y) * (1.0f - c) + (z * s);
	m->matrix[0][2] = (x * z) * (1.0f - c) - (y * s);
	m->matrix[0][3] = 0.0f;
	
	m->matrix[1][0] = (y * x) * (1.0f - c) - (z * s);
	m->matrix[1][1] = (y * y) * (1.0f - c) + c;
	m->matrix[1][2] = (y * z) * (1.0f - c) + (x * s);
	m->matrix[1][3] = 0.0f;
	
	m->matrix[2][0] = (z * x) * (1.0f - c) + (y * s);
	m->matrix[2][1] = (z * y) * (1.0f - c) - (x * s);
	m->matrix[2][2] = (z * z) * (1.0f - c) + c;
	m->matrix[2][3] = 0.0f;
	
	m->matrix[3][0] = 0.0f;
	m->matrix[3][1] = 0.0f;
	m->matrix[3][2] = 0.0f;
	m->matrix[3][3] = 1.0f;
}

/**
 *
 *
 */
void matrix4_identity(matrix4_t *m)
{
	m->matrix[0][0] = 1.0f, m->matrix[0][1] = 0.0f, m->matrix[0][2] = 0.0f, m->matrix[0][3] = 0.0f;
	m->matrix[1][0] = 0.0f, m->matrix[1][1] = 1.0f, m->matrix[1][2] = 0.0f, m->matrix[1][3] = 0.0f;
	m->matrix[2][0] = 0.0f, m->matrix[2][1] = 0.0f, m->matrix[2][2] = 1.0f, m->matrix[2][3] = 0.0f;
	m->matrix[3][0] = 0.0f, m->matrix[3][1] = 0.0f, m->matrix[3][2] = 0.0f, m->matrix[3][3] = 1.0f;				
}

/**
 * Adds m2 to m1
 *
 */
void matrix4_add(matrix4_t *m1, matrix4_t *m2)
{
	m1->matrix[0][0] += m2->matrix[0][0];
	m1->matrix[0][1] += m2->matrix[0][1];
	m1->matrix[0][2] += m2->matrix[0][2];
	m1->matrix[0][3] += m2->matrix[0][3]; 
	
	m1->matrix[1][0] += m2->matrix[1][0];
	m1->matrix[1][1] += m2->matrix[1][1];
	m1->matrix[1][2] += m2->matrix[1][2];
	m1->matrix[1][3] += m2->matrix[1][3];
	
	m1->matrix[2][0] += m2->matrix[2][0];
	m1->matrix[2][1] += m2->matrix[2][1];
	m1->matrix[2][2] += m2->matrix[2][2];
	m1->matrix[2][3] += m2->matrix[2][3];
	
	m1->matrix[3][0] += m2->matrix[3][0];
	m1->matrix[3][1] += m2->matrix[3][1];
	m1->matrix[3][2] += m2->matrix[3][2];
	m1->matrix[3][3] += m2->matrix[3][3];
}

/**
 *
 *
 */
void matrix4_subtract(matrix4_t *m1, matrix4_t *m2)
{
	m1->matrix[0][0] -= m2->matrix[0][0];
	m1->matrix[0][1] -= m2->matrix[0][1];
	m1->matrix[0][2] -= m2->matrix[0][2];
	m1->matrix[0][3] -= m2->matrix[0][3]; 
	
	m1->matrix[1][0] -= m2->matrix[1][0];
	m1->matrix[1][1] -= m2->matrix[1][1];
	m1->matrix[1][2] -= m2->matrix[1][2];
	m1->matrix[1][3] -= m2->matrix[1][3];
	
	m1->matrix[2][0] -= m2->matrix[2][0];
	m1->matrix[2][1] -= m2->matrix[2][1];
	m1->matrix[2][2] -= m2->matrix[2][2];
	m1->matrix[2][3] -= m2->matrix[2][3];
	
	m1->matrix[3][0] -= m2->matrix[3][0];
	m1->matrix[3][1] -= m2->matrix[3][1];
	m1->matrix[3][2] -= m2->matrix[3][2];
	m1->matrix[3][3] -= m2->matrix[3][3];	
}

/**
 *
 *
 */
void matrix4_multiply(matrix4_t *m1, matrix4_t *m2, matrix4_t *m3)
{
	m3->matrix[0][0] = (m1->matrix[0][0] * m2->matrix[0][0]) + (m1->matrix[0][1] * m2->matrix[1][0]) + (m1->matrix[0][2] * m2->matrix[2][0]) + (m1->matrix[0][3] * m2->matrix[3][0]);
	m3->matrix[0][1] = (m1->matrix[0][0] * m2->matrix[0][1]) + (m1->matrix[0][1] * m2->matrix[1][1]) + (m1->matrix[0][2] * m2->matrix[2][1]) + (m1->matrix[0][3] * m2->matrix[3][1]);
	m3->matrix[0][2] = (m1->matrix[0][0] * m2->matrix[0][2]) + (m1->matrix[0][1] * m2->matrix[1][2]) + (m1->matrix[0][2] * m2->matrix[2][2]) + (m1->matrix[0][3] * m2->matrix[3][2]);
	m3->matrix[0][3] = (m1->matrix[0][0] * m2->matrix[0][3]) + (m1->matrix[0][1] * m2->matrix[1][3]) + (m1->matrix[0][2] * m2->matrix[2][3]) + (m1->matrix[0][3] * m2->matrix[3][3]);
	
	m3->matrix[1][0] = (m1->matrix[1][0] * m2->matrix[1][0]) + (m1->matrix[1][1] * m2->matrix[1][0]) + (m1->matrix[1][2] * m2->matrix[2][0]) + (m1->matrix[1][3] * m2->matrix[3][0]);
	m3->matrix[1][1] = (m1->matrix[1][0] * m2->matrix[1][1]) + (m1->matrix[1][1] * m2->matrix[1][1]) + (m1->matrix[1][2] * m2->matrix[2][1]) + (m1->matrix[1][3] * m2->matrix[3][1]);
	m3->matrix[1][2] = (m1->matrix[1][0] * m2->matrix[1][2]) + (m1->matrix[1][1] * m2->matrix[1][2]) + (m1->matrix[1][2] * m2->matrix[2][2]) + (m1->matrix[1][3] * m2->matrix[3][2]);
	m3->matrix[1][3] = (m1->matrix[1][0] * m2->matrix[1][3]) + (m1->matrix[1][1] * m2->matrix[1][3]) + (m1->matrix[1][2] * m2->matrix[2][3]) + (m1->matrix[1][3] * m2->matrix[3][3]);
	
	m3->matrix[2][0] = (m1->matrix[2][0] * m2->matrix[2][0]) + (m1->matrix[2][1] * m2->matrix[1][0]) + (m1->matrix[2][2] * m2->matrix[2][0]) + (m1->matrix[2][3] * m2->matrix[3][0]);
	m3->matrix[2][1] = (m1->matrix[2][0] * m2->matrix[2][1]) + (m1->matrix[2][1] * m2->matrix[1][1]) + (m1->matrix[2][2] * m2->matrix[2][1]) + (m1->matrix[2][3] * m2->matrix[3][1]);
	m3->matrix[2][2] = (m1->matrix[2][0] * m2->matrix[2][2]) + (m1->matrix[2][1] * m2->matrix[1][2]) + (m1->matrix[2][2] * m2->matrix[2][2]) + (m1->matrix[2][3] * m2->matrix[3][2]);
	m3->matrix[2][3] = (m1->matrix[2][0] * m2->matrix[2][3]) + (m1->matrix[2][1] * m2->matrix[1][3]) + (m1->matrix[2][2] * m2->matrix[2][3]) + (m1->matrix[2][3] * m2->matrix[3][3]);
	
	m3->matrix[3][0] = (m1->matrix[3][0] * m2->matrix[3][0]) + (m1->matrix[3][1] * m2->matrix[1][0]) + (m1->matrix[3][2] * m2->matrix[2][0]) + (m1->matrix[3][3] * m2->matrix[3][0]);
	m3->matrix[3][1] = (m1->matrix[3][0] * m2->matrix[3][1]) + (m1->matrix[3][1] * m2->matrix[1][1]) + (m1->matrix[3][2] * m2->matrix[2][1]) + (m1->matrix[3][3] * m2->matrix[3][1]);
	m3->matrix[3][2] = (m1->matrix[3][0] * m2->matrix[3][2]) + (m1->matrix[3][1] * m2->matrix[1][2]) + (m1->matrix[3][2] * m2->matrix[2][2]) + (m1->matrix[3][3] * m2->matrix[3][2]);
	m3->matrix[3][3] = (m1->matrix[3][0] * m2->matrix[3][3]) + (m1->matrix[3][1] * m2->matrix[1][3]) + (m1->matrix[3][2] * m2->matrix[2][3]) + (m1->matrix[3][3] * m2->matrix[3][3]);
}

/**
 *
 *
 */
void matrix4_divide(matrix4_t *m1, matrix4_t *m2)
{
	//TODO
}

/**
 *
 *
 */
bool matrix4_equal(matrix4_t *m1, matrix4_t *m2)
{
	return math_close_enough(m1->matrix[0][0], m2->matrix[0][0]) &&
		math_close_enough(m1->matrix[0][1], m2->matrix[0][1]) &&
		math_close_enough(m1->matrix[0][2], m2->matrix[0][2]) &&
		math_close_enough(m1->matrix[0][3], m2->matrix[0][3]) &&
		math_close_enough(m1->matrix[1][0], m2->matrix[1][0]) &&
		math_close_enough(m1->matrix[1][1], m2->matrix[1][1]) &&
		math_close_enough(m1->matrix[1][2], m2->matrix[1][2]) &&
		math_close_enough(m1->matrix[1][3], m2->matrix[1][3]) &&		
		math_close_enough(m1->matrix[2][0], m2->matrix[2][0]) &&
		math_close_enough(m1->matrix[2][1], m2->matrix[2][1]) &&
		math_close_enough(m1->matrix[2][2], m2->matrix[2][2]) &&
		math_close_enough(m1->matrix[2][3], m2->matrix[2][3]) &&
		math_close_enough(m1->matrix[3][0], m2->matrix[3][0]) &&
		math_close_enough(m1->matrix[3][1], m2->matrix[3][1]) &&
		math_close_enough(m1->matrix[3][2], m2->matrix[3][2]) &&
		math_close_enough(m1->matrix[3][3], m2->matrix[3][3]);
}

/**
 *
 *
 */
bool matrix4_not_equal(matrix4_t *m1, matrix4_t *m2)
{
	return !matrix4_equal(m1, m2);
}



/*float matrix4_determinant(matrix4_t *m)
{
  return (m->matrix[0][0] * m->matrix[1][1] - m->matrix[1][0] * m->matrix[0][1])
      * (m->matrix[2][2] * m->matrix[3][3] - m->matrix[3][2] * m->matrix[2][3])
      - (m->matrix[0][0] * m->matrix[2][1] - m->matrix[2][0] * m->matrix[0][1])
      * (m->matrix[1][2] * m->matrix[3][3] - m->matrix[3][2] * m->matrix[1][3])
      + (m->matrix[0][0] * m->matrix[3][1] - m->matrix[3][0] * m->matrix[0][1])
      * (m->matrix[1][2] * m->matrix[2][3] - m->matrix[2][2] * m->matrix[1][3])
      + (m->matrix[1][0] * m->matrix[2][1] - m->matrix[2][0] * m->matrix[1][1])
      * (m->matrix[0][2] * m->matrix[3][3] - m->matrix[3][2] * m->matrix[0][3])
      - (m->matrix[1][0] * m->matrix[3][1] - m->matrix[3][0] * m->matrix[1][1])
      * (m->matrix[0][2] * m->matrix[2][3] - m->matrix[2][2] * m->matrix[0][3])
      + (m->matrix[2][0] * m->matrix[3][1] - m->matrix[3][0] * m->matrix[2][1])
      * (m->matrix[0][2] * m->matrix[1][3] - m->matrix[1][2] * m->matrix[0][3]);
}*/

/*void matrix4_from_axes(matrix4_t *m, vector3_t *x, vector3_t *y, vector3_t *z)
{
	m->matrix[0][0] = x->x, m->matrix[0][1] = x->y, m->matrix[0][2] = x->z, m->matrix[0][3] = 0.0f;
	m->matrix[1][0] = y->x, m->matrix[1][1] = y->y, m->matrix[1][2] = y->z, m->matrix[1][3] = 0.0f;
	m->matrix[2][0] = z->x, m->matrix[2][1] = z->y, m->matrix[2][2] = z->z, m->matrix[2][3] = 0.0f;
	m->matrix[3][0] = 0.0f, m->matrix[3][1] = 0.0f, m->matrix[3][2] = 0.0f, m->matrix[3][3] = 1.0f;
}

void matrix4_from_axes_transposed(matrix4_t *m, vector3_t *x, vector3_t *y, vector3_t *z)
{
	m->matrix[0][0] = x->x, m->matrix[0][1] = y->y, m->matrix[0][2] = z->z, m->matrix[0][3] = 0.0f; 
	m->matrix[1][0] = x->x, m->matrix[1][1] = y->y, m->matrix[1][2] = z->z, m->matrix[1][3] = 0.0f; 
	m->matrix[2][0] = x->x, m->matrix[2][1] = y->y, m->matrix[2][2] = z->z, m->matrix[2][3] = 0.0f; 
	m->matrix[3][0] = 0.0f, m->matrix[3][1] = 0.0f, m->matrix[3][2] = 0.0f, m->matrix[3][3] = 1.0f;	
}

void matrix4_orient(matrix4_t *m, vector3_t *from, vector3_t *to)
{
	float e = 0.0f;
	
	e = vector3_dot(from, to);
	
	if (math_close_enough(e, 1.0f))
	{
		matrix4_identity(m);
	}
	else if (math_close_enough(e, -1.0f))
	{
		vector3_t side;
		vector3_set(&side, 0.0f, from->z, -from->y);
		
		if (math_close_enough(vector3_dot(&side, &side), 0.0f))
		{
			vector3_set(&side, -from->z, 0.0f, from->x);
		}
		
		vector3_normalize(&side);
		
		vector3_t up;
		
		vector3_cross(&side, from, &up);
		
		vector3_normalize(&up);
		
		m->matrix[0][0] = -(from->x * from->x) + (up.x * up.x) - (side.x * side.x);
		m->matrix[0][1] = -(from->x * from->y) + (up.x * up.y) - (side.x * side.y);
		m->matrix[0][2] = -(from->x * from->z) + (up.x * up.z) - (side.x * side.z);
		m->matrix[0][3] = 0.0f;

		m->matrix[1][0] = -(from->x * from->y) + (up.x * up.y) - (side.x * side.y);
		m->matrix[1][1] = -(from->y * from->y) + (up.y * up.y) - (side.y * side.y);
		m->matrix[1][2] = -(from->y * from->z) + (up.y * up.z) - (side.y * side.z);
		m->matrix[1][3] = 0.0f;
		
		m->matrix[2][0] = -(from->x * from->z) + (up.x * up.z) - (side.x * side.z);
		m->matrix[2][1] = -(from->y * from->z) + (up.y * up.z) - (side.y * side.z);
		m->matrix[2][2] = -(from->z * from->z) + (up.z * up.z) - (side.z * side.z);
		m->matrix[2][3] = 0.0f;
		
		m->matrix[3][0] = 0.0f;
		m->matrix[3][1] = 0.0f;
		m->matrix[3][2] = 0.0f;
		m->matrix[3][3] = 1.0f;						
	}
	else
	{
		vector3_t v;
		float h = 0.0f;
		
		vector3_cross(&v, from, to);
		vector3_normalize(&v);
		
		h = (1.0f - e) / vector3_dot(&v, &v);
		
		m->matrix[0][0] = e + h * v.x * v.x;
		m->matrix[0][1] = h * v.x * v.y + v.z;
		m->matrix[0][2] = h * v.x * v.z - v.y;
		m->matrix[0][3] = 0.0f;
		
		m->matrix[1][0] = h * v.x * v.y - v.z;
		m->matrix[1][1] = e + h * v.y * v.y;
		m->matrix[1][2] = h * v.x * v.z + v.x;
		m->matrix[1][3] = 0.0f;
		
		m->matrix[2][0] = h * v.x * v.z + v.y;
		m->matrix[2][1] = h * v.y * v.z + v.x;
		m->matrix[2][2] = e + h * v.z * v.z;
		m->matrix[2][3] = 0.0f;
		
		m->matrix[3][0] = 0.0f;
		m->matrix[3][1] = 0.0f;
		m->matrix[3][2] = 0.0f;
		m->matrix[3][3] = 1.0f;		
	}
}

void matrix4_scale(matrix4_t *m, float sx, float sy, float sz)
{
	m->matrix[0][0] = sx;
	m->matrix[0][1] = 0.0f;
	m->matrix[0][2] = 0.0f;
	m->matrix[0][3] = 0.0f;

	m->matrix[1][0] = 0.0f;
	m->matrix[1][1] = sy;
	m->matrix[1][2] = 0.0f;
	m->matrix[1][3] = 0.0f;	

	m->matrix[2][0] = 0.0f;
	m->matrix[2][1] = 0.0f;
	m->matrix[2][2] = sz;
	m->matrix[2][3] = 0.0f;
	
	m->matrix[3][0] = 0.0f;
	m->matrix[3][1] = 0.0f;
	m->matrix[3][2] = 0.0f;
	m->matrix[3][3] = 1.0f;	
}

void matrix4_to_axes(matrix4_t *m, vector3_t *x, vector3_t *y, vector3_t *z)
{
	x->x = m->matrix[0][0], x->y = m->matrix[0][1], x->z = m->matrix[0][2];
	y->x = m->matrix[1][0], y->y = m->matrix[1][1], y->z = m->matrix[1][2];
	z->x = m->matrix[2][0], z->y = m->matrix[2][1], z->z = m->matrix[2][2];
}

void matrix4_to_axes_transposed(matrix4_t *m, vector3_t *x, vector3_t *y, vector3_t *z)
{
	
}





void matrix4_inverse(matrix4_t *m, matrix4_t *dst)
{
	float d = 0.0f;
	
	d = matrix4_determinant(m);
	
	if (math_close_enough(d, 0.0f))
	{
		matrix4_identity(dst);
	}
	else
	{
		d = 1.0f / d;
		
		dst->matrix[0][0];
	}
	
}

void matrix4_transpose(matrix4_t *m, matrix4_t *result)
{
	result->matrix[0][0] = m->matrix[0][0];
	result->matrix[0][1] = m->matrix[1][0];
	result->matrix[0][2] = m->matrix[2][0];
	result->matrix[0][3] = m->matrix[3][0];
	
	result->matrix[1][0] = m->matrix[0][1];
	result->matrix[1][1] = m->matrix[1][1];
	result->matrix[1][2] = m->matrix[2][1];
	result->matrix[1][3] = m->matrix[3][1];
	
	result->matrix[2][0] = m->matrix[0][2];
	result->matrix[2][1] = m->matrix[1][2];
	result->matrix[2][2] = m->matrix[2][2];
	result->matrix[2][3] = m->matrix[3][2];
	
	result->matrix[3][0] = m->matrix[0][3];
	result->matrix[3][1] = m->matrix[1][3];
	result->matrix[3][2] = m->matrix[2][3];
	result->matrix[3][3] = m->matrix[3][3];
}
void matrix4_translate(matrix4_t *m);
*/