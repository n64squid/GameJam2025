// Game_Rooms_defs.h

#ifndef GAMEJAM2025_GAME_ROOMS_DEFS_H
#define GAMEJAM2025_GAME_ROOMS_DEFS_H

#include "main.h"
#include "game_tasks_defs.h"

typedef struct game_object_s {
	char* name;
	coord_t pos;
	coord_t size;
	const task_list_t* tasks;
	const game_task_t* active_task;
	sprite_t* sprite;
	float time_left;
} game_object_t;

typedef struct game_room_s {
	char* name;
	game_object_t* objects;
	uint8_t objects_count;
	sprite_t* wall_sprite;
	sprite_t* floor_sprite;
} game_room_t;

extern game_room_t rooms[];
extern const size_t room_count;

void game_room_defs_init (void);
void game_rooms_defs_close (void);

#endif
