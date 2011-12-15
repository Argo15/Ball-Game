#include "Minecraft.h"
#include "MainMenuState.h"
#include "Globals.h"
#include "SoundManager.h"

Minecraft::Minecraft() : LevelState(){
	levelFile = new LevelFile();
	levelFile->loadFile("Data/Saves/Minecraft.ascn");
	level = new Level();
	levelFile->initializeLevel(level);
	endDistance = 0.6;
}

void Minecraft::update(int fps) {
	LevelState::update(fps);
}

void Minecraft::onFinish() {
	LevelState::onFinish();
	Globals::GAMESTATE = new MainMenuState();
	Globals::GAMESTATE->resize(width,height);
	delete this;
}