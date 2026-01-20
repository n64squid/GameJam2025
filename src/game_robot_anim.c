#include "game_robot_anim.h"
#include "game_robot.h"
#define NULL_POS {0.0f,0.0f}
#define TO_RADIANS(x) (x*M_PI/180.0f)

void game_robot_change_animation (const animation_t* animation) {
	if (animation && robot.animation != animation) {
		robot.animation_keyframe = 0;
		robot.animation_frame = 0;
		robot.animation = animation;
	}
}

#define ROBOT_ANIMATION_STANDING_TYPE ROBOT_ANIMATION_SMOOTH
const anim_keyframe_t anim_standing_frames[] = {
	{
		.theta = {
			[ROBOT_BONE_TORSO]			= 0.0f,
			[ROBOT_BONE_HEAD]			= 0.0f,
			[ROBOT_BONE_ARM_UPPER_L]	= 0.0f,
			[ROBOT_BONE_ARM_LOWER_L]	= 0.0f,
			[ROBOT_BONE_ARM_UPPER_R]	= 0.0f,
			[ROBOT_BONE_ARM_LOWER_R]	= 0.0f,
			[ROBOT_BONE_LEG_UPPER_L]	= 0.0f,
			[ROBOT_BONE_LEG_LOWER_L]	= 0.0f,
			[ROBOT_BONE_LEG_UPPER_R]	= 0.0f,
			[ROBOT_BONE_LEG_LOWER_R]	= 0.0f,
		},
		.pos =							NULL_POS,
		.duration =						20,
		.type =							ROBOT_ANIMATION_STANDING_TYPE,
	},
	{
		.theta = {
			[ROBOT_BONE_TORSO]			= 0.0f,
			[ROBOT_BONE_HEAD]			= 0.0f,
			[ROBOT_BONE_ARM_UPPER_L]	= TO_RADIANS(-45.0f),
			[ROBOT_BONE_ARM_LOWER_L]	= TO_RADIANS(45.0f),
			[ROBOT_BONE_ARM_UPPER_R]	= TO_RADIANS(45.0f),
			[ROBOT_BONE_ARM_LOWER_R]	= TO_RADIANS(-45.0f),
			[ROBOT_BONE_LEG_UPPER_L]	= 0.0f,
			[ROBOT_BONE_LEG_LOWER_L]	= 0.0f,
			[ROBOT_BONE_LEG_UPPER_R]	= 0.0f,
			[ROBOT_BONE_LEG_LOWER_R]	= 0.0f,
		},
		.pos =							{0.0f,5.0f},
		.duration =						20,
		.type =							ROBOT_ANIMATION_STANDING_TYPE,
	},
};

const animation_t anim_standing = {
	.name = "Standing",
	.frames = anim_standing_frames,
	.frame_count = COUNT(anim_standing_frames),
};


