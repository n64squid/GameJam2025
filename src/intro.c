#include "intro.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>

#define CAMERA_X_DEFAULT 0.0
#define CAMERA_Y_DEFAULT 0.0
#define CAMERA_Z_DEFAULT 10.0

static const float aspect_ratio = 320.0 / 240.0;
static const float near_plane = 1.0f;
static const float far_plane = 20.0f;
static const vertex_t camera = {CAMERA_X_DEFAULT, CAMERA_Y_DEFAULT, CAMERA_Z_DEFAULT};
static vertex_t light_pos = {0.0, 5.0, 10.0};
static GLfloat light_color[4] = {1.0, 1.0, 1.0, 1.0};

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
	glLightfv(GL_LIGHT1, GL_DIFFUSE, (GLfloat[4]) {0.75f, 0.75f, 0.75f, 0.0f});
	glLightfv(GL_LIGHT1, GL_AMBIENT, (GLfloat[4]) {1.0f, 1.0f, 1.0f, 0.0f});
}

void intro_move (void) {

}

void intro_draw (void) {
	gl_context_begin();
		// Lit 3D objects
		GLfloat light_pos_rel[4] = {
			light_pos.x,
			light_pos.y,
			light_pos.z,
			0.0f
		};

		// Set light positions and colour
		glLightfv(GL_LIGHT0, GL_POSITION, light_pos_rel);
		glLightfv(GL_LIGHT1, GL_POSITION, light_pos_rel);
		glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_color);

		gluLookAt(
			camera.x, camera.y, camera.z,
			0, 0, 0,
			0, 1, 0
		);

		// Clear the screen
		glClearColor(
			0.5f,
			0.5f,
			0.5f,
			1.0f
		);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gl_context_end();

}

void intro_clean (void) {
	gl_close();
}
