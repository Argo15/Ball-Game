#ifndef ARGODIReCTLIGHT_H
#define ARGODIReCTLIGHT_H

#include "ArgoLight.h"
#include <QtOpenGL>
#include "ArgoMatrix.h"

class ArgoDirectLight : public ArgoLight
{
private:
	float direction[4];

public:
	ArgoDirectLight(QString *name);
	~ArgoDirectLight(){}

	void sendToShader(GLSLProgram *glslProgram);
	void setDirection(float x, float y, float z);
	ArgoVector3 getDirection();
	ArgoVector3 getUp();
	ArgoVector3 getRight();

	virtual void updateDockedWidget();
};

#endif