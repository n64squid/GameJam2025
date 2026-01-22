#include "game_rooms.h"
#include "game_rooms_defs.h"
#include "game_main.h"
#include "main.h"

#define FLOOR_COUNT 2
#define ROOMS_PER_FLOOR 2
#define ARROW_MARGIN 4
#define ANIM_FRAME_TICKS 15
#define ANIM_URGENCY_FRAMES 3.0f

game_cursor_t cursor;
uint32_t animation_counter = 0;

void game_rooms_init (void) {
	cursor = (game_cursor_t){
		.room = 0,
		.selected_task = NULL,
		.selected_object = 0,
		.mode = CURSOR_SELECT_OBJECT,
		.sprite = sprite_load("rom:/images/icons/cursor.ci4.sprite"),
	};
	game_room_defs_init();
}

static inline uint8_t wrap_add(uint8_t v, int delta, uint8_t max) {
	return (v + delta + max) % max;
}

void game_rooms_move(float dt) {
	(void)dt;

	// Enter object mode on left/right
	if ((BTN_DOWN(d_left) || BTN_DOWN(d_right)) && cursor.mode != CURSOR_SELECT_OBJECT) {
		cursor.mode = CURSOR_SELECT_OBJECT;
		return;
	}

	// Object traversal
	if (cursor.mode == CURSOR_SELECT_OBJECT) {
		if (BTN_DOWN(d_right)) {
			cursor.selected_object =
				wrap_add(cursor.selected_object, +1, rooms[cursor.room].objects_count);
		}
		if (BTN_DOWN(d_left)) {
			cursor.selected_object =
				wrap_add(cursor.selected_object, -1, rooms[cursor.room].objects_count);
		}
		if (BTN_DOWN(a) && rooms[cursor.room].objects[cursor.selected_object].tasks->count && rooms[cursor.room].objects[cursor.selected_object].active_task) {
			game_tasks_add (rooms[cursor.room].objects[cursor.selected_object].active_task);
		}
	}

	// Room traversal
	int room_delta = 0;

	if (BTN_DOWN(c_right)) room_delta += 1;
	if (BTN_DOWN(c_left))  room_delta += ROOMS_PER_FLOOR-1;

	if (room_delta != 0) {
		cursor.room = ((cursor.room / ROOMS_PER_FLOOR) * ROOMS_PER_FLOOR) + ((cursor.room+room_delta) % ROOMS_PER_FLOOR);
		cursor.selected_object = 0;
		return;
	}
	if (BTN_DOWN(c_up))    room_delta += ROOMS_PER_FLOOR;
	if (BTN_DOWN(c_down))  room_delta += ROOMS_PER_FLOOR * FLOOR_COUNT - ROOMS_PER_FLOOR;

	if (room_delta != 0) {
		cursor.room = (cursor.room+room_delta) % (ROOMS_PER_FLOOR*FLOOR_COUNT);
		cursor.selected_object = 0;
		return;
	}
}


void game_rooms_draw (void) {

	// Draw the background
	rdpq_sprite_blit (
		rooms[cursor.room].wall_sprite,
		GAME_DISPLAY_PADDING,
		GAME_DISPLAY_PADDING,
		NULL
	);
	rdpq_sprite_blit (
		rooms[cursor.room].floor_sprite,
		GAME_DISPLAY_PADDING,
		GAME_DISPLAY_PADDING + WALL_HEIGHT,
		NULL
	);

	// Draw the objects
	for (size_t i=0; i<rooms[cursor.room].objects_count; i++) {
		assertf(rooms[cursor.room].objects[i].sprite->width <= rooms[cursor.room].objects[i].size.x*4, "Problem with: %s", rooms[cursor.room].objects[i].name);
		// Calculate the index of the task with pointer arithmetic
		uint8_t task_index = rooms[cursor.room].objects[i].active_task
			? (rooms[cursor.room].objects[i].active_task->urgency - rooms[cursor.room].objects[i].time_left) * ANIM_URGENCY_FRAMES
				/ rooms[cursor.room].objects[i].active_task->urgency + 1
			: 0;
		task_index = task_index == ANIM_URGENCY_FRAMES + 1 ? ANIM_URGENCY_FRAMES : task_index;
		rdpq_sprite_blit (
			rooms[cursor.room].objects[i].sprite,
			rooms[cursor.room].objects[i].pos.x,
			rooms[cursor.room].objects[i].pos.y,
			&(rdpq_blitparms_t) {
				.s0 = task_index * rooms[cursor.room].objects[i].size.x,
				.t0 = 0,
				.width = rooms[cursor.room].objects[i].size.x,
				.height = rooms[cursor.room].objects[i].size.y,
			}
		);

	}

	// Draw the arrow
	if (cursor.mode == CURSOR_SELECT_OBJECT) {
		rdpq_sprite_blit (
			cursor.sprite,
			rooms[cursor.room].objects[cursor.selected_object].pos.x + rooms[cursor.room].objects[cursor.selected_object].size.x/2 - cursor.sprite->width/2,
			rooms[cursor.room].objects[cursor.selected_object].pos.y - cursor.sprite->height - ARROW_MARGIN,
			NULL
		);
	}
	animation_counter++;
	return;
	rdpq_text_printf(NULL, 1, 20, 20,
		"Current room: %s\nSelected: %s",
		rooms[cursor.room].name,
		rooms[cursor.room].objects[cursor.selected_object].name
	);
}

void game_rooms_close (void) {
	sprite_free(cursor.sprite);
	game_rooms_defs_close();
}
