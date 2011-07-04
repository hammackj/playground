/*
HAMMOUTENE Amir
amir.hammoutene@gmail.com
04/12/2010

This code shows how to move the "camera" in OpenGL like a First Person Viewer (camera piloting)
It moves the camera relatively to its position in 6 degrees of fredom.

The most important code is in : GLvoid transfomCamera()  and in    GLvoid DrawScene
See also   GLvoid Keyboard   for the key used


build links to:
oprngl32
glu32
glut32
gdi32
winmm
*/

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

GLvoid Initialise( char * Titre);//Initialization of the scene
GLvoid DrawScene(GLvoid);// Drawing method, called in loop
GLvoid Resize(const GLsizei ,const  GLsizei);// Used when resizing the application window
GLvoid Keyboard(unsigned char , int , int);// Keyboard and mouse interaction
GLvoid DefineLight(const GLint);//Initialise the light source
GLvoid TeaTeam();//Draw Teapots
GLvoid Intro();//show a litlle demo

    GLfloat keyCamRot = 0.5f;
    GLfloat keyCamTrans = 0.05f;
    GLfloat TrMatrix[]={1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f};
    GLfloat   LightRelativePos[]={0.f,1.3f,-1.f,1.f};
    const GLfloat EPSILON = 0.00000000000001f;

    const GLfloat Red1Amb[] = { 0.9,0.,0. ,1};
    const GLfloat Red1Spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat Red1Dif[] = {0.6,0.,0. ,1};
    const GLfloat Red1Emi[] = {0.,0.,0. ,1};

    GLfloat t=0;

int main(int argc , char **argv)
{
    glutInit(&argc,argv);
    Initialise(argv[0]);  /* Fonction à écrire pour initialiser la machine OpenGL */
    glutKeyboardFunc(Keyboard);
    glutDisplayFunc(DrawScene);  /* fonction à appeler avec la fonction principale de rendu à écrire */
    glutReshapeFunc(Resize);
    glutMainLoop(); /* Fonction de boucle infinie */
    return 0;
}

GLvoid Initialise(char * Titre)
{
    GLvoid DefineWindow(char *);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    DefineWindow("Elbow Manipulator");
    glPointSize(1.f);
    glLineWidth(1.f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glDisable(GL_CULL_FACE );
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL );
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,1.f);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    DefineLight(4);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,Red1Amb);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,Red1Dif);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Red1Spe);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Red1Emi);
    glColor3f(0.9f,0.f,0.f);
    glPointSize(10.f);
}
GLvoid Resize(GLsizei WindowWidth , GLsizei WindowHeight  )
{
    glViewport( 0, 0,WindowWidth , WindowHeight) ;
    GLfloat ratio = (GLfloat)  WindowWidth /  WindowHeight;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.f,ratio,0.1f,130.f);
    glMatrixMode(GL_MODELVIEW);
}

GLvoid DefineWindow(char * Titre)
{
    GLsizei ScreenWidth,ScreenHeight;
    GLsizei WindowWidth, WindowHeight;
    ScreenWidth=glutGet(GLUT_SCREEN_WIDTH);
    ScreenHeight=glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(ScreenWidth,ScreenHeight);
    glutCreateWindow(Titre);
    glClearColor(0.7f,0.7f,1.f, 1.f);
    WindowWidth  = glutGet(GLUT_WINDOW_WIDTH) ;
    WindowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    Resize(WindowWidth,WindowHeight);
}

GLvoid DefineLight(GLint numberofLights)
{
    int i;
    const GLfloat LumiereAmbient[]={ 0.f, 0.0f, 0.0f, 0.0f};
    const GLfloat LumiereDiffuse[]={1.f, 1.f, 1.f, 1.f };
    const GLfloat LumiereSpecular[]={1.0f, 1.0f, 1.0f, 1.0f};
    const GLfloat cst_attenuation =0.025f*numberofLights;
    const GLfloat ln_attenuation= 0.1525f*numberofLights;
    const GLfloat qua_attenuation= 0.0025f*numberofLights;
    const GLint Lights[]= {GL_LIGHT0,GL_LIGHT1,GL_LIGHT2,GL_LIGHT3,GL_LIGHT4,GL_LIGHT5,GL_LIGHT6,GL_LIGHT7};
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glDepthFunc(GL_LESS);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1 );
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );

    for (i = 0 ; i<numberofLights ; i++) {
        glEnable(Lights[i]);
        glLightfv(Lights[i],GL_AMBIENT,LumiereAmbient);
        glLightfv(Lights[i],GL_DIFFUSE,LumiereDiffuse);
        glLightfv(Lights[i],GL_SPECULAR,LumiereSpecular);
        glLightf(Lights[i],GL_CONSTANT_ATTENUATION,  cst_attenuation);
        glLightf(Lights[i],GL_LINEAR_ATTENUATION,  ln_attenuation);
        glLightf(Lights[i],GL_QUADRATIC_ATTENUATION,  qua_attenuation);
    }
}

