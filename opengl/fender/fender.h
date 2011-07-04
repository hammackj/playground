#ifndef FENDER_H
#define FENDER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include "fmath.h"
#include "flog.h"
#include "frenderer.h"
#include "finput.h"
#include "fcamera.h"

void fender_init(void);
void fender_shutdown(void);

#endif
