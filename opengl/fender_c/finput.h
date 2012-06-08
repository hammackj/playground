#ifndef FINPUT_H
#define FINPUT_H

#include "fender.h"

void input_keyboard_loop(unsigned char key, int x, int y);

void input_mouse_loop(int button, int state, int x, int y);

#endif