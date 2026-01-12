// Game_Rooms_tasks.h

#ifndef GAMEJAM2025_GAME_TASKS_H
#define GAMEJAM2025_GAME_TASKS_H

#include "main.h"
#include "game_tasks_defs.h"

typedef struct task_node_s {
	const game_task_t* task;
	coord_t size;
	struct task_node_s* prev;
	struct task_node_s* next;
} task_node_t;

typedef struct {
	task_node_t* start;
	task_node_t* end;
} task_queue_t;

void game_tasks_init (void);
void game_tasks_move (float dt);
void game_tasks_draw (void);
void game_tasks_close (void);
void game_tasks_add (const game_task_t* task_to_add);

extern task_queue_t tasks;

#endif
