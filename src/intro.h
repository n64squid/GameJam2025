#ifndef GAMEJAM2025_INTRO_H
#define GAMEJAM2025_INTRO_H

#include "main.h"

typedef struct vertex_s {
	float x, y, z;
} vertex_t;

void intro_init (void);
void intro_move (void);
void intro_draw (void);
void intro_end (void);

#endif
