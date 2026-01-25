#include "game_robot.h"
#include "game_rooms.h"
#include "game_tasks.h"

#define ROBOT_SPEED 1.2f

typedef struct {
	const char *name;
	sprite_t *sprite;
	coord_t c;
} robot_sprite_t;

#define X(id, fullname, cx_p, cy_p) {fullname, NULL, {cx_p, cy_p}},
robot_sprite_t robot_sprites[ROBOT_SPRITE_COUNT] = {
	ROBOT_SPRITE_TABLE(X)
};
#undef X

game_robot_t robot = {
	.parts = {
		[ROBOT_PARTS_HEAD] = {"HEAD" , ROBOT_PARTS_MAX_HEALTH},
		[ROBOT_PARTS_ARMS] = {"ARMS" , ROBOT_PARTS_MAX_HEALTH},
		[ROBOT_PARTS_LEGS] = {"LEGS" , ROBOT_PARTS_MAX_HEALTH},
	},
#define X(name, parent_p, sprite_p, pos_x, pos_y) \
	[name] = { \
		.parent = parent_p, \
		.sprite = sprite_p, \
		.pos = {pos_x, pos_y} \
	},
	.bones = {
		ROBOT_BONE_TABLE(X)
	},
	.bone_draw_order = {
		ROBOT_BONE_ARM_LOWER_L,
		ROBOT_BONE_ARM_UPPER_L,
		ROBOT_BONE_LEG_LOWER_L,
		ROBOT_BONE_LEG_UPPER_L,
		ROBOT_BONE_TORSO,
		ROBOT_BONE_JAW,
		ROBOT_BONE_HEAD,
		ROBOT_BONE_ARM_LOWER_R,
		ROBOT_BONE_ARM_UPPER_R,
		ROBOT_BONE_LEG_LOWER_R,
		ROBOT_BONE_LEG_UPPER_R,
	},
	.pos = ROBOT_POS_START,
	.room = ROOM_BEDROOM,
	.animation = &anim_walking,
	.animation_keyframe = 0,
	.animation_frame = 0,
	.facing = ROBOT_FACING_RIGHT,
	.target = NULL,
#undef X
};

void game_robot_init (void) {
	char temptext[64];
	char canonical[16];
	for (uint8_t i=0; i<ROBOT_SPRITE_COUNT; i++) {
		make_canonical(canonical, robot_sprites[i].name);
		sprintf(temptext, "rom:/images/robot/%s.ci4.sprite", canonical);
		robot_sprites[i].sprite = sprite_load(temptext);
	}
	uint8_t torso_counter = 0;
	for (uint8_t i=0; i<ROBOT_BONE_COUNT; i++) {
		if (robot.bones[i].parent == ROBOT_BONE_TORSO) {
			robot.bones[robot.bones[i].parent].children[torso_counter++] = i;
		} else {
			robot.bones[robot.bones[i].parent].children[0] = i;
		}
	}
	for (uint8_t i=0; i<ROBOT_PARTS_COUNT; i++) {
		robot.parts[i].health = ROBOT_PARTS_MAX_HEALTH;
	}
	robot.pos = (coord_t)ROBOT_POS_START;
	robot.animation = &anim_standing;
	robot.animation_keyframe = 0;
	robot.animation_frame = 0;
	robot.facing = ROBOT_FACING_LEFT;
	robot.target = NULL;
	robot.room = ROOM_BEDROOM;
}
static inline float smoothstep(float a, float b, float t) {
	t = t * t * (3.0f - 2.0f * t);
	return a + (b - a) * t;
}
static inline coord_t coord_smoothstep(coord_t a, coord_t b, float t) {
	return (coord_t){
		.x = smoothstep(a.x, b.x, t),
		.y = smoothstep(a.y, b.y, t),
	};
}
float compute_tangent(const animation_t* anim, int frame, int bone) {
	int prev = (frame - 1 + anim->frame_count) % anim->frame_count;
	int next = (frame + 1) % anim->frame_count;

	float p_prev = anim->frames[prev].theta[bone];
	float p_next = anim->frames[next].theta[bone];

	return 0.5f * (p_next - p_prev);
}
coord_t compute_coord_tangent(const animation_t* anim, int frame) {
	int prev = (frame - 1 + anim->frame_count) % anim->frame_count;
	int next = (frame + 1) % anim->frame_count;

	coord_t p_prev = anim->frames[prev].pos;
	coord_t p_next = anim->frames[next].pos;

	return (coord_t){
		.x = 0.5f * (p_next.x - p_prev.x),
		.y = 0.5f * (p_next.y - p_prev.y),
	};
}
static inline float hermite(float p0, float m0, float p1, float m1, float t) {
	float t2 = t * t;
	float t3 = t2 * t;

	return
		(2*t3 - 3*t2 + 1) * p0 +
		(t3 - 2*t2 + t) * m0 +
		(-2*t3 + 3*t2) * p1 +
		(t3 - t2) * m1;
}
static inline coord_t coord_hermite(coord_t p0, coord_t m0, coord_t p1, coord_t m1, float t) {
	return (coord_t){
		.x = hermite(p0.x, m0.x, p1.x, m1.x, t),
		.y = hermite(p0.y, m0.y, p1.y, m1.y, t),
	};
}

