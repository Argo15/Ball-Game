#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "Camera.h"
#include "View.h"
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

class Frustum{
private:
	FrustumPlane plane[6];
	float Hnear;
	float Wnear;
	float Hfar;
	float Wfar;
	ArgoVector3 ftl,ftr,fbl,fbr;

public:
	Frustum();
	~Frustum() {}

	void getFrustum(Camera *camera, View *view);
	void getOrthoFrustum(Camera *camera, View *view);
	void calcFarPlane(Camera *camera, View *view);
	bool isInFrustum(ArgoVector3 center, float radius);

	float getHNear() {return Hnear;}
	float getWNear() {return Wnear;}
	float getHFar() {return Hfar;}
	float getWFar() {return Wfar;}
};

#endif