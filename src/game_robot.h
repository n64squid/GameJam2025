// Game_Robot.h

#ifndef GAMEJAM2025_GAME_ROBOT_H
#define GAMEJAM2025_GAME_ROBOT_H

#include <libdragon.h>

void game_robot_init (void);
void game_robot_move (float dt);
void game_robot_draw (void);
void game_robot_close (void);

typedef struct game_robot_part_s {
	char* name;
	uint8_t health;
} game_robot_part_t;

extern game_robot_part_t robot_parts[];
extern const uint8_t GAME_ROBOT_PARTS_COUNT;

#endif
