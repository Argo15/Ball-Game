#ifndef ARGOACTOR_H
#define ARGOACTOR_H

#include <math.h>
#include "ArgoModel.h"
#include "ArgoMatrix.h"
#include "ArgoModelManager.h"
#include "DockedActorEditor.h"

class ArgoActor {
private:
	QString *name;

	QString *model;
	QString *material;

protected:
	float translations[3];
	ArgoQuaternion rotation;
	float scale[3];
	
public:
	ArgoActor(QString *name = new QString("newActor"), QString *model = 0, QString *material = 0);
	~ArgoActor(){}

	void setModel(QString *model) {this->model = model;}
	QString *getModel() {return model;}
	void setMaterial(QString *material) {this->material = material;}
	QString *getMaterial() {return material;}

	void setName(QString newName) {*name=newName;}
	void setName(QString *newName) {name=newName;}
	QString *getName() {return name;}

	void Translate(float x, float y, float z) {translations[0]+=x;translations[1]+=y;translations[2]+=z; actorModified();}
	void Rotate(ArgoQuaternion quat) {rotation=quat*rotation; actorModified();}
	void Scale(float x, float y, float z) {scale[0]+=x;scale[1]+=y;scale[2]+=z; actorModified();}
	void setTranslate(float x, float y, float z) {translations[0]=x;translations[1]=y;translations[2]=z;}
	void setRotate(ArgoQuaternion quat) {rotation = quat; actorModified();}
	void setScale(float x, float y, float z) {scale[0]=x;scale[1]=y;scale[2]=z;}
	float *getTranslate() {float *pTranslate; pTranslate=translations; return pTranslate;}
	ArgoQuaternion getRotate() {return rotation;}
	float *getScale() {float *pScale; pScale=scale; return pScale;}
	ArgoVector3 getTranslateV() {return ArgoVector3(translations[0],translations[1],translations[2]);}

	float getScaledRadius();

	void transform();
	void transformToCurrentMatrix();
	void actorModified();

	virtual void updateDockedWidget();
};

#endif