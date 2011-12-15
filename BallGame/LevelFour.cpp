#include "LevelFour.h"
#include "MainMenuState.h"
#include "Minecraft.h"
#include "Globals.h"
#include "SoundManager.h"

LevelFour::LevelFour() : LevelState(){
	levelFile = new LevelFile();
	levelFile->loadFile("Data/Saves/Level 4.ascn");
	level = new Level();
	levelFile->initializeLevel(level);
	level->setToggleGravity(true);
	endDistance = 0.4;
	SoundManager::Instance()->updateSourcePosition("BeatLevel",level->getEnd());
	SoundManager::Instance()->addSoundSource("Data/Sound/LevelFour.wav","LevelFour",NULL);
	SoundManager::Instance()->makeLoop("LevelFour");
	SoundManager::Instance()->startSound("LevelFour",false);
	SoundManager::Instance()->updateSourcePosition("BeatLevel",level->getEnd());
}

void LevelFour::update(int fps) {
	LevelState::update(fps);
}

void LevelFour::onFinish() {
	Globals::LevelFourPassed = true;
	SoundManager::Instance()->stopSound("LevelFour");
	LevelState::onFinish();
	Globals::GAMESTATE = new MainMenuState();
	Globals::GAMESTATE->resize(width,height);
	delete this;
}