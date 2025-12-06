#include "intro.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>

static const float aspect_ratio = 320.0 / 240.0;
static const float near_plane = 1.0f;
static const float far_plane = 20.0f;

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
	gl_context_end();

}

void intro_clean (void) {
	gl_close();
}
