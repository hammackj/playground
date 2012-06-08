#include "frenderer.h"

static int window_height = 0;
static int window_width = 0;

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

void renderer_render_bitmap_string(float x, float y, float z, void *font, char *string)
{
	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) 
	{
		glutBitmapCharacter(font, *c);
	}
}

void renderer_draw_renderer_status(void)
{
	char fps_status[25];
	
	sprintf(fps_status, "FPS: %4.2f", renderer_get_fps());
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, window_width, window_height, 0);
	glMatrixMode(GL_MODELVIEW);
	//glDisable (GL_LIGHTING);
	glPushMatrix();
	glLoadIdentity();
	renderer_render_bitmap_string(5, 30, 0, GLUT_BITMAP_HELVETICA_12, fps_status);
	glPopMatrix();
	//glEnable (GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

/**
 *
 */
void renderer_resize(int w, int h)
{
	window_width = w;	
	window_height = h;

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
	renderer_draw_renderer_status();
	
	glutSwapBuffers();
}