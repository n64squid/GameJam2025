#include "main.h"
#include "game_hud.h"
#include "game_main.h"
#include "game_tools.h"
#include "game_robot.h"

#define GAME_HUD_WIDTH (DISPLAY_WIDTH - GAME_DISPLAY_PADDING*2)
#define GAME_HUD_HEIGHT 48
#define GAME_HUD_X 0
#define GAME_HUD_Y (DISPLAY_HEIGHT - GAME_DISPLAY_PADDING - GAME_HUD_HEIGHT)

#define GAME_HUD_PADDING_HUGE 16
#define GAME_HUD_PADDING_BIG 8
#define GAME_HUD_PADDING_MID 4
#define GAME_HUD_PADDING_SML 2

#define GAME_HUD_ITEM_HEIGHT_1 12
#define GAME_HUD_ITEM_HEIGHT_2 (GAME_HUD_ITEM_HEIGHT_1*2 + GAME_HUD_PADDING_SML*1)
#define GAME_HUD_ITEM_HEIGHT_3 (GAME_HUD_ITEM_HEIGHT_1*3 + GAME_HUD_PADDING_SML*2)

#define GAME_HUD_ITEM_WIDTH_1 32
#define GAME_HUD_ITEM_WIDTH_2 44
#define GAME_HUD_ITEM_WIDTH_3 92

#define GAME_HUD_ROBOT_PARTS_X (GAME_DISPLAY_PADDING + GAME_HUD_PADDING_HUGE)
#define GAME_HUD_ROBOT_PARTS_Y (GAME_HUD_Y + GAME_HUD_PADDING_MID)
#define GAME_HUD_ROBOT_PARTS_WIDTH (GAME_HUD_ITEM_WIDTH_1)
#define GAME_HUD_ROBOT_PARTS_HEIGHT (GAME_HUD_ITEM_HEIGHT_1)
#define GAME_HUD_ROBOT_PARTS_TEXT_X (GAME_HUD_ROBOT_PARTS_X + GAME_HUD_PADDING_MID)
#define GAME_HUD_ROBOT_PARTS_TEXT_Y (GAME_HUD_ROBOT_PARTS_Y + GAME_HUD_PADDING_BIG + 1)

#define GAME_HUD_ROBOT_PARTS_DOT_X (GAME_HUD_ROBOT_PARTS_X + GAME_HUD_ROBOT_PARTS_WIDTH + GAME_HUD_PADDING_MID)
#define GAME_HUD_ROBOT_PARTS_DOT_Y (GAME_HUD_ROBOT_PARTS_Y + GAME_HUD_PADDING_SML)
#define GAME_HUD_ROBOT_PARTS_DOT_PADDING_TOP (GAME_HUD_PADDING_SML)
#define GAME_HUD_ROBOT_PARTS_DOT_PADDING_LEFT (GAME_HUD_PADDING_BIG)
#define GAME_HUD_ROBOT_PARTS_DOT_PADDING_MID (GAME_HUD_PADDING_MID)
#define GAME_HUD_ROBOT_PARTS_DOT_WIDTH 8
#define GAME_HUD_ROBOT_PARTS_DOT_HEIGHT (GAME_HUD_ROBOT_PARTS_DOT_WIDTH)

#define GAME_HUD_MONEY_X (GAME_HUD_ROBOT_PARTS_X + GAME_HUD_ITEM_WIDTH_3)
#define GAME_HUD_MONEY_Y (GAME_HUD_ROBOT_PARTS_Y)
#define GAME_HUD_MONEY_WIDTH (GAME_HUD_ITEM_WIDTH_3)
#define GAME_HUD_MONEY_HEIGHT (GAME_HUD_ITEM_HEIGHT_1)

#define GAME_HUD_METER_X (GAME_HUD_MONEY_X)
#define GAME_HUD_METER_Y (GAME_HUD_MONEY_Y + GAME_HUD_MONEY_HEIGHT + GAME_HUD_PADDING_SML)
#define GAME_HUD_METER_WIDTH (GAME_HUD_MONEY_WIDTH)
#define GAME_HUD_METER_HEIGHT (GAME_HUD_ITEM_HEIGHT_2)