void game_robot_animate (void) {
	uint8_t next_keyframe = (robot.animation_keyframe + 1) % robot.animation->frame_count;
	uint8_t duration = robot.animation->frames[robot.animation_keyframe].duration;
	float duration_percent = ((float)(duration-robot.animation_frame) / duration);
	float t = (float)robot.animation_frame / duration;
	switch (robot.animation->frames[robot.animation_keyframe].type) {
		case ROBOT_ANIMATION_LINEAR:
			for (uint8_t i=0; i<ROBOT_BONE_COUNT; i++) {
				robot.bones[i].theta =
					robot.animation->frames[robot.animation_keyframe].theta[i] * duration_percent +
					robot.animation->frames[next_keyframe].theta[i] * ((float)robot.animation_frame / duration);
			}
			break;
		case ROBOT_ANIMATION_SMOOTH:
			robot.bones[ROBOT_BONE_TORSO].pos =	coord_smoothstep (
				robot.animation->frames[robot.animation_keyframe].pos,
				robot.animation->frames[next_keyframe].pos,
				t
			);
			for (uint8_t i=0; i<ROBOT_BONE_COUNT; i++) {
				robot.bones[i].theta = smoothstep(
					robot.animation->frames[robot.animation_keyframe].theta[i],
					robot.animation->frames[next_keyframe].theta[i],
					t
				);
			}
			break;
		case ROBOT_ANIMATION_CUBIC:
			robot.bones[ROBOT_BONE_TORSO].pos =	coord_hermite(
			robot.animation->frames[robot.animation_keyframe].pos,
			compute_coord_tangent(robot.animation, robot.animation_keyframe),
			robot.animation->frames[next_keyframe].pos,
			compute_coord_tangent(robot.animation, next_keyframe),
			t
		);
			for (uint8_t i=0; i<ROBOT_BONE_COUNT; i++) {
				robot.bones[i].theta = hermite(
					robot.animation->frames[robot.animation_keyframe].theta[i],
					compute_tangent(robot.animation, robot.animation_keyframe, i),
					robot.animation->frames[next_keyframe].theta[i],
					compute_tangent(robot.animation,next_keyframe, i),
					t
				);
			}
			break;
		default:
			break;
	}

	if (robot.animation_frame >= robot.animation->frames[robot.animation_keyframe].duration) {
		robot.animation_keyframe = (robot.animation_keyframe + 1) % robot.animation->frame_count;
		robot.animation_frame = 0;
	} else {
		robot.animation_frame++;
	}
}

void game_robot_calculate_bone(game_robot_bone_list_t bone_id, coord_t parent_pos, float parent_theta) {
	game_robot_bone_t *bone = &robot.bones[bone_id];

	// Rotate local position by parent's rotation
	float s = -sinf(parent_theta);
	float c = cosf(parent_theta);

	bone->world_pos = (coord_t){
		.x = parent_pos.x + bone->pos.x * c - bone->pos.y * s,
		.y = parent_pos.y + bone->pos.x * s + bone->pos.y * c,
	};

	bone->world_theta = parent_theta + bone->theta;

	// Recurse into children
	for (uint8_t i = 0; i < MAX_BONE_CHILDREN; i++) {
		game_robot_bone_list_t child = bone->children[i];
		if (child != ROBOT_BONE_TORSO) {
			game_robot_calculate_bone(child, bone->world_pos, bone->world_theta);
		}
	}
}

void game_robot_move (float dt) {
	float diff;
	float target_x;

	// Animate the skeleton
	game_robot_animate();
	game_robot_calculate_bone(
		ROBOT_BONE_TORSO,
		robot.pos,
		0.0f
	);

	// Move in space
	if (robot.target) {
		if (&rooms[robot.room] == robot.target->parent) {
			target_x = robot.target->pos.x + robot.target->size.x/2;
		} else {
			target_x = rooms[robot.room].exit;
		}
		diff = target_x - robot.pos.x;

		if (fabs(diff) > ROBOT_SPEED) {
			// Move towards the target
			game_robot_change_animation (&anim_walking);
			robot.facing = ((diff > 0.f) - (diff < 0.f));
			robot.pos.x += ROBOT_SPEED * robot.facing;
		} else {
			// Perform action at target
			if (&rooms[robot.room] == robot.target->parent) {
				// At the object
				game_robot_change_animation (&anim_standing);
				robot.facing = ROBOT_FACING_RIGHT;
				robot.target->active_task = NULL;
				game_tasks_remove(tasks.start);
			} else {
				// At the edge of the screen
				robot.room = robot.target->parent - rooms;
			}
		}

	} else {
		game_robot_change_animation (&anim_standing);
	}
}

void game_robot_draw (void) {
	if (cursor.room != robot.room) {
		return;
	}
	rdpq_set_mode_standard();
	rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
	game_robot_calculate_bone(
		ROBOT_BONE_TORSO,
		robot.pos,
		0.0f
	);
	game_robot_bone_t* bone;
	float x, theta, cx;
	sprite_t* sprite;
	for (uint8_t i = 0; i < ROBOT_BONE_COUNT; i++) {
		bone = &robot.bones[i];
		sprite = robot_sprites[bone->sprite].sprite;

		x = bone->world_pos.x;
		theta = bone->world_theta;
		cx = robot_sprites[bone->sprite].c.x;

		if (robot.facing == ROBOT_FACING_LEFT) {
			x = robot.pos.x * 2.0f - x;
			cx = sprite->width - cx;
			theta = -theta;
		}

		rdpq_sprite_blit (
			sprite,
			x,
			bone->world_pos.y,
			&(rdpq_blitparms_t){
				.flip_x = robot.facing < 0,
				.cx = cx,
				.cy = robot_sprites[bone->sprite].c.y,
				.theta = theta,
			}
		);
	}

	rdpq_text_printf(NULL, 1,
		20,
		30,
		"Target: %p",
		robot.target
	);
}

void game_robot_close (void) {
	for (uint8_t i=0; i<ROBOT_SPRITE_COUNT; i++) {
		sprite_free(robot_sprites[i].sprite);
	}
}
