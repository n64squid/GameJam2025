// Game_Rooms_defs.h

#ifndef GAMEJAM2025_GAME_ROOMS_DEFS_H
#define GAMEJAM2025_GAME_ROOMS_DEFS_H

#include "main.h"

typedef struct game_task_s {
	char* name;
	float duration;
	float urgency;
} game_task_t;

typedef struct game_object_s {
	char* name;
	char* canonical;
	coord_t pos;
	game_task_t* tasks;
	sprite_t* sprite;
} game_object_t;

typedef struct game_room_s {
	char* name;
	char* canonical;
	game_object_t* objects;
	uint8_t objects_count;
	sprite_t* wall_sprite;
	sprite_t* floor_sprite;
} game_room_t;

extern game_room_t rooms[];
extern const size_t room_count;

#endif
