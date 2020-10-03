#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>

#include "utils.h"
#include "input.h"
#include "display.h"
#include "level1.h"

int main() {
	must_init(al_init(), "allegro");
	must_init(al_install_keyboard(), "keyboard");
	must_init(al_install_mouse(), "mouse");

	unsigned char *key = keyboard_init();

	ALLEGRO_DISPLAY *display = display_init();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
	must_init(timer, "timer");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	must_init(queue, "queue");

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_mouse_event_source());

	bool done = false;
	bool redraw = true;
	ALLEGRO_EVENT event;

	al_start_timer(timer);
	level1_init();

	while(1) {
		al_wait_for_event(queue, &event);

		switch(event.type) {
			case ALLEGRO_EVENT_TIMER:
				if (key[ALLEGRO_KEY_ESCAPE])
					done = true;

				redraw = true;
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				puts("button down");
				if (event.mouse.button == 1)
					level1_update(event.mouse.x, event.mouse.y);
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

			level1_draw();

			display_post_draw();
			redraw = false;
		}
	}

	display_deinit();
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}
