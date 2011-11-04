#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "ArgoMatrix.h"
#include "GLSLProgram.h"
#include "PointShadowMap.h"
#include "Level.h"

class Level;

class PointShadowMap;

class PointLight
{
private:
	float color[3];
	float ambient;
	float diffuse;
	float specular;

	bool enabled;

	float translations[3];

	float attenuation;
	float radius;
	PointShadowMap *shadowMap;

public:
	PointLight();
	~PointLight(){}

	void sendToShader(GLSLProgram *glslProgram);

	void setAmbient(float amt) {ambient=amt;}
	void setDiffuse(float amt) {diffuse=amt;}
	void setSpecular(float amt) {specular=amt;}
	float getDiffuse() {return diffuse;}
	float getAmbient() {return ambient;}
	float getSpecular() {return specular;}

	void setColor(float r, float g, float b);
	float *getColor() {return color;}

	bool isenabled() {return enabled;}
	void setEnabled(bool enabled) {this->enabled=enabled;}

	void setPosition(float x, float y, float z);
	ArgoVector3 getPosition() {return ArgoVector3(translations[0],translations[1],translations[2]);}

	void setAttenuation(float atten) {attenuation=atten;}
	float getAttenuation() {return attenuation;}

	void setRadius(float rad) {radius=rad;}
	float getRadius() {return radius;}

	void buildShadowMaps(Frustum *frustum, Level *level, bool drawAll);
	void sendShadowsToShader(GLSLProgram *program);
};

#endif