#include "menu.h"

void menu_init (void) {

}

void menu_move (float dt) {

}

void menu_draw (void) {
	// Clear the frame buffer
	rdpq_set_mode_fill(RGBA32(0x26, 0x3B, 0x52, 0));
	rdpq_fill_rectangle(0, 0, display_get_width(), display_get_height());
	rdpq_text_printf(NULL, 1, 20, 20,
		"This is the menu"
	);
}

void menu_close (void) {

}
