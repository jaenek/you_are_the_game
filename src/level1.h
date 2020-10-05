#ifndef LEVEL1_H
#define LEVEL1_H

#include <allegro5/allegro_primitives.h>

#include "utils.h"
#include "input.h"
#include "display.h"

void level1_init();

bool level1_check_done();

bool level1_update(MOUSE* mouse);

void level1_draw();

#endif
