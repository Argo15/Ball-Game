#include "PointShadowMap.h"

PointShadowMap::PointShadowMap(int resolution) 
{
	this->resolution=resolution;
	cubeShadowMap = new CubeShadowBuffer(resolution);
}

void PointShadowMap::generateShadowMap(ArgoVector3 center, float radius, Frustum *mainFrustum, Level *level)
{
	View *view = new View();
	Camera *camera = new Camera();
	Frustum *frustum = new Frustum();

	view->set3D(90,1.0,0.01,radius);
	camera->setPosition(center[0],center[1],center[2]);
	ArgoVector3 cameraLook[] = {
		ArgoVector3(1.0,0.0,0.0),
		ArgoVector3(-1.0,0.0,0.0),
		ArgoVector3(0.0,1.0,0.0),
		ArgoVector3(0.0,-1.0,0.0),
		ArgoVector3(0.0,0.0,1.0),
		ArgoVector3(0.0,0.0,-1.0),
	};
	ArgoVector3 cameraUp[] = {
		ArgoVector3(0.0,-1.0,0.0),
		ArgoVector3(0.0,-1.0,0.0),
		ArgoVector3(0.0,0.0,1.0),
		ArgoVector3(0.0,0.0,-1.0),
		ArgoVector3(0.0,-1.0,0.0),
		ArgoVector3(0.0,-1.0,0.0),
	};
	ArgoVector3 cameraRight[] = {
		ArgoVector3(0.0,0.0,-1.0),
		ArgoVector3(0.0,0.0,1.0),
		ArgoVector3(1.0,0.0,0.0),
		ArgoVector3(1.0,0.0,0.0),
		ArgoVector3(1.0,0.0,0.0),
		ArgoVector3(-1.0,0.0,0.0),
	};
	for (int i=0; i<6; i++) {
		cubeShadowMap->bind();
		camera->setLookAt(center[0]+cameraLook[i][0],center[1]+cameraLook[i][1],center[2]+cameraLook[i][2]);
		camera->setUp(cameraUp[i][0],cameraUp[i][1],cameraUp[i][2]);
		camera->setRight(cameraRight[i][0],cameraRight[i][1],cameraRight[i][2]);
		frustum->getFrustum(camera,view);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
			glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT+i);
			glClearDepth(1.0f);
			glClearColor(1.0,1.0,1.0,1.0);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glPushAttrib( GL_VIEWPORT_BIT );
			glViewport( 0, 0, resolution, resolution);
			view->use3D(true);
			camera->transform();
			cubeShadowMap->getCubeProgram()->sendUniform("lightPos",center[0],center[1],center[2]);
			cubeShadowMap->getCubeProgram()->sendUniform("radius",radius);
			drawObjects(frustum,mainFrustum,level);
			glPopAttrib();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		cubeShadowMap->unbind();
	}
	glClearColor(0.0,0.0,0.0,1.0);

	delete view;
	delete camera;
	delete frustum;
}

void PointShadowMap::drawObjects(Frustum *frustum, Frustum *mainFrustum, Level *level)
{
	level->drawPointShadows(frustum);
}