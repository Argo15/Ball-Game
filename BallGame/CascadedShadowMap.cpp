#include "CascadedShadowMap.h"

#define ANG2RAD 3.14159265358979323846/180.0

CascadedShadowMap::CascadedShadowMap(int size, float slice1, float slice2, float slice3)
{
	for (int i=0;i<4;i++) {
		shadowMaps[i] = new DepthBuffer(size,size);
	}
	slices[0] = slice1;
	slices[1] = slice2;
	slices[2] = slice3;

	this->size = size;
}

void CascadedShadowMap::buildShadowMaps(Camera *camera, View *view, Frustum *frustum, Level *level)
{
	float slice[] = {0.0, slices[0], slices[1], slices[2], 1.0};

	for (int i=0; i<4; i++) {
		Camera *lightCamera = createLightCamera(slice[i],slice[i+1],camera,view,level->getDirectLight());
		View *lightView = createLightView(slice[i],slice[i+1],camera,lightCamera,view,frustum);
		Frustum *lightFrustum = new Frustum();
		lightFrustum->getOrthoFrustum(lightCamera,lightView);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
			shadowMaps[i]->bind();
			glClearDepth(1.0);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_DEPTH_BUFFER_BIT);
			glPushAttrib( GL_VIEWPORT_BIT );
			glViewport( 0, 0, size, size);
			lightView->use3D(false);
			lightCamera->transform();
			lightMatrix[i].setAsModelViewProjection();
			level->drawNoShaders(lightFrustum);
			glPopAttrib();
			shadowMaps[i]->unbind();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		delete lightCamera;
		delete lightView;
		delete lightFrustum;
	}
	
}

Camera *CascadedShadowMap::createLightCamera(float slice1, float slice2, Camera *camera, View *view, DirectLight *dLight)
{
	ArgoVector3 lightLookAt = dLight->getDirection();
	ArgoVector3 lightRight = dLight->getRight();
	ArgoVector3 lightUp = dLight->getUp();
	float viewDepth = view->getNear()+(view->getFar()-view->getNear())*(slice2+slice1)/2.0;
	ArgoVector3 cameraDir = camera->getLookAt()-camera->geteyeV();
	cameraDir.normalize();
	ArgoVector3 lightLookPoint = camera->geteyeV()+cameraDir*viewDepth;
	ArgoVector3 lightPos = lightLookPoint-lightLookAt*50.0;
	Camera *lightCamera = new Camera();
	lightCamera->setPosition(lightPos[0],lightPos[1],lightPos[2]);
	lightCamera->setLookAt(lightLookPoint[0],lightLookPoint[1],lightLookPoint[2]);
	lightCamera->setUp(lightUp[0],lightUp[1],lightUp[2]);
	lightCamera->setRight(lightRight[0],lightRight[1],lightRight[2]);
	return lightCamera;
}

