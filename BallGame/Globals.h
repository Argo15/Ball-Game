#ifndef GLOBALS_H
#define GLOBALS_H
#include "GameState.h"

enum RenderState {NOSHADERS, FINAL, DEPTH, NORMAL, COLOR, LIGHTING, SSAO, SPECULAR, MOTION};

class Globals {
public:
	static GameState *GAMESTATE;
	static RenderState RENDERSTATE;
	static bool glowEnabled;
	static bool motionblur;
	static bool ambientOcclusion;
	static bool highQualityShadows;
	static bool showHelp;

	static bool OpenedMenu;
	static bool LevelOnePassed;
	static bool LevelTwoPassed;
	static bool LevelThreePassed;
	static bool LevelFourPassed;

	static int matNum;
	static int bumpNum;
	static float ballReflect;
};

#endif