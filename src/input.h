#ifndef INPUT_H
#define INPUT_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#define KEY_SEEN 1
#define KEY_RELEASED 2

unsigned char *keyboard_init();

void keyboard_update(ALLEGRO_EVENT *event);

typedef struct MOUSE {
	float x, y;
	float dx, dy;
	bool buttons[3];
} MOUSE;

MOUSE *mouse_init(ALLEGRO_DISPLAY *display);

void mouse_update(ALLEGRO_DISPLAY * display, ALLEGRO_EVENT *event);

void mouse_draw();

#endif
