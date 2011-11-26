#include "Globals.h"

GameState *Globals::GAMESTATE = 0;
RenderState Globals::RENDERSTATE = NOSHADERS;
bool Globals::glowEnabled = false;
bool Globals::motionblur = true;
bool Globals::ambientOcclusion = true;
bool Globals::highQualityShadows = true;