#ifndef GLOBALS_H
#define GLOBALS_H
#include "GameState.h"

enum RenderState {NOSHADERS, FINAL, DEPTH, NORMAL, COLOR, LIGHTING, SPECULAR};

class Globals {
public:
	static GameState *GAMESTATE;
	static RenderState RENDERSTATE;
};

#endif