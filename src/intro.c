#include "intro.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>

#define CAMERA_X_DEFAULT 0.0
#define CAMERA_Y_DEFAULT 0.0
#define CAMERA_Z_DEFAULT 5.0

#define SEGMENTS_LOGO 1
#define SEGMENTS_DRAGON 4
#define SEGMENTS_START 180
#define SEGMENTS_1_START 0
#define SEGMENTS_2_START 60
#define SEGMENTS_3_START SEGMENTS_2_START
#define SEGMENTS_4_START 120
#define SEGMENTS_END (SEGMENTS_START + SEGMENTS_4_START + 120)
#define SEGMENTS_TOTAL (SEGMENTS_DRAGON + SEGMENTS_LOGO)

#define LIGHT_START_X -5.0f
#define LIGHT_END_X 1.5f
#define LIGHT_START_Y 0.0f
#define LIGHT_START_Z 3.0f
#define LIGHT_END_Z 5.0f
#define LIGHT_SPEED 0.25f

#define ANIMATION_SPEED 0.025f

// Lookup table row struct
typedef struct dragon_model_s {
	vertex_t pos, pos_end;
	vertex_t rot, rot_end;
	model64_t* model;
	uint16_t anim_start;
	float anim_speed;
	uint16_t anim_end;
	uint16_t light_index;
	GLfloat light_color[4];
} dragon_model_t;

// Lookup table with animation data for the intro
static dragon_model_t segments[SEGMENTS_TOTAL] = {
	{
		.rot			= {0.0f, 1080.0f, 0.0f},
		.rot_end		= {0.0f, 0.0f,  0.0f},
		.pos			= {0.0f, 0.0f, 0.0f},
		.pos_end		= {0.0f, 0.0f, 0.0f},
		.anim_start		= 0,
		.anim_speed		= ANIMATION_SPEED,
		.anim_end		= SEGMENTS_START,
		.light_index	= GL_LIGHT0,
		.light_color	= {0.0f, 0.0f, 0.0f, 0.0f},
	},
	{
		.rot			= {0.0f, 0.0f, 90.0f},
		.rot_end		= {0.0f, 0.0f, 0.0f},
		.pos			= {-3.0f, 0.0f, 0.0f},
		.pos_end		= {-3.0f, 0.0f, 0.0f},
		.anim_start		= SEGMENTS_START + SEGMENTS_1_START,
		.anim_speed		= ANIMATION_SPEED,
		.anim_end		= SEGMENTS_END,
		.light_index	= GL_LIGHT0,
		.light_color	= {0.0f, 0.0f, 0.0f, 0.0f},

	},
	{
		.rot			= {0.0f, 0.0f, -180.0f},
		.rot_end 		= {0.0f, 0.0f, -270.0f},
		.pos			= {-1.75f, -0.625f, 0.0f},
		.pos_end		= {-1.75f, -0.625f, 0.0f},
		.anim_start		= SEGMENTS_START + SEGMENTS_2_START,
		.anim_speed		= ANIMATION_SPEED,
		.anim_end		= SEGMENTS_END,
		.light_index	= GL_LIGHT1,
		.light_color	= {0.0f, 0.0f, 0.0f, 0.0f},
	},
	{
		.rot			= {0.0f, 0.0f, -235.0f},
		.rot_end		= {0.0f, 0.0f, -180.0f},
		.pos			= {-2.0f, -0.5f, 0.0f},
		.pos_end		= {-2.0f, -0.5f, 0.0f},
		.anim_start		= SEGMENTS_START + SEGMENTS_3_START,
		.anim_speed		= ANIMATION_SPEED,
		.anim_end		= SEGMENTS_END,
		.light_index	= GL_LIGHT1,
		.light_color	= {0.0f, 0.0f, 0.0f, 0.0f},
	},
	{
		.rot			= {0.0f, 0.0f, 0.0f},
		.rot_end		= {0.0f, 0.0f, 0.0f},
		.pos			= {0.0f, -1.5625f, 0.0f},
		.pos_end		= {-3.875f, -1.5625f, 0.0f},
		.anim_start		= SEGMENTS_START + SEGMENTS_4_START,
		.anim_speed		= ANIMATION_SPEED*4,
		.anim_end		= SEGMENTS_END,
		.light_index	= GL_LIGHT2,
		.light_color	= {0.0f, 0.0f, 0.0f, 0.0f},
	},
};

