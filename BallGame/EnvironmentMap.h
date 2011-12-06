#ifndef ENVIRONMENTMAP_H
#define ENVIRONMENTMAP_H

#include "ArgoMatrix.h"
#include "CubeMapBuffer.h"
#include "Camera.h"
#include "View.h"
#include "Frustum.h"
#include "Level.h"

class Level;

class EnvironmentMap 
{
private:
	CubeMapBuffer *cubeMap; 
	int resolution;

	void drawObjects(Frustum *frustum, Camera *camera, Level *level);

public:
	EnvironmentMap(int resolution);
	~EnvironmentMap() {}

	void generateEnvironmentMap(ArgoVector3 center, float radius, Level *level);
	GLuint getEnvironmentMap() {return cubeMap->getCubeMap();}
};

#endif