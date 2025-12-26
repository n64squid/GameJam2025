// Game_Main.h

#ifndef GAMEJAM2025_GAME_H
#define GAMEJAM2025_GAME_H

#include <libdragon.h>

#define GAME_DISPLAY_PADDING 8
#define WALL_HEIGHT 144
#define FLOOR_HEIGHT 32

#define GAME_COLOR_FRAME RGBA32(0x88, 0x88, 0x88, 0)
#define GAME_COLOR_HUD RGBA32(0xEE, 0xEE, 0xEE, 0)
#define GAME_COLOR_UI RGBA32(0x44, 0x44, 0x44, 0)

void game_init (void);
void game_move (float dt);
void game_draw (void);
void game_close (void);

#endif
