#include "../level3.h"

#define N_PIXELS (BUFFER_W/8)*(BUFFER_H/8)

typedef struct PIXEL {
	int x, y;
	bool drawn;
} PIXEL;
PIXEL pixels[N_PIXELS];
int pixel_index;

ALLEGRO_BITMAP *sprite_to_draw;
int correct_pixels;
long frames;

void level3_init(SPRITES *sprites) {
	memset(pixels, 0, sizeof(pixels));
	pixel_index = 0;

	correct_pixels = 0;
	frames = 0;

	sprite_to_draw = sprites->level3_image1;
}

bool level3_check_done() {
	if (frames < 120) return false;

	ALLEGRO_BITMAP *buffer = display_get_buffer();

	unsigned char r1, g1, b1, r2, g2, b2;
	for (int y = 0; y < BUFFER_H; y++) {
		for (int x = 0; x < BUFFER_W; x++) {
			al_unmap_rgb(al_get_pixel(buffer, x, y), &r1, &g1, &b1);
			al_unmap_rgb(al_get_pixel(sprite_to_draw, x, y), &r2, &g2, &b2);

			if (r1 == r2 && g1 == g2 && b1 == b2)
				correct_pixels++;
		}
	}

	printf("%d %f\n", correct_pixels, (float) correct_pixels / (BUFFER_W * BUFFER_H));
	if ((float) correct_pixels / (BUFFER_W * BUFFER_H) > 0.95)
		return true;

	return false;
}

bool level3_update(MOUSE* mouse) {
	frames++;
	if (mouse->buttons[1]) {
		int x = mouse->x, y = mouse->y;
		if (pixel_index < N_PIXELS) {
			pixels[pixel_index].x = x;
			pixels[pixel_index].y = y;
			pixels[pixel_index].drawn = true;
			pixel_index++;
		} else {
			return true;
		}
	}
	return false;
}

void level3_draw() {
	if (frames < 120)
		al_draw_tinted_bitmap(
			sprite_to_draw,
			al_map_rgb_f(0.3,0.3,0.3),
			0, 0, 0
		);
	for (int i = 0; i < N_PIXELS; i++) {
		if (pixels[i].drawn)
			al_draw_filled_rectangle(
				pixels[i].x-8, pixels[i].y-8,
				pixels[i].x, pixels[i].y,
				al_map_rgb_f(1,1,1)
			);
	}
}
