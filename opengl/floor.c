#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#define MAP_MAX_X 50
#define MAP_MAX_Y 50


float cRadius = 10.0f; // our radius distance from our character

int map[MAP_MAX_X][MAP_MAX_Y];

int frame=0;
long timez, timebase=0;

char s[50];

int g_h, g_w = 0;

float lastx, lasty;

//angle of rotation
GLfloat xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 90, angle=0.0;

int cube_count;

struct 
{
    GLfloat x,y,z;
} Vector3;

struct 
{
    GLfloat x,y,z, w;
} Vector4;


GLfloat vertices[] =
{
	-0.5f, -0.5f, -0.5f,   -0.5f, -0.5f,  0.5f,   -0.5f,  0.5f,  0.5f,   -0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,    0.5f, -0.5f,  0.5f,    0.5f,  0.5f,  0.5f,    0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,   -0.5f, -0.5f,  0.5f,    0.5f, -0.5f,  0.5f,    0.5f, -0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,   -0.5f,  0.5f,  0.5f,    0.5f,  0.5f,  0.5f,    0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,   -0.5f,  0.5f, -0.5f,    0.5f,  0.5f, -0.5f,    0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,   -0.5f,  0.5f,  0.5f,    0.5f,  0.5f,  0.5f,    0.5f, -0.5f,  0.5f
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

void renderBitmapString(float x, float y, float z, void *font, char *string) 
{
	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) 
	{
		glutBitmapCharacter(font, *c);
	}
}

void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, g_w, g_h, 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void init (void) 
{
    glEnable (GL_DEPTH_TEST); //enable the depth testing
//		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK); 
    //glEnable (GL_LIGHTING); //enable the lighting
    //glEnable (GL_LIGHT0); //enable LIGHT0, our Diffuse Light
    glShadeModel (GL_SMOOTH); //set the shader to smooth shader
    
}

void camera (void) 
{
	glTranslatef(xpos, ypos, zpos);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(45.0f, -1.0f, 1.0f, 0.0f);
}

void fps (void)
{
	frame++;

	timez = glutGet(GLUT_ELAPSED_TIME);
	if ((timez - timebase) > 1000) 
	{
		sprintf(s,"FPS:%4.2f", frame*1000.0/(timez-timebase));
		timebase = timez;
		frame = 0;
	}

	setOrthographicProjection();

	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(5,30,0,GLUT_BITMAP_HELVETICA_18,s);
	glPopMatrix();

	restorePerspectiveProjection();
}

void display (void) 
{
	GLfloat i, j =0;
		/* Clear the buffer, clear the matrix */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
    //camera position, x,y,z, looking at x,y,z, Up Positions of the camera
    camera();
		fps();
		
		
		
		//Build character to follow?
		
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -cRadius);
		glRotatef(xrot,1.0,0.0,0.0);
		glColor3f(1.0f, 0.0f, 0.0f); //Red
		glutSolidCube(2); //Our character to follow
		glRotatef(yrot,0.0,1.0,0.0);	//rotate our camera on the y-axis (up and down)
		glTranslated(-xpos,0.0f,-zpos); //translate the screen to the position of our camera
		glColor3f(1.0f, 1.0f, 1.0f);
		
		

		/* A step backward, then spin the cube */
		//glTranslatef(0, 0, -5.0f);
		//glRotatef(30, 1, 0, 0);
	//	glRotatef(alpha, 0, 1, 0);

		/* We have a color array and a vertex array */
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glColorPointer(3, GL_FLOAT, 0, colors);

		for(i = 0.0f; i < (GLfloat) MAP_MAX_X; i += 1.0f)
		{
			for(j = 0.0f; j < (GLfloat) MAP_MAX_Y; j += 1.0f)
			{
				glPushMatrix();
				glTranslatef(i, j, -5.0f);
				glDrawArrays(GL_QUADS, 0, 24);
				cube_count++;
				glPopMatrix();
			}
		}

		/* Cleanup states */
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

    glutSwapBuffers(); //swap the buffers
    angle++; //increase the angle
}

void reshape (int w, int h) 
{
	g_w = w;
	g_h = h;
	
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection
    
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0); //set the perspective (angle of sight, width, height, , depth)
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model
    
}

void mouse (int button, int state, int x, int y)
{
	switch(button) 
	{
	  case GLUT_LEFT_BUTTON:
		{
			zpos += 1;
		}	break;
	  case GLUT_RIGHT_BUTTON:
		{
			zpos -= 1;
		}break;
  }
}
void mouseMovement(int x, int y) 
{
		int diffx=x-lastx; //check the difference between the current x and the last x position
		int diffy=y-lasty; //check the difference between thecurrent y and the last y position
		lastx=x; //set lastx to the current x position
		lasty=y; //set lasty to the current y position
		xrot += (float) diffy; //set the xrot to xrot with the addition of the difference in the y position
		yrot += (float) diffx;		//set the xrot to yrot with the addition of the difference in the x position
}

void keyboard (unsigned char key, int x, int y) 
{
	if (key=='q')
	{
		xrot += 1;
		if (xrot >360) xrot -= 360;
	}

	if (key=='z')
	{
		xrot -= 1;
		if (xrot < -360) xrot += 360;
	}

	if (key=='w')
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos += (float)sin(yrotrad);
		zpos -= (float)cos(yrotrad);
		ypos -= (float)sin(xrotrad);
	}

	if (key=='s')
	{
	float xrotrad, yrotrad;
	yrotrad = (yrot / 180 * 3.141592654f);
	xrotrad = (xrot / 180 * 3.141592654f);
	xpos -= (float)sin(yrotrad);
	zpos += (float)cos(yrotrad);
	ypos += (float)sin(xrotrad);
	}

	if (key=='d')
	{
	float yrotrad;
	yrotrad = (yrot / 180 * 3.141592654f);
	xpos += (float)cos(yrotrad) * 0.2;
	zpos += (float)sin(yrotrad) * 0.2;
	}

	if (key=='a')
	{
	float yrotrad;
	yrotrad = (yrot / 180 * 3.141592654f);
	xpos -= (float)cos(yrotrad) * 0.2;
	zpos -= (float)sin(yrotrad) * 0.2;
	}

    if (key==27)
    {
			printf("Cube Count was => %d\n", cube_count);
      glutLeaveGameMode(); //set the resolution how it was
      exit(0); //quit the program
    }
}

int main (int argc, char **argv) 
{
	int x, y = 0;
	unsigned int iseed = (unsigned int) time(NULL);
	
	srand (iseed);
		
	for(x = 0; x < MAP_MAX_X; ++x)
	{
		for(y = 0; y < MAP_MAX_Y; ++y)
		{
			map[x][y] = (int)((rand() /(RAND_MAX + 1.0)) * 11);			
		}
	}
	
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH); //set the display to Double buffer, with depth
	glutGameModeString( "1920x1080:32@60" ); //the settings  for fullscreen mode
	glutEnterGameMode(); //set glut to fullscreen using the settings in the line above
	init (); //call the init function
	glutDisplayFunc (display); //use the display function to draw everything
	glutIdleFunc (display); //update any variables in display,display can be changed to anyhing, as long as you move the variables to be updated, in this case, angle++;
	glutReshapeFunc (reshape); //reshape the window accordingly
	glutPassiveMotionFunc(mouseMovement); //check for mousemovement
	glutSetCursor(GLUT_CURSOR_NONE);
	glutKeyboardFunc (keyboard); //check the keyboard
	glutMainLoop (); //call the main loop


	return 0;
}