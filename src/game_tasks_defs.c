#include "game_tasks_defs.h"
#include "main.h"

#define TASK_DURATION_SHORT 1.0f
#define TASK_DURATION_MID   1.5f
#define TASK_DURATION_LONG  2.5f

#define TASK_URGENCY_SHORT 15.0f
#define TASK_URGENCY_MID   20.0f
#define TASK_URGENCY_LONG  30.0f


//
// TODO: These are values based on the current difficulty being played.
//
static const task_data_def_t task_data_defs[TASK_DATA_COUNT] = {
	[TASK_DATA_EASY]   = { .min_time = 600, .create_chance = 600 },
	[TASK_DATA_MEDIUM] = { .min_time = 400, .create_chance = 500 },
	[TASK_DATA_HARD]   = { .min_time = 200, .create_chance = 400 },
};

task_data_state_t task_state = {
	.difficulty = TASK_DATA_EASY,
	.timer = 0,
	.data = task_data_defs,
};


//
// Bedroom tasks
//
typedef enum {
	BABY_NAPPY,
	BABY_ROCK,
	BABY_BURP,
	BABY_COUNT,
} tasks_baby_t;
static const uint8_t frames_change_nappy[] = {0, 1};
static const uint8_t frames_rock_to_sleep[] = {0, 2};
static const uint8_t frames_burp[] = {0, 3};
const game_task_t tasks_baby_arr[] = {
	{
		.name = "Change nappy",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_change_nappy,
		.animation_length = sizeof(frames_change_nappy),
	},
	{
		.name = "Rock to sleep",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_rock_to_sleep,
		.animation_length = sizeof(frames_rock_to_sleep),
	},
	{
		.name = "Burp",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_burp,
		.animation_length = sizeof(frames_burp),
	},
};
const task_list_t tasks_baby = {
	.tasks = tasks_baby_arr,
	.count = COUNT(tasks_baby_arr),
};

typedef enum {
	BED_MAKE,
	BED_ALARM,
	BED_WHACK,
	BED_COUNT,
	BED_COMFY,
} tasks_bed_t;
static const uint8_t frames_make_bed[] = {0, 1};
static const uint8_t frames_alarm_clock[] = {0, 2};
static const uint8_t frames_whack_monster[] = {0, 3};
static const uint8_t frames_comfy_bed[] = {0, 4};
const game_task_t tasks_bed_arr[] = {
	{
		.name = "Make Bed",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_make_bed,
		.animation_length = sizeof(frames_make_bed),
	},
	{
		.name = "Shut off alarm",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_alarm_clock,
		.animation_length = sizeof(frames_alarm_clock),
	},
	{
		.name = "Whack Monster",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_BROOM,
		.animation = frames_whack_monster,
		.animation_length = sizeof(frames_whack_monster),
	},
	{
		.name = "Comfy bed",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_DISTRACTION,
		.tool = TOOL_NONE,
		.animation = frames_comfy_bed,
		.animation_length = sizeof(frames_comfy_bed),
	},
};
const task_list_t tasks_bed = {
	.tasks = tasks_bed_arr,
	.count = COUNT(tasks_bed_arr),
};

typedef enum {
	CLOTHES_IRON,
	CLOTHES_FOLD,
	CLOTHES_AWAY,
	CLOTHES_COUNT,
} tasks_clothes_t;
static const uint8_t frames_iron_clothes[] = {0, 1};
static const uint8_t frames_fold_clothes[] = {0, 2};
static const uint8_t frames_put_away_clothes[] = {0, 3};
const game_task_t tasks_clothes_arr[] = {
	{
		.name = "Iron clothes",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_IRON,
		.animation = frames_iron_clothes,
		.animation_length = sizeof(frames_iron_clothes),
	},
	{
		.name = "Fold clothes",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_fold_clothes,
		.animation_length = sizeof(frames_fold_clothes),
	},
	{
		.name = "Put away clothes",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_put_away_clothes,
		.animation_length = sizeof(frames_put_away_clothes),
	},
};
const task_list_t tasks_clothes = {
	.tasks = tasks_clothes_arr,
	.count = COUNT(tasks_clothes_arr),
};

