#include "flog.h"

FLog* FLog::instance = NULL;

FLog* FLog::get_instance()
{
	if(!instance)
		instance = new FLog();
		
	return instance;
}

FLog::FLog ()
{
	log_file_path = "";
}

FLog::~FLog ()
{
	log_file_path = "";
}

void FLog::init(std::string file)
{
	log_file_path = file;
	log_file = fopen(log_file_path.c_str(), "w");
	
	if (log_file == NULL)
	{
		perror("Unable to open file for logging.");
		exit(1);
	}

	write(LogType::GENERAL, "[*] Logger Initialized");

	std::cout << "[*] Logger Initialized" << std::endl;
}

void FLog::write(LogType type, std::string str, ...)
{
	std::string log_type;
	va_list arg_list;
	
	va_start(arg_list, str);
	
	switch (type)
	{
		case LogType::GENERAL:
		{
			fprintf(log_file, "[GENERAL] ");
		} break;
		
		case LogType::DEBUG:
		{
			fprintf(log_file, "[DEBUG] ");
		} break;
		
		case LogType::WARNING:
		{
			fprintf(log_file, "[WARNING] ");
		} break;
		
		case LogType::ERROR:
		{
			fprintf(log_file, "[ERROR] ");
		} break;		
	}
	
	str += "\n";
	
	vfprintf(log_file, str.c_str(), arg_list);
	va_end(arg_list);
}

void FLog::shutdown()
{
	write(LogType::GENERAL, "[*] Logger Shutdown");
	fclose(log_file);
}