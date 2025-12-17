#include "menu.h"
#include "state.h"
#include "main.h"

#define MENU_ITEM_HEIGHT 20
#define MENU_ITEM_PADDING 20
#define MENU_ITEM_COUNT(x) (sizeof(x)/sizeof(x[0]))

#define MENU_STAR_COUNT 250
#define MENU_STAR_DISTANCE_MAX 10
#define MENU_STAR_DISTANCE_STEP 0.5f
#define MENU_STAR_SIZE 2
#define MENU_STAR_SPEED_MIN 1.0f
#define MENU_STAR_SPEED_BOOST 1.75f
#define MENU_STAR_SPEED_DECAY (1.5f / 64)
#define MENU_STAR_SPEED_JOYSTICK (1.0f / 512.0f)

typedef enum {
	MENU_STAR_DIR_X,
	MENU_STAR_DIR_Y,
} menu_star_dir_t;

typedef struct menu_item_s {
	char* name;
	void (*action)(void* ctx);
	void* arg;
} menu_item_t;

typedef struct menu_s {
	const char *title;
	char* desc;
	const menu_item_t *items;
	size_t item_count;
	void (*back)(void* ctx);
	void* arg;
	uint8_t selected;
} menu_t;

typedef struct menu_star_s {
	vertex_t pos;
	vertex_t spd;
	float theta;
	uint32_t color;
} menu_star_t;

typedef enum {
	MENU_MAIN,
	MENU_OPTIONS,
	MENU_CREDITS,
	MENU_COUNT
} menu_id_t;

void menu_action_none (void* ctx);
void menu_action_change_menu (void* ctx);

// Individual menu items
const menu_item_t menu_main[] = {
	{"Play", menu_action_none, NULL},
	{"Tutorial", menu_action_none, NULL},
	{"Options", menu_action_change_menu, (void*)MENU_OPTIONS},
	{"Credits", menu_action_change_menu, (void*)MENU_CREDITS},
};

const menu_item_t menu_options[] = {
	{"Opt1", menu_action_none, NULL},
	{"Opt2", menu_action_none, NULL},
	{"Opt3", menu_action_none, NULL},
	{"Opt4", menu_action_none, NULL},
};

const menu_item_t menu_credits[] = {
	{"Back", menu_action_change_menu, (void*)MENU_MAIN},
};

// Menu main struct
static menu_t menu[MENU_COUNT] = {
	[MENU_MAIN] = {
		"Robo Renovations",
		"",
		menu_main,
		MENU_ITEM_COUNT(menu_main),
		menu_action_none, NULL,
		0,
	},
	[MENU_OPTIONS] = {
		"Options",
		"Change settings here",
		menu_options,
		MENU_ITEM_COUNT(menu_options),
		menu_action_change_menu, (void*)MENU_MAIN,
		0,
	},
	[MENU_CREDITS] = {
		"Credits",
		"Robo Renovations was made by\nCatch 64",
		menu_credits,
		MENU_ITEM_COUNT(menu_credits),
		menu_action_change_menu, (void*)MENU_MAIN,
		0,
	}
};

// Global vars
static uint8_t current_menu;
static menu_star_t stars[MENU_STAR_COUNT];

// These callback functions determine what the buttons in the menu do
void menu_action_none (void* ctx) {
	return;
}

void menu_action_change_menu (void* ctx) {
	current_menu = (uint32_t)ctx;
}

void menu_action_change_state (void* ctx) {
	state_switch ((uint32_t)ctx);
}

void menu_init (void) {
	for (uint8_t i=0; i<MENU_STAR_COUNT; i++) {
		stars[i].pos.x = rand() % DISPLAY_WIDTH;
		stars[i].pos.y = rand() % DISPLAY_HEIGHT;
		stars[i].pos.z = (rand() % (uint8_t)(MENU_STAR_DISTANCE_MAX/MENU_STAR_DISTANCE_STEP)) * MENU_STAR_DISTANCE_STEP;
		stars[i].theta = ((float)rand() / (float)RAND_MAX) * (2.0 * M_PI);
		stars[i].spd.x = cos(stars[i].theta) * MENU_STAR_SPEED_MIN;
		stars[i].spd.y = sin(stars[i].theta) * MENU_STAR_SPEED_MIN;
	}
	current_menu = 0;
}

static inline void star_boost (menu_star_dir_t direction, float value) {
	for (uint8_t i=0; i<MENU_STAR_COUNT; i++) {
		(&stars[i].spd.x)[direction] += value;
	}
}

