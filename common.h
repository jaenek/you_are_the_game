#include <allegro5/allegro5.h>

#pragma once

/* UTILS */
void must_init(bool test, const char *description) {
	if (test) return;

	printf("couldn't initialize %s\n", description);
	exit(1);
}

int between(int lo, int hi) {
	return lo + (rand() % (hi - lo));
}

float between_f(float lo, float hi) {
	return lo + ((float)rand()/ (float)RAND_MAX) * (hi - lo);
}

bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
	if (ax1 > bx2) return false;
	if (ax2 < bx1) return false;
	if (ay1 > by2) return false;
	if (ay2 < by1) return false;

	return true;
}

/* INPUT */
#define KEY_SEEN 1
#define KEY_RELEASED 2
unsigned char key[ALLEGRO_KEY_MAX];

void keyboard_init() {
	memset(key, 0, sizeof(key));
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

/* DISPLAY */
#define BUFFER_W 320
#define BUFFER_H 240

ALLEGRO_DISPLAY* disp;
ALLEGRO_BITMAP* buffer;
ALLEGRO_TRANSFORM transform;

void disp_init() {
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

	disp = al_create_display(BUFFER_W, BUFFER_H);
	must_init(disp, "display");

	buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
	must_init(buffer, "bitmap buffer");

	const float scale_factor_x = ((float)al_get_display_width(disp)) / BUFFER_W;
	const float scale_factor_y = ((float)al_get_display_height(disp)) / BUFFER_H;

	al_identity_transform(&transform);
	al_scale_transform(&transform, scale_factor_x, scale_factor_y);
	al_use_transform(&transform);
}

void disp_deinit() {
	al_destroy_bitmap(buffer);
	al_destroy_display(disp);
}

void disp_pre_draw() {
	al_set_target_bitmap(buffer);
}

void disp_post_draw() {
	al_set_target_backbuffer(disp);
	al_draw_bitmap(buffer, 0, 0, 0);

	al_flip_display();
}
