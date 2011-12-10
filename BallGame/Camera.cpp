#include "Camera.h"

#include <math.h>

#define PI (3.141592653589793)

Camera::Camera()
{
	hAngle=-PI/4.0;
    vAngle=PI/4.0;
	distance=2.5f;
	expectedDistance=2.5f;
    lookAt[0]=0.0f;lookAt[1]=0.0f;lookAt[2]=0.0f;
	updateFromDistance();
	oldX=-1;oldY=-1;
	rotSpeed=1;
}

void Camera::zoom(float amt){
	distance-=0.1*amt;
	if (distance<0.1)
		distance=0.1;
	
	updateFromDistance();
}

void Camera::updateFromDistance()
{
	if (distance > expectedDistance) {
		distance = expectedDistance;
	}

	eyePos[0]=lookAt[0]+distance*cos(hAngle)*abs(cos(vAngle));
	eyePos[1]=lookAt[1]+distance*sin(vAngle);
	eyePos[2]=lookAt[2]-distance*sin(hAngle)*abs(cos(vAngle));
	up[0]=cos(hAngle)*cos(vAngle+PI/2);
	up[1]=sin(vAngle+PI/2);
	up[2]=-sin(hAngle)*cos(vAngle+PI/2);
	ArgoVector3 vLook(lookAt[0]-eyePos[0],lookAt[1]-eyePos[1],lookAt[2]-eyePos[2]);
	ArgoVector3 vUp(up[0],up[1],up[2]);
	ArgoVector3 vRight = vLook.cross(vUp);
	vRight.normalize();
	right[0]=vRight[0];
	right[1]=vRight[1];
	right[2]=vRight[2];
}

void Camera::mouseRotate(int newX,int newY){
	if (oldX==-1){
		oldX=newX;oldY=newY;return;
	}

	int dx=(newX-oldX);
	int dy=(newY-oldY);

	hAngle-=(float)dx*rotSpeed*0.005f;
	vAngle+=(float)dy*rotSpeed*0.005f;


	if (vAngle>0.999*PI/2.0)
        vAngle=0.999f*PI/2.0;
    if (vAngle<-0.999*PI/2.0)
        vAngle=-0.999f*PI/2.0;

	updateFromDistance();

	oldX=newX;oldY=newY;
}

void Camera::move(bool wsad[4],float speed)
{
	if (wsad[0])
		moveForward(speed*0.1);
	if (wsad[1])
		movebackward(speed*0.1);
	if (wsad[2])
		moveLeft(speed*0.1);
	if (wsad[3])
		moveRight(speed*0.1);
}

void Camera::moveForward(float speed)
{
	eyePos[0]-=cos(hAngle)*speed;
	eyePos[2]+=sin(hAngle)*speed;
	lookAt[0]-=cos(hAngle)*speed;
	lookAt[2]+=sin(hAngle)*speed;
}

void Camera::movebackward(float speed)
{
	eyePos[0]+=cos(hAngle)*speed;
	eyePos[2]-=sin(hAngle)*speed;
	lookAt[0]+=cos(hAngle)*speed;
	lookAt[2]-=sin(hAngle)*speed;
}

void Camera::moveLeft(float speed)
{
	eyePos[2]+=cos(hAngle)*speed;
	eyePos[0]+=sin(hAngle)*speed;
	lookAt[2]+=cos(hAngle)*speed;
	lookAt[0]+=sin(hAngle)*speed;
}

void Camera::moveRight(float speed)
{
	eyePos[2]-=cos(hAngle)*speed;
	eyePos[0]-=sin(hAngle)*speed;
	lookAt[2]-=cos(hAngle)*speed;
	lookAt[0]-=sin(hAngle)*speed;
}

void Camera::moveUp(float speed)
{
	eyePos[1]+=1/speed;
	lookAt[1]+=1/speed;
}

void Camera::moveDown(float speed)
{
	eyePos[1]-=1/speed;
	lookAt[1]-=1/speed;
}

void Camera::update(float fps) 
{
	if (distance < expectedDistance) {
		distance += 5.0/fps;
	}
	if (distance > expectedDistance) {
		distance = expectedDistance;
	}
}