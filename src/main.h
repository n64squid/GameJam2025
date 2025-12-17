// Main.h

#ifndef GAMEJAM2025_MAIN_H
#define GAMEJAM2025_MAIN_H

#include <libdragon.h>

#define DISPLAY_WIDTH 360
#define DISPLAY_HEIGHT 240

typedef struct vertex_s {
	float x, y, z;
} vertex_t;

// Inline lerp function to help with the animation functions
static inline float lerp(float current, float target, float speed) {
	return current * (1.0f - speed) + target * speed;
}

extern joypad_inputs_t buttons;

#endif
