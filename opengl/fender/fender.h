#ifndef FENDER_H
#define FENDER_H

#include "common.h"

#include "fmath.h"
#include "fvector3.h"
#include "fmatrix4.h"
#include "fquartnion.h"
#include "flog.h"
#include "frenderer.h"
#include "finput.h"
#include "fcamera.h"
#include "fmatrix4.h"

extern vector3_t zero_vector;

void fender_init(void);
void fender_shutdown(void);

#endif