#define ROBOT_ANIMATION_WALKING_TYPE ROBOT_ANIMATION_CUBIC
#define ROBOT_ANIMATION_WALKING_DURATION 7
const anim_keyframe_t anim_walking_frames[] = {
	{ // Contact
		.theta = {
			[ROBOT_BONE_TORSO]			= 0.0f,
			[ROBOT_BONE_HEAD]			= 0.0f,
			[ROBOT_BONE_ARM_UPPER_L]	= TO_RADIANS(-65.0f),
			[ROBOT_BONE_ARM_LOWER_L]	= TO_RADIANS(65.0f),
			[ROBOT_BONE_ARM_UPPER_R]	= TO_RADIANS(40.0f),
			[ROBOT_BONE_ARM_LOWER_R]	= TO_RADIANS(80.0f),
			[ROBOT_BONE_LEG_UPPER_L]	= TO_RADIANS(42.0f),
			[ROBOT_BONE_LEG_LOWER_L]	= TO_RADIANS(-25.0f),
			[ROBOT_BONE_LEG_UPPER_R]	= TO_RADIANS(-30.0f),
			[ROBOT_BONE_LEG_LOWER_R]	= TO_RADIANS(-30.0f),
		},
		.pos =							{0.0f, 3.0f},
		.duration =						ROBOT_ANIMATION_WALKING_DURATION,
		.type =							ROBOT_ANIMATION_WALKING_TYPE,
	},
	{ // Recoil
		.theta = {
			[ROBOT_BONE_TORSO]			= 0.0f,
			[ROBOT_BONE_HEAD]			= 0.0f,
			[ROBOT_BONE_ARM_UPPER_L]	= TO_RADIANS(-75.0f),
			[ROBOT_BONE_ARM_LOWER_L]	= TO_RADIANS(60.0f),
			[ROBOT_BONE_ARM_UPPER_R]	= TO_RADIANS(40.0f),
			[ROBOT_BONE_ARM_LOWER_R]	= TO_RADIANS(80.0f),
			[ROBOT_BONE_LEG_UPPER_L]	= TO_RADIANS(50.0f),
			[ROBOT_BONE_LEG_LOWER_L]	= TO_RADIANS(-25.0f),
			[ROBOT_BONE_LEG_UPPER_R]	= TO_RADIANS(-10.0f),
			[ROBOT_BONE_LEG_LOWER_R]	= TO_RADIANS(-90.0f),
		},
		.pos =							{0.0f, 3.0f},
		.duration =						ROBOT_ANIMATION_WALKING_DURATION,
		.type =							ROBOT_ANIMATION_WALKING_TYPE,
	},
	{ // Passing
		.theta = {
			[ROBOT_BONE_TORSO]			= 0.0f,
			[ROBOT_BONE_HEAD]			= 0.0f,
			[ROBOT_BONE_ARM_UPPER_L]	= TO_RADIANS(-12.0f),
			[ROBOT_BONE_ARM_LOWER_L]	= TO_RADIANS(32.0f),
			[ROBOT_BONE_ARM_UPPER_R]	= TO_RADIANS(-28.0f),
			[ROBOT_BONE_ARM_LOWER_R]	= TO_RADIANS(53.0f),
			[ROBOT_BONE_LEG_UPPER_L]	= TO_RADIANS(2.0f),
			[ROBOT_BONE_LEG_LOWER_L]	= TO_RADIANS(-13.0f),
			[ROBOT_BONE_LEG_UPPER_R]	= TO_RADIANS(30.0f),
			[ROBOT_BONE_LEG_LOWER_R]	= TO_RADIANS(-60.0f),
		},
		.pos =							{0.0f, 1.5f},
		.duration =						ROBOT_ANIMATION_WALKING_DURATION,
		.type =							ROBOT_ANIMATION_WALKING_TYPE,
	},
	{ // High-point
		.theta = {
			[ROBOT_BONE_TORSO]			= 0.0f,
			[ROBOT_BONE_HEAD]			= 0.0f,
			[ROBOT_BONE_ARM_UPPER_L]	= TO_RADIANS(15.0f),
			[ROBOT_BONE_ARM_LOWER_L]	= TO_RADIANS(100.0f),
			[ROBOT_BONE_ARM_UPPER_R]	= TO_RADIANS(-50.0f),
			[ROBOT_BONE_ARM_LOWER_R]	= TO_RADIANS(50.0f),
			[ROBOT_BONE_LEG_UPPER_L]	= TO_RADIANS(-20.0f),
			[ROBOT_BONE_LEG_LOWER_L]	= TO_RADIANS(-5.0f),
			[ROBOT_BONE_LEG_UPPER_R]	= TO_RADIANS(60.0f),
			[ROBOT_BONE_LEG_LOWER_R]	= TO_RADIANS(-90.0f),
		},
		.pos =							{0.0f, 0.0f},
		.duration =						ROBOT_ANIMATION_WALKING_DURATION,
		.type =							ROBOT_ANIMATION_WALKING_TYPE,
	},
	{ // Contact 2
		.theta = {
			[ROBOT_BONE_TORSO]			= 0.0f,
			[ROBOT_BONE_HEAD]			= 0.0f,
			[ROBOT_BONE_ARM_UPPER_L]	= TO_RADIANS(40.0f),
			[ROBOT_BONE_ARM_LOWER_L]	= TO_RADIANS(90.0f),
			[ROBOT_BONE_ARM_UPPER_R]	= TO_RADIANS(-65.0f),
			[ROBOT_BONE_ARM_LOWER_R]	= TO_RADIANS(65.0f),
			[ROBOT_BONE_LEG_UPPER_L]	= TO_RADIANS(-30.0f),
			[ROBOT_BONE_LEG_LOWER_L]	= TO_RADIANS(-30.0f),
			[ROBOT_BONE_LEG_UPPER_R]	= TO_RADIANS(42.0f),
			[ROBOT_BONE_LEG_LOWER_R]	= TO_RADIANS(-25.0f),
		},
		.pos =							{0.0f, 3.0f},
		.duration =						ROBOT_ANIMATION_WALKING_DURATION,
		.type =							ROBOT_ANIMATION_WALKING_TYPE,
	},
	{ // Recoil 2
		.theta = {
			[ROBOT_BONE_TORSO]			= 0.0f,
			[ROBOT_BONE_HEAD]			= 0.0f,
			[ROBOT_BONE_ARM_UPPER_L]	= TO_RADIANS(40.0f),
			[ROBOT_BONE_ARM_LOWER_L]	= TO_RADIANS(80.0f),
			[ROBOT_BONE_ARM_UPPER_R]	= TO_RADIANS(-75.0f),
			[ROBOT_BONE_ARM_LOWER_R]	= TO_RADIANS(60.0f),
			[ROBOT_BONE_LEG_UPPER_L]	= TO_RADIANS(-10.0f),
			[ROBOT_BONE_LEG_LOWER_L]	= TO_RADIANS(-90.0f),
			[ROBOT_BONE_LEG_UPPER_R]	= TO_RADIANS(50.0f),
			[ROBOT_BONE_LEG_LOWER_R]	= TO_RADIANS(-25.0f),
		},
		.pos =							{0.0f, 3.0f},
		.duration =						ROBOT_ANIMATION_WALKING_DURATION,
		.type =							ROBOT_ANIMATION_WALKING_TYPE,
	},
	{ // Passing 2
		.theta = {
			[ROBOT_BONE_TORSO]			= 0.0f,
			[ROBOT_BONE_HEAD]			= 0.0f,
			[ROBOT_BONE_ARM_UPPER_L]	= TO_RADIANS(-28.0f),
			[ROBOT_BONE_ARM_LOWER_L]	= TO_RADIANS(53.0f),
			[ROBOT_BONE_ARM_UPPER_R]	= TO_RADIANS(-12.0f),
			[ROBOT_BONE_ARM_LOWER_R]	= TO_RADIANS(32.0f),
			[ROBOT_BONE_LEG_UPPER_L]	= TO_RADIANS(30.0f),
			[ROBOT_BONE_LEG_LOWER_L]	= TO_RADIANS(-60.0f),
			[ROBOT_BONE_LEG_UPPER_R]	= TO_RADIANS(2.0f),
			[ROBOT_BONE_LEG_LOWER_R]	= TO_RADIANS(-13.0f),
		},
		.pos =							{0.0f, 1.5f},
		.duration =						ROBOT_ANIMATION_WALKING_DURATION,
		.type =							ROBOT_ANIMATION_WALKING_TYPE,
	},
	{ // High point 2
		.theta = {
			[ROBOT_BONE_TORSO]			= 0.0f,
			[ROBOT_BONE_HEAD]			= 0.0f,
			[ROBOT_BONE_ARM_UPPER_L]	= TO_RADIANS(-50.0f),
			[ROBOT_BONE_ARM_LOWER_L]	= TO_RADIANS(50.0f),
			[ROBOT_BONE_ARM_UPPER_R]	= TO_RADIANS(15.0f),
			[ROBOT_BONE_ARM_LOWER_R]	= TO_RADIANS(80.0f),
			[ROBOT_BONE_LEG_UPPER_L]	= TO_RADIANS(60.0f),
			[ROBOT_BONE_LEG_LOWER_L]	= TO_RADIANS(-90.0f),
			[ROBOT_BONE_LEG_UPPER_R]	= TO_RADIANS(-20.0f),
			[ROBOT_BONE_LEG_LOWER_R]	= TO_RADIANS(-5.0f),
		},
		.pos =							{0.0f, 0.0f},
		.duration =						ROBOT_ANIMATION_WALKING_DURATION,
		.type =							ROBOT_ANIMATION_WALKING_TYPE,
	},
};

const animation_t anim_walking = {
	.name = "Walking",
	.frames = anim_walking_frames,
	.frame_count = COUNT(anim_walking_frames),
};
