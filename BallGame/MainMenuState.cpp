#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "MainMenuState.h"
#include <iostream>
using namespace std;

// init

MainMenuState::MainMenuState() : MenuState() {
	background = new Texture();
	background->load("Data/Textures/TGA/Ice.tga");
	
	items = new MenuItem*[6];
	items[0] = new MenuItem();
	items[0]->setTopLeft(0.02f,0.96f);
	items[0]->setBottomRight(0.96f,0.90f);
	items[0]->setDescription("Play Level 1!!!!!!!!!!!!!!!!!");
}

void MainMenuState::resize(int w, int h) {
	MenuState::resize(w, h);
}

void MainMenuState::update(int fps) {
	MenuState::update(fps);
}

void MainMenuState::render() {
	glLoadIdentity();
	
	drawBackground();

	items[0]->drawItem();

	MenuState::render();
}

void MainMenuState::drawBackground()
{
	background->use();
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1,1);	glVertex3f(1.0, 1.0, -9.0);
	glTexCoord2f(1,0);	glVertex3f(1.0,  0.0, -9.0);
	glTexCoord2f(0,0);	glVertex3f( 0.0, 0.0, -9.0);
	glTexCoord2f(0,1);	glVertex3f(0.0,1.0,-9.0);
	glEnd();
}

