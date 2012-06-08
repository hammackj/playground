#include "fender.h"

int main (int argc, char **argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutGameModeString("1920x1080:32@60");
	glutEnterGameMode();
	
	fender_init();
		
	glutDisplayFunc(renderer_render);
	glutIdleFunc(renderer_render);
	glutReshapeFunc(renderer_resize);
	glutMouseFunc(input_mouse_loop);
	glutKeyboardFunc(input_keyboard_loop);
	glutMainLoop();

	return 0;
}