typedef enum {
	PC_COMPILE,
	PC_RESET,
	PC_SWITCH,
	PC_COUNT,
} tasks_pc_t;
static const uint8_t frames_compile_libdragon[] = {0, 1};
static const uint8_t frames_factory_reset[] = {0, 2};
static const uint8_t frames_switch_pc[] = {0, 3};
const game_task_t tasks_pc_arr[] = {
	{
		.name = "Compile Libdragon",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_AUTO,
		.tool = TOOL_NONE,
		.animation = frames_compile_libdragon,
		.animation_length = sizeof(frames_compile_libdragon),
	},
	{
		.name = "Factory reset",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_AUTO,
		.tool = TOOL_NONE,
		.animation = frames_factory_reset,
		.animation_length = sizeof(frames_factory_reset),
	},
	{
		.name = "Turn on/off PC",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_switch_pc,
		.animation_length = sizeof(frames_switch_pc),
	},
};
const task_list_t tasks_pc = {
	.tasks = tasks_pc_arr,
	.count = COUNT(tasks_pc_arr),
};

//
// Bathroom tasks
//

typedef enum {
	BATHTUB_FILL,
	BATHTUB_CLEAN,
	BATHTUB_UNCLOG,
	BATHTUB_DUCKY,
	BATHTUB_COUNT,
} tasks_bathtub_t;
static const uint8_t frames_fill_tub[] = {0, 1};
static const uint8_t frames_clean_tub[] = {0, 2};
static const uint8_t frames_unclog_tub[] = {0, 3};
static const uint8_t frames_play_ducky[] = {0, 4};
const game_task_t tasks_bathtub_arr[] = {
	{
		.name = "Fill tub",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_AUTO,
		.tool = TOOL_NONE,
		.animation = frames_fill_tub,
		.animation_length = sizeof(frames_fill_tub),
	},
	{
		.name = "Clean tub",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_BRUSH,
		.animation = frames_clean_tub,
		.animation_length = sizeof(frames_clean_tub),
	},
	{
		.name = "Unclog tub",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_PLUNGER,
		.animation = frames_unclog_tub,
		.animation_length = sizeof(frames_unclog_tub),
	},
	{
		.name = "Play with ducky",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_DISTRACTION,
		.tool = TOOL_NONE,
		.animation = frames_play_ducky,
		.animation_length = sizeof(frames_play_ducky),
	},
};
const task_list_t tasks_bathtub = {
	.tasks = tasks_bathtub_arr,
	.count = COUNT(tasks_bathtub_arr),
};

typedef enum {
	SINK_CLEAN,
	SINK_FIX,
	SINK_TIGHTEN,
	SINK_COUNT,
} tasks_sink_t;
static const uint8_t frames_clean_sink[] = {0, 2};
static const uint8_t frames_fix_sink_pipes[] = {0, 1};
static const uint8_t frames_tighten_faucet[] = {0, 3};
const game_task_t tasks_sink_arr[] = {
	{
		.name = "Clean sink",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_BRUSH,
		.animation = frames_clean_sink,
		.animation_length = sizeof(frames_clean_sink),
	},
	{
		.name = "Fix pipes",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_AUTO,
		.tool = TOOL_WRENCH,
		.animation = frames_fix_sink_pipes,
		.animation_length = sizeof(frames_fix_sink_pipes),
	},
	{
		.name = "Tighten faucet",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_WRENCH,
		.animation = frames_tighten_faucet,
		.animation_length = sizeof(frames_tighten_faucet),
	},
};
const task_list_t tasks_sink = {
	.tasks = tasks_sink_arr,
	.count = COUNT(tasks_sink_arr),
};

typedef enum {
	TOILET_CLOSE,
	TOILET_FLUSH,
	TOILET_UNCLOG,
	TOILET_COUNT,
} tasks_toilet_t;
static const uint8_t frames_close_toilet[] = {0, 2};
static const uint8_t frames_flush_toilet[] = {0, 1};
static const uint8_t frames_unclog_toilet[] = {0, 3};
const game_task_t tasks_toilet_arr[] = {
	{
		.name = "Close toilet",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_close_toilet,
		.animation_length = sizeof(frames_close_toilet),
	},
	{
		.name = "Flush toilet",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_flush_toilet,
		.animation_length = sizeof(frames_flush_toilet),
	},
	{
		.name = "Unclog toilet",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_PLUNGER,
		.animation = frames_unclog_toilet,
		.animation_length = sizeof(frames_unclog_toilet),
	},
};
const task_list_t tasks_toilet = {
	.tasks = tasks_toilet_arr,
	.count = COUNT(tasks_toilet_arr),
};

