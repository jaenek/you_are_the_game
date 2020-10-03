#include "../utils.h"
#include "../display.h"

static ALLEGRO_DISPLAY *display;
static ALLEGRO_BITMAP *buffer;
static ALLEGRO_TRANSFORM transform;

ALLEGRO_DISPLAY *display_init() {
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

	display = al_create_display(BUFFER_W, BUFFER_H);
	must_init(display, "display");

	buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
	must_init(buffer, "bitmap buffer");

	const float scale_factor_x = ((float)al_get_display_width(display)) / BUFFER_W;
	const float scale_factor_y = ((float)al_get_display_height(display)) / BUFFER_H;

	al_identity_transform(&transform);
	al_scale_transform(&transform, scale_factor_x, scale_factor_y);
	al_use_transform(&transform);

	return display;
}

void display_deinit() {
	al_destroy_bitmap(buffer);
	al_destroy_display(display);
}

void display_pre_draw() {
	al_set_target_bitmap(buffer);
}

void display_post_draw() {
	al_set_target_backbuffer(display);
	al_draw_bitmap(buffer, 0, 0, 0);

	al_flip_display();
}
