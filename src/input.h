#ifndef INPUT_H
#define INPUT_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#define KEY_SEEN 1
#define KEY_RELEASED 2

unsigned char *keyboard_init();

void keyboard_update();

void mouse_init(ALLEGRO_DISPLAY* display);

void mouse_update(float x, float y);

void mouse_draw();

#endif
