#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>

#include "common.h"

int main() {
	must_init(al_init(), "allegro");
	must_init(al_install_keyboard(), "keyboard");

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
	must_init(timer, "timer");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	must_init(queue, "queue");

	/* more must_inits go here (audio, image etc.) */

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	disp_init();
	keyboard_init();

	/* more non must_init inits*/

	bool done = false;
	bool redraw = true;
	ALLEGRO_EVENT event;

	al_start_timer(timer);

	while(1) {
		al_wait_for_event(queue, &event);

		switch(event.type) {
			case ALLEGRO_EVENT_TIMER:
				/* game logic */
				redraw = true;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				done = true;
				break;
		}

		if (done)
			break;

		keyboard_update(&event);

		if (redraw && al_is_event_queue_empty(queue)) {
			disp_pre_draw();
			al_clear_to_color(al_map_rgb(0,0,0));

			/* draw to buffer */

			disp_post_draw();
			redraw = false;
		}
	}

	/* deinit stuff */
	disp_deinit();
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}
