#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "MenuState.h"
#include "TestLevelOne.h"
#include "Globals.h"
#include "MenuItem.h"
#include <string>
using namespace std;
 int MenuState::screenHeight = 1;
 int MenuState::screenWidth = 1;
/**
creates a menuState
**/
MenuState::MenuState() {
	glShadeModel(GL_SMOOTH);				// GL_SMOOTH or GL_FLAT
	glClearDepth(1.0f);						// depth cleared to
	glEnable(GL_DEPTH_TEST);				// enable depth testing
	glEnable(GL_TEXTURE_2D);				// enable texturing
	glDepthFunc(GL_LEQUAL);					// lesser than or equal to depth
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glEnable( GL_BLEND ); 
	glClearColor(0.0,0.0,0.0,0.0);
}
/**
resizes the screen when the user resizes
**/
void MenuState::resize(int w, int h) {
	GameState::resize(w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glOrtho(0, w, h, 0, 0.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	screenWidth = w;
	screenHeight = h;
}
/**
updates the menustate
**/
void MenuState::update(int fps) {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

/**
renders the menustate
**/
void MenuState::render() {
	glLoadIdentity();
	glutSwapBuffers();
}






