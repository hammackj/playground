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
	log_write(GENERAL, "Fender shutting down.\n");
	log_write(GENERAL, "Log shutdown.\n");
	log_write(GENERAL, "Fender shutdown.\n");
	log_close();
	exit(0);
}