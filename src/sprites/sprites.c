#include "../sprites.h"

SPRITES sprites;

SPRITES *sprites_init() {
	sprites.level3_image1 = al_load_bitmap("image1.png");
	must_init(sprites.level3_image1, "image1");

	return &sprites;
}

void sprites_deinit() {
	al_destroy_bitmap(sprites.level3_image1);
}

