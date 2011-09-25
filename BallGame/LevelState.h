#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include "GameState.h"

class LevelState : public GameState {
public:
	LevelState();
	~LevelState() {}

	void resize(int w, int h);
	void update(int fps);
	void render();
};

#endif