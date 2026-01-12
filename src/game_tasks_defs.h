// Game_tasks_defs.h

#ifndef GAMEJAM2025_GAME_TASKS_DEFS_H
#define GAMEJAM2025_GAME_TASKS_DEFS_H

#include "game_tools.h"

typedef enum {
	TASK_TYPE_AUTO,
	TASK_TYPE_MANUAL,
	TASK_TYPE_DISTRACTION,
} task_type_t;

typedef struct game_task_s {
	char* name;
	float duration;
	float urgency;
	task_type_t type;
	tools_t tool;
	const uint8_t* animation;
	uint8_t animation_length;
} game_task_t;

typedef struct {
	const game_task_t* tasks;
	uint8_t count;
} task_list_t;

typedef enum {
	TASK_DATA_EASY,
	TASK_DATA_MEDIUM,
	TASK_DATA_HARD,
	TASK_DATA_COUNT,
} task_data_enum_t;

typedef struct {
	uint16_t min_time;
	uint16_t create_chance;
} task_data_def_t;

typedef struct {
	task_data_enum_t difficulty;
	uint16_t timer;
	const task_data_def_t* data;
} task_data_state_t;

extern task_data_state_t task_state;

extern const task_list_t tasks_baby;
extern const task_list_t tasks_bed;
extern const task_list_t tasks_clothes;
extern const task_list_t tasks_pc;

extern const task_list_t tasks_bathtub;
extern const task_list_t tasks_sink;
extern const task_list_t tasks_toilet;
extern const task_list_t tasks_washer;

extern const task_list_t tasks_dog;
extern const task_list_t tasks_fridge;
extern const task_list_t tasks_oven;
extern const task_list_t tasks_basin;

extern const task_list_t tasks_door;
extern const task_list_t tasks_sofa;
extern const task_list_t tasks_tv;
extern const task_list_t tasks_window;

extern const task_list_t tasks_room;

#endif
