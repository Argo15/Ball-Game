#include "Funhouse.h"
#include "MainMenuState.h"
#include "Globals.h"

FunHouse::FunHouse() : LevelState(){
	levelFile = new LevelFile();
	levelFile->loadFile("Data/Saves/FunHouse.ascn");
	level = new Level();
	levelFile->initializeLevel(level);
	endDistance = 1.0;
}

void FunHouse::resize(int w, int h) {
	GameState::resize(w,h);
	if(h == 0)
		h = 1;
	GLfloat aspect = GLfloat(w) / h;
	view->viewport(0, 0, w, h);
	view->set3D(45.0f,aspect,0.01,30);
	view->set2D(0,1,0,1,0,1);
}

void FunHouse::update(int fps) {
	LevelState::update(fps);
}

void FunHouse::onFinish() {
	LevelState::onFinish();
	Globals::GAMESTATE = new MainMenuState();
	Globals::GAMESTATE->resize(width,height);
}