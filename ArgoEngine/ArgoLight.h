#ifndef ARGOLIGHT_H
#define ARGOLIGHT_H

#include "ArgoActor.h"
#include "GLSLProgram.h"
#include "ArgoMaterialManager.h"

class ArgoLight : public ArgoActor
{
protected:
	float color[3];
	float ambient;
	float diffuse;
	float specular;

	bool enabled;
public:
	ArgoLight(){}
	~ArgoLight(){}

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

	virtual void sendToShader(GLSLProgram *glslProgram) = 0;

	virtual void updateDockedWidget();
};

#endif