#include <GL/glut.h>
#include "MenuState.h"

// init
MenuState::MenuState() {
	glShadeModel(GL_SMOOTH);				// GL_SMOOTH or GL_FLAT
	glClearDepth(1.0f);						// depth cleared to
	glEnable(GL_DEPTH_TEST);				// enable depth testing
	glEnable(GL_TEXTURE_2D);				// enable texturing
	glDepthFunc(GL_LEQUAL);					// lesser than or equal to depth
}

void MenuState::resize(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void MenuState::update(int fps) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MenuState::render() {
	glLoadIdentity();

	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-1.0, -0.7, -1.0);
		glVertex3f(-0.5,  0.7, -1.0);
		glVertex3f( 0.0, -0.7, -1.0);
	glEnd();

	glutSwapBuffers();
}