void menu_move (float dt) {
	float modifier;
	static bool is_down = false;
	for (uint8_t i=0; i<MENU_STAR_COUNT; i++) {
		// Move it
		modifier = ((MENU_STAR_DISTANCE_MAX - stars[i].pos.z + MENU_STAR_DISTANCE_STEP) / MENU_STAR_DISTANCE_MAX);
		stars[i].pos.x += stars[i].spd.x * modifier;
		stars[i].pos.y -= stars[i].spd.y * modifier;

		// Loop it back
		if (stars[i].pos.x < -MENU_STAR_SIZE) {
			stars[i].pos.x = DISPLAY_WIDTH;
		}
		if (stars[i].pos.y < -MENU_STAR_SIZE) {
			stars[i].pos.y = DISPLAY_HEIGHT;
		}
		if (stars[i].pos.x > DISPLAY_WIDTH) {
			stars[i].pos.x = -MENU_STAR_SIZE;
		}
		if (stars[i].pos.y > DISPLAY_HEIGHT) {
			stars[i].pos.y = -MENU_STAR_SIZE;
		}

		// Normalise them
		stars[i].spd.x = lerp(stars[i].spd.x, cos(stars[i].theta) * MENU_STAR_SPEED_MIN, MENU_STAR_SPEED_DECAY);
		stars[i].spd.y = lerp(stars[i].spd.y, sin(stars[i].theta) * MENU_STAR_SPEED_MIN, MENU_STAR_SPEED_DECAY);
	}

	// Move the stars around
	if (buttons.stick_x) {
		star_boost(MENU_STAR_DIR_X, buttons.stick_x * MENU_STAR_SPEED_JOYSTICK);
	}
	if (buttons.stick_y) {
		star_boost(MENU_STAR_DIR_Y, buttons.stick_y * MENU_STAR_SPEED_JOYSTICK);
	}

	// Button control
	if (!is_down) {
		// Traverse the menu
		if (buttons.btn.d_down) {
			menu[current_menu].selected++;
			star_boost(MENU_STAR_DIR_Y, -MENU_STAR_SPEED_BOOST);
			is_down = true;
			if (menu[current_menu].selected == menu[current_menu].item_count) {
				menu[current_menu].selected = 0;
			}
		}
		if (buttons.btn.d_up) {
			menu[current_menu].selected--;
			star_boost(MENU_STAR_DIR_Y, MENU_STAR_SPEED_BOOST);
			is_down = true;
			if (menu[current_menu].selected == UINT8_MAX) {
				menu[current_menu].selected = menu[current_menu].item_count-1;
			}
		}

		// Activate menu item
		if (buttons.btn.a) {
			menu[current_menu]
				.items[menu[current_menu].selected]
				.action(menu[current_menu].items[menu[current_menu].selected].arg);
			is_down = true;
		}

		// Return to previous menu
		if (buttons.btn.b) {
			menu[current_menu].back(menu[current_menu].arg);
			is_down = true;
		}
	} else {
		// Disengage the button hold
		if (!buttons.btn.raw) {
			is_down = false;
		}
	}
}

void menu_draw (void) {
	uint32_t color;
	rdpq_textmetrics_t text_metrics = {0};

	// Clear the frame buffer
	rdpq_set_mode_fill(RGBA32(0x01, 0x01, 0x01, 0));
	rdpq_fill_rectangle(0, 0, display_get_width(), display_get_height());

	// Draw the stars
	for (uint8_t i=0; i<MENU_STAR_COUNT; i++) {
		color = (uint8_t)(0xff * stars[i].pos.z);
		rdpq_set_mode_fill(RGBA32(color, color, color, 0));
		rdpq_fill_rectangle(
			stars[i].pos.x,
			stars[i].pos.y,
			stars[i].pos.x + MENU_STAR_SIZE,
			stars[i].pos.y + MENU_STAR_SIZE
		);
	}

	// Print the title
	rdpq_text_printf(
		&(rdpq_textparms_t){
			.width = 320,
			.height = 20,
			.align  = ALIGN_CENTER,
			.valign  = VALIGN_TOP,
		}, 1, 0, MENU_ITEM_PADDING,
		menu[current_menu].title
	);

	// Print the description
	if (strlen(menu[current_menu].desc)) {
		text_metrics = rdpq_text_printf(
			&(rdpq_textparms_t){
				.width = 320,
				.height = DISPLAY_HEIGHT - (MENU_ITEM_PADDING + MENU_ITEM_HEIGHT),
				.align  = ALIGN_CENTER,
				.valign  = VALIGN_TOP,
			}, 1, 0, MENU_ITEM_PADDING + MENU_ITEM_HEIGHT,
			menu[current_menu].desc
		);
	}

	// Print the menu items
	for (uint8_t i=0; i<menu[current_menu].item_count; i++) {
		uint8_t gap_height =
			(
			DISPLAY_HEIGHT
			- (MENU_ITEM_PADDING*2 + MENU_ITEM_HEIGHT + (uint8_t)text_metrics.advance_y)
			- (menu[current_menu].item_count*MENU_ITEM_HEIGHT)
			)
			/ (menu[current_menu].item_count > 1 ? menu[current_menu].item_count-1 : 1);

		rdpq_text_printf(
			&(rdpq_textparms_t){
				.width = 320,
				.height = 20,
				.align  = ALIGN_CENTER,
				.valign  = VALIGN_TOP,
			}, 1, 0, MENU_ITEM_PADDING*2 + MENU_ITEM_HEIGHT + (uint8_t)text_metrics.advance_y + (MENU_ITEM_HEIGHT + gap_height)*i,
			"%c %s %c",
			i == menu[current_menu].selected ? '>' : ' ',
			menu[current_menu].items[i].name,
			i == menu[current_menu].selected ? '<' : ' '
		);
	}
}

void menu_close (void) {
	// Nothing in particular
}
