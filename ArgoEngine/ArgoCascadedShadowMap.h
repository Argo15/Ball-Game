#ifndef ARGOCASCASEDSHADOWMAP_H
#define ARGOCASCADEDSHADOWMAP_H

#include "ArgoDepthFBO.h"
#include "ArgoFrustum.h"
#include "ArgoObject.h"
#include "ArgoModelManager.h"
#include "ArgoSceneManager.h"

class ArgoCascadedShadowMap {
private:
	ArgoDepthFBO *shadowMaps[4];
	ArgoMatrix4 lightMatrix[4];
	float slices[3];
	int size;

	ArgoCamera *createLightCamera(float slice1, float slice2, ArgoCamera *camera, ArgoView *view);
	ArgoView *createLightView(float slice1, float slice2, ArgoCamera *camera, ArgoCamera *lightCamera, ArgoView *view, ArgoFrustum *frustum);
	void drawObjects(ArgoFrustum *frustum);

public:
	ArgoCascadedShadowMap() {ArgoCascadedShadowMap(1024);}
	ArgoCascadedShadowMap(int size, float slice1 = 0.15, float slice2 = 0.3, float slice3 = 0.6);
	~ArgoCascadedShadowMap() {}

	void buildShadowMaps(ArgoCamera *camera, ArgoView *view, ArgoFrustum *frustum);
	void bindShadowMap(int map) {glBindTexture(GL_TEXTURE_2D,shadowMaps[map]->getTexture());}
	void sendToShader(GLSLProgram *program, ArgoView *viewport);
};

#endif