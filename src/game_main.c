#include "game_main.h"
#include "game_hud.h"
#include "game_rooms.h"
#include "game_tools.h"
#include "game_tasks.h"
#include "game_state.h"
#include "game_robot.h"
#include "state.h"
#include "main.h"

void game_init (void) {
	game_state_init();
	game_hud_init();
	game_rooms_init();
	game_tools_init();
	game_tasks_init();
	game_robot_init();
}

void game_move (float dt) {
	if (game_state == STATE_GAME_PLAYING) {
		game_rooms_move(dt);
		game_tasks_move(dt);
		game_robot_move(dt);
	}
	game_state_move(dt);
}

void game_draw (void) {
	// Clear the frame buffer
	rdpq_set_mode_fill(GAME_COLOR_FRAME);
	rdpq_fill_rectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);

	// Draw each section of the screen
	game_hud_draw();
	game_rooms_draw();
	game_robot_draw();
	game_tasks_draw();
	game_state_draw();
}

void game_close (void) {
	game_hud_close();
	game_rooms_close();
	game_tools_close();
	game_tasks_close();
	game_robot_close();
	game_state_close();
}
