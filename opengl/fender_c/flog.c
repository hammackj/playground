#include "flog.h"

static FILE *log_file;

void log_init(char *log_file_path)
{
	log_file = fopen(log_file_path, "a");
	
	if (log_file == NULL)
	{
		perror("Unable to open file for logging.");
		exit(1);
	}
}

void log_write(log_type_t type, char *str, ...)
{
	va_list arg_list;
	va_start(arg_list, str);
	switch (type)
	{
		case GENERAL:
		{
			fprintf(log_file, "[GENERAL] ");
		} break;
		
		case DEBUG:
		{
			fprintf(log_file, "[DEBUG] ");			
		} break;
		
		case WARNING:
		{
			fprintf(log_file, "[WARNING] ");
		} break;
		
		case ERROR:
		{
			fprintf(log_file, "[ERROR] ");			
		} break;
		
	}
	vfprintf (log_file, str, arg_list);
	va_end( arg_list );
}

void log_close(void)
{
	fclose(log_file);
}