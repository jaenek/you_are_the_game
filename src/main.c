#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>

#include "utils.h"
#include "input.h"
#include "display.h"
#include "level1.h"

typedef enum LEVELS {
	INIT_PROCESS_INPUT = 0,
	PROCESS_INPUT,
	UPDATE_PHYSICS,
} LEVELS;
LEVELS LEVEL = INIT_PROCESS_INPUT;

int main() {
	srand(time(NULL));

	must_init(al_init(), "allegro");

	ALLEGRO_DISPLAY *display = display_init();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
	must_init(timer, "timer");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	must_init(queue, "queue");

	unsigned char *key = keyboard_init();

	mouse_init(display);

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());

	bool done = false;
	bool redraw = true;
	ALLEGRO_EVENT event;

	al_start_timer(timer);
	al_hide_mouse_cursor(display);

	while(1) {
		al_wait_for_event(queue, &event);

		switch(event.type) {
			case ALLEGRO_EVENT_TIMER:
				if (key[ALLEGRO_KEY_ESCAPE])
					done = true;

				redraw = true;
				break;

			case ALLEGRO_EVENT_MOUSE_AXES:
				mouse_update(event.mouse.x, event.mouse.y);
				redraw = true;
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				if (LEVEL == PROCESS_INPUT && event.mouse.button == 1)
					if (level1_update(event.mouse.x, event.mouse.y))
						LEVEL++;

				redraw = true;
				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				done = true;
				break;
		}

		if (done)
			break;

		keyboard_update(&event);

		if (redraw && al_is_event_queue_empty(queue)) {
			display_pre_draw();
			al_clear_to_color(al_map_rgb(0,0,0));

			switch (LEVEL) {
				case INIT_PROCESS_INPUT:
					level1_init();
					LEVEL++;
				case PROCESS_INPUT:
					level1_draw();
					break;
				case UPDATE_PHYSICS:
					break;
			}

			mouse_draw();

			display_post_draw();
			redraw = false;
		}
	}

	display_deinit();
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}
