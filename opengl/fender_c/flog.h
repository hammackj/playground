#ifndef FLOG_H
#define FLOG_H

#include "common.h"

typedef enum 
{
	GENERAL,
	DEBUG,
	WARNING,
	ERROR
} log_type_t;

void log_init(char *log_file_path);

void log_write(log_type_t type, char *str, ...);

void log_close(void);

#endif