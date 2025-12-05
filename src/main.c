#include "main.h"
#include <libdragon.h>

int main(void)
{
	// Initialise the various systems
	display_init(RESOLUTION_320x240, DEPTH_32_BPP, 3, GAMMA_NONE, FILTERS_RESAMPLE);
	dfs_init(DFS_DEFAULT_LOCATION);
	rdpq_init();
	joypad_init();

	// Register the default font
	rdpq_font_t *fnt1 = rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_MONO);
	rdpq_text_register_font(1, fnt1);

	// Main loop
	while(1) {
		// Start a new frame
		// Get the frame buffer
		surface_t* disp;
		surface_t* zbuf = display_get_zbuf();
		while(!(disp = display_try_get()));

		// Attach the buffer to the RDP
		rdpq_attach(disp, zbuf);
		rdpq_text_printf(NULL, 1, 20, 20,
			"Hello world!"
		);

		// Send frame buffer to display (TV)
		rdpq_detach_show();
	}
}
