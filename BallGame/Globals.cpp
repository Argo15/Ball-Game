#include "Globals.h"

GameState *Globals::GAMESTATE = 0;
RenderState Globals::RENDERSTATE = NOSHADERS;
bool Globals::glowEnabled = false;
bool Globals::motionblur = true;
bool Globals::ambientOcclusion = false;
bool Globals::highQualityShadows = true;
bool Globals::showHelp = true;

bool Globals::OpenedMenu = true;
bool Globals::LevelOnePassed = false;
bool Globals::LevelTwoPassed = false;
bool Globals::LevelThreePassed = false;
bool Globals::LevelFourPassed = false;

int Globals::matNum = 5;
int Globals::bumpNum = 0;
float Globals::ballReflect = 0.3f;