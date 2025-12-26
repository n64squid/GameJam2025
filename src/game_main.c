#include "game_main.h"
#include "game_hud.h"
#include "game_rooms.h"
#include "state.h"
#include "main.h"

void game_init (void) {
	game_hud_init();
	game_rooms_init();
}

void game_move (float dt) {
	game_rooms_move(dt);
}

void game_draw (void) {
	// Clear the frame buffer
	rdpq_set_mode_fill(GAME_COLOR_FRAME);
	rdpq_fill_rectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);

	game_hud_draw();
	game_rooms_draw();

}

void game_close (void) {
	game_hud_close();
}
