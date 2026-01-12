#ifndef GAMEJAM2025_GAME_STATE_H
#define GAMEJAM2025_GAME_STATE_H

#include <libdragon.h>
#include "game_rooms_defs.h"

typedef enum {
	STATE_GAME_BEGIN,
	STATE_GAME_PLAYING,
	STATE_GAME_PAUSE,
	STATE_GAME_GAME_OVER,
} game_state_id_t;

void game_state_init (void);
void game_state_move (float dt);
void game_state_draw (void);
void game_state_close (void);

extern game_state_id_t game_state;
extern game_object_t* failed_task_object;

#endif
