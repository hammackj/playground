#ifndef FLOG_H
#define FLOG_H

#include <iostream>
//#include <fstream>
#include <string>
#include <cstdarg>
#include <cstdio>

#include "flogtype.h"

//class LogType;

class FLog
{
public:
	~FLog ();
	static FLog* get_instance();

	void init(std::string file);
	void write(LogType type, std::string str, ...);
	void shutdown();

private:
	FLog ();

	FLog(FLog const&){};
	FLog& operator=(FLog const&){};
	
	std::string log_file_path;
	FILE* log_file;
	static FLog* instance;
};

#endif