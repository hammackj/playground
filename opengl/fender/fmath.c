#include "fmath.h"

#include <math.h>

//re-implement this
int math_close_enough(float f1, float f2)
{
	return fabsf((f1 - f2) / ((f2 == 0.0f) ? 1.0f : f2)) < EPSILON;
}
