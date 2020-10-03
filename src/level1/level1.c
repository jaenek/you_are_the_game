#include "../level1.h"

#define POINTS 50
typedef struct POINT {
	int x, y;
	bool last;
} POINT;
POINT points[POINTS];

#define BTNS 5
typedef struct BTN {
	int x1, y1, x2, y2;
	int dest_point_index;
} BTN;
BTN btns[BTNS];
int selected = -1;

static void goright(int index) {
	points[index-1].last = false;
	points[index] = (POINT){
		.x = points[index-1].x + between(5, 101),
		.y = points[index-1].y,
		.last = true
	};
}

static void govertical(int index) {
	points[index-1].last = false;
	points[index] = (POINT){
		.x = points[index-1].x,
		.y = points[index-1].y + between(-81, 81),
		.last = true
	};
}

void level1_init() {
	points[0]  = (POINT){ .x = 30, .y = 1*BUFFER_H/6 };
	points[10] = (POINT){ .x = 30, .y = 2*BUFFER_H/6 };
	points[20] = (POINT){ .x = 30, .y = 3*BUFFER_H/6 };
	points[30] = (POINT){ .x = 30, .y = 4*BUFFER_H/6 };
	points[40] = (POINT){ .x = 30, .y = 5*BUFFER_H/6 };

	srand(time(NULL));

	goright(1);
	goright(11);
	goright(21);
	goright(31);
	goright(41);

	bool lastvertical = false;
	for (int i = 0; i < POINTS; i+=10) {
		for (int j = 2; j < 10; j++) {
			if (points[i+j].x < 300) {
				int randint = between(0,2);
				if (lastvertical || randint == 0) {
					goright(i+j);
					lastvertical = false;
				} else {
					govertical(i+j);
					lastvertical = true;
				}
			}

			if (points[i+j].y < 0)
				points[i+j].y = -points[i+j].y;
			else if (points[i+j].y > BUFFER_H)
				points[i+j].y = BUFFER_H+BUFFER_H-points[i+j].y;
		}
	}

	for (int i = 0; i < POINTS; i+=10) {
		for (int j = 2; j < 10; j++) {
			if (points[i+j].x > 300)
				points[i+j].x = 300;
		}
	}

	btns[0] = (BTN){ .x1 = 10, .y1 = 1*BUFFER_H/6-10, .x2 = 30, .y2 = 1*BUFFER_H/6+10 };
	btns[1] = (BTN){ .x1 = 10, .y1 = 2*BUFFER_H/6-10, .x2 = 30, .y2 = 2*BUFFER_H/6+10 };
	btns[2] = (BTN){ .x1 = 10, .y1 = 3*BUFFER_H/6-10, .x2 = 30, .y2 = 3*BUFFER_H/6+10 };
	btns[3] = (BTN){ .x1 = 10, .y1 = 4*BUFFER_H/6-10, .x2 = 30, .y2 = 4*BUFFER_H/6+10 };
	btns[4] = (BTN){ .x1 = 10, .y1 = 5*BUFFER_H/6-10, .x2 = 30, .y2 = 5*BUFFER_H/6+10 };
}

void level1_update(int x, int y) {
	for (int i = 0; i < BTNS; i++) {
		if (collide(btns[i].x1, btns[i].y1, btns[i].x2, btns[i].y2, 0, 0, x, y)) {
			puts("updating");
			selected = i;
		}
	}
}

void level1_draw() {
	for (int i = 0; i < BTNS; i++) {
		al_draw_filled_rectangle(
			btns[i].x1, btns[i].y1,
			btns[i].x2, btns[i].y2,
			(i == selected) ? al_map_rgb_f(0.46, 0.8, 0.4) : al_map_rgb_f(0.86, 0.8, 0.8)
		);
	}

	for (int i = 0; i < POINTS; i+=10) {
		for (int j = 0; j < 9; j++) {
			al_draw_line(
			    points[i+j].x,   points[i+j].y,
			    points[i+j+1].x, points[i+j+1].y,
			    al_map_rgb_f(1,1,1),
				1
			);

			if (points[i+j+1].last) {
				al_draw_filled_circle(
					points[i+j+1].x, points[i+j+1].y,
					5,
					al_map_rgb_f(1,0.5,0.3)
				);
			}
		}
	}
}
