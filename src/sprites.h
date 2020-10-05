#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include "utils.h"

typedef struct SPRITES {
	ALLEGRO_BITMAP *level3_image1;
} SPRITES;

SPRITES *sprites_init();

void sprites_deinit();
