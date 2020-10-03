#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <allegro5/allegro5.h>

void must_init(bool test, const char *description);

int between(int lo, int hi);

float between_f(float lo, float hi);

bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);

#endif
