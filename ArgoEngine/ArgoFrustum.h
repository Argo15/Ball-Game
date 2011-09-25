#ifndef ARGOFRUSTUM_H
#define ARGOFRUSTUM_H

#include "GLSLProgram.h"
#include "ArgoCamera.h"
#include "ArgoView.h"
#include "ArgoMatrix.h"

#define F_NEAR	0
#define F_FAR	1
#define F_LEFT	2
#define F_RIGHT	3
#define F_UP	4
#define F_DOWN	5

struct FrustumPlane{
	ArgoVector3 point;
	ArgoVector3 normal;
	float d;

	float distance(ArgoVector3 *p){
		return (*p).dot(normal)-d;
	}
};

class ArgoFrustum{
private:
	FrustumPlane plane[6];
	float Hnear;
	float Wnear;
	float Hfar;
	float Wfar;
	ArgoVector3 ftl,ftr,fbl,fbr;

public:
	ArgoFrustum();
	~ArgoFrustum() {}

	void getFrustum(ArgoCamera *camera, ArgoView *view);
	void getOrthoFrustum(ArgoCamera *camera, ArgoView *view);
	void calcFarPlane(ArgoCamera *camera, ArgoView *view);
	void bindFarPlane(GLSLProgram *program);
	bool isInFrustum(ArgoVector3 center, float radius);

	float getHNear() {return Hnear;}
	float getWNear() {return Wnear;}
	float getHFar() {return Hfar;}
	float getWFar() {return Wfar;}
};

#endif