#include "finput.h"

void input_keyboard_loop(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:
		{
			glutLeaveGameMode();
			fender_shutdown();
		} break;
	}
}

void input_mouse_loop(int button, int state, int x, int y)
{
	
}

