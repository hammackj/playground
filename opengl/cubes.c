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

void init (void) 
{
    glEnable (GL_DEPTH_TEST); //enable the depth testing
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

void display (void) 
{
	GLfloat i, j =0;
	int x, y=0;
	int dir;
		/* Clear the buffer, clear the matrix */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
    //camera position, x,y,z, looking at x,y,z, Up Positions of the camera
    camera();

		for(x = 0; x < MAP_MAX_X; ++x)
		{
			for(y = 0; y < MAP_MAX_Y; ++y)
			{
				
				dir = (int)((rand() /(RAND_MAX + 1.0)) * 2);
				
				if (dir == 0)
				{
					map[x][y]--;
				}
				else
				{
					map[x][y]++;
				}
				
				if (map[x][y] == 0)
				{
					map[x][y] = 1;
				}
				else
				if (map[x][y] > 10)
				{
					map[x][y]--;
				}
				

				
			}
		}


		/* A step backward, then spin the cube */
		glTranslatef(0, 0, -10);
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
				int r = 0;
				
				for (r = 0; r < map[(int)i][(int)j]; r++)
				{
					glPushMatrix();
					glTranslatef(i, j, r);
					glDrawArrays(GL_QUADS, 0, 24);
					cube_count++;
					glPopMatrix();
				}
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
  //case GLUT_LEFT_BUTTON:
  //case GLUT_RIGHT_BUTTON:
     // ...
   //  break;

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
        xpos += (float)sin(yrotrad) ;
        zpos -= (float)cos(yrotrad) ;
        ypos -= (float)sin(xrotrad) ;
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
	unsigned int iseed = (unsigned int)time(NULL);
	
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
    glutMouseFunc(mouse);
    glutKeyboardFunc (keyboard); //check the keyboard
    glutMainLoop (); //call the main loop

		
    return 0;
}