#ifndef ARGOMATERIAL_H
#define ARGOMATERIAL_H

#include <QGLWidget>
#include <QtGui>
#include "GLSLProgram.h"
#include "ArgoTextureManager.h"

class ArgoMaterial
{
private:
	float color[3];
	float emission[3];
	float specular;
	int shininess;

	float texOffset[2];
	float texScale[2];
	float texRotate;

	QString *name;
	QString *textureName;
	QString *normalName;

	bool normalEnabled;
public:
	ArgoMaterial(QString *newName);
	ArgoMaterial(ArgoMaterial *copyMaterial) {*this=*copyMaterial;}
	~ArgoMaterial(){}

	void use(GLSLProgram *program = 0);

	void setColor(float r, float g, float b) {color[0]=r;color[1]=g;color[2]=b;}
	void setEmission(float r, float g, float b) {emission[0]=r;emission[1]=g;emission[2]=b;}
	void setSpecular(float i) {specular=i;}
	void setShine(int shine) {shininess=shine;}
	void setTexOffset(float x, float y) {texOffset[0]=x; texOffset[1]=y;}
	void setUTexOffset(float value) {texOffset[0]=value;}
	void setVTexOffset(float value) {texOffset[1]=value;}
	void setTexScale(float x, float y) {texScale[0]=x; texScale[1]=y;}
	void setUTexScale(float value) {texScale[0]=value;}
	void setVTexScale(float value) {texScale[1]=value;}
	void setTexRotate(float rotate) {texRotate=rotate;}

	float *getColor() {return color;}
	float *getEmission() {return emission;}
	float getSpecular() {return specular;}
	int getShine() {return shininess;}
	float *getTexOffset() {return texOffset;}
	float *getTexScale() {return texScale;}
	float getTexRotate() {return texRotate;}

	void setName(QString newName) {*name=newName;}
	void setName(QString *newName) {name=newName;}
	QString *getName() {return name;}

	void setTexture(QString *newTextureName) {textureName=newTextureName;}
	QString *getTexture() {return textureName;}
	void setNormal(QString *newNormalName) {normalName=newNormalName;}
	QString *getNormal() {return normalName;}

	void enableNormal(bool enabled) {normalEnabled=enabled;}
	bool normalsEnabled() {return normalEnabled;}
};

#endif