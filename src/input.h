#ifndef INPUT_H
#define INPUT_H

#include <allegro5/allegro5.h>

#define KEY_SEEN 1
#define KEY_RELEASED 2

unsigned char *keyboard_init();

void keyboard_update();

#endif
