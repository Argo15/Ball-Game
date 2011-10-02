#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include "GameState.h"
#include "Camera.h"
#include "LevelFile.h"

class LevelState : public GameState {
private:
	Camera *camera;
	LevelFile *levelFile;
	Level *level;

public:
	LevelState();
	~LevelState() {}

	void resize(int w, int h);
	void update(int fps);
	void render();

	void mousePressedMove(int x, int y);
	void mouseReleasedMove(int x, int y);
};

#endif