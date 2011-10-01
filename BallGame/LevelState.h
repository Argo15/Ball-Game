#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include "GameState.h"
#include "Material.h"
#include "ModelRegistry.h"

class LevelState : public GameState {
private:
	Material *testMat;
	ModelRegistry *models;
	TextureRegistry *textures;

public:
	LevelState();
	~LevelState() {}

	void resize(int w, int h);
	void update(int fps);
	void render();
};

#endif