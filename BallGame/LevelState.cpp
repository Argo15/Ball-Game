#include <GL/glut.h>
#include "LevelState.h"

// init
LevelState::LevelState() {
	glShadeModel(GL_SMOOTH);				// GL_SMOOTH or GL_FLAT
	glClearDepth(1.0f);						// depth cleared to
	glEnable(GL_DEPTH_TEST);				// enable depth testing
	glEnable(GL_TEXTURE_2D);				// enable texturing
	glDepthFunc(GL_LEQUAL);					// lesser than or equal to depth
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);	// Really Nice Perspective Calculations
	glEnable(GL_NORMALIZE);
}

void LevelState::resize(int w, int h) {
	if(h == 0)
		h = 1;
	GLfloat aspect = GLfloat(w) / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0,aspect,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

void LevelState::update(int fps) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LevelState::render() {
	glLoadIdentity();
	glTranslated(0,0,-5.0);

	glBegin(GL_TRIANGLES);
		glVertex3f(-2.0f, -2.0f, 0.0f);
		glVertex3f( 0.0f, 2.0f, 0.0);
		glVertex3f( 2.0f, -2.0f, 0.0);
	glEnd();

	glutSwapBuffers();
}