typedef enum {
	WASHER_WASH,
	WASHER_LOAD,
	WASHER_LINT,
	WASHER_COUNT,
} tasks_washer_t;
static const uint8_t frames_wash_clothes[] = {0, 2};
static const uint8_t frames_load_clothes[] = {0, 1};
static const uint8_t frames_clear_lint[] = {0, 3};
const game_task_t tasks_washer_arr[] = {
	{
		.name = "Wash clothes",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_AUTO,
		.tool = TOOL_NONE,
		.animation = frames_wash_clothes,
		.animation_length = sizeof(frames_wash_clothes),
	},
	{
		.name = "Load clothes",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_load_clothes,
		.animation_length = sizeof(frames_load_clothes),
	},
	{
		.name = "Clear lint",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_clear_lint,
		.animation_length = sizeof(frames_clear_lint),
	},
};
const task_list_t tasks_washer = {
	.tasks = tasks_washer_arr,
	.count = COUNT(tasks_washer_arr),
};

//
// Kitchen tasks
//

typedef enum {
	DOG_FEED,
	DOG_SIT,
	DOG_OUT,
	DOG_COUNT,
} tasks_dog_t;
static const uint8_t frames_feed_dog[] = {0, 1};
static const uint8_t frames_sit_dog[] = {0, 2};
static const uint8_t frames_dog_out[] = {0, 3};
const game_task_t tasks_dog_arr[] = {
	{
		.name = "Feed dog",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_AUTO,
		.tool = TOOL_NONE,
		.animation = frames_feed_dog,
		.animation_length = sizeof(frames_feed_dog),
	},
	{
		.name = "Make dog sit",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_sit_dog,
		.animation_length = sizeof(frames_sit_dog),
	},
	{
		.name = "Let dog out",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_BONE,
		.animation = frames_dog_out,
		.animation_length = sizeof(frames_dog_out),
	},
};
const task_list_t tasks_dog = {
	.tasks = tasks_dog_arr,
	.count = COUNT(tasks_dog_arr),
};

typedef enum {
	FRIDGE_DEFROST,
	FRIDGE_ICE,
	FRIDGE_GROCERIES,
	FRIDGE_SNACK,
	FRIDGE_COUNT,
} tasks_fridge_t;
static const uint8_t frames_defrost_fridge[] = {0, 1};
static const uint8_t frames_fill_tray[] = {0, 2};
static const uint8_t frames_load_groceries[] = {0, 3};
static const uint8_t frames_eat_snack[] = {0, 4};
const game_task_t tasks_fridge_arr[] = {
	{
		.name = "Defrost fridge",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_AUTO,
		.tool = TOOL_NONE,
		.animation = frames_defrost_fridge,
		.animation_length = sizeof(frames_defrost_fridge),
	},
	{
		.name = "Fill ice tray",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_AUTO,
		.tool = TOOL_NONE,
		.animation = frames_fill_tray,
		.animation_length = sizeof(frames_fill_tray),
	},
	{
		.name = "Load groceries",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_load_groceries,
		.animation_length = sizeof(frames_load_groceries),
	},
	{
		.name = "Eat snack",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_DISTRACTION,
		.tool = TOOL_NONE,
		.animation = frames_eat_snack,
		.animation_length = sizeof(frames_eat_snack),
	},
};
const task_list_t tasks_fridge = {
	.tasks = tasks_fridge_arr,
	.count = COUNT(tasks_fridge_arr),
};

typedef enum {
	OVEN_PREHEAT,
	OVEN_COOK,
	OVEN_REMOVE,
	OVEN_COUNT,
} tasks_oven_t;
static const uint8_t frames_preheat_oven[] = {0, 1};
static const uint8_t frames_cook_food[] = {0, 2};
static const uint8_t frames_remove_food[] = {0, 3};
const game_task_t tasks_oven_arr[] = {
	{
		.name = "Preheat oven",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_AUTO,
		.tool = TOOL_NONE,
		.animation = frames_preheat_oven,
		.animation_length = sizeof(frames_preheat_oven),
	},
	{
		.name = "Cook food",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_AUTO,
		.tool = TOOL_NONE,
		.animation = frames_cook_food,
		.animation_length = sizeof(frames_cook_food),
	},
	{
		.name = "Remove food",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_GLOVES,
		.animation = frames_remove_food,
		.animation_length = sizeof(frames_remove_food),
	},
};
const task_list_t tasks_oven = {
	.tasks = tasks_oven_arr,
	.count = COUNT(tasks_oven_arr),
};

