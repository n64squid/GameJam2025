#include <libdragon.h>
#include "main.h"
#include "intro.h"

#define FPS_SAMPLES 20
#define FPS_TARGET 60.0

heap_stats_t heap_stats;

float update_fps (void) {
	static float samples[FPS_SAMPLES] = {1.0};
	static uint8_t i = 0;
	float total = 0;

	samples[i++] = display_get_delta_time();
	i %= FPS_SAMPLES;

	for (uint8_t j=0; j<FPS_SAMPLES;j++) {
		total += samples[j];
	}

	return 1.0f / (total / FPS_SAMPLES);
}

int main(void)
{
	// Initialise the various systems
	display_init(RESOLUTION_320x240, DEPTH_32_BPP, 3, GAMMA_NONE, FILTERS_RESAMPLE);
	dfs_init(DFS_DEFAULT_LOCATION);
	audio_init(32000, 3);
	mixer_init(32);
	rdpq_init();
	joypad_init();

	// Init own own functionality
	intro_init();

	// Register the default font
	rdpq_font_t *fnt1 = rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_MONO);
	rdpq_text_register_font(1, fnt1);

	// Main loop
	while(1) {
		// Start a new frame
		sys_get_heap_stats(&heap_stats);

		// Get the frame buffer
		surface_t* disp;
		surface_t* zbuf = display_get_zbuf();
		while(!(disp = display_try_get()));

		// Attach the buffer to the RDP
		rdpq_attach(disp, zbuf);

		intro_move();
		intro_draw();

		rdpq_text_printf(NULL, 1, 20, 20,
			"FPS: %.0f\nRAM: %i KB",
			update_fps(),
			heap_stats.used / 1024
		);

		// Send frame buffer to display (TV)
		rdpq_detach_show();
	}
}
