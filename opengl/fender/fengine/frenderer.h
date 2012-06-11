#ifndef FRENDERER_H
#define FRENDERER_H

class FRenderer
{
	
public:
	void init();
	void shutdown();
	
	void render();
	void resize(int w, int h);
	
	void set_show_debug(bool value);
	void render_bitmap_string(float x, float y, float z, void *font, char *string)
	
private:
	bool show_debug;
	int frame;
	long time_elapsed;
	long time_base;
	float fps;
	
	void calculate_fps();
	float get_fps();
	void render_debug_status();
	
};

#endif