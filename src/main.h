// Main.h

#ifndef GAMEJAM2025_MAIN_H
#define GAMEJAM2025_MAIN_H

#include <libdragon.h>

#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 240

#define GAME_DISPLAY_PADDING 8

#define COUNT(room) (sizeof(room) / sizeof(room[0]))

#define BTN_DOWN(butt) (buttons.cur.btn.butt & ~buttons.prev.btn.butt)

typedef struct vertex_s {
	float x, y, z;
} vertex_t;

typedef struct coord_s {
	float x, y;
} coord_t;

// Inline lerp function to help with the animation functions
static inline float lerp(float current, float target, float speed) {
	return current * (1.0f - speed) + target * speed;
}
void make_canonical(char *dst, const char *src);

typedef struct {
	joypad_inputs_t cur;
	joypad_inputs_t prev;
} buttons_t;

extern buttons_t buttons;

#endif