typedef enum {
	BASIN_WASH,
	BASIN_DISPOSAL,
	BASIN_PIPES,
	BASIN_COUNT,
} tasks_basin_t;
static const uint8_t frames_wash_dishes[] = {0, 1};
static const uint8_t frames_fix_disposal[] = {0, 2};
static const uint8_t frames_fix_basin_pipes[] = {0, 3};
const game_task_t tasks_basin_arr[] = {
	{
		.name = "Wash dishes",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_AUTO,
		.tool = TOOL_NONE,
		.animation = frames_wash_dishes,
		.animation_length = sizeof(frames_wash_dishes),
	},
	{
		.name = "Fix disposal",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_AUTO,
		.tool = TOOL_PLUNGER,
		.animation = frames_fix_disposal,
		.animation_length = sizeof(frames_fix_disposal),
	},
	{
		.name = "Fix pipes",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_WRENCH,
		.animation = frames_fix_basin_pipes,
		.animation_length = sizeof(frames_fix_basin_pipes),
	},
};
const task_list_t tasks_basin = {
	.tasks = tasks_basin_arr,
	.count = COUNT(tasks_basin_arr),
};

//
// Living room tasks
//

typedef enum {
	DOOR_ANSWER,
	DOOR_PHONE,
	DOOR_LOCK,
	DOOR_COUNT,
} tasks_door_t;
static const uint8_t frames_answer_door[] = {0, 1};
static const uint8_t frames_answer_phone[] = {0, 2};
static const uint8_t frames_lock_door[] = {0, 3};
const game_task_t tasks_door_arr[] = {
	{
		.name = "Answer door",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_answer_door,
		.animation_length = sizeof(frames_answer_door),
	},
	{
		.name = "Answer phone",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_answer_phone,
		.animation_length = sizeof(frames_answer_phone),
	},
	{
		.name = "Lock door",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_lock_door,
		.animation_length = sizeof(frames_lock_door),
	},
};
const task_list_t tasks_door = {
	.tasks = tasks_door_arr,
	.count = COUNT(tasks_door_arr),
};

typedef enum {
	SOFA_ADJUST,
	SOFA_CLEAN,
	SOFA_SHOO,
	SOFA_COUNT,
} tasks_sofa_t;
static const uint8_t frames_adjust_sofa[] = {0, 1};
static const uint8_t frames_clean_cushions[] = {0, 2};
static const uint8_t frames_shoo_dog[] = {0, 3};
const game_task_t tasks_sofa_arr[] = {
	{
		.name = "Adjust sofa",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_adjust_sofa,
		.animation_length = sizeof(frames_adjust_sofa),
	},
	{
		.name = "Clean cushions",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_BRUSH,
		.animation = frames_clean_cushions,
		.animation_length = sizeof(frames_clean_cushions),
	},
	{
		.name = "Shoo dog",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_BONE,
		.animation = frames_shoo_dog,
		.animation_length = sizeof(frames_shoo_dog),
	},
};
const task_list_t tasks_sofa = {
	.tasks = tasks_sofa_arr,
	.count = COUNT(tasks_sofa_arr),
};

typedef enum {
	TV_RECORD,
	TV_ANTENNA,
	TV_CHANNEL,
	TV_WATCH,
	TV_COUNT,
} tasks_tv_t;
static const uint8_t frames_record_program[] = {0, 1};
static const uint8_t frames_adjust_antenna[] = {0, 2};
static const uint8_t frames_change_channel[] = {0, 3};
static const uint8_t frames_watch_tv[] = {0, 4};
const game_task_t tasks_tv_arr[] = {
	{
		.name = "Record program",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_AUTO,
		.tool = TOOL_NONE,
		.animation = frames_record_program,
		.animation_length = sizeof(frames_record_program),
	},
	{
		.name = "Adjust antenna",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_adjust_antenna,
		.animation_length = sizeof(frames_adjust_antenna),
	},
	{
		.name = "Change channel",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_REMOTE,
		.animation = frames_change_channel,
		.animation_length = sizeof(frames_change_channel),
	},
	{
		.name = "Watch TV",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_DISTRACTION,
		.tool = TOOL_NONE,
		.animation = frames_watch_tv,
		.animation_length = sizeof(frames_watch_tv),
	},
};
const task_list_t tasks_tv = {
	.tasks = tasks_tv_arr,
	.count = COUNT(tasks_tv_arr),
};