GLvoid DrawScene(GLvoid)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (t<1000) t++;

    glPushMatrix();
        glLoadIdentity();
        glBegin(GL_POINTS);
        glVertex3f(0.f,0.f,-100.f);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        TeaTeam();
        if (t<1000) Intro();
        glutSwapBuffers();
        glutPostRedisplay();
    glPopMatrix();

}

GLvoid Keyboard(unsigned char key , int x, int y)
{
  switch(key)
    {
////////////////// ROTATE
    case 'e':
      glLoadIdentity();
      glRotatef(keyCamRot,0.f,0.f,1.f);
      glMultMatrixf(TrMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      break;
    case 'q':
      glLoadIdentity();
      glRotatef(-keyCamRot,0.f,0.f,1.f);
      glMultMatrixf(TrMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      break;
    case 's' :
      glLoadIdentity();
      glRotatef(keyCamRot,1.f,0.f,0.f);
      glMultMatrixf(TrMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      break;
    case 'w' :
      glLoadIdentity();
      glRotatef(-keyCamRot,1.f,0.f,0.f);
      glMultMatrixf(TrMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      break;
    case 'd' :
      glLoadIdentity();
      glRotatef(keyCamRot,0.f,1.f,0.f);
      glMultMatrixf(TrMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      break;
    case 'a' :
      glLoadIdentity();
      glRotatef(-keyCamRot,0.f,1.f,0.f);
      glMultMatrixf(TrMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      break;
//////////////TRANSLATE
    case 'j' :
      glLoadIdentity();
      glTranslatef(keyCamTrans,0.f,0.f);
      glMultMatrixf(TrMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      break;
    case 'l':
      glLoadIdentity();
      glTranslatef(-keyCamTrans,0.f,0.f);
      glMultMatrixf(TrMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      break;
    case 'u' :
      glLoadIdentity();
      glTranslatef(0.f,keyCamTrans,0.f);
      glMultMatrixf(TrMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      break;
    case 'o' :
      glLoadIdentity();
      glTranslatef(0.f,-keyCamTrans,0.f);
      glMultMatrixf(TrMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      break;
    case 'i' :
      glLoadIdentity();
      glTranslatef(0.f,0.f,keyCamTrans);
      glMultMatrixf(TrMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      break;
    case 'k' :
      glLoadIdentity();
      glTranslatef(0.f,0.f,-keyCamTrans);
      glMultMatrixf(TrMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      break;

    case 'v':
        glLoadIdentity();
        glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      break;

    case 27:
      exit(1);
      break;
    }

      glutPostRedisplay();
}


GLvoid TeaTeam()
{
        glLoadMatrixf(TrMatrix);
        glLightfv(GL_LIGHT0,GL_POSITION,LightRelativePos);
        glTranslatef(0.f,0.f,-6.f);
        glLightfv(GL_LIGHT1,GL_POSITION,LightRelativePos);
        glutSolidTeapot(1);
        glTranslatef(3.f,0.f,-3.f);
        glLightfv(GL_LIGHT2,GL_POSITION,LightRelativePos);
        glutSolidTeapot(1);
        glTranslatef(-9.f,0.f,-5.f);
        glLightfv(GL_LIGHT3,GL_POSITION,LightRelativePos);
        glutSolidTeapot(1);
        //DessineSalle();
}

GLvoid Intro()
{
    if(t>10 && t< 100) {
      glLoadIdentity();
      glTranslatef(0.f,0.f,-keyCamTrans);
      glMultMatrixf(TrMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      glutPostRedisplay();
    }
    else if(t>=120 && t< 220) {
      glLoadIdentity();
      glTranslatef(-keyCamTrans,0.f,0.f);
      glMultMatrixf(TrMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      glutPostRedisplay();
    }
    else if(t>=240 && t< 290) {
      glLoadIdentity();
      glRotatef(-keyCamRot,0.f,1.f,0.f);
      glMultMatrixf(TrMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      glutPostRedisplay();
    }
    else if(t>=310 && t< 410) {
      glLoadIdentity();
      glTranslatef(0.f,-keyCamTrans,0.f);
      glMultMatrixf(TrMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      glutPostRedisplay();
    }
    else if(t>=430 && t< 465) {
      glLoadIdentity();
      glRotatef(keyCamRot,1.f,0.f,0.f);
      glMultMatrixf(TrMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      glutPostRedisplay();
    }
    else if(t>=490 && t< 630) {
      glLoadIdentity();
      glTranslatef(0.f,0.f,keyCamTrans);
      glMultMatrixf(TrMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
      glutPostRedisplay();
    }
    else if (t>630) {
        glLoadIdentity();
        glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
        t=1001;
        glutPostRedisplay();
    }
}