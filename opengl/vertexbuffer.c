#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

GLfloat vertices[] =
{
  -1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
   1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
  -1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
  -1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
  -1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
  -1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
};

GLfloat colors[] =
{
  0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
  1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
  0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
  0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
  0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
  0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
};

/*
** Function called to update rendering
*/
void		DisplayFunc(void)
{
  static float alpha = 0;

  /* Clear the buffer, clear the matrix */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  /* A step backward, then spin the cube */
  glTranslatef(0, 0, -10);
  glRotatef(30, 1, 0, 0);
  glRotatef(alpha, 0, 1, 0);

  /* We have a color array and a vertex array */
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glColorPointer(3, GL_FLOAT, 0, colors);

  /* Send data : 24 vertices */
  glDrawArrays(GL_QUADS, 0, 24);

  /* Cleanup states */
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);


  /* Rotate a bit more */
  alpha = alpha + 0.1;

  /* End */
  glFlush();
  glutSwapBuffers();

  /* Update again and again */
  glutPostRedisplay();
}

/*
** Function called when the window is created or resized
*/
void		ReshapeFunc(int width, int height)
{
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  gluPerspective(20, width / (float) height, 5, 15);
  glViewport(0, 0, width, height);

  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();
}

/*
** Function called when a key is hit
*/
void		KeyboardFunc(unsigned char key, int x, int y)
{
  int foo;

  foo = x + y; /* Has no effect: just to avoid a warning */
  if ('q' == key || 'Q' == key || 27 == key)
      exit(0);
}


int		main(int argc, char **argv)
{
  /* Creation of the window */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Spinning cube");

  /* OpenGL settings */
  glClearColor(0, 0, 0, 0);
  glEnable(GL_DEPTH_TEST);

  /* Declaration of the callbacks */
  glutDisplayFunc(&DisplayFunc);
  glutReshapeFunc(&ReshapeFunc);
  glutKeyboardFunc(&KeyboardFunc);

  /* Loop */
  glutMainLoop();

  /* Never reached */
  return 0;
}

/* ========================================================================= */