typedef enum {
	WINDOW_PLANT,
	WINDOW_OPEN,
	WINDOW_CLEAN,
	WINDOW_COUNT,
} tasks_window_t;
static const uint8_t frames_water_plant[] = {0, 1};
static const uint8_t frames_open_window[] = {0, 2};
static const uint8_t frames_clean_cindow[] = {0, 3};
const game_task_t tasks_window_arr[] = {
	{
		.name = "Water plant",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_AUTO,
		.tool = TOOL_NONE,
		.animation = frames_water_plant,
		.animation_length = sizeof(frames_water_plant),
	},
	{
		.name = "Open window",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_open_window,
		.animation_length = sizeof(frames_open_window),
	},
	{
		.name = "Clean window",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_BRUSH,
		.animation = frames_clean_cindow,
		.animation_length = sizeof(frames_clean_cindow),
	},
};
const task_list_t tasks_window = {
	.tasks = tasks_window_arr,
	.count = COUNT(tasks_window_arr),
};

//
// Floor tasks
//

typedef enum {
	FLOOR_TRASH,
	FLOOR_VACUUM,
	FLOOR_BULB,
	FLOOR_COUNT,
} tasks_floor_t;
static const uint8_t frames_destroy_trash[] = {0, 1};
static const uint8_t frames_vacuum_floor[] = {0, 2};
static const uint8_t frames_replace_bulb[] = {0, 3};
const game_task_t tasks_room_arr[] = {
	{
		.name = "Destroy trash",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_NONE,
		.animation = frames_destroy_trash,
		.animation_length = sizeof(frames_destroy_trash),
	},
	{
		.name = "Vacuum Floor",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_VACUUM,
		.animation = frames_vacuum_floor,
		.animation_length = sizeof(frames_vacuum_floor),
	},
	{
		.name = "Replace bulb",
		.duration = TASK_DURATION_SHORT,
		.urgency = TASK_URGENCY_SHORT,
		.type = TASK_TYPE_MANUAL,
		.tool = TOOL_BULB,
		.animation = frames_replace_bulb,
		.animation_length = sizeof(frames_replace_bulb),
	},
};
const task_list_t tasks_room = {
	.tasks = tasks_room_arr,
	.count = COUNT(tasks_room_arr),
};

