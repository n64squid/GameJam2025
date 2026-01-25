// Game_Rooms_defs.h

#ifndef GAMEJAM2025_GAME_ROOMS_DEFS_H
#define GAMEJAM2025_GAME_ROOMS_DEFS_H

#include "main.h"
#include "game_tasks_defs.h"

typedef struct game_room_s game_room_t;

typedef struct game_object_s {
	char* name;
	coord_t pos, highlight_pos;
	coord_t size, highlight_size;
	const task_list_t* tasks;
	const game_task_t* active_task;
	sprite_t* sprite;
	float time_left;
	game_room_t* parent;
} game_object_t;

typedef enum {
	ROOM_EXIT_LEFT = 0,
	ROOM_EXIT_RIGHT = DISPLAY_WIDTH,
} game_room_exit_t;

typedef enum {
	ROOM_BEDROOM,
	ROOM_BATHROOM,
	ROOM_KITCHEN,
	ROOM_LIVINGROOM,
	ROOM_COUNT,
} game_rooms_enum_t;

typedef struct game_room_s {
	char* name;
	game_object_t* objects;
	uint8_t objects_count;
	sprite_t* wall_sprite;
	sprite_t* floor_sprite;
	game_room_exit_t exit;
} game_room_t;

extern game_room_t rooms[ROOM_COUNT];

void game_room_defs_init (void);
void game_rooms_defs_close (void);

#endif
