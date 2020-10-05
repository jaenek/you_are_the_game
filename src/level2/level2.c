#include "../level2.h"

typedef enum ITEM_TYPE {
	TRIANGLE = 0,
	FILL_TRIANGLE,
	RECT,
	FILL_RECT,
	CIRCLE,
	FILL_CIRCLE,
	N_ITEM_TYPES
} ITEM_TYPE;

typedef struct ITEM {
	float x1, y1, x2, y2;
	ITEM_TYPE type;
	ALLEGRO_COLOR color;
} ITEM;

#define N_ITEMS 10
ITEM items[10];
int selected_item;

void level2_init() {
	selected_item = 0;

	for (int i = 0; i < N_ITEMS; i++) {
		ITEM_TYPE type = between(0, N_ITEM_TYPES);

		if (type != CIRCLE && type != FILL_CIRCLE) {
			int w = between(50, 70);
			int h = between(30, 50);

			items[i] = (ITEM) {
				.x1 = between(w/2, BUFFER_W-w/2),
				.y1 = between(h/2, BUFFER_H-h/2),
				.type = type
			};

			items[i].x2 = items[i].x1 + w;
			items[i].y2 = items[i].y1 + h;
		} else {
			int d = between(10, 50);

			items[i] = (ITEM) {
				.x1 = between(d/2, BUFFER_W-d/2),
				.y1 = between(d/2, BUFFER_H-d/2),
				.type = type
			};

			items[i].x2 = items[i].x1 + d;
			items[i].y2 = items[i].y1 + d;
		}

		items[i].color = al_map_rgb_f(between_f(0.3, 1), between_f(0.3, 1), between_f(0.3, 1));
	}
}

void level2_select_item(MOUSE *mouse) {
	if (mouse->buttons[1]) {
		if (selected_item) {
			selected_item = 0;
		} else {
			for (int i = 0; i < N_ITEMS; i++) {
				if (collide(
						mouse->x,    mouse->y,
						mouse->x,    mouse->y,
						items[i].x1, items[i].y1,
						items[i].x2, items[i].y2)) {
					selected_item = i+1;
				}
			}
		}
	}
}

bool level2_check_done() {
	for (int i = 0; i < N_ITEMS; i++) {
		for (int j = 0; j < N_ITEMS; j++) {
			if (i == j) continue;
			if (collide(
					items[i].x1, items[i].y1, items[i].x2, items[i].y2,
					items[j].x1, items[j].y1, items[j].x2, items[j].y2
				)) {
				return false;
			}
		}
	}

	return true;
}

void level2_update(MOUSE *mouse) {
	if (selected_item) {
		items[selected_item-1].x1 += mouse->dx;
		items[selected_item-1].y1 += mouse->dy;
		items[selected_item-1].x2 += mouse->dx;
		items[selected_item-1].y2 += mouse->dy;
	}
}

void level2_draw() {
	int y, r;
	for (int i = 0; i < N_ITEMS; i++) {
		switch (items[i].type) {
			case TRIANGLE:
				y = items[i].y2 - items[i].y1 + items[i].y1;
				al_draw_triangle(
					items[i].x1, items[i].y1,
					items[i].x1, y,
					items[i].x2, items[i].y2,
					items[i].color,
					2
				);
				break;
			case FILL_TRIANGLE:
				y = items[i].y2 - items[i].y1 + items[i].y1;
				al_draw_triangle(
					items[i].x1, items[i].y1,
					items[i].x1, y,
					items[i].x2, items[i].y2,
					items[i].color,
					2
				);
				break;
			case RECT:
				al_draw_rectangle(
					items[i].x1, items[i].y1,
					items[i].x2, items[i].y2,
					items[i].color,
					2
				);
				break;
			case FILL_RECT:
				al_draw_filled_rectangle(
					items[i].x1, items[i].y1,
					items[i].x2, items[i].y2,
					items[i].color
				);
				break;
			case CIRCLE:
				r = (items[i].x2 - items[i].x1)/2;
				al_draw_circle(
					items[i].x1+r, items[i].y1+r,
					r,
					items[i].color,
					2
				);
				break;
			case FILL_CIRCLE:
				r = (items[i].x2 - items[i].x1)/2;
				al_draw_circle(
					items[i].x1+r, items[i].y1+r,
					r,
					items[i].color,
					2
				);
				break;
			default:
				break;
		}
	}
	putchar('\n');
}
