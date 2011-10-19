#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include "ArgoMatrix.h"
#include "ModelRegistry.h"
#include "btBulletDynamicsCommon.h"
using namespace std;

class Object {
protected:
	string model;
	string material;

	float translations[3];
	ArgoQuaternion rotation;
	float scale[3];

	btRigidBody* body;

public:
	Object() {}
	~Object(){}

	void setModel(string model) {this->model = model;}
	string getModel() {return model;}
	void setMaterial(string material) {this->material = material;}
	string getMaterial() {return material;}


	void Translate(float x, float y, float z) {translations[0]+=x;translations[1]+=y;translations[2]+=z;}
	void Rotate(ArgoQuaternion quat) {rotation=quat*rotation;}
	void Scale(float x, float y, float z) {scale[0]+=x;scale[1]+=y;scale[2]+=z;}

	void setTranslate(float x, float y, float z) {translations[0]=x;translations[1]=y;translations[2]=z;}
	void setRotate(ArgoQuaternion quat) {rotation = quat;}
	void setScale(float x, float y, float z) {scale[0]=x;scale[1]=y;scale[2]=z;}
	
	float *getTranslate() {float *pTranslate; pTranslate=translations; return pTranslate;}
	ArgoQuaternion getRotate() {return rotation;}
	float *getScale() {float *pScale; pScale=scale; return pScale;}
	ArgoVector3 getTranslateV() {return ArgoVector3(translations[0],translations[1],translations[2]);}

	float getScaledRadius(ModelRegistry *models);

	btRigidBody* getRigidBody() {return body;}
	void setRigidBody(btRigidBody* newBody) {body = newBody;}

	void transform();
	void transformToCurrentMatrix();
};

#endif