#define GAME_HUD_TOOLS_X (GAME_HUD_MONEY_X + GAME_HUD_MONEY_WIDTH + GAME_HUD_PADDING_MID)
#define GAME_HUD_TOOLS_Y (GAME_HUD_MONEY_Y)
#define GAME_HUD_TOOLS_WIDTH (GAME_HUD_ITEM_WIDTH_2)
#define GAME_HUD_TOOLS_HEIGHT (GAME_HUD_ITEM_HEIGHT_3)
#define GAME_HUD_TOOLS_SPRITE_OFFSET_X (GAME_HUD_PADDING_MID + GAME_HUD_PADDING_SML)
#define GAME_HUD_TOOLS_SPRITE_OFFSET_Y (GAME_HUD_ITEM_HEIGHT_1 + GAME_HUD_PADDING_MID + GAME_HUD_PADDING_SML)

#define GAME_HUD_AVATAR_X (GAME_HUD_TOOLS_X + GAME_HUD_TOOLS_WIDTH + GAME_HUD_PADDING_BIG)
#define GAME_HUD_AVATAR_Y (GAME_HUD_TOOLS_Y)
#define GAME_HUD_AVATAR_WIDTH (GAME_HUD_ITEM_WIDTH_1)
#define GAME_HUD_AVATAR_HEIGHT (GAME_HUD_ITEM_HEIGHT_3)
#define GAME_HUD_AVATAR_FUEL_WIDTH 16
#define GAME_HUD_AVATAR_FUEL_HEIGHT 34
#define GAME_HUD_AVATAR_FUEL_SPRITES 10

#define GAME_COLOR_FRAME RGBA32(0x88, 0x88, 0x88, 0)
#define GAME_COLOR_HUD RGBA32(0xEE, 0xEE, 0xEE, 0)
#define GAME_COLOR_UI RGBA32(0x44, 0x44, 0x44, 0)

typedef enum {
	SPRITE_BG_BOTTOM,
	SPRITE_BG_TOP,
	SPRITE_BG_LEFT,
	SPRITE_BG_RIGHT,
	SPRITE_UPGRADE,
	SPRITE_DOT,
	SPRITE_BUILD,
	SPRITE_CENTER,
	SPRITE_FUEL,
	SPRITE_TOOL,
	SPRITE_COUNT,
} sprite_id_t;

static sprite_t* sprites[SPRITE_COUNT];

void game_hud_init (void) {
	sprites[SPRITE_BG_BOTTOM] = sprite_load("rom:/images/hud/bg_bottom.ci4.sprite");
	sprites[SPRITE_BG_TOP] = sprite_load("rom:/images/hud/bg_top.ci4.sprite");
	sprites[SPRITE_BG_LEFT] = sprite_load("rom:/images/hud/bg_left.ci4.sprite");
	sprites[SPRITE_BG_RIGHT] = sprite_load("rom:/images/hud/bg_right.ci4.sprite");
	sprites[SPRITE_UPGRADE] = sprite_load("rom:/images/hud/upgrade.ci4.sprite");
	sprites[SPRITE_DOT] = sprite_load("rom:/images/hud/dot.ci16.sprite");
	sprites[SPRITE_BUILD] = sprite_load("rom:/images/hud/build.ci4.sprite");
	sprites[SPRITE_CENTER] = sprite_load("rom:/images/hud/center.ci4.sprite");
	sprites[SPRITE_FUEL] = sprite_load("rom:/images/hud/fuel.ci4.sprite");
	sprites[SPRITE_TOOL] = sprite_load("rom:/images/hud/tool.ci4.sprite");
}

void game_hud_move (float dt) {
}

