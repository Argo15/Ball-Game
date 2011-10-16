#ifndef DIRECTLIGHT_H
#define DIRECTLIGHT_H

#include "ArgoMatrix.h"
#include "GLSLProgram.h"

class DirectLight
{
private:
	float color[3];
	float ambient;
	float diffuse;
	float specular;

	bool enabled;

	float direction[4];

	ArgoQuaternion rotation;

public:
	DirectLight();
	~DirectLight(){}

	void sendToShader(GLSLProgram *glslProgram);
	void setDirection(float x, float y, float z);
	ArgoVector3 getDirection();
	ArgoVector3 getUp();
	ArgoVector3 getRight();

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

	void Rotate(ArgoQuaternion quat) {rotation=quat*rotation;}
	void setRotate(ArgoQuaternion quat) {rotation = quat;}
	ArgoQuaternion getRotate() {return rotation;}
};

#endif