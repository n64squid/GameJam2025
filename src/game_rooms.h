// Game_Rooms.h

#ifndef GAMEJAM2025_GAME_ROOMS_H
#define GAMEJAM2025_GAME_ROOMS_H

#include <libdragon.h>
#include "game_tasks.h"
#include "game_rooms_defs.h"

typedef enum {
	CURSOR_SELECT_OBJECT,
	CURSOR_SELECT_TASK,
	CURSOR_SELECT_COUNT,
} cursor_select_t;

typedef struct game_cursor_s {
	task_node_t* selected_task;
	uint8_t selected_object;
	uint8_t mode;
	uint8_t room;
	sprite_t* sprite;
} game_cursor_t;

void game_rooms_init (void);
void game_rooms_move (float dt);
void game_rooms_draw (void);
void game_rooms_close (void);

extern game_cursor_t cursor;

#endif
