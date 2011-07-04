#include "fender.h"

void fender_init(void)
{
	log_init("log.txt");
	log_write(GENERAL, "Log initialized.\n");
	
	renderer_init();
	log_write(GENERAL, "Renderer initalized.\n");
	
}

void fender_shutdown(void)
{
	log_close();
	log_write(GENERAL, "Log shutdown.\n");
	
	exit(0);
}