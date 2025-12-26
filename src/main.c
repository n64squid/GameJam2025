#include "main.h"
#include "state.h"

#define FPS_SAMPLES 20
#define FPS_TARGET 60.0

heap_stats_t heap_stats;
joypad_inputs_t buttons = {0};

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
	display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, FILTERS_RESAMPLE);
	dfs_init(DFS_DEFAULT_LOCATION);
	audio_init(32000, 3);
	mixer_init(32);
	rdpq_init();
	joypad_init();

	// Init own own functionality
	states[current_state].init_func();

	// Main variables
	float fps;

	// Register the default font
	rdpq_font_t *fnt1 = rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_MONO);
	rdpq_text_register_font(1, fnt1);

	// Main loop
	while(1) {
		// Start a new frame
		sys_get_heap_stats(&heap_stats);
		joypad_poll();
		buttons = joypad_get_inputs(JOYPAD_PORT_1);
		fps = update_fps();

		// Get the frame buffer
		surface_t* disp;
		surface_t* zbuf = display_get_zbuf();
		while(!(disp = display_try_get()));

		// Attach the buffer to the RDP
		rdpq_attach(disp, zbuf);

		// Run the state functions
		states[current_state].move_func(1.0f / fps);
		states[current_state].draw_func();

		// Some debug stuff
		rdpq_text_printf(NULL, 1, 240, 20,
			"FPS: %.0f\nRAM: %i KB\n%i\n%i,%i",
			fps,
			heap_stats.used / 1024,
			buttons.btn.raw,
			buttons.stick_x, buttons.stick_y
		);

		// Send frame buffer to display (TV)
		rdpq_detach_show();
	}
}
