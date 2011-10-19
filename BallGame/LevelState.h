#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include <gl/glut.h>
#include "GameState.h"
#include "Camera.h"
#include "LevelFile.h"
#include "GBuffer.h"
#include "View.h"
#include "GLSLProgram.h"
#include "GLSLShader.h"
#include "LinearDepthBuffer.h"
#include "LightBuffer.h"
#include "FinalBuffer.h"
#include "ColorBuffer.h"
#include "Frustum.h"
#include "CascadedShadowMap.h"

class LevelState : public GameState {
private:
	GBuffer *gBuffer;
	LinearDepthBuffer *depthBuffer;
	LightBuffer *lightBuffer;
	FinalBuffer *finalBuffer;
	ColorBuffer *hBlurBuffer;
	ColorBuffer *glowBlurBuffer;
	ColorBuffer *glowBlurBuffer2;
	GLSLProgram *gBufferProg;
	GLSLProgram *depthProg;
	GLSLProgram *dLightProg;
	GLSLProgram *pLightProg;
	GLSLProgram *finalProg;
	GLSLProgram *hBlurProg;
	GLSLProgram *vBlurProg;
	View *view;
	Frustum *frustum;
	CascadedShadowMap *cascadedShadowMap;

protected:
	Camera *camera;
	LevelFile *levelFile;
	Level *level;

	float endDistance;
	bool glowEnabled;

public:
	LevelState();
	~LevelState() {}

	void resize(int w, int h);
	void update(int fps);
	void render();
	virtual void renderGBuffer();
	virtual void onFinish();

	void mousePressedMove(int x, int y);
	void mouseReleasedMove(int x, int y);

	void drawScreen(float x1, float y1, float x2, float y2);
	void blurTexture(ColorBuffer *resultBuffer, GLuint texture, float scale);
};

#endif