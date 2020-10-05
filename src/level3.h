#pragma once

#include <allegro5/allegro5.h>

#include "display.h"
#include "input.h"
#include "sprites.h"

void level3_init(SPRITES *sprites);

bool level3_check_done();

bool level3_update(MOUSE *mouse);

void level3_draw();