void game_hud_draw (void) {
	rdpq_set_mode_copy(true);
	// Draw the HUD BG
	rdpq_sprite_blit (
		sprites[SPRITE_BG_TOP],
		GAME_DISPLAY_PADDING,
		0,
		NULL
	);
	rdpq_sprite_blit (
		sprites[SPRITE_BG_LEFT],
		0,
		0,
		NULL
	);
	rdpq_sprite_blit (
		sprites[SPRITE_BG_RIGHT],
		DISPLAY_WIDTH - GAME_DISPLAY_PADDING,
		0,
		NULL
	);
	rdpq_sprite_blit (
		sprites[SPRITE_BG_BOTTOM],
		GAME_HUD_X,
		GAME_HUD_Y,
		NULL
	);

	// Draw the part health
	for (uint8_t i=0; i<ROBOT_PARTS_COUNT; i++) {
		rdpq_sprite_blit (
			sprites[SPRITE_UPGRADE],
			GAME_HUD_ROBOT_PARTS_X,
			GAME_HUD_ROBOT_PARTS_Y + i * (GAME_HUD_ROBOT_PARTS_HEIGHT + GAME_HUD_PADDING_SML),
			NULL
		);
		rdpq_text_printf(NULL, 1,
			GAME_HUD_ROBOT_PARTS_TEXT_X,
			GAME_HUD_ROBOT_PARTS_TEXT_Y + i * (GAME_HUD_ROBOT_PARTS_HEIGHT + GAME_HUD_PADDING_SML),
			"%s",
			robot.parts[i].name
		);
		for (uint8_t j=0; j<ROBOT_PARTS_MAX_HEALTH; j++) {
			rdpq_sprite_blit (
				sprites[SPRITE_DOT],
				GAME_HUD_ROBOT_PARTS_DOT_X + GAME_HUD_ROBOT_PARTS_DOT_PADDING_LEFT
				+ j * (GAME_HUD_ROBOT_PARTS_DOT_PADDING_MID + GAME_HUD_ROBOT_PARTS_DOT_WIDTH),
				GAME_HUD_ROBOT_PARTS_DOT_Y + i * (GAME_HUD_ROBOT_PARTS_HEIGHT + GAME_HUD_ROBOT_PARTS_DOT_PADDING_TOP),
				&(rdpq_blitparms_t){
					.s0 = 0,
					.t0 = 0,
					.width = GAME_HUD_ROBOT_PARTS_DOT_WIDTH,
					.height = GAME_HUD_ROBOT_PARTS_DOT_HEIGHT,
				}
			);
		}
	}
	// Draw the cash and gauge
	rdpq_sprite_blit (
		sprites[SPRITE_CENTER],
		GAME_HUD_MONEY_X,
		GAME_HUD_MONEY_Y,
		NULL
	);

	// Draw the toolbox
	rdpq_sprite_blit (
		sprites[SPRITE_TOOL],
		GAME_HUD_TOOLS_X,
		GAME_HUD_TOOLS_Y,
		NULL
	);
	rdpq_sprite_blit (
		tools[current_tool].sprite,
		GAME_HUD_TOOLS_X + GAME_HUD_TOOLS_SPRITE_OFFSET_X,
		GAME_HUD_TOOLS_Y + GAME_HUD_TOOLS_SPRITE_OFFSET_Y,
		NULL
	);

	// Draw the fuel status
	rdpq_sprite_blit (
		sprites[SPRITE_BUILD],
		GAME_HUD_AVATAR_X,
		GAME_HUD_AVATAR_Y,
		&(rdpq_blitparms_t){
			.cx = 0,
			.cy = 0,
			.width = GAME_HUD_AVATAR_WIDTH,
			.height = GAME_HUD_AVATAR_HEIGHT,
		}
	);
	uint8_t fuel_sprite = ((robot.fuel * GAME_HUD_AVATAR_FUEL_SPRITES) / ROBOT_MAX_FUEL);
	rdpq_sprite_blit (
		sprites[SPRITE_FUEL],
		GAME_HUD_AVATAR_X + GAME_HUD_PADDING_BIG,
		GAME_HUD_AVATAR_Y + 3,
		&(rdpq_blitparms_t){
			.s0 = (fuel_sprite >= GAME_HUD_AVATAR_FUEL_SPRITES ? GAME_HUD_AVATAR_FUEL_SPRITES - 1 : fuel_sprite) * GAME_HUD_AVATAR_FUEL_WIDTH,
			.t0 = 0,
			.width = GAME_HUD_AVATAR_FUEL_WIDTH,
			.height = GAME_HUD_AVATAR_FUEL_HEIGHT,
		}
	);
	return;
}

void game_hud_close (void) {
	for (uint8_t i=0; i<ROBOT_PARTS_COUNT; i++) {
		sprite_free(sprites[i]);
	}
}
