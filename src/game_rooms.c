#include "game_rooms.h"
#include "game_rooms_defs.h"
#include "game_main.h"
#include "main.h"

#define FLOOR_COUNT 2
#define ROOMS_PER_FLOOR 2
#define ARROW_MARGIN 4

typedef struct game_cursor_s {
	uint8_t selected;
	uint8_t room;
	sprite_t* sprite;
} game_cursor_t;


game_cursor_t cursor;

void game_rooms_init (void) {
	cursor = (game_cursor_t){
		.room = 0,
		.selected = 0,
		.sprite = sprite_load("rom:/images/icons/cursor.ci4.sprite"),
	};
	char temptext[64];
	// Load bg sprites
	for (size_t i=0; i<room_count; i++) {
		sprintf(temptext, "rom:/images/bg/wall-%s.ci4.sprite", rooms[i].canonical);
		rooms[i].wall_sprite = sprite_load(temptext);
		sprintf(temptext, "rom:/images/bg/floor-%s.ci4.sprite", rooms[i].canonical);
		rooms[i].floor_sprite = sprite_load(temptext);
		// Load the objects
		for (size_t j=0; j<rooms[i].objects_count; j++) {
			sprintf(temptext, "rom:/images/obj/%s.ci4.sprite", rooms[i].objects[j].canonical);
			rooms[i].objects[j].sprite = sprite_load(temptext);
		}
	}
}

void game_rooms_move (float dt) {
	static bool is_down = false;
	// Button control
	if (!is_down) {
		// Traverse the objects
		if (buttons.btn.d_right) {
			cursor.selected = (cursor.selected + 1) % rooms[cursor.room].objects_count;
			is_down = true;
		}
		if (buttons.btn.d_left) {
			cursor.selected = (cursor.selected + (rooms[cursor.room].objects_count-1)) % rooms[cursor.room].objects_count;
			is_down = true;
		}
		// Traverse the rooms
		if (buttons.btn.c_right) {
			cursor.room = (cursor.room + 1) % ROOMS_PER_FLOOR;
			cursor.selected = 0;
			is_down = true;
		}
		if (buttons.btn.c_left) {
			cursor.room = (cursor.room + ROOMS_PER_FLOOR - 1) % ROOMS_PER_FLOOR;
			cursor.selected = 0;
			is_down = true;
		}
		if (buttons.btn.c_up) {
			cursor.room = (cursor.room + ROOMS_PER_FLOOR) % (ROOMS_PER_FLOOR + FLOOR_COUNT);
			cursor.selected = 0;
			is_down = true;
		}
		if (buttons.btn.c_down) {
			cursor.room = (cursor.room + (ROOMS_PER_FLOOR + FLOOR_COUNT) - ROOMS_PER_FLOOR) % (ROOMS_PER_FLOOR + FLOOR_COUNT);
			cursor.selected = 0;
			is_down = true;
		}

	} else {
		// Disengage the button hold
		if (!buttons.btn.raw) {
			is_down = false;
		}
	}
}

void game_rooms_draw (void) {

	// Draw teh background
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
		assertf(rooms[cursor.room].objects[i].sprite, "Sprite not found: %s", rooms[cursor.room].objects[i].name);
		rdpq_sprite_blit (
			rooms[cursor.room].objects[i].sprite,
			rooms[cursor.room].objects[i].pos.x,
			rooms[cursor.room].objects[i].pos.y,
			NULL
		);
	}

	// Draw the arrow
	rdpq_sprite_blit (
		cursor.sprite,
		rooms[cursor.room].objects[cursor.selected].pos.x + rooms[cursor.room].objects[cursor.selected].sprite->width/2 - cursor.sprite->width/2,
		rooms[cursor.room].objects[cursor.selected].pos.y - cursor.sprite->height - ARROW_MARGIN,
		NULL
	);

	rdpq_text_printf(NULL, 1, 20, 20,
		"Current room: %s\nSelected: %s",
		rooms[cursor.room].name,
		rooms[cursor.room].objects[cursor.selected].name
	);
}

void game_rooms_close (void) {

	for (size_t i=0; i<room_count; i++) {
		sprite_free(rooms[i].wall_sprite);
		sprite_free(rooms[i].floor_sprite);
	}
	sprite_free(cursor.sprite);
}
