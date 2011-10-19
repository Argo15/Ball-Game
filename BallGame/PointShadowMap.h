#ifndef POINTSHADOWMAP_H
#define POINTSHADOWMAP_H

#include "ArgoMatrix.h"
#include "CubeShadowBuffer.h"
#include "Camera.h"
#include "View.h"
#include "Frustum.h"
#include "Level.h"

class Level;

class PointShadowMap 
{
private:
	CubeShadowBuffer *cubeShadowMap; 
	int resolution;

	void drawObjects(Frustum *frustum, Frustum *mainFrustum, Level *level);

public:
	PointShadowMap(int resolution);
	~PointShadowMap() {}

	void generateShadowMap(ArgoVector3 center, float radius, Frustum *mainFrustum, Level *level);
	GLuint getShadowMap() {return cubeShadowMap->getCubeMap();}
};

#endif