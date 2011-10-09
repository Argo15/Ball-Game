#include <stdlib.h>
#include <GL/glut.h>
#include "LevelState.h"
#include "Globals.h"
#include "MainMenuState.h"

// init
LevelState::LevelState() {
	glShadeModel(GL_SMOOTH);				// GL_SMOOTH or GL_FLAT
	glClearDepth(1.0f);						// depth cleared to
	glEnable(GL_DEPTH_TEST);				// enable depth testing
	glEnable(GL_TEXTURE_2D);				// enable texturing
	glDepthFunc(GL_LEQUAL);					// lesser than or equal to depth
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);	// Really Nice Perspective Calculations
	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	camera = new Camera();
	camera->setRotSpeed(2.0);
	camera->updateFromDistance();

	levelFile = new LevelFile();
	levelFile->loadFile("Data/Saves/Test Level.ascn");
	level = new Level();
	levelFile->initializeLevel(level);
}

void LevelState::resize(int w, int h) {
	GameState::resize(w,h);
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
	if (keys['r']){
		GameState::GAMESTATE = new MainMenuState();
		GameState::GAMESTATE->resize(width,height);
	}
}

void LevelState::render() {
	glLoadIdentity();

	camera->transform();

	float direction[] = {1.0,2.0,3.0,0.0};
	glLightfv(GL_LIGHT0,GL_POSITION,direction);

	level->drawNoShaders();

	glutSwapBuffers();
}

void LevelState::mousePressedMove(int x, int y) {
	if (mouse[2])
		camera->mouseRotate(x, y);
}

void LevelState::mouseReleasedMove(int x, int y) {
	camera->noRotate();
}