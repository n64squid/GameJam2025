#include "game_tasks.h"
#include "game_rooms.h"
#include "game_state.h"
#include "game_robot.h"
#include "main.h"
#include "state.h"

#define TASKBAR_PADDING 4

task_queue_t tasks;

void game_tasks_update_target (void) {
	if (tasks.start == NULL) {
		robot.target = NULL;
		return;
	}
	for (uint8_t i=0; i<ROOM_COUNT; i++) {
		for (size_t j=0; j<rooms[i].objects_count; j++) {
			if (tasks.start->task == rooms[i].objects[j].active_task) {
				robot.target = &rooms[i].objects[j];
				return;
			}
		}
	}
}

void game_tasks_add (const game_task_t* task_to_add) {
	task_node_t* new_task = malloc(sizeof(task_node_t));
	if (new_task) {
		if (tasks.start == NULL) {
			tasks.start = new_task;
		} else {
			tasks.end->next = new_task;
		}
		new_task->task = task_to_add;
		new_task->next = NULL;
		new_task->prev = tasks.end;
		tasks.end = new_task;
		cursor.selected_task = cursor.selected_task ? cursor.selected_task : new_task;
	}
	game_tasks_update_target();
}

void game_tasks_remove(task_node_t* node) {
	if (!node) return;

	// If node has a previous element, bypass it
	if (node->prev) {
		node->prev->next = node->next;
	} else {
		// Removing the first node
		tasks.start = node->next;
	}

	// If node has a next element, bypass it
	if (node->next) {
		node->next->prev = node->prev;
	} else {
		// Removing the last node
		tasks.end = node->prev;
	}

	cursor.selected_task = node->next ? node->next : node->prev;
	free(node);
	game_tasks_update_target();
}

void game_tasks_init (void) {
	tasks.start = NULL;
	tasks.end = NULL;
	task_state.timer = 0;
}

typedef enum {
	MOVE_NEXT,
	MOVE_PREV
} move_dir_t;

void move_task_cursor(move_dir_t dir) {
	if (cursor.mode == CURSOR_SELECT_OBJECT) {
		cursor.mode = CURSOR_SELECT_TASK;
		return;
	}

	if (!cursor.selected_task)  {
		return;
	}

	if (dir == MOVE_NEXT) {
		task_node_t* next = cursor.selected_task->next;
		cursor.selected_task = next ? next : tasks.start;
	} else {
		task_node_t* prev = cursor.selected_task->prev;
		cursor.selected_task = prev ? prev : tasks.end;
	}
}

void game_tasks_move (float dt) {

	// Handle button inputs
	if (BTN_DOWN(r)) {
		move_task_cursor(MOVE_NEXT);
	}
	if (BTN_DOWN(l)) {
		move_task_cursor(MOVE_PREV);
	}
	if (BTN_DOWN(b)) {
		if (cursor.mode == CURSOR_SELECT_TASK) {
			game_tasks_remove(cursor.selected_task);
		}
	}

	// Handle task creation
	if (task_state.timer > task_state.data[task_state.difficulty].min_time) {
		if (!(rand() % task_state.data[task_state.difficulty].create_chance)) {
			uint8_t random_room = rand() % ROOM_COUNT;
			uint8_t random_object = rand() % rooms[random_room].objects_count;
			uint8_t random_task = rand() % rooms[random_room].objects[random_object].tasks->count;
			rooms[random_room].objects[random_object].active_task = &rooms[random_room].objects[random_object].tasks->tasks[random_task];
			rooms[random_room].objects[random_object].time_left = rooms[random_room].objects[random_object].active_task->urgency;
			task_state.timer = 0;
		}
	}
	task_state.timer++;

	// Count down the timers on active tasks
	for (size_t i=0; i<ROOM_COUNT; i++) {
		for (size_t j=0; j<rooms[i].objects_count; j++) {
			if (rooms[i].objects[j].active_task) {
				rooms[i].objects[j].time_left -= 1.0 * dt;
				if (rooms[i].objects[j].time_left <= 0) {
					game_state = STATE_GAME_GAME_OVER;
					failed_task_object = &rooms[i].objects[j];
				}
			}
		}
	}
}

void game_tasks_draw (void) {
	task_node_t* current = tasks.start;
	rdpq_textmetrics_t text_metrics;
	coord_t task_cursor = {
		GAME_DISPLAY_PADDING + TASKBAR_PADDING,
		GAME_DISPLAY_PADDING*2,
	};
	while (current) {
		text_metrics = rdpq_text_printf(NULL, 1,
			task_cursor.x,
			task_cursor.y,
			"%s",
			current->task->name
		);
		current->size = (coord_t){
			text_metrics.advance_x,
			text_metrics.advance_y,
		};

		// Draw the arrow
		if (current == cursor.selected_task && cursor.mode == CURSOR_SELECT_TASK) {
			rdpq_sprite_blit (
				cursor.sprite,
				task_cursor.x + current->size.x/2 - cursor.sprite->width/2,
				task_cursor.y + TASKBAR_PADDING,
				&(rdpq_blitparms_t) {
					.flip_y = true
				}
			);
		}

		task_cursor.x += current->size.x + TASKBAR_PADDING;
		current = current->next;
	}
	return;
	rdpq_text_printf(NULL, 1,
		20,
		30,
		"%i",
		task_state.timer
	);
}

void game_tasks_close (void) {
	task_node_t* current = tasks.start;
	task_node_t* to_free;
	while (current) {
		to_free = current;
		current = current->next;
		free(to_free);
	}
	tasks.start = NULL;
	tasks.end = NULL;
}
