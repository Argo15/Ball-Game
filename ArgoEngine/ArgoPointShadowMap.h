#ifndef ARGOPOINTSHADOWMAP_H
#define ARGOPOINTSHADOWMAP_H

#include <QtOpenGL>
#include "ArgoMatrix.h"
#include "ArgoCubeShadowFBO.h"
#include "ArgoSceneManager.h"
#include "ArgoCamera.h"
#include "ArgoView.h"
#include "ArgoFrustum.h"

class ArgoPointShadowMap 
{
private:
	ArgoCubeShadowFBO *cubeShadowMap; 
	int resolution;

	void drawObjects(ArgoFrustum *frustum, ArgoFrustum *mainFrustum);

public:
	ArgoPointShadowMap(int resolution);
	~ArgoPointShadowMap() {}

	void generateShadowMap(ArgoVector3 center, float radius, ArgoFrustum *mainFrustum);
	GLuint getShadowMap() {return cubeShadowMap->getCubeMap();}
};

#endif