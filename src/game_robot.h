// Game_Robot.h

#ifndef GAMEJAM2025_GAME_ROBOT_H
#define GAMEJAM2025_GAME_ROBOT_H

#include <libdragon.h>
#include "main.h"
#include "game_robot_anim.h"
#include "game_rooms_defs.h"

#define MAX_BONE_CHILDREN 6
#define ROBOT_PARTS_MAX_HEALTH 3
#define ROBOT_POS_START {240, 100}

typedef enum {
	ROBOT_PARTS_HEAD,
	ROBOT_PARTS_ARMS,
	ROBOT_PARTS_LEGS,
	ROBOT_PARTS_COUNT,
} game_robot_health_enum_t;

#define ROBOT_SPRITE_TABLE(X) \
	X(ROBOT_SPRITE_TORSO, "Torso", 13, 0) \
	X(ROBOT_SPRITE_JAW, "Jaw", 26, 6) \
	X(ROBOT_SPRITE_HEAD, "Head", 25, 36) \
	X(ROBOT_SPRITE_LIMB, "Limb", 4, 0) \
	X(ROBOT_SPRITE_ARM, "Arm", 7, 3) \
	X(ROBOT_SPRITE_LEG, "Leg", 4, 3) \

#define X(name, uri, cx, cy) name,
typedef enum {
	ROBOT_SPRITE_TABLE(X)
	ROBOT_SPRITE_COUNT,
} game_robot_sprite_t;
#undef X

typedef enum {
	ROBOT_FACING_RIGHT = 1,
	ROBOT_FACING_LEFT  = -1,
} robot_facing_t;

typedef struct game_robot_bone_s {
	game_robot_bone_list_t parent;
	game_robot_bone_list_t children[MAX_BONE_CHILDREN];
	coord_t pos, world_pos;
	float theta, world_theta;
	game_robot_sprite_t sprite;
} game_robot_bone_t;

typedef struct game_robot_part_s {
	char* name;
	uint8_t health;
} game_robot_part_t;

typedef struct game_robot_s {
	game_robot_part_t parts[ROBOT_PARTS_COUNT];
	game_robot_bone_t bones[ROBOT_BONE_COUNT];
	game_robot_bone_list_t bone_draw_order[ROBOT_BONE_COUNT];
	coord_t pos;
	game_rooms_enum_t room;
	const animation_t* animation;
	uint8_t animation_keyframe;
	uint8_t animation_frame;
	robot_facing_t facing;
	game_object_t* target;
} game_robot_t;

extern game_robot_t robot;

void game_robot_init (void);
void game_robot_move (float dt);
void game_robot_draw (void);
void game_robot_close (void);

#endif
