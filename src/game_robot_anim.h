// Game_Robot_anim.h

#ifndef GAMEJAM2025_GAME_ROBOT_ANIMS_H
#define GAMEJAM2025_GAME_ROBOT_ANIMS_H

#include <libdragon.h>
#include "main.h"

	//Bone                     Parent                   Sprite              Hook point on parent
#define ROBOT_BONE_TABLE(X) \
	X(ROBOT_BONE_TORSO,        -1,                      ROBOT_SPRITE_TORSO, 0.0f,   0.0f) \
	X(ROBOT_BONE_JAW,          ROBOT_BONE_TORSO,        ROBOT_SPRITE_JAW,   0.0f,  -1.0f) \
	X(ROBOT_BONE_HEAD,         ROBOT_BONE_JAW,          ROBOT_SPRITE_HEAD,  0.0f,  -6.0f) \
	X(ROBOT_BONE_ARM_UPPER_L,  ROBOT_BONE_TORSO,        ROBOT_SPRITE_LIMB,  0.0f,  0.0f) \
	X(ROBOT_BONE_ARM_LOWER_L,  ROBOT_BONE_ARM_UPPER_L,  ROBOT_SPRITE_ARM,   0.0f,  19.0f) \
	X(ROBOT_BONE_ARM_UPPER_R,  ROBOT_BONE_TORSO,        ROBOT_SPRITE_LIMB,  18.0f, 0.0f) \
	X(ROBOT_BONE_ARM_LOWER_R,  ROBOT_BONE_ARM_UPPER_R,  ROBOT_SPRITE_ARM,   0.0f,  19.0f) \
	X(ROBOT_BONE_LEG_UPPER_L,  ROBOT_BONE_TORSO,        ROBOT_SPRITE_LIMB,  3.0f,  30.0) \
	X(ROBOT_BONE_LEG_LOWER_L,  ROBOT_BONE_LEG_UPPER_L,  ROBOT_SPRITE_LEG,   0.0f,  19.0f) \
	X(ROBOT_BONE_LEG_UPPER_R,  ROBOT_BONE_TORSO,        ROBOT_SPRITE_LIMB,  17.0f, 30.0) \
	X(ROBOT_BONE_LEG_LOWER_R,  ROBOT_BONE_LEG_UPPER_R,  ROBOT_SPRITE_LEG,   0.0f,  19.0f)

#define X(name, parent, sprite, pos_x, pos_y) name,
typedef enum {
	ROBOT_BONE_TABLE(X)
	ROBOT_BONE_COUNT
} game_robot_bone_list_t;
#undef X

typedef enum {
	ROBOT_ANIMATION_LINEAR,
	ROBOT_ANIMATION_SMOOTH,
	ROBOT_ANIMATION_CUBIC,
	ROBOT_ANIMATION_COUNT,
} game_robot_animation_type_t;

typedef struct {
	float theta[ROBOT_BONE_COUNT];
	coord_t pos;
	uint8_t duration;
	game_robot_animation_type_t type;
} anim_keyframe_t;

typedef struct {
	char* name;
	const anim_keyframe_t* frames;
	uint8_t frame_count;
} animation_t;

void game_robot_change_animation (const animation_t* animation);

extern const animation_t anim_standing;
extern const animation_t anim_walking;

#endif
