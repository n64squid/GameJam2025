#include "game_robot.h"

game_robot_part_t robot_parts[3] = {
	{"HEAD" , 3},
	{"ARMS" , 3},
	{"LEGS" , 3},
};

const uint8_t GAME_ROBOT_PARTS_COUNT = sizeof(robot_parts) / sizeof(robot_parts[0]);

void game_robot_init (void) {
}

void game_robot_move (float dt) {
}

void game_robot_draw (void) {
}

void game_robot_close (void) {
}
