#include "frenderer.h"

static int frame = 0;
static long time_elapsed = 0;
static long time_base = 0;
static float fps = 0;

/**
 *
 */
void renderer_init()
{
	glEnable (GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glShadeModel (GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
}

/**
 *
 */
void renderer_calculate_fps()
{
	frame++;

	time_elapsed = glutGet(GLUT_ELAPSED_TIME);
	
	if ((time_elapsed - time_base) > 1000) 
	{
		fps = (frame * 1000.0) / (time_elapsed - time_base);
		time_base = time_elapsed;
		frame = 0;
	}	
}

/**
 *
 */
float renderer_get_fps()
{
	return fps;
}

/**
 *
 */
void renderer_resize(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

/**
 *
 */
void renderer_render(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	renderer_calculate_fps();
	
	glutSwapBuffers();
}