// Put new tools here
#define TASKS_TABLE \
	X(TASKS_BABY_NAPPY, &tasks_baby_arr[BABY_NAPPY]) \
	X(TASKS_BABY_ROCK,  &tasks_baby_arr[BABY_ROCK])  \
	X(TASKS_BABY_BURP,  &tasks_baby_arr[BABY_BURP])  \
	X(TASKS_BED_MAKE,   &tasks_bed_arr[BED_MAKE])    \
	X(TASKS_BED_ALARM,  &tasks_bed_arr[BED_ALARM])   \
	X(TASKS_BED_WHACK,  &tasks_bed_arr[BED_WHACK])   \
	X(TASKS_BED_COMFY,  &tasks_bed_arr[BED_COMFY])   \
	X(TASKS_CLOTHES_IRON, &tasks_clothes_arr[CLOTHES_IRON]) \
	X(TASKS_CLOTHES_FOLD, &tasks_clothes_arr[CLOTHES_FOLD]) \
	X(TASKS_CLOTHES_AWAY, &tasks_clothes_arr[CLOTHES_AWAY]) \
	X(TASKS_PC_COMPILE, &tasks_pc_arr[PC_COMPILE]) \
	X(TASKS_PC_RESET, &tasks_pc_arr[PC_RESET]) \
	X(TASKS_PC_SWITCH, &tasks_pc_arr[PC_SWITCH]) \
	X(TASKS_BATHTUB_FILL, &tasks_bathtub_arr[BATHTUB_FILL]) \
	X(TASKS_BATHTUB_CLEAN, &tasks_bathtub_arr[BATHTUB_CLEAN]) \
	X(TASKS_BATHTUB_UNCLOG, &tasks_bathtub_arr[BATHTUB_UNCLOG]) \
	X(TASKS_BATHTUB_DUCKY, &tasks_bathtub_arr[BATHTUB_DUCKY]) \
	X(TASKS_SINK_CLEAN, &tasks_sink_arr[SINK_CLEAN]) \
	X(TASKS_SINK_FIX, &tasks_sink_arr[SINK_FIX]) \
	X(TASKS_SINK_TIGHTEN, &tasks_sink_arr[SINK_TIGHTEN]) \
	X(TASKS_TOILET_CLOSE, &tasks_toilet_arr[TOILET_CLOSE]) \
	X(TASKS_TOILET_FLUSH, &tasks_toilet_arr[TOILET_FLUSH]) \
	X(TASKS_TOILET_UNCLOG, &tasks_toilet_arr[TOILET_UNCLOG]) \
	X(TASKS_WASHER_WASH, &tasks_washer_arr[WASHER_WASH]) \
	X(TASKS_WASHER_LOAD, &tasks_washer_arr[WASHER_LOAD]) \
	X(TASKS_WASHER_LINT, &tasks_washer_arr[WASHER_LINT]) \
	X(TASKS_DOG_FEED, &tasks_dog_arr[DOG_FEED]) \
	X(TASKS_DOG_SIT, &tasks_dog_arr[DOG_SIT]) \
	X(TASKS_DOG_OUT, &tasks_dog_arr[DOG_OUT]) \
	X(TASKS_FRIDGE_DEFROST, &tasks_fridge_arr[FRIDGE_DEFROST]) \
	X(TASKS_FRIDGE_ICE, &tasks_fridge_arr[FRIDGE_ICE]) \
	X(TASKS_FRIDGE_GROCERIES, &tasks_fridge_arr[FRIDGE_GROCERIES]) \
	X(TASKS_FRIDGE_SNACK, &tasks_fridge_arr[FRIDGE_SNACK]) \
	X(TASKS_OVEN_PREHEAT, &tasks_oven_arr[OVEN_PREHEAT]) \
	X(TASKS_OVEN_COOK, &tasks_oven_arr[OVEN_COOK]) \
	X(TASKS_OVEN_REMOVE, &tasks_oven_arr[OVEN_REMOVE]) \
	X(TASKS_BASIN_WASH, &tasks_basin_arr[BASIN_WASH]) \
	X(TASKS_BASIN_DISPOSAL, &tasks_basin_arr[BASIN_DISPOSAL]) \
	X(TASKS_BASIN_PIPES, &tasks_basin_arr[BASIN_PIPES]) \
	X(TASKS_DOOR_ANSWER, &tasks_door_arr[DOOR_ANSWER]) \
	X(TASKS_DOOR_PHONE, &tasks_door_arr[DOOR_PHONE]) \
	X(TASKS_DOOR_LOCK, &tasks_door_arr[DOOR_LOCK]) \
	X(TASKS_SOFA_ADJUST, &tasks_sofa_arr[SOFA_ADJUST]) \
	X(TASKS_SOFA_CLEAN, &tasks_sofa_arr[SOFA_CLEAN]) \
	X(TASKS_SOFA_SHOO, &tasks_sofa_arr[SOFA_SHOO]) \
	X(TASKS_TV_RECORD, &tasks_tv_arr[TV_RECORD]) \
	X(TASKS_TV_ANTENNA, &tasks_tv_arr[TV_ANTENNA]) \
	X(TASKS_TV_CHANNEL, &tasks_tv_arr[TV_CHANNEL]) \
	X(TASKS_TV_WATCH, &tasks_tv_arr[TV_WATCH]) \
	X(TASKS_WINDOW_PLANT, &tasks_window_arr[WINDOW_PLANT]) \
	X(TASKS_WINDOW_OPEN, &tasks_window_arr[WINDOW_OPEN]) \
	X(TASKS_WINDOW_CLEAN, &tasks_window_arr[WINDOW_CLEAN]) \
	X(TASKS_FLOOR_TRASH, &tasks_room_arr[FLOOR_TRASH]) \
	X(TASKS_FLOOR_VACUUM, &tasks_room_arr[FLOOR_VACUUM]) \
	X(TASKS_FLOOR_BULB, &tasks_room_arr[FLOOR_BULB]) \

// Enum table will be generated by the above
#define X(id, task_pointer) id,
typedef enum {
	TASKS_TABLE
	TASKS_COUNT
} tasks_enum_t;
#undef X

#define X(id, task_pointer) task_pointer,
const game_task_t* all_tasks[TASKS_COUNT] = {
	TASKS_TABLE
};
#undef X
