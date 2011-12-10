#include "LevelFour.h"
#include "MainMenuState.h"
#include "Globals.h"

LevelFour::LevelFour() : LevelState(){
	levelFile = new LevelFile();
	levelFile->loadFile("Data/Saves/Level 4.ascn");
	level = new Level();
	levelFile->initializeLevel(level);
	level->setToggleGravity(true);
	endDistance = 0.4;
}

void LevelFour::update(int fps) {
	LevelState::update(fps);
}

void LevelFour::onFinish() {
	LevelState::onFinish();
	//Globals::LevelOnePassed = true;
	Globals::GAMESTATE = new MainMenuState();
	Globals::GAMESTATE->resize(width,height);
	delete this;
}