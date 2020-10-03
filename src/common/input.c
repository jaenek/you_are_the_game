#include "../utils.h"
#include "../input.h"

unsigned char key[ALLEGRO_KEY_MAX];

unsigned char *keyboard_init() {
	must_init(al_install_keyboard(), "keyboard");

	memset(key, 0, sizeof(key));
	return key;
}

void keyboard_update(ALLEGRO_EVENT* event) {
	switch (event->type) {
		case ALLEGRO_EVENT_TIMER:
			for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
				key[i] &= KEY_SEEN;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
			break;
		case ALLEGRO_EVENT_KEY_UP:
			key[event->keyboard.keycode] &= KEY_RELEASED;
			break;
	}
}

typedef struct MOUSE {
	float x, y;
} MOUSE;
MOUSE mouse;

void mouse_init(ALLEGRO_DISPLAY* display) {
	must_init(al_install_mouse(), "mouse");

	al_hide_mouse_cursor(display);

	al_set_mouse_xy(display, 0, 0);
}

void mouse_update(float x, float y) {
	mouse = (MOUSE){ .x = x, .y = y};
}

void mouse_draw() {
	al_draw_filled_rectangle(mouse.x-2, mouse.y-2, mouse.x+2, mouse.y+2, al_map_rgb_f(1,1,1));
}
