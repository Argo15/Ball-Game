#include "EnvironmentMap.h"

EnvironmentMap::EnvironmentMap(int resolution) 
{
	this->resolution=resolution;
	cubeMap = new CubeMapBuffer(resolution);
}

void EnvironmentMap::generateEnvironmentMap(ArgoVector3 center, float radius, Level *level)
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
		cubeMap->bind();
		camera->setLookAt(center[0]+cameraLook[i][0],center[1]+cameraLook[i][1],center[2]+cameraLook[i][2]);
		camera->setUp(cameraUp[i][0],cameraUp[i][1],cameraUp[i][2]);
		camera->setRight(cameraRight[i][0],cameraRight[i][1],cameraRight[i][2]);
		frustum->getFrustum(camera,view);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
			glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT+i);
			glClearDepth(1.0f);
			glClearColor(0.0,0.0,0.0,0.0);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glPushAttrib( GL_VIEWPORT_BIT );
			glViewport( 0, 0, resolution, resolution);
			view->use3D(true);
			camera->transform();
			drawObjects(frustum,camera,level);
			glPopAttrib();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
	}
	delete view;
	delete camera;
	delete frustum;
}

void EnvironmentMap::drawObjects(Frustum *frustum, Camera *camera, Level *level)
{
	level->getDirectLight()->sendToShader(0);
	PointLight **lights = new PointLight*[4];
	int lightCount = level->getBestPointLights(lights,frustum,camera,4);
	for (int i=0; i<lightCount; i++) {
		glEnable(GL_LIGHT1+i);
		lights[i]->sendToShader(0,GL_LIGHT1+i);
	}
	glDisable(GL_COLOR_MATERIAL);
	level->drawNoBall(frustum);
}