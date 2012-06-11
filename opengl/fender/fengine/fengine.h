#ifndef FENGINE_H
#define FENGINE_H

#include <stdio.h>

#include "flog.h"

class FEngine
{
public:
	FEngine () { }
	~FEngine () { }

	void init();
	void shutdown();

private:

};

#endif