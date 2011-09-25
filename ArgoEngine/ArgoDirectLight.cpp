#include "ArgoDirectLight.h"

ArgoDirectLight::ArgoDirectLight(QString *name)
{
	color[0]=1.0; color[1]=1.0; color[2]=1.0;
	ambient=0.5;
	diffuse=0.5;
	specular=1.0;
	direction[0]=0;direction[1]=-1.0;direction[2]=0.0;direction[3]=0.0;
	ArgoQuaternion quat;
	quat.createQuaternion(-30,1.0,1.0,-1.0);
	this->Rotate(quat);
	enabled=true;
	this->setName(name);
}

void ArgoDirectLight::setDirection(float x, float y, float z)
{
	direction[0]=x;
	direction[1]=y;
	direction[2]=z;
}

void ArgoDirectLight::sendToShader(GLSLProgram *glslProgram)
{
	if (glslProgram != 0)
		glslProgram->sendUniform("lightenabled",isenabled());
	ArgoQuaternion rotate = this->getRotate();
	float amb[] = {ambient*color[0],ambient*color[1],ambient*color[2]};
	float dif[] = {diffuse*color[0],diffuse*color[1],diffuse*color[2]};
	float spc[] = {specular*color[0],specular*color[1],specular*color[2]};
	glPushMatrix();
		rotate.getMatrix().multiplyToCurrent();
		if (glslProgram == 0) {
			float dir[] = {-direction[0],-direction[1],-direction[2],0};
			float ambi[] = {amb[0]-0.2,amb[1]-0.2,amb[2]-0.2,0};
			glLightfv(GL_LIGHT0,GL_POSITION,dir);
			glLightfv(GL_LIGHT0,GL_AMBIENT,ambi);
		} else {
			glLightfv(GL_LIGHT0,GL_POSITION,direction);
			glLightfv(GL_LIGHT0,GL_AMBIENT,amb);
		}
		glLightfv(GL_LIGHT0,GL_DIFFUSE,dif);
		glLightfv(GL_LIGHT0,GL_SPECULAR,spc);
	glPopMatrix();
}

ArgoVector3 ArgoDirectLight::getDirection()
{
	ArgoVector4 dir(direction[0],direction[1],direction[2],direction[3]);
	ArgoMatrix4 rot = this->getRotate().getMatrix();
	ArgoVector4 final = rot*dir;
	return ArgoVector3(final);
}

ArgoVector3 ArgoDirectLight::getUp()
{
	ArgoVector4 dir(1.0,0,0,0);
	ArgoMatrix4 rot = this->getRotate().getMatrix();
	ArgoVector4 final = rot*dir;
	return ArgoVector3(final);
}

ArgoVector3 ArgoDirectLight::getRight()
{
	ArgoVector4 dir(0,0,1.0,0);
	ArgoMatrix4 rot = this->getRotate().getMatrix();
	ArgoVector4 final = rot*dir;
	return ArgoVector3(final);
}

void ArgoDirectLight::updateDockedWidget()
{
	ArgoLight::updateDockedWidget();
}