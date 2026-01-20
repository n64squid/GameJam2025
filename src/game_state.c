// game_state.c
#include "game_state.h"
#include "main.h"
#include "state.h"

#define GAME_STATE_BEGIN_LENGTH 10
#define GAME_STATE_GAME_OVER_LENGTH 180

game_state_id_t game_state;
uint16_t game_state_timer;
game_object_t* failed_task_object;

void game_state_init (void) {
	game_state_timer = 0;
	game_state = STATE_GAME_BEGIN;
}

void game_state_move(float dt) {
	switch (game_state) {
	case STATE_GAME_BEGIN:
		game_state_timer++;
		if (game_state_timer >= GAME_STATE_BEGIN_LENGTH) {
			game_state = STATE_GAME_PLAYING;
			game_state_timer = 0;
		}
		break;

	case STATE_GAME_PLAYING:
		if (BTN_DOWN(start)) {
			game_state = STATE_GAME_PAUSE;
		}
		break;

	case STATE_GAME_PAUSE:
		if (BTN_DOWN(start)) {
			game_state = STATE_GAME_PLAYING;
		}
		break;

	case STATE_GAME_GAME_OVER:
		game_state_timer++;
		if (game_state_timer >= GAME_STATE_GAME_OVER_LENGTH) {
			state_switch(STATE_MENU);
			game_state_timer = 0;
		}
		break;
	}
}

void game_state_draw (void) {
	rdpq_textparms_t params = {
		.width = DISPLAY_WIDTH,
		.height = DISPLAY_HEIGHT,
		.align  = ALIGN_CENTER,
		.valign  = VALIGN_CENTER,
	};

	if (game_state == STATE_GAME_PAUSE) {
		rdpq_text_printf(
			&params, 1, 0, 0,
			"PAUSE"
		);
	}
	if (game_state == STATE_GAME_GAME_OVER) {
		rdpq_text_printf(
			&params, 1, 0, 0,
			"GAME OVER\nFailed task:\n%s\n%s",
			failed_task_object->name,
			failed_task_object->active_task->name
		);
	}
	if (game_state == STATE_GAME_BEGIN) {
		rdpq_text_printf(
			&params, 1, 0, 0,
			"Get ready!\n%i",
			(GAME_STATE_BEGIN_LENGTH - game_state_timer) / 60 + 1
		);
	}
}

void game_state_close (void) {
}