View *CascadedShadowMap::createLightView(float slice1, float slice2, Camera *camera, Camera *lightCamera, View *view, Frustum *frustum)
{
	ArgoVector3 ntl,ntr,nbl,nbr,ftl,ftr,fbl,fbr,nc,fc,X,Y,Z;

	float nearDepth = view->getNear()+(view->getFar()-view->getNear())*slice1;
	float farDepth = view->getNear()+(view->getFar()-view->getNear())*slice2;

	float nh = (frustum->getHNear()+(frustum->getHFar()-frustum->getHNear())*slice1)/2.0;
	float nw = (frustum->getWNear()+(frustum->getWFar()-frustum->getWNear())*slice1)/2.0; 
	float fh = (frustum->getHNear()+(frustum->getHFar()-frustum->getHNear())*slice2)/2.0;
	float fw = (frustum->getWNear()+(frustum->getWFar()-frustum->getWNear())*slice2)/2.0;

	X = camera->getRight();
	X.normalize();
	Y = camera->getUp();
	Y.normalize();
	Z = camera->getLookAt()-camera->geteyeV();
	Z.normalize();

	nc = camera->geteyeV()+Z*nearDepth;
	fc = camera->geteyeV()+Z*farDepth;

	ntl = nc + Y * nh - X * nw;
	ntr = nc + Y * nh + X * nw;
	nbl = nc - Y * nh - X * nw;
	nbr = nc - Y * nh + X * nw;
	ftl = fc + Y * fh - X * fw;
	ftr = fc + Y * fh + X * fw;
	fbl = fc - Y * fh - X * fw;
	fbr = fc - Y * fh + X * fw;

	// set up the light matrix with a -1 -> 1 size projection
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		lightCamera->transform();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		glOrtho(-1,1,-1,1,0,1);

	// calculate the actual bounds for the ortho projection
	ArgoMatrix4 lightMVP;
	lightMVP.setAsModelViewProjection();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	float left, right, up, down, back;

	ArgoVector4 corners[] = {ArgoVector4(ntl), ArgoVector4(ntr), ArgoVector4(nbl), ArgoVector4(nbr),
							ArgoVector4(ftl), ArgoVector4(ftr), ArgoVector4(fbl), ArgoVector4(fbr)};

	// get the projected positions of the corners
	for (int i=0; i<8; i++){
		corners[i]=lightMVP*corners[i];
	}


	left  = corners[0][0];
	right = corners[0][0];
	up    = corners[0][1];
	down  = corners[0][1];
	back  = corners[0][2];

	// determine the bounds
	for (int i=1; i<8; i++){
		if (corners[i][0]<left)
			left=corners[i][0];
		if (corners[i][0]>right)
			right=corners[i][0];
		if (corners[i][1]<down)
			down=corners[i][1];
		if (corners[i][1]>up)
			up=corners[i][1];
		if (corners[i][2]>back)
			back=corners[i][2];
	}

	View *lightView = new View();
	lightView->set2D(left,right,down,up,0.1,100);
	return lightView;
}

void CascadedShadowMap::sendToShader(GLSLProgram *glslProgram, View *viewport)
{
	glPushMatrix();
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D,shadowMaps[0]->getTexture());
		glslProgram->sendUniform("shadowMap[0]",4);
		glActiveTexture(GL_TEXTURE5);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,shadowMaps[1]->getTexture());
		glslProgram->sendUniform("shadowMap[1]",5);
		glActiveTexture(GL_TEXTURE6);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,shadowMaps[2]->getTexture());
		glslProgram->sendUniform("shadowMap[2]",6);
		glActiveTexture(GL_TEXTURE7);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,shadowMaps[3]->getTexture());
		glslProgram->sendUniform("shadowMap[3]",7);

		glslProgram->sendUniform("slices[0]",slices[0]);
		glslProgram->sendUniform("slices[1]",slices[1]);
		glslProgram->sendUniform("slices[2]",slices[2]);


		glMatrixMode(GL_TEXTURE);
		glActiveTextureARB(GL_TEXTURE3);
		glLoadIdentity();
		glTranslated(0.5, 0.5, 0.5); // we have to clamp values in the [0.0, 1.0] range, not [-1.0, 1.0]
		glScaled(0.5, 0.5, 0.5);
		lightMatrix[0].multiplyToCurrent();

		glActiveTextureARB(GL_TEXTURE4);
		glLoadIdentity();
		glTranslated(0.5, 0.5, 0.5); // we have to clamp values in the [0.0, 1.0] range, not [-1.0, 1.0]
		glScaled(0.5, 0.5, 0.5);
		lightMatrix[1].multiplyToCurrent();

		glActiveTextureARB(GL_TEXTURE5);
		glLoadIdentity();
		glTranslated(0.5, 0.5, 0.5); // we have to clamp values in the [0.0, 1.0] range, not [-1.0, 1.0]
		glScaled(0.5, 0.5, 0.5);
		lightMatrix[2].multiplyToCurrent();

		glActiveTextureARB(GL_TEXTURE6);
		glLoadIdentity();
		glTranslated(0.5, 0.5, 0.5); // we have to clamp values in the [0.0, 1.0] range, not [-1.0, 1.0]
		glScaled(0.5, 0.5, 0.5);
		lightMatrix[3].multiplyToCurrent();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}