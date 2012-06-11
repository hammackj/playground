
#include <stdio.h>

#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/glext.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#endif

#include "fender.h"

int main (int argc, char const *argv[])
{	
	FEngine engine;
	
	//glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	//glutGameModeString("1920x1080:32@60");
	//glutEnterGameMode();
	
	engine.init();
	
	
	
	//glutDisplayFunc(renderer_render);
	//glutIdleFunc(renderer_render);
	//glutReshapeFunc(renderer_resize);
	//glutMouseFunc(input_mouse_loop);
	//glutKeyboardFunc(input_keyboard_loop);
	//glutMainLoop();
	
	engine.shutdown();
	
	return 0;
}