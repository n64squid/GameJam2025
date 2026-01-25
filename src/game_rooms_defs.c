#include "game_rooms_defs.h"
#include "game_main.h"

#define OBJECT_SPRITE_COUNT 4

game_object_t objects_bedroom[] = {
	{
		.name = "Bed",
		.pos = {15, 21},
		.size = {116, 128},
		.tasks = &tasks_bed,
	},
	{
		.name = "Bed light",
		.pos = {70, 14},
		.size = {168, 47},
		.tasks = &tasks_room,
	},
	{
		.name = "Computer",
		.pos = {114, 63},
		.size = {79, 59},
		.tasks = &tasks_pc,
	},
	{
		.name = "Baby",
		.pos = {202, 52},
		.size = {57, 92},
		.tasks = &tasks_baby,
	},
	{
		.name = "Clothes",
		.pos = {268, 11},
		.size = {44, 173},
		.tasks = &tasks_clothes,
	},
};

game_object_t objects_bathroom[] = {
	{
		.name = "Washer",
		.pos = {19, 32},
		.size = {67, 126},
		.tasks = &tasks_washer,
	},
	{
		.name = "Bathtub",
		.tasks = &tasks_bathtub,
		.pos = {87, 64},
		.size = {101, 85},
	},
	{
		.name = "Bath light",
		.pos = {76, 14},
		.size = {164, 38},
		.tasks = &tasks_room,
	},
	{
		.name = "Toilet",
		.pos = {197, 82},
		.size = {52, 76},
		.tasks = &tasks_toilet,
	},
	{
		.name = "Sink",
		.pos = {252, 19},
		.size = {53, 140},
		.tasks = &tasks_sink,
	},
};

game_object_t objects_kitchen[] = {
	{
		.name = "Dog",
		.pos = {8, 8},
		.size = {75, 171},
		.tasks = &tasks_dog,
	},
	{
		.name = "Oven",
		.pos = {80, 15},
		.size = {66, 144},
		.tasks = &tasks_oven,
	},
	{
		.name = "Basin",
		.pos = {139, 94},
		.size = {80, 65},
		.tasks = &tasks_basin,
	},
	{
		.name = "Kitchen light",
		.pos = {169, 14},
		.size = {69, 64},
		.tasks = &tasks_room,
	},
	{
		.name = "Fridge",
		.pos = {226, 34},
		.size = {72, 125},
		.tasks = &tasks_fridge,
	},
};

game_object_t objects_living[] = {
	{
		.name = "TV",
		.pos = {18, 56},
		.size = {59, 66},
		.tasks = &tasks_tv,
	},
	{
		.name = "L Room light",
		.pos = {76, 14},
		.size = {56, 73},
		.tasks = &tasks_room,
	},
	{
		.name = "Sofa",
		.pos = {81, 64},
		.size = {136, 85},
		.tasks = &tasks_sofa,
	},
	{
		.name = "Window",
		.pos = {173, 15},
		.size = {83, 147},
		.tasks = &tasks_window,
	},
	{
		.name = "Front door",
		.pos = {236, 11},
		.size = {76, 173},
		.tasks = &tasks_door,
	},
};

game_room_t rooms[] = {
	{
		.name = "Bedroom",
		.objects = objects_bedroom,
		.objects_count = COUNT(objects_bedroom),
		.exit = ROOM_EXIT_RIGHT,
	},
	{
		.name = "Bathroom",
		.objects = objects_bathroom,
		.objects_count = COUNT(objects_bathroom),
		.exit = ROOM_EXIT_LEFT,
	},
	{
		.name = "Kitchen",
		.objects = objects_kitchen,
		.objects_count = COUNT(objects_kitchen),
		.exit = ROOM_EXIT_RIGHT,
	},
	{
		.name = "Living Room",
		.objects = objects_living,
		.objects_count = COUNT(objects_living),
		.exit = ROOM_EXIT_LEFT,
	},
};

const size_t room_count = sizeof(rooms) / sizeof(rooms[0]);

void game_room_defs_init (void) {
	char temptext[64];
	char canonical[16];
	for (size_t i=0; i<room_count; i++) {

		// Do things for each room
		make_canonical(canonical, rooms[i].name);
		sprintf(temptext, "rom:/images/bg/wall_%s.ci4.sprite", canonical);
		rooms[i].wall_sprite = sprite_load(temptext);
		sprintf(temptext, "rom:/images/bg/floor_%s.ci4.sprite", canonical);
		rooms[i].floor_sprite = sprite_load(temptext);

		// Do things for each object
		for (size_t j=0; j<rooms[i].objects_count; j++) {
			make_canonical(canonical, rooms[i].objects[j].name);
			// Load sprites
			sprintf(temptext, "rom:/images/obj/%s.ci4.sprite", canonical);
			rooms[i].objects[j].sprite = sprite_load(temptext);
			// Reset objects to base values
			rooms[i].objects[j].time_left = 0.0f;
			rooms[i].objects[j].active_task = NULL;
			rooms[i].objects[j].parent = &rooms[i];
			rooms[i].objects[j].highlight_size = (coord_t){
				.x = rooms[i].objects[j].sprite->width - (rooms[i].objects[j].size.x * OBJECT_SPRITE_COUNT),
				.y = rooms[i].objects[j].sprite->height,
			};
		}
	}
}
void game_rooms_defs_close (void) {
	for (size_t i=0; i<room_count; i++) {
		sprite_free(rooms[i].wall_sprite);
		sprite_free(rooms[i].floor_sprite);
		for (size_t j=0; j<rooms[i].objects_count; j++) {
			sprite_free(rooms[i].objects[j].sprite);
		}
	}
}
