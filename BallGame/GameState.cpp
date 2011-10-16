#include "GameState.h"
#include "Globals.h"
#include <stdlib.h>
#include <GL/glut.h>

void GameState::resize(int w, int h) {
	width = w;
	height = h;
}

void GameState::keyDown(unsigned char key, int xx, int yy)
{
	keys[key]=true;
	if (key >= '0' && key <= '9') 
		Globals::RENDERSTATE = (RenderState)((int)key-(int)'0');
}


void GameState::keyUp(unsigned char key, int xx, int yy)
{
	keys[key]=false;
}

void GameState::mousePress(int button, int state, int x, int y) 
{
	if (state == GLUT_DOWN)
		mouse[button]=true;
	else
		mouse[button]=false;
}

void GameState::mousePressedMove(int x, int y) 
{

}

void GameState::mouseReleasedMove(int x, int y) 
{

}