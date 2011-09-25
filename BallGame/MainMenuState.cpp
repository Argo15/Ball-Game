#include <GL/glut.h>
#include "MainMenuState.h"

// init
MainMenuState::MainMenuState() : MenuState() {

}

void MainMenuState::resize(int w, int h) {
	MenuState::resize(w, h);
}

void MainMenuState::update(int fps) {
	MenuState::update(fps);
}

void MainMenuState::render() {
	glLoadIdentity();

	glBegin(GL_TRIANGLES);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(1.0, 0.7, -1.0);
		glVertex3f(0.5,  -0.7, -1.0);
		glVertex3f( 0.0, 0.7, -1.0);
	glEnd();

	MenuState::render();
}