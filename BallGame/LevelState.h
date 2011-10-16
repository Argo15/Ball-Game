#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include "GameState.h"
#include "Camera.h"
#include "LevelFile.h"
#include "GBuffer.h"
#include "View.h"
#include "GLSLProgram.h"
#include "GLSLShader.h"
#include "LinearDepthBuffer.h"

class LevelState : public GameState {
private:
	GBuffer *gBuffer;
	LinearDepthBuffer *depthBuffer;
	GLSLProgram *gBufferProg;
	GLSLProgram *depthProg;
	View *view;

protected:
	Camera *camera;
	LevelFile *levelFile;
	Level *level;

	float endDistance;

public:
	LevelState();
	~LevelState() {}

	void resize(int w, int h);
	void update(int fps);
	void render();
	virtual void renderGBuffer();
	virtual void onFinish() = 0;

	void mousePressedMove(int x, int y);
	void mouseReleasedMove(int x, int y);

	void drawScreen(float x1, float y1, float x2, float y2);
};

#endif