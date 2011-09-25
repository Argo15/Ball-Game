#ifndef DRAGPOINT_H
#define DRAGPOINT_H

#include "ArgoMatrix.h"

static ArgoVector3 getDragPoint(ArgoVector3 *dragLine, ArgoVector3 *unProjLine)
{
	ArgoVector3 P0(dragLine[0]);
	ArgoVector3 Vp(dragLine[1]);
	ArgoVector3 Q0(unProjLine[0]);
	ArgoVector3 Vq(unProjLine[1]);
	float a;
	float b[2];
	float c[2];
	float s;

	Vp.normalize();
	Vq.normalize();

	a=1.0/(1.0-(Vp.dot(Vq)*Vp.dot(Vq)));

	b[0]=a;
	b[1]=Vp.dot(Vq)*a;

	c[0]=ArgoVector3(Q0-P0).dot(Vp);
	c[1]=ArgoVector3(P0-Q0).dot(Vq);

	s=b[0]*c[0]+b[1]*c[1];

	ArgoVector3 dragPoint(P0+Vp*s);

	return dragPoint;
}

#endif