static const float aspect_ratio = 320.0 / 240.0;
static const float near_plane = 1.0f;
static const float far_plane = 20.0f;
static const vertex_t camera = {CAMERA_X_DEFAULT, CAMERA_Y_DEFAULT, CAMERA_Z_DEFAULT};
static vertex_t light_pos = {LIGHT_START_X, LIGHT_START_Y, LIGHT_START_Z};
static uint16_t intro_timer = 0;
static wav64_t intro_jingle;

void intro_init (void) {
	gl_init();
	// Set the viewing area
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
	glLoadIdentity();
	glFrustum(
		-near_plane*aspect_ratio,
		near_plane*aspect_ratio,
		-near_plane,
		near_plane,
		near_plane,
		far_plane
		);

	// Load audio
	wav64_open(&intro_jingle, "rom:/audio/dragon.wav64");

	// Set starting values for each segment
	char buff[32];
	for (uint8_t i=SEGMENTS_LOGO; i<SEGMENTS_TOTAL; i++) {
		sprintf(buff, "rom:/models/dragon%i.model64", i-1);
		segments[i].model = model64_load(buff);
		glLightfv(segments[i].light_index, GL_DIFFUSE, segments[i].light_color);
		glLightfv(segments[i].light_index, GL_AMBIENT, segments[i].light_color);
	}
	segments[0].model = model64_load("rom:/models/logo.model64");
}

// Inline lerp function to help with the animation functions
static inline float lerp(float current, float target, float speed) {
	return current * (1.0f - speed) + target * speed;
}

void intro_move (void) {

	intro_timer++;

	// Play the jingle
	if (intro_timer == SEGMENTS_START) {
		wav64_play(&intro_jingle, 0);
	}

	// Rotate the segments
	for (uint8_t i=0; i<SEGMENTS_TOTAL; i++) {
		if (intro_timer >= segments[i].anim_start) {
			// Average out current rotation with the target rotation
			segments[i].pos.x = lerp(segments[i].pos.x,     segments[i].pos_end.x,     segments[i].anim_speed);
			segments[i].rot.y = lerp(segments[i].rot.y,     segments[i].rot_end.y,     segments[i].anim_speed);
			segments[i].rot.z = lerp(segments[i].rot.z,     segments[i].rot_end.z,     segments[i].anim_speed);

			// Average out the lights
			segments[i].light_color[0] = lerp(segments[i].light_color[0], 1.0f, segments[i].anim_speed);
			segments[i].light_color[1] = lerp(segments[i].light_color[1], 1.0f, segments[i].anim_speed);
			segments[i].light_color[2] = lerp(segments[i].light_color[2], 1.0f, segments[i].anim_speed);
			glLightfv(segments[i].light_index, GL_DIFFUSE, segments[i].light_color);
			glLightfv(segments[i].light_index, GL_AMBIENT, segments[i].light_color);
		}
	}

	// Move the light when the text appears
	if (intro_timer > (SEGMENTS_START + SEGMENTS_4_START)) {
		light_pos.x = lerp(light_pos.x, LIGHT_END_X, ANIMATION_SPEED);
		light_pos.z = lerp(light_pos.z, LIGHT_END_Z, ANIMATION_SPEED);
	}

	// Finish this
	if (intro_timer > SEGMENTS_END) {
		intro_end();
	}
}

void intro_draw (void) {
	gl_context_begin();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluLookAt(
			camera.x, camera.y, camera.z,
			0, 0, 0,
			0, 1, 0
		);

		// Clear the screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Configure settings
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

		// Loop through all segments
		for (uint8_t i=0; i<SEGMENTS_TOTAL; i++) {

			// Set the lighting
			GLfloat light_pos_rel[4] = {
				light_pos.x,
				light_pos.y,
				light_pos.z,
				1.0f
			};
			glLightfv(segments[i].light_index, GL_POSITION, light_pos_rel);

			// If this segment can run
			if (intro_timer >= segments[i].anim_start && intro_timer < segments[i].anim_end) {
				glEnable(segments[i].light_index);

				// Transform and draw
				glPushMatrix();

					glTranslatef(
						segments[i].pos.x,
						segments[i].pos.y,
						segments[i].pos.z
					);
					glRotatef(segments[i].rot.y, 0.0f, 1.0f, 0.0f);
					glRotatef(segments[i].rot.z, 0.0f, 0.0f, 1.0f);

					model64_draw(segments[i].model);


				// Clean things up
				glPopMatrix();
				glDisable(segments[i].light_index);
			}
		}

		// Unconfigure settings
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

	gl_context_end();

	// Play the music
	mixer_try_play();
}

void intro_end (void) {
	wav64_close(&intro_jingle);
	for (uint8_t i=0; i<SEGMENTS_TOTAL; i++) {
		model64_free(segments[i].model);
	}
	gl_close();
}
