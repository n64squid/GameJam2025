#include "game_rooms_defs.h"
#include "game_main.h"

#define TASK_DURATION_SHORT 1.0f
#define TASK_DURATION_MID   1.5f
#define TASK_DURATION_LONG  2.5f

#define TASK_URGENCY_SHORT 10.0f
#define TASK_URGENCY_MID   15.0f
#define TASK_URGENCY_LONG  25.0f

#define OBJECT_COUNT(room) (sizeof(room) / sizeof(room[0]))

game_task_t tasks_baby[] = {
	{
		.name = "Change nappy",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
	},
	{.name = "Rock to sleep"},
	{.name = "Burp"},
};

game_object_t objects_bedroom[] = {
	{
		.name = "Baby",
		.canonical = "baby",
		.pos = {GAME_DISPLAY_PADDING, 96},
		.tasks = tasks_baby,
	},
	{
		.name = "Bed",
		.canonical = "bed",
		.pos = {GAME_DISPLAY_PADDING+66, 96},
	},
	{
		.name = "Clothes",
		.canonical = "clothes",
		.pos = {GAME_DISPLAY_PADDING+66+66, 96},
	},
	{
		.name = "Computer",
		.canonical = "computer",
		.pos = {GAME_DISPLAY_PADDING+66+66+66, 96},
	},
	{
		.name = "Floor",
		.canonical = "floor",
		.pos = {DISPLAY_WIDTH/2, GAME_DISPLAY_PADDING + WALL_HEIGHT + 8},
	},
};

game_object_t objects_bathroom[] = {
	{
		.name = "Baby",
		.canonical = "baby",
		.tasks = tasks_baby,
		.pos = {GAME_DISPLAY_PADDING, 96},
	}
};

game_object_t objects_kitchen[] = {
	{
		.name = "Baby",
		.canonical = "baby",
		.tasks = tasks_baby,
	}
};

game_object_t objects_living[] = {
	{
		.name = "Baby",
		.canonical = "baby",
		.tasks = tasks_baby,
	}
};

game_room_t rooms[] = {
	{
		.name = "Bedroom",
		.canonical = "bedroom",
		.objects = objects_bedroom,
		.objects_count = OBJECT_COUNT(objects_bedroom),
	},
	{
		.name = "Bathroom",
		.canonical = "bathroom",
		.objects = objects_bathroom,
		.objects_count = OBJECT_COUNT(objects_bathroom),
	},
	{
		.name = "Kitchen",
		.canonical = "kitchen",
		.objects = objects_kitchen,
		.objects_count = OBJECT_COUNT(objects_kitchen),
	},
	{
		.name = "Living Room",
		.canonical = "living",
		.objects = objects_living,
		.objects_count = OBJECT_COUNT(objects_living),
	},
};

const size_t room_count = sizeof(rooms) / sizeof(rooms[0]);
