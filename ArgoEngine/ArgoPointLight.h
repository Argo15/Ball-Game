#ifndef ARGOPOINTLIGHT_H
#define ARGOPOINTLIGHT_H

#include <QtOpenGL>
#include "ArgoLight.h"
#include "ArgoMatrix.h"
#include "ArgoMaterialManager.h"
#include "ArgoPointShadowMap.h"
#include "GLSLProgram.h"

class ArgoPointShadowMap;

class ArgoPointLight : public ArgoLight
{
private:
	float attenuation;
	float radius;
	ArgoPointShadowMap *shadowMap;

public:
	ArgoPointLight(QString *name);
	~ArgoPointLight(){}

	void sendToShader(GLSLProgram *glslProgram);
	void setPosition(float x, float y, float z);
	ArgoVector3 getPosition() {return ArgoVector3(translations[0],translations[1],translations[2]);}

	void setAttenuation(float atten) {attenuation=atten;}
	float getAttenuation() {return attenuation;}

	void setRadius(float rad) {radius=rad;}
	float getRadius() {return radius;}

	void buildShadowMaps(ArgoFrustum *frustum);
	void sendShadowsToShader(GLSLProgram *program);

	virtual void updateDockedWidget();
};

#endif