#ifndef FLOGTYPE_H
#define FLOGTYPE_H

#include <cassert>

class LogType
{
public:
	typedef enum
	{
		GENERAL,
		DEBUG,
		WARNING,
		ERROR
	} log_type;

	LogType(log_type val = GENERAL) : _val(val)
	{
		assert(val <= ERROR);
	}

	operator log_type() const
	{
		return _val;
	}
	
private:
    log_type _val;	
};

#endif