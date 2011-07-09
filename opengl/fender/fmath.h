#ifndef FMATH_H
#define FMATH_H

#define PI 3.1415926f
#define HALF_PI PI / 2.0f
#define QUARTER_PI PI / 4.0f
#define TWO_PI PI * 2.0f
#define EPSILON 1e-6f

#define DEGREES_TO_RADIANS(degrees) ((degrees * PI) / 180.0f)
#define RADIANS_TO_DEGREES(radians) ((radians * 180.0f) / PI)

int math_close_enough(float f1, float f2);

#endif