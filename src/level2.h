#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "utils.h"
#include "input.h"
#include "display.h"

void level2_init();

void level2_select_item();

bool level2_check_done();

void level2_update(MOUSE *mouse);

void level2_draw();
