#ifndef DISPLAY_H
#define DISPLAY_H

#include <allegro5/allegro5.h>

#define BUFFER_W 320
#define BUFFER_H 240

ALLEGRO_DISPLAY *display_init();

void display_transform_coords(float *x, float *y);

void display_deinit();

void display_pre_draw();

void display_post_draw();

#endif
