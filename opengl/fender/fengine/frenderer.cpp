FRenderer::init()
{
	FLog::get_instance()->write(LogType::GENERAL, "FRenderer Init");
	
	glEnable (GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glShadeModel (GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	
}

FRenderer::shutdown()
{
	FLog::get_instance()->write(LogType::GENERAL, "FRenderer Shutdown");
}

FRenderer::render()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	calculate_fps();
	
	if (show_debug)
	renderer_draw_renderer_status();
	
	glutSwapBuffers();	
}

FRenderer::resize(int w, int h)
{
	
}

FRenderer::set_show_debug(bool value)
{
	show_debug = value;
}

FRenderer::calculate_fps()
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

float FRenderer::get_fps()
{
	return fps;
}

FRenderer::render_debug_status()
{
	char fps_status[25];
	
	sprintf(fps_status, "FPS: %4.2f", get_fps());
	
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

FRenderer::render_bitmap_string(float x, float y, float z, void *font, char *string)
{
	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) 
	{
		glutBitmapCharacter(font, *c);
	}
}