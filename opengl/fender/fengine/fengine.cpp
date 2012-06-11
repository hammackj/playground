#include "fengine.h"

void FEngine::init()
{
	FLog::get_instance()->init("log.txt");
	FLog::get_instance()->write(LogType::GENERAL, "Engine Initialized");		
}

void FEngine::shutdown()
{
	FLog::get_instance()->write(LogType::GENERAL, "Engine Shutdown");
	FLog::get_instance()->shutdown();
}