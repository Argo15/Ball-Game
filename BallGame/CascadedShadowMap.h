#ifndef CASCASEDSHADOWMAP_H
#define CASCADEDSHADOWMAP_H

#include "DepthBuffer.h"
#include "Frustum.h"
#include "Camera.h"
#include "View.h"
#include "Object.h"
#include "Level.h"
#include "DirectLight.h"

class CascadedShadowMap {
private:
	DepthBuffer *shadowMaps[4];
	ArgoMatrix4 lightMatrix[4];
	float slices[3];
	int size;

	Camera *createLightCamera(float slice1, float slice2, Camera *camera, View *view, DirectLight *dLight);
	View *createLightView(float slice1, float slice2, Camera *camera, Camera *lightCamera, View *view, Frustum *frustum);

public:
	CascadedShadowMap() {CascadedShadowMap(1024);}
	CascadedShadowMap(int size, float slice1 = 0.15, float slice2 = 0.3, float slice3 = 0.6);
	~CascadedShadowMap() {}

	void buildShadowMaps(Camera *camera, View *view, Frustum *frustum, Level *level);
	void bindShadowMap(int map) {glBindTexture(GL_TEXTURE_2D,shadowMaps[map]->getTexture());}
	void sendToShader(GLSLProgram *program, View *viewport);
};

#endif