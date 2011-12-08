#include "GameState.h"
#include "Globals.h"
#include <stdlib.h>
#include <math.h>
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
	if (key == 'o') Globals::ambientOcclusion = !Globals::ambientOcclusion;
	if (key == 'm') Globals::motionblur = !Globals::motionblur;
	if (key == 'g') Globals::glowEnabled = !Globals::glowEnabled;
	if (key == 'l') Globals::highQualityShadows = !Globals::highQualityShadows;
	if (key == 'z') Globals::matNum = (Globals::matNum - 1)%6;
	if (key == 'x')	Globals::matNum = (Globals::matNum + 1)%6;
	if (key == 'c')	Globals::bumpNum = (Globals::bumpNum - 1)%5;
	if (key == 'v')	Globals::bumpNum = (Globals::bumpNum + 1)%5;
	if (key == '-')	Globals::ballReflect = (Globals::ballReflect - 0.1);
	if (key == '=')	Globals::ballReflect = (Globals::ballReflect + 0.1);
	if (Globals::matNum < 0) Globals::matNum = 5;
	if (Globals::bumpNum < 0) Globals::bumpNum = 4;
	if (Globals::ballReflect < 0) Globals::ballReflect = 0;
	if (Globals::ballReflect > 1) Globals::ballReflect = 1;
	if (key == 'h')	Globals::showHelp = !Globals::showHelp;
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