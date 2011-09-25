#ifndef ARGOCAMeRA_H
#define ARGOCAMeRA_H

#include <QGLWidget>
#include "ArgoMatrix.h"

class ArgoCamera{
private:
	float eyePos[3];
	float lookAt[3];
	float up[3];
	float right[3];
	float distance;
	float hAngle;
	float vAngle;

	int oldX, oldY;
	float rotSpeed;

public:
	ArgoCamera();
	~ArgoCamera(){}

	void setPosition(float x, float y, float z) {eyePos[0]=x;eyePos[1]=y;eyePos[2]=z;}
	void setLookAt(float x, float y, float z) {lookAt[0]=x;lookAt[1]=y;lookAt[2]=z;}
	void setUp(float x, float y, float z) {up[0]=x;up[1]=y;up[2]=z;}
	void setRight(float x, float y, float z) {right[0]=x;right[1]=y;right[2]=z;}
	void setRotSpeed(float speed) {rotSpeed=speed;}
	void setDistance(float dist) {distance = dist;}
	void zoom(float amt);
	void transform() {gluLookAt(eyePos[0],eyePos[1],eyePos[2],lookAt[0],lookAt[1],lookAt[2],up[0],up[1],up[2]);}

	float geteyeX() {return eyePos[0];}
	float geteyeY() {return eyePos[1];}
	float geteyeZ() {return eyePos[2];}
	float *getEye() {float *peye = eyePos; return peye;}

	ArgoVector3 geteyeV() {return ArgoVector3(eyePos[0],eyePos[1],eyePos[2]);}
	ArgoVector3 getLookAt() {return ArgoVector3(lookAt[0],lookAt[1],lookAt[2]);}
	ArgoVector3 getUp() {return ArgoVector3(up[0],up[1],up[2]);}
	ArgoVector3 getRight() {return ArgoVector3(right[0],right[1],right[2]);}


	void mouseRotate(int newX, int newY);
	void noRotate(){oldX=-1;oldY=-1;}

	void move(bool wsad[4],float speed);
	void moveForward(float speed);
	void movebackward(float speed);
	void moveLeft(float speed);
	void moveRight(float speed);
	void moveUp(float speed);
	void moveDown(float speed);

	void updateFromDistance();
};

#endif