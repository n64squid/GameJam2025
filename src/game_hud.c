#include "main.h"
#include "game_hud.h"
#include "game_main.h"
#include "game_robot.h"

#define GAME_DISPLAY_PADDING 8
#define GAME_HUD_WIDTH (DISPLAY_WIDTH - GAME_DISPLAY_PADDING*2)
#define GAME_HUD_HEIGHT 48
#define GAME_HUD_X (GAME_DISPLAY_PADDING)
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
#define GAME_HUD_ITEM_WIDTH_3 96

#define GAME_HUD_ROBOT_PARTS_X (GAME_DISPLAY_PADDING + GAME_HUD_PADDING_HUGE)
#define GAME_HUD_ROBOT_PARTS_Y (GAME_HUD_Y + GAME_HUD_PADDING_MID)
#define GAME_HUD_ROBOT_PARTS_WIDTH (GAME_HUD_ITEM_WIDTH_1)
#define GAME_HUD_ROBOT_PARTS_HEIGHT (GAME_HUD_ITEM_HEIGHT_1)

#define GAME_HUD_ROBOT_PARTS_HP_X (GAME_HUD_ROBOT_PARTS_X + GAME_HUD_ROBOT_PARTS_WIDTH + GAME_HUD_PADDING_MID)
#define GAME_HUD_ROBOT_PARTS_HP_Y (GAME_HUD_ROBOT_PARTS_Y)
#define GAME_HUD_ROBOT_PARTS_HP_WIDTH (GAME_HUD_ITEM_WIDTH_2)
#define GAME_HUD_ROBOT_PARTS_HP_HEIGHT (GAME_HUD_ITEM_HEIGHT_1)

#define GAME_HUD_MONEY_X (GAME_HUD_ROBOT_PARTS_HP_X + GAME_HUD_ROBOT_PARTS_HP_WIDTH + GAME_HUD_PADDING_BIG)
#define GAME_HUD_MONEY_Y (GAME_HUD_ROBOT_PARTS_HP_Y)
#define GAME_HUD_MONEY_WIDTH (GAME_HUD_ITEM_WIDTH_3)
#define GAME_HUD_MONEY_HEIGHT (GAME_HUD_ITEM_HEIGHT_1)

#define GAME_HUD_METER_X (GAME_HUD_MONEY_X)
#define GAME_HUD_METER_Y (GAME_HUD_MONEY_Y + GAME_HUD_MONEY_HEIGHT + GAME_HUD_PADDING_SML)
#define GAME_HUD_METER_WIDTH (GAME_HUD_MONEY_WIDTH)
#define GAME_HUD_METER_HEIGHT (GAME_HUD_ITEM_HEIGHT_2)

#define GAME_HUD_TOOLS_X (GAME_HUD_MONEY_X + GAME_HUD_MONEY_WIDTH + GAME_HUD_PADDING_BIG)
#define GAME_HUD_TOOLS_Y (GAME_HUD_MONEY_Y)
#define GAME_HUD_TOOLS_WIDTH (GAME_HUD_ITEM_WIDTH_2)
#define GAME_HUD_TOOLS_HEIGHT (GAME_HUD_ITEM_HEIGHT_3)

#define GAME_HUD_AVATAR_X (GAME_HUD_TOOLS_X + GAME_HUD_TOOLS_WIDTH + GAME_HUD_PADDING_MID)
#define GAME_HUD_AVATAR_Y (GAME_HUD_TOOLS_Y)
#define GAME_HUD_AVATAR_WIDTH (GAME_HUD_ITEM_WIDTH_1)
#define GAME_HUD_AVATAR_HEIGHT (GAME_HUD_ITEM_HEIGHT_3)

#define GAME_COLOR_FRAME RGBA32(0x88, 0x88, 0x88, 0)
#define GAME_COLOR_HUD RGBA32(0xEE, 0xEE, 0xEE, 0)
#define GAME_COLOR_UI RGBA32(0x44, 0x44, 0x44, 0)

typedef enum {
	SPRITE_BG,
	SPRITE_BUILD,
	SPRITE_CASH,
	SPRITE_DOT,
	SPRITE_GAUGE,
	SPRITE_TOOL,
	SPRITE_UPGRADE_0,
	SPRITE_UPGRADE_1,
	SPRITE_COUNT,
} state_id_t;

static sprite_t* sprites[SPRITE_COUNT];

void game_hud_init (void) {
	sprites[SPRITE_BG] = sprite_load("rom:/images/hud/bg.ci4.sprite");
	sprites[SPRITE_BUILD] = sprite_load("rom:/images/hud/build.ci4.sprite");
	sprites[SPRITE_CASH] = sprite_load("rom:/images/hud/cash.ci4.sprite");
	sprites[SPRITE_DOT] = sprite_load("rom:/images/hud/dot.ci4.sprite");
	sprites[SPRITE_GAUGE] = sprite_load("rom:/images/hud/gauge.ci4.sprite");
	sprites[SPRITE_TOOL] = sprite_load("rom:/images/hud/tool.ci4.sprite");
	sprites[SPRITE_UPGRADE_0] = sprite_load("rom:/images/hud/upgrade_0.ci4.sprite");
	sprites[SPRITE_UPGRADE_1] = sprite_load("rom:/images/hud/upgrade_1.ci4.sprite");
}

void game_hud_move (float dt) {
}

void game_hud_draw (void) {
	rdpq_set_mode_copy(true);
	// Draw the HUD BG
	rdpq_sprite_blit (
		sprites[SPRITE_BG],
		GAME_HUD_X,
		GAME_HUD_Y,
		NULL
	);

	// Draw the part health
	for (uint8_t i=0; i<GAME_ROBOT_PARTS_COUNT; i++) {
		rdpq_sprite_blit (
			sprites[SPRITE_UPGRADE_0],
			GAME_HUD_ROBOT_PARTS_X,
			GAME_HUD_ROBOT_PARTS_Y + i * (GAME_HUD_ROBOT_PARTS_HEIGHT + GAME_HUD_PADDING_SML),
			NULL
		);
		rdpq_sprite_blit (
			sprites[SPRITE_UPGRADE_1],
			GAME_HUD_ROBOT_PARTS_HP_X,
			GAME_HUD_ROBOT_PARTS_HP_Y + i * (GAME_HUD_ROBOT_PARTS_HP_HEIGHT + GAME_HUD_PADDING_SML),
			NULL
		);
	}
	// Draw the cash and gauge
	rdpq_sprite_blit (
		sprites[SPRITE_CASH],
		GAME_HUD_MONEY_X,
		GAME_HUD_MONEY_Y,
		NULL
	);
	rdpq_sprite_blit (
		sprites[SPRITE_GAUGE],
		GAME_HUD_METER_X,
		GAME_HUD_METER_Y,
		NULL
	);

	// Draw the toolbox
	rdpq_sprite_blit (
		sprites[SPRITE_TOOL],
		GAME_HUD_TOOLS_X,
		GAME_HUD_TOOLS_Y,
		NULL
	);

	// Draw the avatar
	rdpq_sprite_blit (
		sprites[SPRITE_BUILD],
		GAME_HUD_AVATAR_X,
		GAME_HUD_AVATAR_Y,
		NULL
	);
	return;
}

void game_hud_close (void) {
	for (uint8_t i=0; i<GAME_ROBOT_PARTS_COUNT; i++) {
		sprite_free(sprites[i]);
	}
}
