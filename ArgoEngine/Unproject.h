#ifndef UNPROJECT_H
#define UNPROJECT_H

#include <QtOpenGL>
#include "ArgoMatrix.h"

static ArgoVector3 getUnproject(double depth,int mouseX, int mouseY){
	ArgoVector3 finalPos;
	GLdouble result[3];
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	
	glGetIntegerv(GL_VIEWPORT,viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);

	gluUnProject((GLdouble)mouseX,(GLdouble)(viewport[3]-mouseY),(GLdouble)depth,
					mvmatrix,projmatrix,viewport,
					&result[0],&result[1],&result[2]);
	finalPos[0]=result[0];
	finalPos[1]=result[1];
	finalPos[2]=result[2];
	return finalPos;
}

#endif