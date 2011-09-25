#ifndef TRANSFORMANGLE_H
#define TRANSFORMANGLE_H

#include <math.h>
#include "ArgoMatrix.h"

#define PI 3.14159265

static float getRotAngle(ArgoVector3 *unProjLine, ArgoVector3 *normal, ArgoVector3 *tangent)
{
	float t;

	t = -(normal->dot(unProjLine[0]))/normal->dot(unProjLine[1]);

	ArgoVector3 intersectPoint = unProjLine[0]+unProjLine[1]*t;
	intersectPoint.normalize();
	tangent->normalize();

	float angle = acos(intersectPoint.dot(*tangent));

	ArgoVector3 cross = intersectPoint.cross(*tangent);
	cross.normalize();
	normal->normalize();
	if (cross.dot(*normal)>0.01)
		angle*=-1;

	return angle+PI/2;
}

#endif