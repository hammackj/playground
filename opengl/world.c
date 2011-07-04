#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

//angle of rotation
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 90, angle=0.0;

int g_h, g_w = 0;

char s[50];

int frame=0;
long timez, timebase=0;

GLfloat quad[] =
{
	-0.5f, 0.5f, -0.0f, //0
	0.5f, 0.5f, -0.0f, //1
	0.5f, -0.5f, -0.0f, //2 
	-0.5f, -0.5f, -0.0f, //3
	
	-1.0f, 1.0f, -0.0f, //0
	0.0f, 1.0f, -0.0f, //1
	0.0f, -1.0f, -0.0f, //2 
	-0.0f, -1.0f, -0.0f, //3
	
	
};

#define FLOOR_WIDTH 8.0f
#define FLOOR_HEIGHT 8.0f

GLfloat floor_vert[] =
{
	-FLOOR_WIDTH * 0.5f, 0.0f, FLOOR_HEIGHT * 5.0f, //0
	FLOOR_WIDTH * 0.5f, 0.0f, FLOOR_HEIGHT * 5.0f, //1
	-FLOOR_WIDTH * 0.5f, 0.0f, -FLOOR_HEIGHT * 5.0f, //2
	-FLOOR_WIDTH * 0.5f, 0.0f, -FLOOR_HEIGHT * 5.0f, //3
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



void init (void) 
{
		glEnable (GL_DEPTH_TEST); //enable the depth testing
	//	glEnable (GL_LIGHTING); //enable the lighting
	//	glEnable (GL_LIGHT0); //enable LIGHT0, our Diffuse Light
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glShadeModel (GL_SMOOTH); //set the shader to smooth shader
		
		glClearColor (0.0,0.0,0.0,1.0); //clear the screen to black
		
}
void renderBitmapString(float x, float y, float z, void *font, char *string) 
{
	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) 
	{
		glutBitmapCharacter(font, *c);
	}
}

void restorePerspectiveProjection() 
{

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void setOrthographicProjection() 
{

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
//	glDisable (GL_LIGHTING);
	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(5,30,0,GLUT_BITMAP_HELVETICA_18,s);
	glPopMatrix();
	//glEnable (GL_LIGHTING);
	restorePerspectiveProjection();
}

void player_position (void)
{
	char position[50];
	
	sprintf(position,"X = %f, Y = %f, Z = %f", xpos, ypos, zpos);
	
	setOrthographicProjection();
	//glDisable (GL_LIGHTING);
	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(5,50,0,GLUT_BITMAP_HELVETICA_18, position);
	glPopMatrix();
	//glEnable (GL_LIGHTING);
	restorePerspectiveProjection();
	
}

void camera (void) 
{
		glRotatef(xrot,1.0,0.0,0.0); 
		glRotatef(yrot,0.0,1.0,0.0); 
		glTranslated(-xpos,-ypos,-zpos); 
}

void display (void) 
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	//clear the color buffer and the depth buffer
	glLoadIdentity();	 
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
	//camera position, x,y,z, looking at x,y,z, Up Positions of the camera
	camera();
	fps();
	player_position();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, floor_vert);
	glColorPointer(3, GL_FLOAT, 0, colors);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glDrawArrays(GL_QUADS, 0, 4);
	glPopMatrix();

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

void keyboard (unsigned char key, int x, int y) 
{		
		if (key=='w')
		{
				/*float xrotrad, yrotrad;
				yrotrad = (yrot / 180 * 3.141592654f);
				xrotrad = (xrot / 180 * 3.141592654f); 
				xpos += (float)sin(yrotrad) ;
				zpos -= (float)cos(yrotrad) ;
				ypos -= (float)sin(xrotrad) ;*/

				xpos += (float) sin((yrot) * 0.0174532925f) * 5.0f;
				zpos += (float) cos((yrot) * 0.0174532925f) * 5.0f;				
		}
		
		if (key=='s')
		{
				/*float xrotrad, yrotrad;
				yrotrad = (yrot / 180 * 3.141592654f);
				xrotrad = (xrot / 180 * 3.141592654f); 
				xpos -= (float)sin(yrotrad);
				zpos += (float)cos(yrotrad) ;
				ypos += (float)sin(xrotrad);*/
				
			xpos -= (float) sin((yrot) * 0.0174532925f) * 5.0f;
			zpos -= (float) cos((yrot) * 0.0174532925f) * 5.0f;
				
				
		}

		if (key=='a') //left
		{
			xpos += (float) sin((yrot + 90) * 0.0174532925f) * 5.0f;
			zpos += (float) cos((yrot + 90) * 0.0174532925f) * 5.0f;
		}
		
		if (key=='d') // right
		{
			xpos += (float) sin((yrot - 90) * 0.0174532925f) * 5.0f;
			zpos += (float) cos((yrot - 90) * 0.0174532925f) * 5.0f;
		}
		

		if (key==27)
		{
				glutLeaveGameMode(); //set the resolution how it was
				exit(0); //quit the program
		}
}

void mouse (int button, int state, int x, int y)
{
	switch(button) 
	{
	//case GLUT_LEFT_BUTTON:
	//case GLUT_RIGHT_BUTTON:
		 // ...
	 //	 break;

	case GLUT_LEFT_BUTTON:
	{

	} break;
	case GLUT_RIGHT_BUTTON:
	{

	}break;
	
	}
}

int main (int argc, char **argv) 
{
		unsigned int iseed = (unsigned int) time(NULL);

		srand (iseed);
	
		glutInit (&argc, argv);
		glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH); //set the display to Double buffer, with depth
		glutGameModeString( "1920x1080:32@60" ); //the settings	 for fullscreen mode
		glutEnterGameMode(); //set glut to fullscreen using the settings in the line above
		init (); 
		glutDisplayFunc (display); //use the display function to draw everything
		glutIdleFunc (display); //update any variables in display,display can be changed to anyhing, as long as you move the variables to be updated, in this case, angle++;
		glutReshapeFunc (reshape); //reshape the window accordingly
		glutMouseFunc(mouse);
		glutKeyboardFunc (keyboard); //check the keyboard
		glutMainLoop (); //call the main loop
		return 0;
}