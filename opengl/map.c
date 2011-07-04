#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#define MAP_MAX_X 100
#define MAP_MAX_Y 100


int map[MAP_MAX_X][MAP_MAX_Y];

/* = {
	{0,0,0,0,0},
	{0,1,0,0,0},
	{0,0,1,0,0},
	{0,0,0,1,0},
	{0,0,0,0,0},
};*/

int frame=0;
long timez, timebase=0;

char s[50];

int g_h, g_w = 0;

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


GLfloat cube[] =
{
	-0.5f, -0.5f, -0.5f,   -0.5f, -0.5f,  0.5f,   -0.5f,  0.5f,  0.5f,   -0.5f,  0.5f, -0.5f, //0 1 2 3
	 0.5f, -0.5f, -0.5f,    0.5f, -0.5f,  0.5f,    0.5f,  0.5f,  0.5f,    0.5f,  0.5f, -0.5f, //4 5 6 7
	-0.5f, -0.5f, -0.5f,   -0.5f, -0.5f,  0.5f,    0.5f, -0.5f,  0.5f,    0.5f, -0.5f, -0.5f, //8 9 10 11
	-0.5f,  0.5f, -0.5f,   -0.5f,  0.5f,  0.5f,    0.5f,  0.5f,  0.5f,    0.5f,  0.5f, -0.5f, //12 13 14 15
	-0.5f, -0.5f, -0.5f,   -0.5f,  0.5f, -0.5f,    0.5f,  0.5f, -0.5f,    0.5f, -0.5f, -0.5f, //16 17 18 19
	-0.5f, -0.5f,  0.5f,   -0.5f,  0.5f,  0.5f,    0.5f,  0.5f,  0.5f,    0.5f, -0.5f,  0.5f //20 21 22 23 
};

GLfloat quad[] =
{
	-0.5f, 0.5f, -0.5f, //0
	0.5f, 0.5f, -0.5f, //1
	0.5f, -0.5f, -0.5f, //2 
	-0.5f, -0.5f, -0.5f, //3
};

// normal array
GLfloat normals[] = {0,0,1,  0,0,1,  0,0,1,  0,0,1,             // v0-v1-v2-v3
                     1,0,0,  1,0,0,  1,0,0, 1,0,0,              // v0-v3-v4-v5
                     0,1,0,  0,1,0,  0,1,0, 0,1,0,              // v0-v5-v6-v1
                     -1,0,0,  -1,0,0, -1,0,0,  -1,0,0,          // v1-v6-v7-v2
                     0,-1,0,  0,-1,0,  0,-1,0,  0,-1,0,         // v7-v4-v3-v2
                     0,0,-1,  0,0,-1,  0,0,-1,  0,0,-1};        // v4-v7-v6-v5

GLfloat quad2[] =
{
	-0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,	
	-1.5f, 1.5f, -0.5f,
	1.5f, 1.5f, -0.5f,
	1.5f, -1.5f, -0.5f,
	-1.5f, -1.5f, -0.5f
};

//GLfloat generated[(MAP_MAX_X * MAP_MAX_Y)*4];

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
//			glEnable(GL_CULL_FACE);
//		glCullFace(GL_BACK); 
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

		/* A step backward, then spin the cube */
		glTranslatef(0, 0, -5.0f);
		//	glRotatef(30, 1, 0, 0);
	//	glRotatef(alpha, 0, 1, 0);

		/* We have a color array and a vertex array */
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, quad2);
		glColorPointer(3, GL_FLOAT, 0, colors);

		for(i = 0.0f; i < (GLfloat) MAP_MAX_X; i += 1.0f)
		{
			for(j = 0.0f; j < (GLfloat) MAP_MAX_Y; j += 1.0f)
			{
				if (map[(int)i][(int)j] == 5)
				{
					glVertexPointer(3, GL_FLOAT, 0, cube);
					glPushMatrix();
					glTranslatef(i, j, -5.0f);
					glDrawArrays(GL_QUADS, 0, 24);
					glPopMatrix();
					glVertexPointer(3, GL_FLOAT, 0, quad);
				}
				else //if (map[(int)i][(int)j] == 5)
				{
					glPushMatrix();
					glTranslatef(i, j, -5.0f);
					glDrawArrays(GL_QUADS, 0, 4);
					glPopMatrix();
				}
				//else
				{
					//draw nothing
				}
				
				cube_count++;
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
        zpos += (float)cos(yrotrad) ;
        ypos += (float)sin(xrotrad);
    }
    
    if (key=='d')
    {
        yrot += 1;
        if (yrot >360) yrot -= 360;
    }
    
    if (key=='a')
    {
        yrot -= 1;
        if (yrot < -360)yrot += 360;
    }

		if (key == 't')
		{
			ypos -= 1;
		}
		
		if (key == 'g')
		{
			ypos += 1;
		}
		
		if (key == 'f')
		{
			xpos += 1;
		}
		
		if (key == 'h')
		{
			xpos -= 1;
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
//	int max_ver = (MAP_MAX_X * MAP_MAX_Y)*4;
	unsigned int iseed = (unsigned int) time(NULL);
	
	srand (iseed);
		
	for(x = 0; x < MAP_MAX_X; ++x)
	{
		for(y = 0; y < MAP_MAX_Y; ++y)
		{
			if (x == 0 || y == 0 || x == (MAP_MAX_X -1) || y == (MAP_MAX_Y -1))
			{	
				map[x][y] = 5;
			}
			else
			{
				map[x][y] = (int)((rand() /(RAND_MAX + 1.0)) * 6);
			}
				
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
	glutMouseFunc(mouse);
	glutKeyboardFunc (keyboard); //check the keyboard
	glutMainLoop (); //call the main loop


	return 0;
}