#include "../input.h"

#include <allegro5/allegro5.h>

#include "../utils.h"
#include "../display.h"

unsigned char key[ALLEGRO_KEY_MAX];

unsigned char *keyboard_init() {
	must_init(al_install_keyboard(), "keyboard");

	memset(key, 0, sizeof(key));
	return key;
}

void keyboard_update(ALLEGRO_EVENT *event) {
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

MOUSE mouse;
float scale_factor_x, scale_factor_y;

MOUSE *mouse_init(ALLEGRO_DISPLAY *display) {
	must_init(al_install_mouse(), "mouse");

	al_hide_mouse_cursor(display);

	mouse = (MOUSE){
		.x = 0,
		.y = 0,
	};

	al_set_mouse_xy(display, mouse.x, mouse.y);

	scale_factor_x = BUFFER_W / (float) al_get_display_width(display);
	scale_factor_y = BUFFER_H / (float) al_get_display_height(display);

	return &mouse;
}

void mouse_update(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT *event) {
	mouse.dx = event->mouse.dx * scale_factor_x;
	mouse.dy =  event->mouse.dy * scale_factor_y;
	mouse.x +=  mouse.dx;
	mouse.y +=  mouse.dy;

	if (mouse.x > BUFFER_W) {
		mouse.x = BUFFER_W;
		al_set_mouse_xy(display, mouse.x, mouse.y);
	}

	if (mouse.y > BUFFER_H) {
		mouse.y = BUFFER_H;
		al_set_mouse_xy(display, mouse.x, mouse.y);
	}
}

void mouse_draw() {
	al_draw_filled_rectangle(mouse.x-2, mouse.y-2, mouse.x+2, mouse.y+2, al_map_rgb_f(1,1,1));
}
